  
project "zlib"
	language    "C"
	kind        "StaticLib"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	defines     { "N_FSEEKO" }
	warnings    "off"

	

	filter "system:windows"
		defines { "_WINDOWS", "WIN32" }

	filter "system:not windows"
		defines { 'HAVE_UNISTD_H', "unix" }

		
	files
	{
		"*.h",
		"*.c"
	}

