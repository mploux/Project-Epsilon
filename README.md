# Project Epsilon - A simple c++ game engine
![Project Epsilon in engine screen](http://i.imgur.com/VKT7fYM.jpg)

Project Epsilon is a prototype c++ game engine currently in development. It currently builds on Linux and macOS, the Windows version will come later with cmake.

## Goals
The main goal of the project is to create a simple c++ game engine that uses both OpenGL and Vulkan with Bullet Physics and the Autodesk FBX SDK. The engine currently runs on OpenGL with libLZ.

 - **✔ Physically Based Rendering**
 - Post processing effects
 - Bullet physics implementation
 - Autodesk FBX SDK implementation
 - Animation support

## Dependencies
Project Epsilon uses a number of projects to work:
* [GLFW](https://github.com/glfw/glfw) - A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input
* [GLEW](http://glew.sourceforge.net/) - The OpenGL Extension Wrangler Library
* [libLZ]() - An OpenGL utility for windows, inputs, textures, meshes and more

Everything is provided in the deps folder.

## Building
Building the project is relativelly easy and uses a single **Makefile** for both Linux an macOS:
```sh
$ cd Project-Epsilon
$ make
```
In the future, the Makefile will be replaced with cmake. The windows version will be available along it.

## Licence
Project Epsilon is fully open source and licensed under the [GNU 3.0 License](http://www.gnu.org/licenses/) and available in source code form at [GitHub](https://github.com/TeamUbercube/ubercube).
