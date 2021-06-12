project "libzip"
	language    "C"
	kind        "StaticLib"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	includedirs "include"
	defines     { "N_FSEEKO" }
	warnings    "off"


	files
	{
		"**.h",
		"**.c"
	}

	filter "system:linux or bsd or solaris or haiku"
		defines { "HAVE_SSIZE_T_LIBZIP", "HAVE_CONFIG_H" }
	filter{}

	filter "system:windows"
		defines { "_WINDOWS" }
	filter {}

	filter "action:vs*"
		includedirs {"vs"}
	filter{}

	filter { "system:windows", "toolset:mingw" }
		defines { "HAVE_SSIZE_T_LIBZIP" }
	filter{}

	filter "system:macosx"
		defines { "HAVE_SSIZE_T_LIBZIP" }
	filter{}
