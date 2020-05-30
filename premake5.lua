workspace "Rosewood"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

IncludeDir["GLFW"] = "Rosewood/Vendor/GLFW/include"
IncludeDir["Glad"] = "Rosewood/Vendor/Glad/include"
IncludeDir["ImGui"] = "Rosewood/Vendor/imgui"
IncludeDir["glm"] = "Rosewood/Vendor/glm"
IncludeDir["stb_image"] = "Rosewood/Vendor/stb_image"

include "Rosewood/vendor/GLFW"
include "Rosewood/vendor/Glad"
include "Rosewood/vendor/imgui"

project "Rosewood"
    location "Rosewood"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rwpch.h"
    pchsource "Rosewood/src/rwpch.cpp"

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "Rosewood/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    defines
    {
        "_CRT_SCURE_NO_WARNINGS"
    }

    filter "system:windows"
        
        systemversion "latest"

        defines
        {
            "RW_PLATFORM_WINDOWS",
            "RW_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations.Debug"
        defines "RW_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations.Release"
        defines "RW_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations.Dist"
        defines "RW_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox2D"
        location "Sandbox2D"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "On"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
        files
        {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.hpp",
            "%{prj.name}/src/**.c",
        }
    
        includedirs
        {
            "Rosewood/vendor/spdlog/include",
            "Rosewood/src",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.glm}"
        }

        links
        {
            "Rosewood",
            "Glad"
        }

        filter "system:windows"
            
            systemversion "latest"
    
            defines
            {
                "RW_PLATFORM_WINDOWS"
            }
    
        filter "configurations.Debug"
            defines "RW_DEBUG"
            buildoptions "/MDd"
            symbols "On"
    
        filter "configurations.Release"
            defines "RW_RELEASE"
            buildoptions "/MD"
            optimize "On"
    
        filter "configurations.Dist"
            defines "RW_DIST"
            buildoptions "/MD"
            optimize "On"
            project "Sandbox"
            location "Sandbox"
            kind "ConsoleApp"
            language "C++"
            cppdialect "C++17"
            staticruntime "On"
    
            targetdir ("bin/" .. outputdir .. "/%{prj.name}")
            objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        
            files
            {
                "%{prj.name}/src/**.cpp",
                "%{prj.name}/src/**.h",
                "%{prj.name}/src/**.hpp",
                "%{prj.name}/src/**.c",
            }
        
            includedirs
            {
                "Rosewood/vendor/spdlog/include",
                "Rosewood/src",
                "%{IncludeDir.Glad}",
                "%{IncludeDir.ImGui}",
                "%{IncludeDir.glm}"
            }
    
            links
            {
                "Rosewood",
                "Glad"
            }
    
            filter "system:windows"
                
                systemversion "latest"
        
                defines
                {
                    "RW_PLATFORM_WINDOWS"
                }
        
            filter "configurations.Debug"
                defines "RW_DEBUG"
                buildoptions "/MDd"
                symbols "On"
        
            filter "configurations.Release"
                defines "RW_RELEASE"
                buildoptions "/MD"
                optimize "On"
        
            filter "configurations.Dist"
                defines "RW_DIST"
                buildoptions "/MD"
                optimize "On"