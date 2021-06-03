project "Glad"
	kind "StaticLib"
	language "C"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "action:xcode4"
		sysincludedirs
		{
			"${PROJECT_DIR}/include"
		}
	
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "system:macosx"
		staticruntime "On"
        
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"

