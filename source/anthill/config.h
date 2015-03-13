#pragma once

#if defined(__clang__)

    #include <TargetConditionals.h>

    #define AX_PLATFORM_WINDOWS 0
    #define AX_PLATFORM_MAC (TARGET_OS_MAC && !TARGET_OS_IPHONE)
    #define AX_PLATFORM_IOS TARGET_OS_IPHONE
    #define AX_PLATFORM_ANDROID 0
    #define AX_PLATFORM_LINUX 0

    #if AX_PLATFORM_MAC
        #define AX_PLATFORM "Mac"
        #define AX_TBB_ENABLED 1
    #elif AX_PLATFORM_IOS
        #define AX_PLATFORM "iOS"
        #define AX_TBB_ENABLED 0
    #else
        #error "Undefined Apple platform"
    #endif

    #define AX_COMPILER_VISUAL_STUDIO 0
    #define AX_COMPILER_CLANG 1
    #define AX_COMPILER_GCC 0
    #define AX_COMPILER_INTEL 0
    #define AX_COMPILER "clang"

    #if TARGET_CPU_X86
        #define AX_CPU_X86   1
        #define AX_CPU_X64   0
        #define AX_CPU_ARM   0
        #define AX_CPU_ARM64 0
        #define AX_CPU "x86"
    #elif TARGET_CPU_X86_64
        #define AX_CPU_X86   0
        #define AX_CPU_X64   1
        #define AX_CPU_ARM   0
        #define AX_CPU_ARM64 0
        #define AX_CPU "x64"
    #elif TARGET_CPU_ARM
        #define AX_CPU_X86   0
        #define AX_CPU_X64   0
        #define AX_CPU_ARM   1
        #define AX_CPU_ARM64 0
        #define AX_CPU "ARM"
    #elif TARGET_CPU_ARM64
        #define AX_CPU_X86   0
        #define AX_CPU_X64   0
        #define AX_CPU_ARM   0
        #define AX_CPU_ARM64 1
        #define AX_CPU "ARM64"
    #else
        #error "Unsupported Apple CPU architecture"
    #endif

    #if (!defined(_DEBUG) && (defined(DEBUG)))
        #define _DEBUG
    #endif

    #if (defined(_DEBUG))
        #define AX_DEBUG 1
    #else
        #define AX_DEBUG 0
    #endif

    #if defined(_DEBUG)
        #define AX_FORCEINLINE inline
    #elif defined(NDEBUG)
        #define AX_FORCEINLINE inline __attribute__ ((always_inline))
    #else
        #define AX_FORCEINLINE inline
    #endif

    #define AX_DSO_EXPORT __attribute__((visibility("default")))
    #define AX_DSO_IMPORT 
    #define AX_TEMPLATE_EXTERN_KEYWORD extern

#elif defined(_MSC_VER)

    #define AX_PLATFORM_WINDOWS 1
    #define AX_PLATFORM_MAC 0
    #define AX_PLATFORM_IOS 0
    #define AX_PLATFORM_ANDROID 0
    #define AX_PLATFORM_LINUX 0
    #define AX_PLATFORM "Windows"

    #define AX_COMPILER_VISUAL_STUDIO 1
    #define AX_COMPILER_CLANG  0
    #define AX_COMPILER_GCC    0
    #define AX_COMPILER_INTEL  0
    #define AX_COMPILER "Visual Studio"

    #define AX_CPU_ARM   0
    #define AX_CPU_ARM64 0

    #if defined(_M_IX86)
        #define AX_CPU_X86 1
        #define AX_CPU_X64 0
        #define AX_CPU "x86"
    #elif defined(_M_X64)
        #define AX_CPU_X86 0
        #define AX_CPU_X64 1
        #define AX_CPU "x64"
    #else
        #error Unsupported architecture
    #endif

    #define AX_TBB_ENABLED 1

    #if (defined(_DEBUG))
        #define AX_DEBUG 1
    #else
        #define AX_DEBUG 0
    #endif

    #if defined(_DEBUG)
        #define AX_FORCEINLINE inline
    #elif defined(NDEBUG)
        #define AX_FORCEINLINE __forceinline
    #else
        #define AX_FORCEINLINE inline
    #endif        

    #define AX_DSO_EXPORT __declspec(dllexport)
    #define AX_DSO_IMPORT __declspec(dllimport)
    #define AX_TEMPLATE_EXTERN_KEYWORD extern

    // Including SDKDDKVer.h defines the highest available Windows platform.

    // If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
    // set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

    #include <SDKDDKVer.h>

#else

    #error "Unsupported Compiler"

#endif

#ifndef __OBJC__

    namespace anthill {

    template <typename T>
    class id final {

    public:

        id();
        ~id();
        
    private:

        void* m_pointer;

    };

    static_assert(sizeof(id<int>) == sizeof(void*), "The id template must be a pointer wide or function signatures for c++ and objective-C++ code won't be exactly the same, which could be chaos causing");

    #define AX_OBJC 0
    } // anthill

#else

    #define AX_OBJC 1

#endif

#ifdef ANTHILL_BUILD
    #define ANTHILL_API AX_DSO_EXPORT
#else
    #define ANTHILL_API AX_DSO_IMPORT
#endif


