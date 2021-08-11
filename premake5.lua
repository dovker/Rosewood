workspace "Rosewood"
    architecture "x86_64"

    --disablewarnings { "switch" }
    --disablewarnings { "#warnings" }

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    flags
	{
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    require "/vendor/cmake"
    require "/vendor/export-compile-commands"

    IncludeDir = {}

    IncludeDir["assimp"]=       "%{wks.location}/Rosewood/vendor/assimp/include"
    IncludeDir["GLFW"] =        "%{wks.location}/Rosewood/vendor/glfw/include"  
    IncludeDir["spdlog"] =      "%{wks.location}/Rosewood/vendor/spdlog/include"
    IncludeDir["Glad"] =        "%{wks.location}/Rosewood/vendor/Glad/include"  
    IncludeDir["ImGui"] =       "%{wks.location}/Rosewood/vendor/imgui"         
    IncludeDir["glm"] =         "%{wks.location}/Rosewood/vendor/glm"           
    IncludeDir["stb_image"] =   "%{wks.location}/Rosewood/vendor/stb_image/include"     
    IncludeDir["SoLoud"] =      "%{wks.location}/Rosewood/vendor/soloud/include"
    IncludeDir["zlib"] =        "%{wks.location}/Rosewood/vendor/zlib"      
    IncludeDir["libzip"] =      "%{wks.location}/Rosewood/vendor/libzip"
    IncludeDir["entt"] =        "%{wks.location}/Rosewood/vendor/entt/include"          
    IncludeDir["lua"] =         "%{wks.location}/Rosewood/vendor/lua/src"          
    IncludeDir["sol"] =         "%{wks.location}/Rosewood/vendor/sol"          
    IncludeDir["asio"] =        "%{wks.location}/Rosewood/vendor/asio/include"          
    IncludeDir["yaml_cpp"] =    "%{wks.location}/Rosewood/vendor/yaml-cpp/include"
    IncludeDir["json"] =        "%{wks.location}/Rosewood/vendor/json/include"
    IncludeDir["openssl"] =     "%{wks.location}/Rosewood/vendor/openssl/include"



    group "Dependencies"
        include "Rosewood/vendor/glfw"
        include "Rosewood/vendor/soloud/build"
        include "Rosewood/vendor/Glad"
        include "Rosewood/vendor/imgui"
        include "Rosewood/vendor/assimp"
        include "Rosewood/vendor/zlib"
        include "Rosewood/vendor/libzip"
        include "Rosewood/vendor/lua"
        include "Rosewood/vendor/yaml-cpp"
    group ""

    include "Rosewood"
    --include "Sandbox2D"
    --include "Sandbox3D"
    include "TestGame"
    include "Game/Server"