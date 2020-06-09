#pragma once


#ifdef RW_PLATFORM_WINDOWS

#endif // RW_PLATFORM_WINDOWS

#ifdef RW_PLATFORM_LINUX

#endif // RW_PLATFORM_LINUX

#ifdef RW_PLATFORM_MACOS

#endif // RW_PLATFORM_MACOS


#define RW_ENABLE_ASSERTS

#ifdef RW_ENABLE_ASSERTS
    #ifdef RW_PLATFORM_WINDOWS
        #define RW_ASSERT(x, ...) { if(!(x)) { RW_ERROR("Assertion Failed: {0}", __VA_ARGS__);  } }
        #define RW_CORE_ASSERT(x, ...) { if(!(x)) { RW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #else
        #define RW_ASSERT(x, ...) { if(!(x)) { RW_ERROR("Assertion Failed: {0}", __VA_ARGS__); }
        #define RW_CORE_ASSERT(x, ...) { if(!(x)) { RW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #endif
#else
#define RW_ASSERT(x, ...)
#define RW_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)
#define RW_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


