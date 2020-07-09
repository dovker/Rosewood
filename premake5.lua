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

IncludeDir["GLFW"] = "Rosewood/vendor/GLFW/include"
IncludeDir["spdlog"] = "Rosewood/vendor/spdlog/include"
IncludeDir["Glad"] = "Rosewood/vendor/Glad/include"
IncludeDir["ImGui"] = "Rosewood/vendor/imgui"
IncludeDir["glm"] = "Rosewood/vendor/glm"
IncludeDir["stb_image"] = "Rosewood/vendor/stb_image"
IncludeDir["SoLoud"] = "Rosewood/vendor/soloud/include"


group "Dependencies"
    include "Rosewood/vendor/GLFW"
    include "Rosewood/vendor/soloud/build"
    include "Rosewood/vendor/Glad"
    include "Rosewood/vendor/imgui"
group ""

xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }


project "Rosewood"
    location "Rosewood"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    filter "action:vs2019"
        pchheader "rwpch.h"
        pchsource "Rosewood/src/rwpch.cpp"

    filter "action:vs2017"
        pchheader "rwpch.h"
        pchsource "Rosewood/src/rwpch.cpp"

    filter "action:xcode4"
        pchheader "src/rwpch.h"
        pchsource "Rosewood/src/rwpch.cpp"

    filter "action:gmake"
        pchheader "../src/rwpch.h"
        pchsource "Rosewood/src/rwpch.cpp"


    filter {}

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
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.SoLoud}"
    }
    
    filter "action:xcode4"
		sysincludedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{prj.name}/vendor/GLFW/include",
			"%{prj.name}/vendor/Glad/include",
            "%{prj.name}/vendor/imgui",
            "%{prj.name}/vendor/glm",
            "%{prj.name}/vendor/stb_image",
            "%{prj.name}/vendor/soloud"
		}

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
            "GLFW_INCLUDE_NONE"
        }

    filter "system:linux"
        
        systemversion "latest"

        defines
        {
            "RW_PLATFORM_LINUX",
            "GLFW_INCLUDE_NONE"
        }
    filter "system:macosx"
        
        systemversion "latest"

        defines
        {
            "RW_PLATFORM_MACOS",
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
    staticruntime "Off"

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
    filter "action:xcode4"
		sysincludedirs
		{
			"Rosewood/src",
            "Rosewood/vendor/spdlog/include",
            "Rosewood/vendor/Glad/include",
            "Rosewood/vendor/imgui",
            "Rosewood/vendor/glm"
		}

    links
    {
        "Rosewood"
    }
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
    
    postbuildcommands 
        {
            "{COPY} Content %{cfg.targetdir}",
            "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}"

        }
    filter "system:windows"
        
        systemversion "latest"
    
        defines
        {
            "RW_PLATFORM_WINDOWS"
        }
    filter "system:linux"
        
        systemversion "latest"
    
        defines
        {
            "RW_PLATFORM_LINUX"
        }
    filter "system:macosx"
            
        systemversion "latest"

        defines
        {
            "RW_PLATFORM_MACOS"
        }
--["RW_WORKSPACE_DIR=%{wks.location}"]
    
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
