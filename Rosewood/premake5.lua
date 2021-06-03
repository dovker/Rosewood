project "Rosewood"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
    cppdialect "C++17"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rwpch.h"
    pchsource "src/rwpch.cpp"

    files
    {
        "src/**.cpp",
        "src/**.h",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
        "vendor/lua/**.cpp",
        "vendor/lua/**.h",

    }
    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.SoLoud}",
        "%{IncludeDir.zlib}",
        "%{IncludeDir.lua}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}"
    }
    filter "action:xcode4"
        pchheader "src/rwpch.h"
        pchsource "src/rwpch.cpp"

        xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
        sysincludedirs
        {
            "src",
            "vendor/spdlog/include",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.stb_image}",
            "%{IncludeDir.assimp}",
            "%{IncludeDir.SoLoud}",
            "%{IncludeDir.zlib}",
            "%{IncludeDir.lua}",
            "%{IncludeDir.entt}",
            "%{IncludeDir.yaml_cpp}"
        }
    filter {}
    
    filter "system:macosx"
        links
        {
            "Cocoa.framework",
            "IOKit.framework",
            "QuartzCore.framework",
            "AudioToolbox.framework",
            "AudioUnit.framework",
            "CoreAudio.framework",
            "CoreFoundation.framework"
        }
    filter {}
    
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "SoloudStatic",
        "assimp",
        "zlib",
        "lua",
        "yaml-cpp",
        "opengl32.lib"
    }
    defines
    {
        "_CRT_SCURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }
    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"


    filter "configurations:Debug"
        defines "RW_DEBUG"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines "RW_RELEASE"
        runtime "Release"
        optimize "On"
    filter "configurations:Dist"
        defines "RW_DIST"
        runtime "Release"
        optimize "On"