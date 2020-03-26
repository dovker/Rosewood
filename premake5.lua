workspace "Rosewood"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Rosewood"
    location "Rosewood"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "RW_PLATFORM_WINDOWS",
            "RW_BUILD_DLL"
        }

        postbuildcommands
        {
            {"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
        }

    filter "configurations.Debug"
        defines "RW_DEBUG"
        symbols "On"

    filter "configurations.Release"
        defines "RW_RELEASE"
        optimize "On"

    filter "configurations.Dist"
        defines "RW_DIST"
        optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"

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
            "Rosewood/src"
        }

        links
        {
            "Rosewood"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"
    
            defines
            {
                "RW_PLATFORM_WINDOWS"
            }
    
        filter "configurations.Debug"
            defines "RW_DEBUG"
            symbols "On"
    
        filter "configurations.Release"
            defines "RW_RELEASE"
            optimize "On"
    
        filter "configurations.Dist"
            defines "RW_DIST"
            optimize "On"
