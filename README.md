# Rosewood
Rosewood Game Engine

**Rosewood Engine** is a game engine created for learning purposes. The core and ECS of the engine are based of [The Cherno's Game Engine series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) although is highly customized to my own interests, needs.

# Plan
My plan for this engine is to develop it to a point I can make an advanced 2D game and a simple 3D game with it, whilst learning Game Engine development, Design patterns, graphics programming, Advanced c++, problem solving.

# Features
* OpenGL Support
* Cross-Platform (Tested on major desktop platforms)
* *Fast* Sprite / Quad Batcher
* Simple Asset manager and library
* Event system
* Audio (SoLoud) support
* Spritefont support
* 2D Rendering
* Assimp 3D Model loading
* entt ECS

# Currently working on
* LUA Scriptin
* Better ECS support

# Goals / To-do
* LUA Scripting
* Virtual File system
* Scene Serialization
* Level editor
* 3D Rendering
* Compression
* Project Exporting
* Scripted UI
* Text rendering
* Particle effects
* Support Vulkan and Metal
* Physics support
* Multi-threading
* Networking

# Building
## Windows:

  Double click **"premake5.bat"** file and VS2019 project files will be generated
  
  If you wish to create project files for another IDE, change `vs2019` with whatever you choose in **"premake5.bat"** file.
  
## MacOS:

  Open **Terminal** and type `cd <Enter the solution direction>`
  Proceed by entering this command:
  `vendor/bin/premake/premake5 xcode4`
  Your project files should now be generated!
  Once again, you are free to change `xcode4` with whatever you please!

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
* More to be written later
