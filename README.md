# Rosewood
Rosewood Game Engine

**Rosewood Engine** is a game engine created for learning purposes. The base of the engine loosely is based of [The Cherno's Game Engine series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) although is highly customized to my own interests, needs.

# Plan
My plan for this engine is to develop it to a point I can make an advanced 2D game and a simple 3D game with it, whilst learning Game Engine development, Design patterns, graphics programming, Advanced c++, problem solving.

# Features
* OpenGL Support
* Graphics API abstractions
* Cross-Platform (Tested on major desktop platforms)
* *Fast* Sprite / Quad Batcher
* Simple Asset / content manager and library
* Event system
* Audio (SoLoud) support
* Spritefont support
* 2D Light Pre-pass renderer with HDR support

# Goals / To-do
* Serialization
* Text rendering
* Particle effects
* Primitive rendering (~~Circle~~, Triangle, ~~Quad~~, Line, Function / curve)
* Implement ECS
* Support DX11, Vulkan and Metal
* Asset importer tool
* Level editor / IDE
* Shader cross-compilation
* Deferred Renderer (~~2D~~, 3D)
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
