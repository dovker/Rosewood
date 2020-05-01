#pragma once


#ifdef RW_PLATFORM_WINDOWS

	#ifdef RW_BUILD_DLL
		#define ROSEWOOD_API _declspec(dllexport)
	#else
		#define ROSEWOOD_API _declspec(dllimport)
	#endif // RW_BUILD_DLL
#else
#define ROSEWOOD_API
#endif // RW_PLATFORM_WINDOWS

#define RW_ENABLE_ASSERTS

#ifdef RW_ENABLE_ASSERTS
#define RW_ASSERT(x, ...) { if(!(x)) { RW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define RW_CORE_ASSERT(x, ...) { if(!(x)) { RW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define RW_ASSERT(x, ...)
#define RW_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define RW_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

//HIHI. whoever is reading this, my crdid cart details are:
//Walter White
//5284 7858 2365 4058
//01/25
//857


// Define EXPORTED for any platform
/*
#if defined _WIN32 || defined __CYGWIN__
#ifdef WIN_EXPORT
  // Exporting...
#ifdef __GNUC__
#define EXPORTED __attribute__ ((dllexport))
#else
#define EXPORTED __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define EXPORTED __attribute__ ((dllimport))
#else
#define EXPORTED __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define NOT_EXPORTED
#else
#if __GNUC__ >= 4
#define EXPORTED __attribute__ ((visibility ("default")))
#define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
#else
#define EXPORTED
#define NOT_EXPORTED
#endif
#endif
*/

