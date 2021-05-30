project "Sandbox2D"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "src/**.cpp",
        "src/**.h",
        "src/**.hpp",
        "src/**.c",
    }
    
    includedirs
    {
        "%{wks.location}/Rosewood/vendor/spdlog/include",
        "%{wks.location}/Rosewood/src",
        "%{wks.location}/Rosewood/vendor",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.SoLoud}",
        "%{IncludeDir.lua}",

    }
    links
    {
        "Rosewood",
        "GLFW",
        "Glad",
        "ImGui",
        "SoloudStatic",
        "assimp",
        "zlib",
        "lua"
    }
    
    filter "action:xcode4"
        xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
        sysincludedirs
        {
            "%{wks.location}/Rosewood/vendor/spdlog/include",
            "%{wks.location}/Rosewood/src",
            "%{wks.location}/Rosewood/vendor",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.entt}",
            "%{IncludeDir.assimp}",
            "%{IncludeDir.SoLoud}",
            "%{IncludeDir.lua}",

        }
    
    
    filter "system:macosx"
        systemversion "latest"
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
        postbuildcommands 
        {
            "{COPY} Content %{cfg.targetdir}",
            "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}" --For some fucking reason folder copying is different on different platforms... FOR FUCKS SAKE
        }
    
    filter "system:windows"
        
        systemversion "latest"
    
        postbuildcommands 
        {
            "{COPY} Content %{cfg.targetdir}/Content",
            "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}/EngineContent"
        }
    filter "system:linux"
        
        systemversion "latest"
        postbuildcommands 
        {
            "{COPY} Content %{cfg.targetdir}",
            "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}"
        }
--["RW_WORKSPACE_DIR=%{wks.location}"]
    
    filter "configurations.Debug"
        defines "RW_DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations.Release"
        defines "RW_RELEASE"
        runtime "Release"            
        optimize "On"
    
    filter "configurations.Dist"
        defines "RW_DIST"
        runtime "Release"
        optimize "On"