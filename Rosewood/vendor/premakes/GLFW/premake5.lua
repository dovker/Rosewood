project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",
		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"src/x11_init.c",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_time.c",
			"src/posix_thread.c",
			"src/glx_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c",
			"src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:macosx"
      	system "macosx"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"src/cocoa_platform.h",
			"src/cocoa_joystick.h",
			"src/posix_thread.h",
			"src/nsgl_context.h",
			"src/egl_context.h",
			"src/osmesa_context.h",
			"src/cocoa_init.m",
			"src/cocoa_joystick.m",
			"src/cocoa_monitor.m",
			"src/cocoa_window.m",
			"src/cocoa_time.c",
			"src/posix_thread.c",
			"src/nsgl_context.m",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_COCOA"
		}


	filter "system:linux"
			systemversion "latest"
			staticruntime "On"

			files
			{
				"src/x11_platform.h",
				"src/xkb_unicode.h",
				"src/posix_time.h",
				"src/posix_thread.h",
				"src/glx_context.h",
				"src/egl_context.h",
				"src/osmesa_context.h",
				"src/x11_init.c",
				"src/x11_monitor.c",
				"src/x11_window.c",
				"src/xkb_unicode.c",
				"src/posix_time.c",
				"src/posix_thread.c",
				"src/glx_context.c",
				"src/egl_context.c",
				"src/osmesa_context.c"
			}

			defines
			{
				"_GLFW_X11"
			}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
