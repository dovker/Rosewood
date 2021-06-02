# Rosewood
Rosewood Game Engine

**Rosewood Engine** is a game engine created for learning purposes and GameJam games. The base I had no idea how it worked was based on [The Cherno's Game Engine series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) although at this stage the engine is very different.

# Plan
My plan for this engine is to develop it to a point I can make an advanced 2D game and a simple 3D game with it, whilst learning Game Engine development, Design patterns, graphics programming, Advanced c++, problem solving.

# Features
* OpenGL Support
* Cross-Platform (Tested on major desktop platforms)
* 2D Rendering (Line Rendering to come in the future)
* Simple Asset manager and library
* Audio (SoLoud) support
* Spritefont support
* ECS
* Virtual File System

# Currently working on
* Yaml Serialization
* Lua Scripting

# Goals / To-do
* Networking
* LUA Scripting
* Scene Serialization
* Asset Importing (Tool Later)
* Level editor
* 3D Rendering
* Asset Compression
* Project Exporting
* Scripted UI
* Text rendering
* Particle effects
* Support Vulkan and Metal
* Physics support
* Multi-threading

# Building
## Windows:

  Double click **"premake5.bat"** file and VS2019 project files will be generated
  
  If you wish to create project files for another IDE, change `vs2019` with whatever you choose in **"premake5.bat"** file.
  
## MacOS:

  Open **Terminal** and type `cd <Enter the solution direction>`
  Proceed by entering this command:
  `./premake5.sh [build system (gmake by default)]`
  Your makefiles should now be generated!
  Then you can build and run the project with this command:
  `./build.sh [project name to launch]`

## Linux coming soon


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
* [zlib](https://zlib.net) Will be utilized later
* [LUA](http://www.lua.org/home.html)
* [Entt](https://github.com/skypjack/entt)
* [yaml-cpp](https://github.com/jbeder/yaml-cpp)
