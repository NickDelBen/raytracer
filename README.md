# Raytracer

This is my implementation of a [raytracer](https://en.wikipedia.org/wiki/Ray_tracing_(graphics), "Raytracer Information").

Requirements:
    Requires [opengl](https://www.opengl.org/wiki/Getting_Started, "Getting started with opengl")

###Example Usage
```
$  ./bin/raytrace <world_file>
```

When making ensure that you have the correct binaries linked for opengl.
This can be achieved by commenting out the FB line in the makefile, and adding you own opengl FB linker flags.