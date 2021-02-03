workspace "Rosewood"
    architecture "x86_64"
    startproject "Sandbox3D"

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

    IncludeDir = {}

    IncludeDir["assimp"]="Rosewood/vendor/assimp/include"
    IncludeDir["GLFW"] = "Rosewood/vendor/GLFW/include"
    IncludeDir["spdlog"] = "Rosewood/vendor/spdlog/include"
    IncludeDir["Glad"] = "Rosewood/vendor/Glad/include"
    IncludeDir["ImGui"] = "Rosewood/vendor/imgui"
    IncludeDir["glm"] = "Rosewood/vendor/glm"
    IncludeDir["stb_image"] = "Rosewood/vendor/stb_image"
    IncludeDir["SoLoud"] = "Rosewood/vendor/soloud/include"
    IncludeDir["zlib"] = "Rosewood/vendor/zlib"



    group "Dependencies"
        include "Rosewood/vendor/GLFW"
        include "Rosewood/vendor/soloud/build"
        include "Rosewood/vendor/Glad"
        include "Rosewood/vendor/imgui"
        include "Rosewood/vendor/assimp"
        include "Rosewood/vendor/zlib"
    group ""

    


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
            xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
            sysincludedirs
            {
                "%{prj.name}/src",
                "%{prj.name}/vendor/spdlog/include",
                "%{IncludeDir.GLFW}",
                "%{IncludeDir.Glad}",
                "%{IncludeDir.ImGui}",
                "%{IncludeDir.glm}",
                "%{IncludeDir.stb_image}",
                "%{IncludeDir.assimp}",
                "%{IncludeDir.SoLoud}",
                "%{IncludeDir.zlib}"

            }
            
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
            "%{IncludeDir.assimp}",
            "%{IncludeDir.SoLoud}",
            "%{IncludeDir.zlib}"
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
            "assimp",
            "zlib",
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

    project "TestGame"
        location "TestGame"
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
            "%{IncludeDir.glm}",
            "%{IncludeDir.SoLoud}",
            "%{IncludeDir.assimp}",
            "%{IncludeDir.zlib}"
        }

        links
        {
            "Rosewood"
        }
        

        filter "action:xcode4"
            xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
            sysincludedirs
            {
                "Rosewood/src",
                    "Rosewood/vendor/spdlog/include",
                    "Rosewood/vendor/Glad/include",
                    "Rosewood/vendor/imgui",
                    "Rosewood/vendor/glm",
                    "Rosewood/vendor/soloud",
                    "%{IncludeDir.assimp}",
                    "%{IncludeDir.zlib}"
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
                "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}" --For some fucking reason folder copying is different on different platforms... FOR FUCKS SAKE
            }
        
        filter "system:windows"
            
            systemversion "latest"
        
            defines
            {
                "RW_PLATFORM_WINDOWS"
            }
            postbuildcommands 
            {
                "{COPY} Content %{cfg.targetdir}/Content",
                "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}/EngineContent"
            }
        filter "system:linux"
            
            systemversion "latest"
        
            defines
            {
                "RW_PLATFORM_LINUX"
            }
            postbuildcommands 
            {
                "{COPY} Content %{cfg.targetdir}",
                "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}"
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

    project "Sandbox3D"
            location "Sandbox3D"
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
                "%{IncludeDir.glm}",
                "%{IncludeDir.assimp}",
                "%{IncludeDir.SoLoud}",
                "%{IncludeDir.zlib}"
            }
    
            links
            {
                "Rosewood"
            }
            
    
            filter "action:xcode4"
                xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
                sysincludedirs
                {
                    "Rosewood/src",
                        "Rosewood/vendor/spdlog/include",
                        "Rosewood/vendor/Glad/include",
                        "Rosewood/vendor/imgui",
                        "Rosewood/vendor/glm",
                        "%{IncludeDir.assimp}",
                        "Rosewood/vendor/soloud",
                        "%{IncludeDir.zlib}"
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
                    "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}" --For some fucking reason folder copying is different on different platforms... FOR FUCKS SAKE
                }
            
            filter "system:windows"
                
                systemversion "latest"
            
                defines
                {
                    "RW_PLATFORM_WINDOWS"
                }
                postbuildcommands 
                {
                    "{COPY} Content %{cfg.targetdir}/Content",
                    "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}/EngineContent"
                }
            filter "system:linux"
                
                systemversion "latest"
            
                defines
                {
                    "RW_PLATFORM_LINUX"
                }
                postbuildcommands 
                {
                    "{COPY} Content %{cfg.targetdir}",
                    "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}"
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
            "%{IncludeDir.glm}",
            "%{IncludeDir.assimp}",
            "%{IncludeDir.SoLoud}",
            "%{IncludeDir.zlib}"
        }

        links
        {
            "Rosewood"
        }
        

        filter "action:xcode4"
            xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
            sysincludedirs
            {
                "Rosewood/src",
                    "Rosewood/vendor/spdlog/include",
                    "Rosewood/vendor/Glad/include",
                    "Rosewood/vendor/imgui",
                    "Rosewood/vendor/glm",
                    "%{IncludeDir.assimp}",
                    "Rosewood/vendor/soloud",
                    "%{IncludeDir.zlib}"
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
                "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}" --For some fucking reason folder copying is different on different platforms... FOR FUCKS SAKE
            }
        
        filter "system:windows"
            
            systemversion "latest"
        
            defines
            {
                "RW_PLATFORM_WINDOWS"
            }
            postbuildcommands 
            {
                "{COPY} Content %{cfg.targetdir}/Content",
                "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}/EngineContent"
            }
        filter "system:linux"
            
            systemversion "latest"
        
            defines
            {
                "RW_PLATFORM_LINUX"
            }
            postbuildcommands 
            {
                "{COPY} Content %{cfg.targetdir}",
                "{COPY} ../Rosewood/EngineContent %{cfg.targetdir}"
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