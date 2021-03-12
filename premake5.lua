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

    IncludeDir = {}

    IncludeDir["assimp"]=       "%{wks.location}/Rosewood/vendor/assimp/include"
    IncludeDir["GLFW"] =        "%{wks.location}/Rosewood/vendor/GLFW/include"  
    IncludeDir["spdlog"] =      "%{wks.location}/Rosewood/vendor/spdlog/include"
    IncludeDir["Glad"] =        "%{wks.location}/Rosewood/vendor/Glad/include"  
    IncludeDir["ImGui"] =       "%{wks.location}/Rosewood/vendor/imgui"         
    IncludeDir["glm"] =         "%{wks.location}/Rosewood/vendor/glm"           
    IncludeDir["stb_image"] =   "%{wks.location}/Rosewood/vendor/stb_image/include"     
    IncludeDir["SoLoud"] =      "%{wks.location}/Rosewood/vendor/soloud/include"
    IncludeDir["zlib"] =        "%{wks.location}/Rosewood/vendor/zlib"      
    IncludeDir["entt"] =        "%{wks.location}/Rosewood/vendor/entt/include"          
    



    group "Dependencies"
        include "Rosewood/vendor/GLFW"
        include "Rosewood/vendor/soloud/build"
        include "Rosewood/vendor/Glad"
        include "Rosewood/vendor/imgui"
        include "Rosewood/vendor/assimp"
        include "Rosewood/vendor/zlib"
    group ""

    include "Rosewood"
    include "Sandbox2D"
    include "Sandbox3D"
    include "TestGame"
    --include "RayTracing"