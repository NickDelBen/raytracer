
#Name of broject
project=raytrace

# Compiler to use
cc=g++
# Location to store object files
DO=obj
# Directory for main binaries
DB=bin
# Directory where source files are
DS=src
# Directory where docs are stored
DD=doc

# Compiler flags to use for debugging
FD=-Wall -g
# Compiler flags to use for object files
FO=-c -Wno-deprecated
# Compiler Flags to use for binaries
FB=-framework Carbon -framework OpenGL -framework GLUT
#FB=-lglut32cu -lglu32 -lopengl32
#FB=-lGL -lGLU -lglut

################################################
# Build Commands
################################################

all: prep $(project)

# Remove any previously built files
clean:
	# Remove any objects from the object directory
	rm -rf $(DO)

# Removes any files other thatn the source from the directory
purge: clean
	#Remove any binaries from the output directory
	rm -rf $(DB)
	#Remove the source tarball if it exists
	rm -rf $(project).tar.gz
	#Remove the documentation files
	rm -rf $(DD)

# Create the directory structure required for output
prep:
	# Create the objects directory
	mkdir -p $(DO)
	# Create output directory
	mkdir -p $(DB)

# Create the documentation for the project
documentation:
	#Generating documentaton
	doxygen Doxyfile

# Tar the project to make it easier to move around
tarball:
	# Creating tarball
	tar -zcv -f $(project).tar.gz {m,M}akefile src README{.src,,.txt,.md} {D,d}oxyfile


################################################
# Executable Binaries
################################################

#Build project executable
$(project): prep driver.o canvas.o vector.o line.o plane.o sphere.o triangle.o color.o light.o material.o world.o camera.o raytracer.o util.o
	# Building and linking the project binary
	$(cc) -o $(DB)/$@ $(addprefix $(DO)/, $(filter-out prep, $^)) $(FB)

################################################
# Object Files
################################################

driver.o: $(DS)/driver.cpp
	# Compiling driver object
	$(cc) $(FO) -o $(DO)/$@ $^

canvas.o: $(DS)/canvas.cpp
	# Compiling canvas object
	$(cc) $(FO) -o $(DO)/$@ $^

vector.o: $(DS)/vector.cpp
	# Compiling vector object
	$(cc) $(FO) -o $(DO)/$@ $^

line.o: $(DS)/line.cpp
	# Compiling line object
	$(cc) $(FO) -o $(DO)/$@ $^

plane.o: $(DS)/plane.cpp
	# Compiling plane object
	$(cc) $(FO) -o $(DO)/$@ $^

sphere.o: $(DS)/sphere.cpp
	# Compiling sphere object
	$(cc) $(FO) -o $(DO)/$@ $^

triangle.o: $(DS)/triangle.cpp
	# Compiling triangle object
	$(cc) $(FO) -o $(DO)/$@ $^

color.o: $(DS)/color.cpp
	# Compiling color object
	$(cc) $(FO) -o $(DO)/$@ $^

light.o: $(DS)/light.cpp
	# Compiling light object
	$(cc) $(FO) -o $(DO)/$@ $^

material.o: $(DS)/material.cpp
	# Compiling material object
	$(cc) $(FO) -o $(DO)/$@ $^

world.o: $(DS)/world.cpp
	# Compiling world object
	$(cc) $(FO) -o $(DO)/$@ $^

camera.o: $(DS)/camera.cpp
	# Compiling camera object
	$(cc) $(FO) -o $(DO)/$@ $^

raytracer.o: $(DS)/raytracer.cpp
	# Compiling raytracer object
	$(cc) $(FO) -o $(DO)/$@ $^

util.o: $(DS)/util.c
	# Compiling utility object
	$(cc) $(FO) -o $(DO)/$@ $^
