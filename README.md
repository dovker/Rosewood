# Rosewood
Rosewood Game Engine

**Rosewood Engine** is a game engine created for learning purposes and GameJam games. The game engine started of following [The Cherno's Game Engine series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) although has vastly moved on from it.

# Plan
My plan for this engine is to develop it to a point I can make an advanced 2D game and a simple 3D game with it, whilst learning Game Engine development, Design patterns, graphics programming, Advanced c++, problem solving.

# Features
* OpenGL Support
* Cross-Platform (Tested on major desktop platforms)
* 2D Rendering (Line Rendering to come in the future)
* Asset Manager and loader with zip archive support
* Audio (SoLoud) support
* Spritefont support
* ECS
* Virtual File System
* File Compression
* Lua Scripting

# Currently working on
* Scene Serialization
* Observers

# Goals / To-do
* Networking
* Binary Serialization
* Level editor
* 3D Rendering
* Scripted UI
* Text rendering
* Particle effects
* Support Vulkan and Metal
* Physics support
* Multi-threading

# Building
## All Platforms
  If you try to make project and it fails, make sure every dependency has it's premake5.lua file, if not, you can find those files in **"Rosewood/vendor/premakes"** folder.
## Windows:

  Double click **"premake5.bat"** file and VS2019 project files will be generated
  
  If you wish to create project files for another IDE, change `vs2019` with whatever you choose in **"premake5.bat"** file.
  
## MacOS:
  1. Download Premake5 binaries for Mac OS and paste them in vendor/bin/premake folder.
  2. Open **Terminal** and type `cd <Enter the solution direction>`
  3. Proceed by entering this command:
  `./premake5.sh [build system (gmake by default)]`
  
  Your makefiles should now be generated!
  4. Then you can build and run the project with this command:
  `./build.sh [project name to launch]`

## Linux:
  1. Download Premake5 binaries for Linux and paste them in vendor/bin/premake folder.
  2. REQUIRED PACKAGES:
    ** `xorg-dev`
    ** `libasound2-dev`
  3. Open **Terminal** and type `cd <Enter the solution direction>`
  4. Proceed by entering this command:
  `./premake5.sh [build system (gmake by default)]`
  
  Your makefiles should now be generated!
  5. Then you can build and run the project with this command:
  `./build-linux.sh [project name to launch]`
### **[Trello board](https://trello.com/b/bTRVKkrL/rosewood-engine)**

# Libraries / dependencies
* [Premake5](https://github.com/premake/premake-core)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [GLFW](https://github.com/glfw/glfw)
* [glm](https://github.com/g-truc/glm)
* [Glad](https://glad.dav1d.de/)
* [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)
* [spdlog](https://github.com/gabime/spdlog)
* [SoLoud](https://github.com/jarikomppa/soloud)
* [Assimp](https://github.com/assimp/assimp)
* [zlib](https://zlib.net)
* [libzip](https://libzip.org)
* [LUA](http://www.lua.org/home.html)
* [Sol2](https://github.com/ThePhD/sol2)
* [Entt](https://github.com/skypjack/entt)
* [yaml-cpp](https://github.com/jbeder/yaml-cpp)
