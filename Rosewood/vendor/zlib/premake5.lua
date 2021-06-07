  
project "zlib"
	language    "C"
	kind        "StaticLib"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	defines     { "N_FSEEKO" }
	warnings    "off"

	

	filter "system:windows"
		defines { "_WINDOWS", "WIN32" }
		iowin32_src = "minizip/iowin32.c"
		iowin32_h = "minizip/iowin32.h"

	filter "system:not windows"
		defines { 'HAVE_UNISTD_H', "unix" }

		
	files
	{
		"*.h",
		"*.c",
		"minizip/ioapi.c",
		"minizip/mztools.c",
		"minizip/unzip.c",
		"minizip/zip.c",
		"${iowin32_src}",
		"minizip/crypt.h",
		"minizip/ioapi.h",
		"minizip/mztools.h",
		"minizip/unzip.h",
		"minizip/zip.h",
		"${iowin32_h}",
		"minizip/minizip.c",
		"minizip/miniunz.c"
	}

