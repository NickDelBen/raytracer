
#include "raytracer.hpp"

// Reads a raytracer from the specified stream
int Raytracer::readFrom(std::istream* stream)
{
    unsigned int got_cam, got_bg, got_ga;
    std::string type;
    int material_id;

    // Read file line by line
    while (*stream >> type) {
        // Check for plane
        if (type == "P") {
            *stream >> material_id;
            // Check if material exists
            if (material_id >= this->world.numMaterials()) {
                return 0;
                break;
            }
            Plane new_plane = Plane(this->world.getMaterial(material_id), stream);
            this->world.addPlane(&new_plane);
            std::cout << "Read plane with material id: " << material_id << " [" << new_plane << "]" << std::endl;
            continue;
        }
        // Check for sphere
        if (type == "S") {
            *stream >> material_id;
            // Check if material exists
            if (material_id >= this->world.numMaterials()) {
                return 0;
                break;
            }
            Sphere new_sphere = Sphere(this->world.getMaterial(material_id), stream);
            this->world.addSphere(&new_sphere);
            std::cout << "Read sphere with material id: " << material_id << " [" << new_sphere << "]" << std::endl;
            continue;
        }
        // Check for triangle
        if (type == "T") {
            *stream >> material_id;
            // Check material exists
            if (material_id >= this->world.numMaterials()) {
                return 0;
                break;
            }
            Triangle new_triangle = Triangle(this->world.getMaterial(material_id), stream);
            this->world.addTriangle(&new_triangle);
            std::cout << "Read triangle with material id: " << material_id << " [" << new_triangle << "]" << std::endl;
        }
        // Check for material
        if (type == "MAT") {
            Material new_material = Material(stream);
            this->world.addMaterial(&new_material);
            std::cout << "Read material with id " << this->world.numMaterials() - 1 << " [" << new_material << "]" << std::endl;
            continue;
        }
        // Check for light
        if (type == "LIT") {
            Light new_light = Light(stream);
            this->world.addLight(&new_light);
            std::cout << "Read light [" << new_light << "]" << std::endl;
            continue;
        }
        // Check for camera
        if (type == "CAM") {
            this->camera = Camera(stream);
            got_cam = 1;
            std::cout << "Read camera [" << this->camera << "]" << std::endl;
            continue;
        }
        // Check for background
        if (type == "BG") {
            Color background_color = Color(stream);
            this->world.setBackground(&background_color);
            got_bg = 1;
            std::cout << "Read background Color [" << background_color << "]" << std::endl;
            continue;
        }
        // Check for global ambient light
        if (type == "GA") {
            Color global_ambient = Color(stream);
            this->world.setAmbient(&global_ambient);
            got_ga = 1;
            std::cout << "Read global Ambient [" << global_ambient << "]" << std::endl;
            continue;
        }
    }
    if (! (got_cam & got_bg & got_ga)) {
        return 0;
    }
    // Create the rays to be traced
    this->createRays();
    return 1;
}

// Compleatly traces the ray at the specific pixel
Color Raytracer::getPixel(int x, int y)
{
    return this->traceRay(this->getRay(x,y), 0);
}

// Compleatly traces the specified ray
Color Raytracer::traceRay(Line* ray, int depth)
{
    float object_distance;      // Distance sphere is from initial ray
    Line light_ray;             // The resulting ray after bouncing
    Vector3 normal;             // Normal to the intersection
    Material* current_material; // Material covering to object of intersection
    Vector3 intersection;       // Point on ray intersection occurs

    // Initially assume color is background
    Color result = *(this->world.getBackground());
    // If maximum recursive depth has ben reached just return the result
    if (depth > MAXIMUM_RAYTRACE_DEPTH) {
        return result;
    }
    object_distance = MAXIMUM_DISTANCE;
    // Check to see if there is intersection with any object
    WorldObject* object_intersection = this->world.getClosestIntersect(ray, object_distance, &object_distance, &normal);
    // Check if no object was intersected with
    if (object_intersection == NULL) {
        // Return background color
        return result;
    }
    // Find the current material
    current_material = object_intersection->getMaterial();
    // Calculate the ambient color (replacing the default background color)
    result = this->calculateAmbient(current_material, this->world.getAmbient());
    // Calculate the intersection
    intersection = ray->endpoint(object_distance);
    // Check each light for shadows and stuff like that
    for (unsigned int li = 0; li < this->world.numLights(); li++) {
        // Normal for object intersection
        Light* current_light = this->world.getLight(li);    
        // Calculate the light ray towards the light from the point of incidence
        light_ray.fromPoints(&intersection, current_light->getPosition());
        // Only evaluate shading if this object is not inside a shadow
        if (! this->world.checkIntesect(&light_ray, MAXIMUM_DISTANCE, object_intersection)) {
            // Calculate diffuse lighting
            result = result + this->calculateDiffuse(&light_ray, &normal, current_light, current_material);
            // Calculate the specular light
            result = result + this->calculateSpecular(ray, &light_ray, &normal, current_light, current_material);
        }
    }
    // Calculate the reflection ray
    Line reflection_ray = this->calculareReflectionRay(ray, &intersection, &normal);
    // Recursively add the reflection
    result = result + this->traceRay(&reflection_ray, depth + 1).scaledColor(current_material->getReflectivity());
    result.setMax(255);
    return result;
}

// Calculates the reflection ray form and intersection
Line Raytracer::calculareReflectionRay(Line* initial_ray, Vector3* intersection, Vector3* intersect_normal)
{
    // Calculate reflection amount
    float reflect_amount = 2.0f * std::fabsf(intersection->dotProduct(intersect_normal));
    // Compute direction of reflected ray
    Vector3 reflection_direction = *(initial_ray->getDirection()) + intersect_normal->scale(reflect_amount * REFLECTION_BIAS);
    return Line(*intersection, reflection_direction);
}

// Calculates the ambient shading of an object
Color Raytracer::calculateAmbient(Material* material, Color* world_ambient)
{
    return material->getColor()->multiplyColor(material->getAmbient()).multiplyColor(world_ambient);
}

// Calculates the diffuse lighting of an intersection
Color Raytracer::calculateDiffuse(Line* ray, Vector3* intersection_normal, Light* light, Material* material)
{
    float diffuse;

    diffuse = std::fmax(0.0, ray->getDirection()->dotProduct(intersection_normal));
    return material->getDiffuse()->scaledColor(diffuse).multiplyColor(light->getIntensity());
}

// Calculates the specular lighting of a reflection
Color Raytracer::calculateSpecular(Line* initial_ray, Line* reflection_ray, Vector3* intersection_normal, Light* light, Material* material)
{
    float specular;

    Vector3 inverse_ray = initial_ray->getDirection()->scale(-1);
    Vector3 t1 = reflection_ray->getDirection()->scale(-1);
    Vector3 t2 = t1 + intersection_normal->scale(2 * intersection_normal->dotProduct(reflection_ray->getDirection()));
    specular = std::powf(std::fmax(0.0, inverse_ray.dotProduct(&t2)), material->getPower());
    return material->getSpecular()->scaledColor(specular).multiplyColor(light->getIntensity());
}

// Cretes the list fo rays taht are to be traced
void Raytracer::createRays()
{
    int x, y;
    // Free any rays that were prefiously created
    this->freeRays();
    // Allocate space for the rays
    this->rays = (Line* ) malloc(sizeof(Line) * this->getCamera()->planeHeight() * this->getCamera()->planeWidth());
    for (y = 0; y < this->getCamera()->planeHeight(); y++) {
        for (x = 0; x < this->getCamera()->planeWidth(); x++) {
            // Store the ray in the ray list
            this->rays[this->getCamera()->planeWidth() * y + x] = this->camera.getRay(x, y);
        }
    }
}

// Gets the world
World* Raytracer::getWorld()
{
    return &(this->world);
}

// Gets the camera
Camera* Raytracer::getCamera()
{
    return &(this->camera);
}

// Deconstructs a raytracer
Raytracer::~Raytracer()
{
    this->freeRays();
}

// Gets the specified ray
Line* Raytracer::getRay(int x, int y)
{
    return this->getRay(y * this->getCamera()->planeWidth() + x);
}

// Frees the space allocated for rays
void Raytracer::freeRays()
{
    if (this->rays != NULL) {
        free(this->rays);
        this->rays = NULL;
    }
}

// Gets the specified ray]
Line* Raytracer::getRay(int index)
{
    return &(this->rays[index]);
}
