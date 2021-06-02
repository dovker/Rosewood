#pragma once


// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define RW_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define RW_PLATFORM_IOS
	#elif TARGET_OS_MAC == 1
		#define RW_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define RW_PLATFORM_ANDROID
#elif defined(__linux__)
	#define RW_PLATFORM_LINUX
#else
	#error "Unknown platform!"
#endif // End of platform detection



#define RW_ENABLE_ASSERTS

#ifdef RW_ENABLE_ASSERTS
    #ifdef RW_PLATFORM_WINDOWS
        #define RW_ASSERT(x, ...) { if(!(x)) { RW_ERROR("Assertion Failed: {0}", __VA_ARGS__);  } }
        #define RW_CORE_ASSERT(x, ...) { if(!(x)) { RW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #else
        #define RW_ASSERT(x, ...) { if(!(x)) { RW_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
        #define RW_CORE_ASSERT(x, ...) { if(!(x)) { RW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #endif
#else
#define RW_ASSERT(x, ...)
#define RW_CORE_ASSERT(x, ...)
#endif

#ifndef NDEBUG
#define RW_DEBUG
#endif


#define BIT(x) (1 << x)
#define RW_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Rosewood
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }


}
