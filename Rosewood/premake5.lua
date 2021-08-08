project "Rosewood"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
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
        "%{IncludeDir.sol}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.json}",
        "%{IncludeDir.libzip}",
        "%{IncludeDir.asio}",
        "%{IncludeDir.openssl}",
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
            "%{IncludeDir.yaml_cpp}",
            "%{IncludeDir.json}",
            "%{IncludeDir.libzip}",
            "%{IncludeDir.asio}",
            "%{IncludeDir.openssl}",
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

    libdirs { "%{wks.location}/Rosewood/vendor/openssl" }
    
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "SoloudStatic",
        "assimp",
        "zlib",
        "libzip",
        "lua",
        "yaml-cpp",
        "crypto",
        "ssl",
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

    configuration "vs*"
        buildoptions { "/Zm250", "/bigobj" } 