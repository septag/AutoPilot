// This header file is auto-generated
// Inlined files:
//	allocators.h
//	arrays.h
//	atomic.h
//	base.h
//	blitsort.h
//	blobs.h
//	config.h
//	debug.h
//	c89atomic.h
//	hash.h
//	iniparser.h
//	jobs.h
//	jsonparser.h
//	log.h
//	mathall.h
//	mathscalar.h
//	mathtypes.h
//	pools.h
//	settings.h
//	stringutil.h
//	system.h

#pragma once


//----------------------------------------------------------------------------------------------------------------------
// Base.h



#include <stdint.h>     // uint32, int64_t, etc..
#include <stdbool.h>    // bool
#include <stddef.h>     // NULL, size_t, offsetof
#include <memory.h>		// memset, memcpy
#include <limits.h>     // LONG_MAX, INT_MAX, etc.

//----------------------------------------------------------------------------------------------------------------------
// Config.h


#if !defined(CONFIG_FINAL_BUILD)
    #define CONFIG_FINAL_BUILD 0
#endif

#if !defined(CONFIG_MACHINE_ALIGNMENT)
    #define CONFIG_MACHINE_ALIGNMENT 16u
#endif

#if !defined(CONFIG_CHECK_OUTOFBOUNDS)
    #if defined(_DEBUG) || defined(DEBUG)
        #define CONFIG_CHECK_OUTOFBOUNDS
    #endif
#endif

#if !defined(CONFIG_TOOLMODE)
    #if !CONFIG_FINAL_BUILD
        #define CONFIG_TOOLMODE 1
    #else
        #define CONFIG_TOOLMODE 0
    #endif
#endif

#if !defined(CONFIG_FORCE_INLINE_DEBUG)
    #define CONFIG_FORCE_INLINE_DEBUG 0
#endif

#if !defined(CONFIG_MAX_PATH)
    #define CONFIG_MAX_PATH 260
#endif

#if !defined(MEMPRO_ENABLED)
    #define MEMPRO_ENABLED 0
#endif

#if !defined(CONFIG_VALIDATE_IO_READ_WRITES)
    #define CONFIG_VALIDATE_IO_READ_WRITES 1
#endif

#if !defined(CONFIG_ENABLE_ASSERT) 
    #if (defined(_DEBUG) || defined(DEBUG)) && !CONFIG_FINAL_BUILD
        #define CONFIG_ENABLE_ASSERT 1
    #else
        #define CONFIG_ENABLE_ASSERT 0
    #endif
#endif

#define CONFIG_DEV_MODE CONFIG_ENABLE_ASSERT

#if !defined(CONFIG_APP_NAME)
    #define CONFIG_APP_NAME "Junkyard"
#endif

#if !defined(CONFIG_TEMP_ALLOC_MAX)
    #define CONFIG_TEMP_ALLOC_MAX SIZE_GB
#endif

#if !defined(CONFIG_TEMP_ALLOC_PAGE_SIZE)
    #define CONFIG_TEMP_ALLOC_PAGE_SIZE 256*SIZE_KB
#endif




                                                        
#define ARCH_32BIT 0
#define ARCH_64BIT 0
#define ARCH_PTRSIZE 0

#define COMPILER_CLANG 0
#define COMPILER_CLANG_ANALYZER 0
#define COMPILER_CLANG_CL 0
#define COMPILER_GCC 0
#define COMPILER_MSVC 0

#define CPU_ARM 0
#define CPU_X86 0

#define PLATFORM_ANDROID 0
#define PLATFORM_IOS 0
#define PLATFORM_LINUX 0
#define PLATFORM_OSX 0
#define PLATFORM_WINDOWS 0

#define __STRINGIZE__(_x) #_x
#define STRINGIZE(_x) __STRINGIZE__(_x)

#define __CONCAT__(a, b) a##b
#define CONCAT(a, b) __CONCAT__(a, b)

#if defined(__clang__)
    #undef COMPILER_CLANG
    #define COMPILER_CLANG 1
    #define COMPILER_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
    #if defined(__clang_analyzer__)
        #undef COMPILER_CLANG_ANALYZER
        #define COMPILER_CLANG_ANALYZER 1
    #endif    // defined(__clang_analyzer__)
    #if defined(_MSC_VER)
        #undef COMPILER_MSVC
        #define COMPILER_MSVC 1
        #undef COMPILER_CLANG_CL
        #define COMPILER_CLANG_CL_VERSION COMPILER_CLANG
    #endif
#elif defined(_MSC_VER)
    #undef COMPILER_MSVC
    #define COMPILER_MSVC 1
    #define COMPILER_MSVC_VERSION _MSC_VER
#elif defined(__GNUC__)
    #undef COMPILER_GCC
    #define COMPILER_GCC 1
    #define COMPILER_GCC_VERIONS (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
    #error "COMPILER_* is not defined!"
#endif    //

#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM) || defined(__arm64__)
    #undef CPU_ARM
    #define CPU_ARM 1
    #define CACHE_LINE_SIZE 64u
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
    #undef CPU_X86
    #define CPU_X86 1
    #define CACHE_LINE_SIZE 64u
#else
    #error "Cpu not supported"
#endif    //

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__arm64__) || defined(__64BIT__) || \
    defined(__mips64) || defined(__powerpc64__) || defined(__ppc64__) || defined(__LP64__)
    #undef ARCH_64BIT
    #define ARCH_64BIT 1
    #undef ARCH_PTRSIZE
    #define ARCH_PTRSIZE 8
#else
    #undef ARCH_32BIT
    #define ARCH_32BIT 1
    #undef ARCH_PTRSIZE
    #define ARCH_PTRSIZE 4
#endif    //

#if defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID_API__)
    #include <sys/cdefs.h>    // Defines __BIONIC__ and includes android/api-level.h
    #undef PLATFORM_ANDROID
    #define PLATFORM_ANDROID 1
    #define  PLATFORM_ANDROID_VERSION __ANDROID__
#elif defined(_WIN32) || defined(_WIN64)
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif    // NOMINMAX
    #if defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
        #include <winapifamily.h>
    #endif    // defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
    #undef PLATFORM_WINDOWS
    #if !defined(WINVER) && !defined(_WIN32_WINNT)
        #if ARCH_64BIT
            #define WINVER 0x0a00
            #define _WIN32_WINNT 0x0a00
        #else
            #define WINVER 0x0502
            #define _WIN32_WINNT 0x0502
        #endif    // ARCH_64BIT
    #endif        // !defined(WINVER) && !defined(_WIN32_WINNT)
    #define PLATFORM_WINDOWS 1
    #define PLATFORM_WINDOWS_VERSION WINVER
#elif defined(__linux__)
    #undef PLATFORM_LINUX
    #define PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
    #undef PLATFORM_IOS
    #define PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
    #undef PLATFORM_OSX
    #define PLATFORM_OSX __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#endif    //

#if COMPILER_GCC
    #define COMPILER_NAME \
        "GCC " STRINGIZE(__GN_) "." STRINGIZE(__GNMINOR__) "." STRINGIZE(__GNPATCHLEVEL__)
#elif COMPILER_CLANG
    #define COMPILER_NAME \
        "Clang " STRINGIZE(__clang_major__) "." STRINGIZE(__clang_minor__) "." STRINGIZE(__clang_patchlevel__)
#elif COMPILER_MSVC
    #if COMPILER_MSVC_VERSION >= 1930
        #define COMPILER_NAME "MSVC 17 (" STRINGIZE(COMPILER_MSVC_VERSION)  ")"
    #elif COMPILER_MSVC_VERSION >= 1920      // Visual Studio 2019
        #define COMPILER_NAME "MSVC 16 (" STRINGIZE(COMPILER_MSVC_VERSION)  ")"
    #elif COMPILER_MSVC_VERSION >= 1910    // Visual Studio 2017
        #define COMPILER_NAME "MSVC 15"
    #elif COMPILER_MSVC_VERSION >= 1900    // Visual Studio 2015
        #define COMPILER_NAME "MSVC 14"
    #elif COMPILER_MSVC_VERSION >= 1800    // Visual Studio 2013
        #define COMPILER_NAME "MSVC 12"
    #elif COMPILER_MSVC_VERSION >= 1700    // Visual Studio 2012
        #define COMPILER_NAME "MSVC 11"
    #elif COMPILER_MSVC_VERSION >= 1600    // Visual Studio 2010
        #define COMPILER_NAME "MSVC 10"
    #elif COMPILER_MSVC_VERSION >= 1500    // Visual Studio 2008
        #define COMPILER_NAME "MSVC 9"
    #else
        #define COMPILER_NAME "MSVC"
    #endif    
#endif        // COMPILER_NAME

#if PLATFORM_ANDROID
    #define PLATFORM_NAME "Android " STRINGIZE(PLATFORM_ANDROID)
#elif PLATFORM_IOS
    #define PLATFORM_NAME "iOS"
#elif PLATFORM_LINUX
    #define PLATFORM_NAME "Linux"
#elif PLATFORM_NX
    #define PLATFORM_NAME "NX"
#elif PLATFORM_OSX
    #define PLATFORM_NAME "OSX"
#elif PLATFORM_WINDOWS
    #define PLATFORM_NAME "Windows"
#else
    #error "Unknown PLATFORM!"
#endif    // PLATFORM_

#define PLATFORM_APPLE (0 || PLATFORM_IOS || PLATFORM_OSX)

#if CPU_ARM
    #define CPU_NAME "ARM"
#elif CPU_X86
    #define CPU_NAME "x86"
#endif    // CPU_

#if ARCH_32BIT
    #define ARCH_NAME "32-bit"
#elif ARCH_64BIT
    #define ARCH_NAME "64-bit"
#endif    // ARCH_

#if defined(__has_feature)
    #define CLANG_HAS_FEATURE(_x) __has_feature(_x)
#else
    #define CLANG_HAS_FEATURE(_x) 0
#endif    // defined(__has_feature)

#if defined(__has_extension)
    #define CLANG_HAS_EXTENSION(_x) __has_extension(_x)
#else
    #define CLANG_HAS_EXTENSION(_x) 0
#endif    // defined(__has_extension)

#if COMPILER_GCC || COMPILER_CLANG
    #define FORCE_INLINE inline __attribute__((__always_inline__))
    #define FUNCTION __PRETTY_FUNCTION__
    #define NO_OPT_BEGIN __attribute__((optnone))
    #define NO_OPT_END 
    #define NO_INLINE __attribute__((noinline))
    #define CONSTFN __attribute__((const))
    #define RESTRICT __restrict__
    #define FLATTEN __attribute__((flatten))    // inline everything in the function body
    #if CONFIG_FORCE_INLINE_DEBUG
        #define INLINE NO_INLINE 
    #else
        #define INLINE static inline 
    #endif
    #ifdef _MSC_VER
        #define __stdcall
    #endif
    #define NO_VTABLE 
#elif COMPILER_MSVC
    #define FORCE_INLINE __forceinline
    #define FUNCTION __FUNCTION__
    #define NO_INLINE __declspec(noinline)
    #define NO_OPT_BEGIN __pragma(optimize("", off)) 
    #define NO_OPT_END __pragma(optimize("", on)) 
    #define CONSTFN __declspec(noalias)
    #define RESTRICT __restrict
    #define FLATTEN
    #define NO_VTABLE __declspec(novtable)
    #if CONFIG_FORCE_INLINE_DEBUG
        #define INLINE NO_INLINE 
    #else
        #define INLINE static inline 
    #endif
#else
    #error "Unknown COMPILER_?"
#endif

#if COMPILER_CLANG
    #define PRAGMA_DIAGNOSTIC_PUSH_CLANG_() _Pragma("clang diagnostic push")
    #define PRAGMA_DIAGNOSTIC_POP_CLANG_() _Pragma("clang diagnostic pop")
    #define PRAGMA_DIAGNOSTIC_IGNORED_CLANG(_x) _Pragma(STRINGIZE(clang diagnostic ignored _x))
#else
    #define PRAGMA_DIAGNOSTIC_PUSH_CLANG_()
    #define PRAGMA_DIAGNOSTIC_POP_CLANG_()
    #define PRAGMA_DIAGNOSTIC_IGNORED_CLANG(_x)
#endif    // COMPILER_CLANG

#if COMPILER_GCC && COMPILER_GCC >= 40600
    #define PRAGMA_DIAGNOSTIC_PUSH_GCC_() _Pragma("GCC diagnostic push")
    #define PRAGMA_DIAGNOSTIC_POP_GCC_() _Pragma("GCC diagnostic pop")
    #define PRAGMA_DIAGNOSTIC_IGNORED_GCC(_x) _Pragma(STRINGIZE(GCC diagnostic ignored _x))
#else
    #define PRAGMA_DIAGNOSTIC_PUSH_GCC_()
    #define PRAGMA_DIAGNOSTIC_POP_GCC_()
    #define PRAGMA_DIAGNOSTIC_IGNORED_GCC(_x)
#endif    // COMPILER_GCC

#if COMPILER_MSVC
    #define PRAGMA_DIAGNOSTIC_PUSH_MSVC_() __pragma(warning(push))
    #define PRAGMA_DIAGNOSTIC_POP_MSVC_() __pragma(warning(pop))
    #define PRAGMA_DIAGNOSTIC_IGNORED_MSVC(_x) __pragma(warning(disable : _x))
#else
    #define PRAGMA_DIAGNOSTIC_PUSH_MSVC_()
    #define PRAGMA_DIAGNOSTIC_POP_MSVC_()
    #define PRAGMA_DIAGNOSTIC_IGNORED_MSVC(_x)
#endif    // COMPILER_MSVC

#if COMPILER_CLANG
    #define PRAGMA_DIAGNOSTIC_PUSH PRAGMA_DIAGNOSTIC_PUSH_CLANG_
    #define PRAGMA_DIAGNOSTIC_POP PRAGMA_DIAGNOSTIC_POP_CLANG_
    #define PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC PRAGMA_DIAGNOSTIC_IGNORED_CLANG
#elif COMPILER_GCC
    #define PRAGMA_DIAGNOSTIC_PUSH PRAGMA_DIAGNOSTIC_PUSH_GCC_
    #define PRAGMA_DIAGNOSTIC_POP PRAGMA_DIAGNOSTIC_POP_GCC_
    #define PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC PRAGMA_DIAGNOSTIC_IGNORED_GCC
#elif COMPILER_MSVC
    #define PRAGMA_DIAGNOSTIC_PUSH PRAGMA_DIAGNOSTIC_PUSH_MSVC_
    #define PRAGMA_DIAGNOSTIC_POP PRAGMA_DIAGNOSTIC_POP_MSVC_
    #define PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC(_x)
#endif    // COMPILER_

#define PLATFORM_POSIX (0 || PLATFORM_ANDROID || PLATFORM_IOS || PLATFORM_LINUX || PLATFORM_NX || PLATFORM_OSX)
#define PLATFORM_PC (0 || PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_OSX)
#define PLATFORM_MOBILE (0 || PLATFORM_ANDROID || PLATFORM_IOS)

#if CONFIG_TOOLMODE && !PLATFORM_PC
    #undef CONFIG_TOOLMODE
    #define CONFIG_TOOLMODE 0
#endif
   
#define UNUSED(_a) (void)(_a)

#define INVALID_INDEX UINT32_MAX

#ifndef API
    #define API 
#endif

#define IS_ASAN_ENABLED 0
#define NO_ASAN 

#if COMPILER_MSVC
    #if defined(__SANITIZE_ADDRESS__)
        #undef IS_ASAN_ENABLED
        #define IS_ASAN_ENABLED 1
        
        #undef NO_ASAN
        #define NO_ASAN __declspec(no_sanitize_address)
    #endif
#elif COMPILER_CLANG
    #if defined(__has_feature)
        #if __has_feature(address_sanitizer)
            #undef NO_ASAN
            #define NO_ASAN __attribute__((no_sanitize("address")))

            #undef IS_ASAN_ENABLED
            #define IS_ASAN_ENABLED 1
        #endif
    #endif
#elif COMPILER_GCC
    #if defined(__SANITIZE_ADDRESS__) && __SANITIZE_ADDRESS__
        #undef NO_ASAN
        #define NO_ASAN __attribute__((__no_sanitize_address__))

        #undef IS_ASAN_ENABLED
        #define IS_ASAN_ENABLED 1
    #endif
#endif  

#if IS_ASAN_ENABLED
    extern "C" void __asan_poison_memory_region(void const volatile *addr, size_t size);
    extern "C" void __asan_unpoison_memory_region(void const volatile *addr, size_t size);
    
    #define ASAN_POISON_MEMORY(_addr, _size) __asan_poison_memory_region((_addr), (_size));
    #define ASAN_UNPOISON_MEMORY(_addr, _size) __asan_unpoison_memory_region((_addr), (_size))
#else
    #define ASAN_POISON_MEMORY(_addr, _size)
    #define ASAN_UNPOISON_MEMORY(_addr, _size)
#endif

#define HAS_INCLUDE(incl) __has_include(incl)

#define STRUCT_PADDING_2_BYTES() uint8 CONCAT(_padding, __LINE__)[2]
#define STRUCT_PADDING_4_BYTES() uint8 CONCAT(_padding, __LINE__)[4]
#define STRUCT_PADDING_8_BYTES() uint8 CONCAT(_padding, __LINE__)[8]
#define STRUCT_PADDING_12_BYTES() uint8 CONCAT(_padding, __LINE__)[12]
#define STRUCT_PADDING_16_BYTES() uint8 CONCAT(_padding, __LINE__)[16]


using uint8 = uint8_t;
using int8 = int8_t;
using uint16 = uint16_t;
using int16 = int16_t;
using uint32 = uint32_t;
using int32 = int32_t;
using uint64 = uint64_t;
using int64 = int64_t;
using fl32 = float;
using fl64 = double;
using uintptr = uintptr_t;

static inline constexpr uint32 PATH_CHARS_MAX = CONFIG_MAX_PATH;
static inline constexpr size_t SIZE_KB = 1024;
static inline constexpr size_t SIZE_MB = 1024*1024;
static inline constexpr size_t SIZE_GB = 1024*1024*1024;

inline constexpr uint32 MakeVersion(uint32 major, uint32 minor, uint32 patch, uint32 variant = 0);
inline constexpr uint32 GetVersionMajor(uint32 ver);
inline constexpr uint32 GetVersionMinor(uint32 ver);
inline constexpr uint32 GetVersionPatch(uint32 ver);

template <typename T> T Max(T a, T b);
template <typename T> T Min(T a, T b);
template <typename T> T Clamp(T v, T _min, T _max);
template <typename T> void Swap(T& a, T& b);
template <typename T, size_t N> constexpr uint32 CountOf(T const (&)[N]);

template <typename T> 
inline void Swap(T& a, T& b)
{
    T tmp = b;
    b = a;
    a = tmp;
}

template <typename T, size_t N> 
constexpr uint32 CountOf(T const (&)[N])
{
    return static_cast<uint32>(N);
}
    
template<typename T> inline T Max(T a, T b) { return (a > b) ? a : b; }
template<> inline int Max(int a, int b) { return (a > b) ? a : b; }
template<> inline fl32 Max(fl32 a, fl32 b) { return (a > b) ? a : b; }
template<> inline fl64 Max(fl64 a, fl64 b) { return (a > b) ? a : b; }
template<> inline int8 Max(int8 a, int8 b) { return (a > b) ? a : b; }
template<> inline uint8 Max(uint8 a, uint8 b) { return (a > b) ? a : b; }
template<> inline uint16 Max(uint16 a, uint16 b) { return (a > b) ? a : b; }
template<> inline int16 Max(int16 a, int16 b) { return (a > b) ? a : b; }
template<> inline uint32 Max(uint32 a, uint32 b) { return (a > b) ? a : b; }
template<> inline int64 Max(int64 a, int64 b) { return (a > b) ? a : b; }
template<> inline uint64 Max(uint64 a, uint64 b) { return (a > b) ? a : b; }

template<typename T> T Min(T a, T b) { return (a < b) ? a : b; }
template<> inline int Min(int a, int b) { return (a < b) ? a : b; }
template<> inline fl32 Min(fl32 a, fl32 b) { return (a < b) ? a : b; }
template<> inline fl64 Min(fl64 a, fl64 b) { return (a < b) ? a : b; }
template<> inline int8 Min(int8 a, int8 b) { return (a < b) ? a : b; }
template<> inline uint8 Min(uint8 a, uint8 b) { return (a < b) ? a : b; }
template<> inline uint16 Min(uint16 a, uint16 b) { return (a < b) ? a : b; }
template<> inline int16 Min(int16 a, int16 b) { return (a < b) ? a : b; }
template<> inline uint32 Min(uint32 a, uint32 b) { return (a < b) ? a : b; }
template<> inline int64 Min(int64 a, int64 b) { return (a < b) ? a : b; }
template<> inline uint64 Min(uint64 a, uint64 b) { return (a < b) ? a : b; }

template<typename T> inline T Clamp(T v, T _min, T _max) { return Max(Min(v, _max), _min); }
template<> inline int Clamp(int v, int _min, int _max) { return Max(Min(v, _max), _min); }
template<> inline fl32 Clamp(fl32 v, fl32 _min, fl32 _max) { return Max(Min(v, _max), _min); }
template<> inline fl64 Clamp(fl64 v, fl64 _min, fl64 _max) { return Max(Min(v, _max), _min); }
template<> inline int8 Clamp(int8 v, int8 _min, int8 _max) { return Max(Min(v, _max), _min); }
template<> inline uint8 Clamp(uint8 v, uint8 _min, uint8 _max) { return Max(Min(v, _max), _min); }
template<> inline int16 Clamp(int16 v, int16 _min, int16 _max) { return Max(Min(v, _max), _min); }
template<> inline uint16 Clamp(uint16 v, uint16 _min, uint16 _max) { return Max(Min(v, _max), _min); }
template<> inline uint32 Clamp(uint32 v, uint32 _min, uint32 _max) { return Max(Min(v, _max), _min); }
template<> inline int64 Clamp(int64 v, int64 _min, int64 _max) { return Max(Min(v, _max), _min); }
template<> inline uint64 Clamp(uint64 v, uint64 _min, uint64 _max) { return Max(Min(v, _max), _min); }

template <typename T> T PtrToInt(void* ptr);

template<> inline uint16 PtrToInt(void* ptr) { return static_cast<uint16>((uintptr_t)ptr); }
template<> inline uint32 PtrToInt(void* ptr) { return static_cast<uint32>((uintptr_t)ptr); }
template<> inline int    PtrToInt(void* ptr) { return static_cast<int>((uintptr_t)ptr); }
template<> inline uint64 PtrToInt(void* ptr) { return static_cast<uint64>((uintptr_t)ptr); }
template<> inline int64  PtrToInt(void* ptr) { return static_cast<int64>((uintptr_t)ptr); }

template <typename T> void* IntToPtr(T i);

template<> inline void* IntToPtr(uint16 i)  { return reinterpret_cast<void*>((uintptr_t)i); }
template<> inline void* IntToPtr(uint32 i)  { return reinterpret_cast<void*>((uintptr_t)i); }
template<> inline void* IntToPtr(int i)     { return reinterpret_cast<void*>((uintptr_t)i); }
template<> inline void* IntToPtr(uint64 i)  { return reinterpret_cast<void*>((uintptr_t)i); }
template<> inline void* IntToPtr(int64 i)   { return reinterpret_cast<void*>((uintptr_t)i); }

template <typename T> T IndexToId(T i);
template<> inline uint16 IndexToId(uint16 i)  { return i + 1; }
template<> inline uint32 IndexToId(uint32 i)  { return i + 1; }

template <typename T> T IdToIndex(T i);
template<> inline uint16 IdToIndex(uint16 i)  { return i - 1; }
template<> inline uint32 IdToIndex(uint32 i)  { return i - 1; }

#define ENABLE_BITMASK(_EnumType) \
    FORCE_INLINE _EnumType operator|(_EnumType lhs, _EnumType rhs) {   \
        return static_cast<_EnumType>(static_cast<uint32>(lhs) | static_cast<uint32>(rhs));  \
    }   \
    FORCE_INLINE _EnumType operator&(_EnumType lhs, _EnumType rhs) {   \
        return static_cast<_EnumType>(static_cast<uint32>(lhs) & static_cast<uint32>(rhs));  \
    }   \
    FORCE_INLINE _EnumType operator^(_EnumType lhs, _EnumType rhs) {   \
        return static_cast<_EnumType>(static_cast<uint32>(lhs) ^ static_cast<uint32>(rhs));  \
    }    \
    FORCE_INLINE _EnumType operator~(_EnumType rhs) {   \
        return static_cast<_EnumType>(~static_cast<uint32>(rhs));  \
    }   \
    FORCE_INLINE _EnumType& operator|=(_EnumType& lhs, _EnumType rhs)  {   \
        lhs = static_cast<_EnumType>(static_cast<uint32>(lhs) | static_cast<uint32>(rhs));  \
        return lhs; \
    }   \
    FORCE_INLINE _EnumType& operator&=(_EnumType& lhs, _EnumType rhs)   {   \
        lhs = static_cast<_EnumType>(static_cast<uint32>(lhs) & static_cast<uint32>(rhs));  \
        return lhs; \
    }   \
    FORCE_INLINE _EnumType& operator^=(_EnumType& lhs, _EnumType rhs)   {   \
        lhs = static_cast<_EnumType>(static_cast<uint32>(lhs) ^ static_cast<uint32>(rhs));  \
        return lhs; \
    }

template <typename _T> bool IsBitsSet(_T flags, _T bits) { return (flags & bits) == bits; }

template <typename _A, typename _B>
struct Pair
{
    _A first;
    _B second;

    Pair() = default;
    explicit Pair(const _A& a, const _B& b) : 
        first(a), second(b) {}
};


struct RandomContext
{
    uint64 state[2];
};

namespace Random
{
    API uint32 Seed();
    API RandomContext CreateContext(uint32 seed = 0);

    API uint32 Int(RandomContext* ctx);
    API int Int(RandomContext* ctx, int _min, int _max);

    API float Float(RandomContext* ctx);
    API float Float(RandomContext* ctx, float _min, float _max);

    API uint32 Int();
    API int Int(int _min, int _max);

    API float Float();
    API float Float(float _min, float _max);
}

INLINE constexpr uint32 MakeFourCC(uint8 _a, uint8 _b, uint8 _c, uint8 _d)
{
    return  static_cast<uint32>(_a) | 
           (static_cast<uint32>(_b) << 8) | 
           (static_cast<uint32>(_c) << 16) | 
           (static_cast<uint32>(_d) << 24);
}

template<typename _T> inline constexpr _T AlignValue(_T value, _T align);
template<> inline constexpr int AlignValue(int value, int align) { int mask = align - 1; return (value + mask) & ((~0) & (~mask)); }
template<> inline constexpr uint16 AlignValue(uint16 value, uint16 align) { uint16 mask = align - 1; return (value + mask) & ((~0) & (~mask)); }
template<> inline constexpr uint32 AlignValue(uint32 value, uint32 align) { uint32 mask = align - 1; return (value + mask) & ((~0) & (~mask)); }
template<> inline constexpr uint64 AlignValue(uint64 value, uint64 align) { uint64 mask = align - 1; return (value + mask) & ((~0) & (~mask)); }
#if PLATFORM_APPLE
template<> inline constexpr size_t AlignValue(size_t value, size_t align) { size_t mask = align - 1; return (value + mask) & ((~0) & (~mask)); }
#endif

template<typename _T> inline constexpr _T DivCeil(_T value, _T divider);
template<> inline constexpr int DivCeil(int value, int divider) { return (value + divider - 1)/divider; }
template<> inline constexpr uint16 DivCeil(uint16 value, uint16 divider) { return (value + divider - 1)/divider; }
template<> inline constexpr uint32 DivCeil(uint32 value, uint32 divider) { return (value + divider - 1)/divider; }
template<> inline constexpr uint64 DivCeil(uint64 value, uint64 divider) { return (value + divider - 1)/divider; }

#if defined(Main)
    #undef Main
#endif

#if PLATFORM_ANDROID
    #define Main AndroidMain
#else
    #define Main main
#endif


#if PLATFORM_ANDROID
    #include <signal.h> // raise
#endif

using AssertFailCallback = void(*)(void* userData);

namespace Assert
{
    API void SetFailCallback(AssertFailCallback callback, void* userdata);
    API void RunFailCallback();
    API void DebugMessage(const char* fmt, ...);
} // Assert

#if PLATFORM_ANDROID
    #define DEBUG_BREAK() raise(SIGINT)
#elif COMPILER_MSVC
    #define DEBUG_BREAK() __debugbreak()
#elif COMPILER_CLANG
    #if (__has_builtin(__builtin_debugtrap))
        #define DEBUG_BREAK() __builtin_debugtrap()
    #else
        #define DEBUG_BREAK() __builtin_trap()    // This cannot be used in constexpr functions
    #endif
#elif COMPILER_GCC
    #define DEBUG_BREAK() __builtin_trap()
#endif

#ifdef ASSERT
    #undef ASSERT
#endif

#if CONFIG_ENABLE_ASSERT
    #define ASSERT(_expr) do { if (!(_expr)) { Assert::DebugMessage(#_expr); Assert::RunFailCallback(); DEBUG_BREAK(); }} while(0)
    #define ASSERT_MSG(_expr, ...) do { if (!(_expr)) { Assert::DebugMessage(__VA_ARGS__); Assert::RunFailCallback(); DEBUG_BREAK(); }} while(0)
#else
    #define ASSERT(_expr)
    #define ASSERT_MSG(_expr, ...)
#endif

#define ASSERT_ALWAYS(_expr, ...) do { if (!(_expr)) { Assert::DebugMessage(__VA_ARGS__); Assert::RunFailCallback(); DEBUG_BREAK(); }} while(0)


template <typename _T>
struct RelativePtr
{
    RelativePtr() : mOffset(0) {}
    RelativePtr(_T* ptr) { Set(ptr); }
    _T* operator->() { return Get(); }
    const _T* operator->() const { return Get(); }
    RelativePtr<_T>& operator=(_T* ptr) { Set(ptr); return *this; }
    RelativePtr<_T>& operator=(const _T* ptr) { Set(ptr); return *this; }
    _T& operator[](uint32 index) { return Get()[index]; }
    const _T& operator[](uint32 index) const { return Get()[index]; }
    bool IsNull() const { return mOffset == 0; };
    void SetNull() { mOffset = 0; }
    bool operator!() const { return IsNull(); }
    operator bool() const { return !IsNull(); }
    _T& operator*() const { return *Get(); }

    inline void Set(const _T* ptr)
    { 
        if (ptr == nullptr) {
            mOffset = 0;
        }
        else {
            intptr_t offset = intptr_t(ptr) - intptr_t(this);
            ASSERT(offset <= INT_MAX && offset >= INT_MIN);
            mOffset = int(offset);
        }
    }

    inline _T* Get() const 
    { 
        if (mOffset == 0)
            return nullptr;
        return (_T*)((uint8*)this + mOffset); 
    }

private:
    int mOffset;
};



template <typename _T>
struct Span
{
    Span() : mData(nullptr), mCount(0) {}
    explicit Span(_T* data, uint32 count) : mData(data), mCount(count) {}
    explicit Span(_T* data, _T* end) : mData(data), mCount(PtrToInt<uint32>(end - data)) { ASSERT(data); ASSERT(end); }

    _T& operator[](uint32 index)    
    { 
        #ifdef CONFIG_CHECK_OUTOFBOUNDS
            ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
        #endif
        return mData[index];
    }

    const _T& operator[](uint32 index) const
    { 
        #ifdef CONFIG_CHECK_OUTOFBOUNDS
            ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
        #endif
        return mData[index];
    }

    uint32 Count() const    { return mCount; }
    const _T* Ptr() const   { return mData; }
    _T* Ptr()   { return mData; }

    Span<_T> Slice(uint32 index, uint32 count)
    {
        #ifdef CONFIG_CHECK_OUTOFBOUNDS
            ASSERT_MSG(index < mCount, "Index out of bounds (mCount: %u, index: %u)", mCount, index);
            ASSERT_MSG((index + count) <= mCount, "Count out of bounds (mCount: %u, index: %u, count: %u)", mCount, index, count);
        #endif
        return Span(mData + index, count);
    }

    struct Iterator 
    {
        Iterator(_T* ptr) : _ptr(ptr) {}
        _T& operator*() { return *_ptr; }
        void operator++() { ++_ptr; }
        bool operator!=(Iterator it) { return _ptr != it._ptr; }
        _T* _ptr;
    };

    Iterator begin()    { return Iterator(&mData[0]); }
    Iterator end()      { return Iterator(&mData[mCount]); }

    Iterator begin() const    { return Iterator(&mData[0]); }
    Iterator end() const     { return Iterator(&mData[mCount]); }

private:
    _T* mData;
    uint32 mCount;
};


enum class MemAllocatorType
{
    Unknown,
    Heap,       // Normal malloc/free heap allocator
    Temp,       // Stack-based temp allocator. Grows by page. Only works within a single thread context and function scopes.
    Bump,       // Bump/Offset-based allocator. Fixed capacity. Grows page by page. Can be backed by any kind of memory (VM/gpu/stack/heap/etc.)
    Tlsf,       // TLSF dynamic allocator. Fixed capacity. Persists in memory and usually used for subsystems with unknown memory allocation pattern.
    Proxy       // Allocator that doesn't do anything except keeping track of allocs and references another allocator for actual allocs
};

struct NO_VTABLE MemAllocator
{
    virtual void* Malloc(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) = 0;
    virtual void* Realloc(void* ptr, size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) = 0;
    virtual void  Free(void* ptr, uint32 align = CONFIG_MACHINE_ALIGNMENT) = 0;
    virtual MemAllocatorType GetType() const = 0;
};

using MemFailCallback = void(*)(void* userData);

namespace Mem
{
    API void SetFailCallback(MemFailCallback callback, void* userdata);
    API void RunFailCallback();
    API void* AlignPointer(void* ptr, size_t extra, uint32 align);
    API MemAllocator* GetDefaultAlloc();
    API void SetDefaultAlloc(MemAllocator* alloc);

    API void EnableMemPro(bool enable);
    API bool IsMemProEnabled();
    API void TrackMalloc(void* ptr, size_t size);
    API void TrackFree(void* ptr);
    API void TrackRealloc(void* oldPtr, void* ptr, size_t size);

    #define MEM_FAIL() do { Mem::RunFailCallback(); ASSERT_ALWAYS(0, "Out of memory"); } while (0)

    FORCE_INLINE void* Alloc(size_t size, MemAllocator* alloc = GetDefaultAlloc());
    FORCE_INLINE void* AllocZero(size_t size, MemAllocator* alloc = GetDefaultAlloc());
    FORCE_INLINE void* Realloc(void* ptr, size_t size, MemAllocator* alloc = GetDefaultAlloc());
    FORCE_INLINE void  Free(void* ptr, MemAllocator* alloc = GetDefaultAlloc());

    FORCE_INLINE void* AllocAligned(size_t size, uint32 align, MemAllocator* alloc = GetDefaultAlloc());
    FORCE_INLINE void* AllocAlignedZero(size_t size, uint32 align, MemAllocator* alloc = GetDefaultAlloc());
    FORCE_INLINE void* ReallocAligned(void* ptr, size_t size, uint32 align, MemAllocator* alloc = GetDefaultAlloc());
    FORCE_INLINE void  FreeAligned(void* ptr, uint32 align, MemAllocator* alloc = GetDefaultAlloc());

    template<typename _T> _T* AllocTyped(uint32 count = 1, MemAllocator* alloc = GetDefaultAlloc());
    template<typename _T> _T* AllocZeroTyped(uint32 count = 1, MemAllocator* alloc = GetDefaultAlloc());
    template<typename _T> _T* AllocAlignedTyped(uint32 count = 1, uint32 align = CONFIG_MACHINE_ALIGNMENT, MemAllocator* alloc = GetDefaultAlloc());
    template<typename _T> _T* AllocAlignedZeroTyped(uint32 count = 1, uint32 align = CONFIG_MACHINE_ALIGNMENT, MemAllocator* alloc = GetDefaultAlloc());
    template<typename _T> _T* ReallocTyped(_T* ptr, uint32 count = 1, MemAllocator* alloc = GetDefaultAlloc());
    template<typename _T> _T* AllocCopy(const _T* src, uint32 count = 1, MemAllocator* alloc = GetDefaultAlloc());
    template<typename _T> _T* AllocCopyRawBytes(const _T* src, size_t sizeBytes, MemAllocator* alloc = GetDefaultAlloc());
}

namespace _private
{
    struct PlacementNewTag {};
}

#define PLACEMENT_NEW(_ptr, _type) ::new(_private::PlacementNewTag(), _ptr) _type
#define NEW(_alloc, _type) PLACEMENT_NEW(Mem::Alloc(sizeof(_type), _alloc), _type)
#define ALIGNED_NEW(_alloc, _type, _align) PLACEMENT_NEW(Mem::AllocAligned(sizeof(_type), _align, _alloc), _type)

#define PLACEMENT_NEW_ARRAY(_ptr, _type, _n) new(_private::PlacementNewTag(), _ptr) _type[_n]
#define NEW_ARRAY(_alloc, _type, _n) PLACEMENT_NEW_ARRAY(Mem::Alloc(sizeof(_type)*_n, _alloc), _type, _n)

inline void* operator new(size_t, _private::PlacementNewTag, void* _ptr) { return _ptr; }
inline void* operator new[](size_t, _private::PlacementNewTag, void* _ptr) { return _ptr; }
inline void  operator delete(void*, _private::PlacementNewTag, void*) throw() {}

inline constexpr uint32 MakeVersion(uint32 major, uint32 minor, uint32 patch, uint32 variant)
{
    return ((variant << 29U) | (major << 22U) | (minor << 12U) | patch);
}

inline constexpr uint32 GetVersionMajor(uint32 ver)
{
    return (ver >> 22U) & 0x7FU;
}

inline constexpr uint32 GetVersionMinor(uint32 ver)
{
    return (ver >> 12U) & 0x3FFU;
}

inline constexpr uint32 GetVersionPatch(uint32 ver)
{
    return ver & 0xFFFU;
}

inline constexpr uint32 GetVersionVariant(uint32 ver)
{
    return ver >> 29U;
}

[[nodiscard]] FORCE_INLINE void* Mem::Alloc(size_t size, MemAllocator* alloc)
{
    ASSERT(alloc);
    void* ptr = alloc->Malloc(size, CONFIG_MACHINE_ALIGNMENT);
    if (ptr == NULL) {
        MEM_FAIL();
    }
    return ptr;
}

[[nodiscard]] FORCE_INLINE void* Mem::AllocZero(size_t size, MemAllocator* alloc)
{
    ASSERT(alloc);
    void* ptr = alloc->Malloc(size, CONFIG_MACHINE_ALIGNMENT);
    if (ptr == NULL) {
        MEM_FAIL();
    }
    memset(ptr, 0x0, size);
    return ptr;
}

[[nodiscard]] FORCE_INLINE void* Mem::Realloc(void* ptr, size_t size, MemAllocator* alloc)
{
    ASSERT(alloc);
    ptr = alloc->Realloc(ptr, size, CONFIG_MACHINE_ALIGNMENT);
    if (ptr == NULL) {
        MEM_FAIL();
    }
    return ptr;
}

FORCE_INLINE void Mem::Free(void* ptr, MemAllocator* alloc)
{
    ASSERT(alloc);
    alloc->Free(ptr, CONFIG_MACHINE_ALIGNMENT);
}

[[nodiscard]] FORCE_INLINE void* Mem::AllocAligned(size_t size, uint32 align, MemAllocator* alloc)
{
    ASSERT(alloc);
    align = Max(align, CONFIG_MACHINE_ALIGNMENT);
    void* ptr = alloc->Malloc(AlignValue<size_t>(size, align), align);
    if (ptr == NULL) {
        MEM_FAIL();
    }
    return ptr;
}

[[nodiscard]] FORCE_INLINE void* Mem::AllocAlignedZero(size_t size, uint32 align, MemAllocator* alloc)
{
    ASSERT(alloc);
    align = Max(align, CONFIG_MACHINE_ALIGNMENT);
    void* ptr = alloc->Malloc(AlignValue<size_t>(size, align), align);
    if (ptr == NULL) {
        MEM_FAIL();
        return nullptr;
    }
    memset(ptr, 0x0, size);
    return ptr;
}

[[nodiscard]] FORCE_INLINE void* Mem::ReallocAligned(void* ptr, size_t size, uint32 align, MemAllocator* alloc)
{
    ASSERT(alloc);
    align = Max(align, CONFIG_MACHINE_ALIGNMENT);
    ptr = alloc->Realloc(ptr, AlignValue<size_t>(size, align), align);
    if (ptr == NULL) {
        MEM_FAIL();
    }
    return ptr;

}

FORCE_INLINE void Mem::FreeAligned(void* ptr, uint32 align, MemAllocator* alloc)
{
    ASSERT(alloc);
    alloc->Free(ptr, Max(align, CONFIG_MACHINE_ALIGNMENT));
}

template<typename _T>
[[nodiscard]] inline _T* Mem::AllocTyped(uint32 count, MemAllocator* alloc)
{
    return reinterpret_cast<_T*>(Mem::Alloc(sizeof(_T)*count, alloc));
}

template<typename _T>
[[nodiscard]] inline _T* Mem::AllocZeroTyped(uint32 count, MemAllocator* alloc)
{
    return reinterpret_cast<_T*>(Mem::AllocZero(sizeof(_T)*count, alloc));
}

template<typename _T>
[[nodiscard]] inline _T* Mem::AllocAlignedTyped(uint32 count, uint32 align, MemAllocator* alloc)
{
    return reinterpret_cast<_T*>(Mem::AllocAligned(sizeof(_T)*count, align, alloc));
}

template<typename _T>
[[nodiscard]] inline _T* Mem::AllocAlignedZeroTyped(uint32 count, uint32 align, MemAllocator* alloc)
{
    return reinterpret_cast<_T*>(Mem::AllocAlignedZero(sizeof(_T)*count, align, alloc));
}

template<typename _T>
[[nodiscard]] inline _T* Mem::ReallocTyped(_T* ptr, uint32 count, MemAllocator* alloc)
{
    return reinterpret_cast<_T*>(Mem::Realloc(ptr, sizeof(_T)*count, alloc));
}

template<typename _T> 
[[nodiscard]] inline _T* Mem::AllocCopy(const _T* src, uint32 count, MemAllocator* alloc)
{
    if (count == 0) {
        ASSERT(0);
        return nullptr;
    }

    auto buff = Mem::AllocTyped<_T>(count, alloc);
    if (buff) {
        memcpy(buff, src, sizeof(_T)*count);
        return buff;
    }
    else {
        return nullptr;
    }
}

template<typename _T> 
[[nodiscard]] inline _T* Mem::AllocCopyRawBytes(const _T* src, size_t sizeBytes, MemAllocator* alloc)
{
    if (sizeBytes == 0) {
        ASSERT(0);
        return nullptr;
    }

    auto buff = (_T*)Mem::Alloc(sizeBytes, alloc);
    if (buff) {
        memcpy(buff, src, sizeBytes);
        return buff;
    }
    else {
        return nullptr;
    }
}





template <typename _T> struct Array; // Fwd from Array.h
using SpinLockFake = uint8[CACHE_LINE_SIZE];

template <typename _T> struct HashTable;

struct MemDebugPointer
{
    void* ptr;
    uint32 align;
};

struct MemProxyAllocatorItem
{
    void* ptr;
    size_t size;
};

enum class MemProxyAllocatorFlags : uint32
{
    None = 0,
    EnableTracking = 0x1,
    EnableCaptureCallstacks = 0x2 // TODO
};
ENABLE_BITMASK(MemProxyAllocatorFlags);


struct alignas(CACHE_LINE_SIZE) MemProxyAllocator final : MemAllocator
{
    MemProxyAllocator();

    void Initialize(const char* name, MemAllocator* baseAlloc, MemProxyAllocatorFlags flags);
    void Release();

    [[nodiscard]] void* Malloc(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    [[nodiscard]] void* Realloc(void* ptr, size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    void Free(void* ptr, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    MemAllocatorType GetType() const override { return MemAllocatorType::Proxy; }

    const char* mName = nullptr;
    MemAllocator* mBaseAlloc = nullptr;
    HashTable<MemProxyAllocatorItem>* mAllocTable;
    uint64 mTotalSizeAllocated = 0;
    uint32 mNumAllocs = 0;
    MemProxyAllocatorFlags mFlags = MemProxyAllocatorFlags::None;

    uint8 _padding[CACHE_LINE_SIZE - sizeof(MemAllocator) - sizeof(void*)*3 - sizeof(uint64) - sizeof(uint32)*2];
    SpinLockFake mLock;
};

struct MemTempAllocator final : MemAllocator
{
    using ID = uint32;

    struct Stats
    {
        size_t maxPeak;
        size_t commitedBytes;
        size_t reservedBytes;
        uint32 threadId;
        const char* threadName;
    };

    MemTempAllocator();
    explicit MemTempAllocator(ID id);
    ~MemTempAllocator();

    ID GetId() const { return mId; }
    bool OwnsId() const { return mOwnsId; }

    [[nodiscard]] void* Malloc(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    [[nodiscard]] void* Realloc(void* ptr, size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    [[nodiscard]] void* MallocZero(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT);
    void Free(void* ptr, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;

    template <typename _T>
    [[nodiscard]] _T* MallocTyped(uint32 count = 1, uint32 align = CONFIG_MACHINE_ALIGNMENT) { return reinterpret_cast<_T*>(Malloc(count*sizeof(_T), align)); }
   
    template <typename _T>
    [[nodiscard]] _T* MallocZeroTyped(uint32 count = 1, uint32 align = CONFIG_MACHINE_ALIGNMENT)  { return reinterpret_cast<_T*>(MallocZero(count*sizeof(_T), align)); }
    
    template <typename _T>
    [[nodiscard]] _T* ReallocTyped(_T* ptr, uint32 count = 1, uint32 align = CONFIG_MACHINE_ALIGNMENT) { return reinterpret_cast<_T*>(Realloc(ptr, count*sizeof(_T), align)); }

    MemAllocatorType GetType() const override { return MemAllocatorType::Temp; }
    size_t GetOffset() const;
    size_t GetPointerOffset(void* ptr) const;

    API [[nodiscard]] static ID PushId();
    API static void PopId(ID id);
    API static void EnableDebugMode(bool enable);
    API static void EnableCallstackCapture(bool capture);
    API static void GetStats(MemAllocator* alloc, Stats** outStats, uint32* outCount);
    API static void Reset();

private:
    ID mId = 0;
    uint16 mFiberProtectorId = 0;
    bool mOwnsId = false;
};

#define DEFINE_SAFE_TEMP_ALLOCATOR(_name, _alloc) MemTempAllocator _name(_alloc->GetType() == MemAllocatorType::Temp ? ((MemTempAllocator*)_alloc)->GetId() : 0);

                                                                                     
struct MemBumpAllocatorBase : MemAllocator
{
    void Initialize(size_t reserveSize, size_t pageSize, bool debugMode = false);
    void Release();
    void Reset();
    void CommitAll();
    bool IsInitialized() const;

    [[nodiscard]] void* Malloc(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    [[nodiscard]] void* Realloc(void* ptr, size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    void  Free(void* ptr, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    MemAllocatorType GetType() const override { return MemAllocatorType::Bump; }

    size_t GetReservedSize() const { return mReserveSize; }
    size_t GetAllocatedSize() const { return mOffset; }
    size_t GetCommitedSize() const { return mCommitSize; }
    size_t GetPointerOffset(void* ptr);
    size_t GetOffset() const { return mOffset; }
    void SetOffset(size_t offset);      // Only accepts lesser values than current offset. potentially harmful. Use with care!
    bool IsDebugMode() const { return mDebugMode; }

protected:
    virtual void* BackendReserve(size_t size) = 0;
    virtual void* BackendCommit(void* ptr, size_t size) = 0;
    virtual void  BackendDecommit(void* ptr, size_t size) = 0;
    virtual void  BackendRelease(void* ptr, size_t size) = 0;

    uint8* mBuffer = nullptr;
    size_t mCommitSize = 0;
    size_t mOffset = 0;
    size_t mPageSize = 0;
    size_t mReserveSize = 0;
    void* mLastAllocatedPtr = 0;
    Array<MemDebugPointer>* mDebugPointers = nullptr;
    bool mDebugMode = false;
};

struct MemBumpAllocatorVM final : MemBumpAllocatorBase
{
    void WarmUp();

private:
    void* BackendReserve(size_t size) override;
    void* BackendCommit(void* ptr, size_t size) override;
    void  BackendDecommit(void* ptr, size_t size) override;
    void  BackendRelease(void* ptr, size_t size) override;
};

struct MemBumpAllocatorCustom final : MemBumpAllocatorBase
{
    MemBumpAllocatorCustom() = default;
    explicit MemBumpAllocatorCustom(MemAllocator* alloc) : mAlloc(alloc) {}
    void SetAllocator(MemAllocator* alloc) { mAlloc = alloc; }

private:
    MemAllocator* mAlloc = Mem::GetDefaultAlloc();
    void* BackendReserve(size_t size) override;
    void* BackendCommit(void* ptr, size_t size) override;
    void  BackendDecommit(void* ptr, size_t size) override;
    void  BackendRelease(void* ptr, size_t size) override;
};

struct alignas(CACHE_LINE_SIZE) MemThreadSafeAllocator final : MemAllocator
{
    MemThreadSafeAllocator();
    explicit MemThreadSafeAllocator(MemAllocator* alloc);
    void SetAllocator(MemAllocator* alloc);

    [[nodiscard]] void* Malloc(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    [[nodiscard]] void* Realloc(void* ptr, size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    void Free(void* ptr, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    MemAllocatorType GetType() const override;

private:
    MemAllocator* mAlloc = nullptr;
    [[maybe_unused]] uint8 _padding1[CACHE_LINE_SIZE - sizeof(MemAllocator) - sizeof(MemAllocator*)];
    SpinLockFake mLock;
};


struct MemTlsfAllocator final : MemAllocator
{
    static size_t GetMemoryRequirement(size_t poolSize);

    void Initialize(MemAllocator* alloc, size_t poolSize, bool debugMode = false);
    void Initialize(size_t poolSize, void* buffer, size_t size, bool debugMode = false);
    void Release();

    [[nodiscard]] void* Malloc(size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    [[nodiscard]] void* Realloc(void* ptr, size_t size, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    void  Free(void* ptr, uint32 align = CONFIG_MACHINE_ALIGNMENT) override;
    MemAllocatorType GetType() const override { return MemAllocatorType::Tlsf; }

    size_t GetAllocatedSize() const { return mAllocatedSize; }

    float CalculateFragmentation();
    bool Validate();
    bool IsDebugMode() const { return mDebugMode; }

protected:
    MemAllocator* mAlloc = nullptr;
    size_t mPoolSize = 0;
    size_t mAllocatedSize = 0;
    void*  mTlsf = nullptr;
    size_t mTlsfSize = 0;
    bool   mDebugMode = false;
};


                                                                                                                                     
struct NO_VTABLE MemSingleshotMallocBase
{
    virtual void* MallocInternal(void* buff, size_t size) = 0;
    virtual size_t GetMemoryRequirement() const = 0;
};

template <typename _T, uint32 _MaxFields = 8>
struct MemSingleShotMalloc final : MemSingleshotMallocBase
{
    MemSingleShotMalloc();

    template <typename _FieldType> MemSingleShotMalloc& AddMemberArray(uint32 offsetInStruct, size_t arrayCount, 
                                                                       bool relativePtr = false,
                                                                       uint32 align = CONFIG_MACHINE_ALIGNMENT);
    MemSingleShotMalloc& AddChildStructSingleShot(MemSingleshotMallocBase& childSingleShot, 
                                                  uint32 offsetInStruct, size_t arrayCount, 
                                                  bool relativePtr = false,
                                                  uint32 align = CONFIG_MACHINE_ALIGNMENT);
    template <typename _FieldType> MemSingleShotMalloc& AddExternalPointerField(_FieldType** pPtr, size_t arrayCount, 
                                                                                uint32 align = CONFIG_MACHINE_ALIGNMENT);

    _T* Calloc(MemAllocator* alloc = Mem::GetDefaultAlloc());
    _T* Calloc(void* buff, size_t size);

    _T* Malloc(MemAllocator* alloc = Mem::GetDefaultAlloc());
    _T* Malloc(void* buff, size_t size);

    void* MallocInternal(void* buff, size_t size) override;
    size_t GetMemoryRequirement() const override;

    static void Free(_T* p, MemAllocator* alloc = Mem::GetDefaultAlloc());
    size_t GetSize() const;

private:
    struct Field
    {
        void** pPtr;
        MemSingleshotMallocBase* childStruct;
        size_t offset;
        uint32 offsetInStruct;
        bool   relativePtr;
    };

    Field  mFields[_MaxFields+1];
    size_t mSize;
    uint32 mNumFields;
};


template <typename _T, uint32 _MaxFields>
inline MemSingleShotMalloc<_T, _MaxFields>::MemSingleShotMalloc()
{
    mSize = sizeof(_T);

    mFields[0].pPtr = nullptr;
    mFields[0].childStruct = nullptr;
    mFields[0].offset = 0;
    mFields[0].offsetInStruct = uint32(-1);
    mNumFields = 1;
}

template <typename _T, uint32 _MaxFields>
template <typename _FieldType> inline MemSingleShotMalloc<_T, _MaxFields>& 
    MemSingleShotMalloc<_T, _MaxFields>::AddMemberArray(uint32 offsetInStruct, size_t arrayCount, bool relativePtr, uint32 align)
{
    uint32 index = mNumFields;
    ASSERT_MSG(index < (_MaxFields + 1), "Cannot add more fields, increase the _MaxFields");
    
    align = Max(CONFIG_MACHINE_ALIGNMENT, align);
    size_t size = sizeof(_FieldType) * arrayCount;
    size = AlignValue<size_t>(size, align);

    size_t offset = mSize;
    if (offset % align != 0) {
        offset = AlignValue<size_t>(offset, align);
        size += offset - mSize;
    }

    Field& buff = mFields[index];
    buff.pPtr = nullptr;
    buff.childStruct = nullptr;
    buff.offset = offset;
    buff.offsetInStruct = offsetInStruct;
    buff.relativePtr = relativePtr;

    mSize += size;
    ++mNumFields;

    return *this;
}

template <typename _T, uint32 _MaxFields>
inline MemSingleShotMalloc<_T, _MaxFields>& 
    MemSingleShotMalloc<_T, _MaxFields>::AddChildStructSingleShot(MemSingleshotMallocBase& childSingleShot, uint32 offsetInStruct, 
                                                                  size_t arrayCount, bool relativePtr, uint32 align)
{
    uint32 index = mNumFields;
    ASSERT_MSG(index < (_MaxFields+1), "Cannot add more fields, increase the _MaxFields");
    
    align = Max(CONFIG_MACHINE_ALIGNMENT, align);
    size_t size = childSingleShot.GetMemoryRequirement() * arrayCount;
    size = AlignValue<size_t>(size, align);

    size_t offset = mSize;
    if (offset % align != 0) {
        offset = AlignValue<size_t>(offset, align);
    }

    Field& buff = mFields[index];
    buff.pPtr = nullptr;
    buff.childStruct = &childSingleShot;
    buff.offset = offset;
    buff.offsetInStruct = offsetInStruct;
    buff.relativePtr = relativePtr;

    mSize += size;
    ++mNumFields;

    return *this;
}


template <typename _T, uint32 _MaxFields>
template <typename _FieldType> inline MemSingleShotMalloc<_T, _MaxFields>& 
    MemSingleShotMalloc<_T, _MaxFields>::AddExternalPointerField(_FieldType** pPtr, size_t arrayCount, uint32 align)
{
    ASSERT(pPtr);

    uint32 index = mNumFields;
    ASSERT_MSG(index < (_MaxFields+1), "Cannot add more fields, increase the _MaxFields");
    
    align = Max(CONFIG_MACHINE_ALIGNMENT, align);
    size_t size = sizeof(_FieldType) * arrayCount;
    size = AlignValue<size_t>(size, align);
    
    size_t offset = mSize;
    if (offset % align != 0) {
        offset = AlignValue<size_t>(offset, align);
    }
    
    Field& buff = mFields[index];
    buff.pPtr = (void**)pPtr;
    buff.offset = offset;
    buff.offsetInStruct = uint32(-1);
    buff.relativePtr = false;
    
    mSize += size;
    ++mNumFields;

    return *this;
}

template <typename _T, uint32 _MaxFields>
inline size_t MemSingleShotMalloc<_T, _MaxFields>::GetMemoryRequirement() const
{
    return mSize;
}

template <typename _T, uint32 _MaxFields>
inline void MemSingleShotMalloc<_T, _MaxFields>::Free(_T* p, MemAllocator* alloc)
{
    ASSERT(alloc);
    if (p)
        Mem::FreeAligned(p, alignof(_T), alloc);
}

template <typename _T, uint32 _MaxFields>
inline size_t MemSingleShotMalloc<_T, _MaxFields>::GetSize() const
{
    return mSize;
}

template <typename _T, uint32 _MaxFields>
inline _T* MemSingleShotMalloc<_T, _MaxFields>::Calloc(MemAllocator* alloc)
{
    void* mem = Mem::AllocAligned(mSize, alignof(_T), alloc);
    return Calloc(mem, mSize);
}

template <typename _T, uint32 _MaxFields>
inline _T*  MemSingleShotMalloc<_T, _MaxFields>::Calloc(void* buff, [[maybe_unused]] size_t size)
{
    ASSERT(buff);
    ASSERT(size == 0 || size >= GetMemoryRequirement());

    memset(buff, 0x0, mSize);

    return Malloc(buff, size);
}

template <typename _T, uint32 _MaxFields>
inline _T* MemSingleShotMalloc<_T, _MaxFields>::Malloc(MemAllocator* alloc)
{
    void* mem = Mem::AllocAligned(mSize, alignof(_T), alloc);
    return (_T*)MallocInternal(mem, mSize);
}

template <typename _T, uint32 _MaxFields>
inline _T*  MemSingleShotMalloc<_T, _MaxFields>::Malloc(void* buff, size_t size)
{
    return (_T*)MallocInternal(buff, size);
}

template <typename _T, uint32 _MaxFields>
inline void* MemSingleShotMalloc<_T, _MaxFields>::MallocInternal(void* buff, [[maybe_unused]] size_t size)
{
    ASSERT(buff);
    ASSERT(size == 0 || size >= GetMemoryRequirement());

    uint8* tmp = (uint8*)buff;
    
    for (int i = 1, c = mNumFields; i < c; i++) {
        if (mFields[i].offsetInStruct != -1) {
            ASSERT(mFields[i].pPtr == nullptr);
            void* ptr = tmp + mFields[i].offset;
            void* srcPtr = tmp + mFields[i].offsetInStruct;
            if (!mFields[i].relativePtr)
                *((void**)srcPtr) = ptr;
            else
                *((int*)srcPtr) = (int)mFields[i].offset - (int)mFields[i].offsetInStruct;

            if (mFields[i].childStruct)
                mFields[i].childStruct->MallocInternal(ptr, 0);
        } else {
            ASSERT(mFields[i].offsetInStruct == -1);
            *mFields[i].pPtr = tmp + mFields[i].offset;
        }
    }

    return buff;
}





template <typename _T>
struct Array
{
    using SortFunc = bool (*)(const _T& a, const _T& b);

    Array() : Array(Mem::GetDefaultAlloc()) {}
    explicit Array(MemAllocator* alloc) : mAlloc(alloc) {}
    explicit Array(const void* buffer, size_t size);

    void SetAllocator(MemAllocator* alloc);
    void Reserve(uint32 capacity);
    void Reserve(uint32 capacity, void* buffer, size_t size);
    void Free();
    static size_t GetMemoryRequirement(uint32 capacity);

    [[nodiscard]] _T* Push();
    _T* Push(const _T& item);
    _T* PushBatch(const _T* items, uint32 numItems);

    template <typename _Func> _T* PushAndSort(const _T& item, _Func sortFunc);

    void RemoveAndSwap(uint32 index);
    void RemoveAndShift(uint32 index);
    void RemoveRangeAndShift(uint32 index, uint32 endIndex = INVALID_INDEX);

    uint32 Count() const;
    uint32 Capacity() const;
    bool IsEmpty() const;
    void Clear();
    _T& Last();
    _T PopLast();
    _T PopFirst();
    _T Pop(uint32 index);
    void Extend(const Array<_T>& arr);
    void Extend(const _T* arr, uint32 numArrItems);
    const _T& operator[](uint32 index) const;
    _T& operator[](uint32 index);
    void Shrink();
    bool IsFull() const;
    const _T* Ptr() const;
    _T* Ptr();
    void ForceSetCount(uint32 count);
    
    void Detach(_T** outBuffer, uint32* outCount);
    Span<_T> Detach();

    void ShiftLeft(uint32 count);
    void CopyTo(Array<_T>* otherArray) const;

    uint32 Find(const _T& value);

    template <typename _Func> uint32 FindIf(_Func findFunc);
    
    struct Iterator 
    {
        Iterator(_T* ptr) : _ptr(ptr) {}
        _T& operator*() { return *_ptr; }
        void operator++() { ++_ptr; }
        bool operator!=(Iterator it) { return _ptr != it._ptr; }
        _T* _ptr;
    };

    Iterator begin()    { return Iterator(&mBuffer[0]); }
    Iterator end()      { return Iterator(&mBuffer[mCount]); }

    Iterator begin() const    { return Iterator(&mBuffer[0]); }
    Iterator end() const     { return Iterator(&mBuffer[mCount]); }

private:
    MemAllocator* mAlloc = nullptr;
    uint32 mCapacity = 0;
    uint32 mCount = 0;
    _T* mBuffer = nullptr;
};


template <typename _T, uint32 _MaxCount>
struct StaticArray
{
    _T* Push();
    _T* Push(const _T& item);

    template <typename _Func> _T* PushAndSort(const _T& item, _Func sortFunc);

    void RemoveAndSwap(uint32 index);
    uint32 Count() const;
    bool IsEmpty() const;
    bool IsFull() const;
    void Clear();
    _T& Last();
    _T PopFirst();
    _T Pop(uint32 index);
    _T& PopLast();
    const _T& operator[](uint32 index) const;
    _T& operator[](uint32 index);
    const _T* Ptr() const;
    _T* Ptr();

    uint32 Find(const _T& value);
    template <typename _Func> uint32 FindIf(_Func findFunc);

    struct Iterator 
    {
        Iterator(_T* ptr) : _ptr(ptr) {}
        _T& operator*() { return *_ptr; }
        void operator++() { ++_ptr; }
        bool operator!=(Iterator it) { return _ptr != it._ptr; }
        _T* _ptr;
    };
    
    Iterator begin()    { return Iterator(&mBuffer[0]); }
    Iterator end()      { return Iterator(&mBuffer[mCount]); }

    Iterator begin() const    { return Iterator(&mBuffer[0]); }
    Iterator end() const     { return Iterator(&mBuffer[mCount]); }

private:
    uint32 mCount = 0;
    _T mBuffer[_MaxCount];
};


template <typename _T>
inline Array<_T>::Array(const void* buffer, size_t size)
{
    mCapacity = size / sizeof(_T);
    ASSERT(mCapacity);
    mBuffer = buffer;
}

template <typename _T>
inline void Array<_T>::SetAllocator(MemAllocator* alloc)
{
    ASSERT_MSG(mBuffer == nullptr, "buffer should be freed/uninitialized before setting allocator");
    mAlloc = alloc;
}    

template <typename _T>
inline _T* Array<_T>::Push()
{
    if (mCount >= mCapacity) {
        if (mAlloc) {
            Reserve(mCapacity ? (mCapacity << 1) : 8);
        } 
        else {
            ASSERT(mBuffer);
            ASSERT_MSG(mCount < mCapacity, "Array overflow, capacity=%u", mCapacity);
            return nullptr;
        }
    }
    
    return PLACEMENT_NEW(&mBuffer[mCount++], _T) {};
}

template <typename _T>
inline _T* Array<_T>::Push(const _T& item)
{
    if (mCount >= mCapacity) {
        if (mAlloc) {
            Reserve(mCapacity ? (mCapacity << 1) : 8);
        } 
        else {
            ASSERT(mBuffer);
            ASSERT_MSG(mCount < mCapacity, "Array overflow, capacity=%u", mCapacity);
            return nullptr;
        }
    }
    
    _T* dest = &mBuffer[mCount++];
    *dest = item;
    return dest;
}

template <typename _T>
template<typename _Func> inline _T* Array<_T>::PushAndSort(const _T& item, _Func sortFunc)
{
    Push(item);
    uint32 itemIndex = mCount - 1;
    if (itemIndex) {
        for (uint32 i = itemIndex; i-- > 0;) {
            int val = sortFunc(mBuffer[itemIndex], mBuffer[i]);
            if (val >= 0)
                break;

            Swap<_T>(mBuffer[itemIndex], mBuffer[i]);
            itemIndex = i;
        }
    }

    return &mBuffer[itemIndex];    
}

template <typename _T>
inline _T* Array<_T>::PushBatch(const _T* items, uint32 numItems)
{
    ASSERT(items);
    ASSERT(numItems);

    uint32 targetCount = mCount + numItems;
    if (targetCount > mCapacity) {
        if (mAlloc) {
            Reserve(AlignValue(targetCount, 8u));
        }
        else {
            ASSERT(mBuffer);
            ASSERT_MSG(mCount < mCapacity, "Array overflow, capacity=%u", mCapacity);
            return nullptr;
        }
    }

    _T* dest = &mBuffer[mCount];
    memcpy(dest, items, sizeof(_T)*numItems);
    mCount += numItems;

    return dest;
}

template <typename _T>
inline void Array<_T>::RemoveAndSwap(uint32 index)
{
    ASSERT(mBuffer);
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif
    --mCount;
    if (index < mCount)
        Swap<_T>(mBuffer[index], mBuffer[mCount]);
}

template <typename _T>
inline void Array<_T>::RemoveAndShift(uint32 index)
{
    Pop(index);
}

template <typename _T>
inline void Array<_T>::RemoveRangeAndShift(uint32 index, uint32 endIndex)
{
    if (endIndex == INVALID_INDEX)
        endIndex = mCount;

    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT(endIndex > index);
    ASSERT(endIndex <= mCount);
    #endif

    uint32 removeCount = endIndex - index;
    for (uint32 i = 0; i < removeCount; i++) {
        uint32 start = i + index;
        uint32 end = i + endIndex;
        if (end < mCount)
            mBuffer[start] = mBuffer[end];
    }

    mCount -= removeCount;
}

template <typename _T>
inline uint32 Array<_T>::Count() const
{
    return mCount;
}

template <typename _T>
inline void Array<_T>::ForceSetCount(uint32 count)
{
    ASSERT(count <= mCapacity);
    mCount = count;
}

template <typename _T>
inline bool Array<_T>::IsEmpty() const
{
    return mCount == 0;
}

template <typename _T>
inline uint32 Array<_T>::Capacity() const
{
    return mCapacity;
}

template <typename _T>
inline void Array<_T>::Reserve(uint32 capacity)
{
    ASSERT(mAlloc);
    if (capacity > mCapacity) {
        mCapacity = Max(capacity, 8u);
        mBuffer = Mem::ReallocTyped<_T>(mBuffer, mCapacity, mAlloc);
        ASSERT(mBuffer);
    }
}

template <typename _T>
inline void Array<_T>::Reserve(uint32 capacity, void* buffer, [[maybe_unused]] size_t size)
{
    capacity = Max(capacity, 8u);

    ASSERT(buffer);
    ASSERT_MSG(mBuffer == nullptr, "Array should not be initialized before reserve by pointer");
    ASSERT_MSG(size >= capacity*sizeof(_T), "Buffer should have at least %u bytes long (size=%u)", capacity*sizeof(_T), size);
    
    mAlloc = nullptr;
    mCapacity = capacity;
    mBuffer = (_T*)buffer;
}    

template <typename _T>
inline void Array<_T>::Clear()
{
    mCount = 0;
}

template <typename _T>
inline _T& Array<_T>::Last()
{
    ASSERT(mCount > 0);
    return mBuffer[mCount - 1];
}

template <typename _T>
inline _T Array<_T>::PopLast()
{
    ASSERT(mCount > 0);
    return mBuffer[--mCount];
}

template <typename _T>
inline _T Array<_T>::PopFirst()
{
    return Pop(0);
}

template <typename _T>
inline _T Array<_T>::Pop(uint32 index)
{
    ASSERT(mCount > 0);
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif

    _T item = mBuffer[index];
    for (uint32 i = index+1, c = mCount; i < c; i++)
        mBuffer[i-1] = mBuffer[i];
    --mCount;
    return item;
}

template <typename _T>
inline void Array<_T>::Extend(const Array<_T>& arr)
{
    if (arr.Count()) {
        uint32 newCount = mCount + arr.mCount;
        uint32 newCapacity = Max(newCount, Min(mCapacity, arr.mCapacity));
        if (newCapacity > mCapacity)
            Reserve(newCapacity);
        memcpy(&mBuffer[mCount], arr.mBuffer, sizeof(_T)*arr.mCount);
        mCount = newCount;
    }
}

template <typename _T>
inline void Array<_T>::Extend(const _T* arr, uint32 numArrItems)
{
    if (numArrItems) {
        uint32 newCount = mCount + numArrItems;
        uint32 newCapacity = Max(newCount, mCapacity);
        if (newCapacity > mCapacity)
            Reserve(newCapacity);
        memcpy(&mBuffer[mCount], arr, sizeof(_T)*numArrItems);
        mCount = newCount;
    }
}

template <typename _T>
inline void Array<_T>::ShiftLeft(uint32 count)
{
    ASSERT(count <= mCount);
    
    mCount -= count;
    if (mCount)
        memmove(mBuffer, mBuffer + sizeof(_T)*count, sizeof(_T)*mCount);
}

template <typename _T>
inline void Array<_T>::CopyTo(Array<_T>* otherArray) const
{
    ASSERT(otherArray);

    if (mCapacity)
        otherArray->Reserve(mCapacity);

    if (mCount) {
        otherArray->mCount = mCount;
        memcpy(otherArray->mBuffer, mBuffer, sizeof(_T)*mCount);
    }
}

template <typename _T>
inline const _T& Array<_T>::operator[](uint32 index) const
{
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif
    return mBuffer[index];
}

template <typename _T>
inline _T& Array<_T>::operator[](uint32 index)
{
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif
    return mBuffer[index];
}

template <typename _T>
inline const _T* Array<_T>::Ptr() const
{
    return mBuffer;
}

template <typename _T>
inline _T* Array<_T>::Ptr()
{
    return mBuffer;
}

template <typename _T>
inline void Array<_T>::Detach(_T** outBuffer, uint32* outCount)
{
    ASSERT(outBuffer);
    ASSERT(outCount);

    *outBuffer = mBuffer;
    *outCount = mCount;

    mBuffer = nullptr;
    mCount = 0;
    mCapacity = 0;
}

template <typename _T>
inline Span<_T> Array<_T>::Detach()
{
    _T* ptr;
    uint32 count;

    Detach(&ptr, &count);
    return Span<_T>(ptr, count);
}

template<typename _T>
inline bool Array<_T>::IsFull() const
{
    return mCount >= mCapacity;
}    

template <typename _T>
inline void Array<_T>::Free()
{
    if (mAlloc)
        Mem::Free(mBuffer, mAlloc);

    mCount = 0;
    mCapacity = 0;
    mBuffer = nullptr;
}

template <typename _T>
inline void Array<_T>::Shrink()
{
    ASSERT(mAlloc);
    mCapacity = Max(mCount, 8u);
    Reserve(mCapacity);
}

template <typename _T> 
inline uint32 Array<_T>::Find(const _T& value)
{
    for (uint32 i = 0; i < mCount; i++) {
        if (mBuffer[i] == value)
            return i;
    }

    return UINT32_MAX;
}

template<typename _T>
template<typename _Func> inline uint32 Array<_T>::FindIf(_Func findFunc)
{
    for (uint32 i = 0, c = mCount; i < c; i++) {
        if (findFunc(mBuffer[i]))
            return i;
    }

    return UINT32_MAX;
}

template<typename _T>
inline size_t Array<_T>::GetMemoryRequirement(uint32 capacity)
{
    capacity = Max(capacity, 8u);
    return capacity * sizeof(_T);
}

template<typename _T, uint32 _MaxCount>
inline _T* StaticArray<_T, _MaxCount>::Push()
{
    ASSERT_MSG(mCount < _MaxCount, "Trying to add more than _MaxCount=%u", _MaxCount);
    return &mBuffer[mCount++];
}

template<typename _T, uint32 _MaxCount>
inline _T* StaticArray<_T, _MaxCount>::Push(const _T& item)
{
    ASSERT_MSG(mCount < _MaxCount, "Trying to add more than _MaxCount=%u", _MaxCount);
    uint32 index = mCount++;
    mBuffer[index] = item;
    return &mBuffer[index];
}

template <typename _T, uint32 _MaxCount>
template<typename _Func> inline _T* StaticArray<_T, _MaxCount>::PushAndSort(const _T& item, _Func sortFunc)
{
    Push(item);
    uint32 itemIndex = mCount - 1;
    if (itemIndex) {
        for (uint32 i = itemIndex; i-- > 0;) {
            int val = sortFunc(mBuffer[itemIndex], mBuffer[i]);
            if (val >= 0)
                break;

            Swap<_T>(mBuffer[itemIndex], mBuffer[i]);
            itemIndex = i;
        }
    }

    return &mBuffer[itemIndex];    
}


template<typename _T, uint32 _MaxCount>
inline void StaticArray<_T, _MaxCount>::RemoveAndSwap(uint32 index)
{
    ASSERT(mBuffer);
#ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index <= mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
#endif
    Swap<_T>(mBuffer[index], mBuffer[--mCount]);
}

template<typename _T, uint32 _MaxCount>
inline uint32 StaticArray<_T, _MaxCount>::Count() const
{
    return mCount;
}

template<typename _T, uint32 _MaxCount>
inline bool StaticArray<_T, _MaxCount>::IsEmpty() const
{
    return mCount == 0;
}

template<typename _T, uint32 _MaxCount>
inline bool StaticArray<_T, _MaxCount>::IsFull() const
{
    return mCount == _MaxCount;
}

template<typename _T, uint32 _MaxCount>
inline void StaticArray<_T, _MaxCount>::Clear()
{
    mCount = 0;
}

template<typename _T, uint32 _MaxCount>
inline _T& StaticArray<_T, _MaxCount>::Last()
{
    ASSERT(mCount > 0);
    return mBuffer[mCount - 1];
}

template <typename _T, uint32 _MaxCount>
inline _T StaticArray<_T, _MaxCount>::Pop(uint32 index)
{
    ASSERT(mCount > 0);
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index < mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif

    _T item = mBuffer[index];
    for (uint32 i = index+1, c = mCount; i < c; i++)
        mBuffer[i-1] = mBuffer[i];
    --mCount;
    return item;
}

template <typename _T, uint32 _MaxCount>
inline _T StaticArray<_T, _MaxCount>::PopFirst()
{
    Pop(0);
}

template<typename _T, uint32 _MaxCount>
inline _T& StaticArray<_T, _MaxCount>::PopLast()
{
    ASSERT(mCount > 0);
    return mBuffer[--mCount];
}

template<typename _T, uint32 _MaxCount>
inline const _T& StaticArray<_T, _MaxCount>::operator[](uint32 index) const
{
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index <= mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif
    return mBuffer[index];
}

template<typename _T, uint32 _MaxCount>
inline _T& StaticArray<_T, _MaxCount>::operator[](uint32 index)
{
    #ifdef CONFIG_CHECK_OUTOFBOUNDS
    ASSERT_MSG(index <= mCount, "Index out of bounds (count: %u, index: %u)", mCount, index);
    #endif
    return mBuffer[index];
}

template<typename _T, uint32 _MaxCount>
inline const _T* StaticArray<_T, _MaxCount>::Ptr() const
{
    return reinterpret_cast<const _T*>(mBuffer);
}

template<typename _T, uint32 _MaxCount>
inline _T* StaticArray<_T, _MaxCount>::Ptr()
{
    return reinterpret_cast<_T*>(mBuffer);
}

template <typename _T, uint32 _MaxCount> 
inline uint32 StaticArray<_T, _MaxCount>::Find(const _T& value)
{
    for (uint32 i = 0; i < mCount; i++) {
        if (mBuffer[i] == value)
            return i;
    }
    return UINT32_MAX;
}

template <typename _T, uint32 _MaxCount>
template <typename _Func> inline uint32 StaticArray<_T, _MaxCount>::FindIf(_Func findFunc)
{
    for (uint32 i = 0, c = mCount; i < c; i++) {
        if (findFunc(mBuffer[i])) {
            return i;
        }
    }
    
    return UINT32_MAX;
}






//----------------------------------------------------------------------------------------------------------------------
// External/c89atomic/c89atomic.h

/*
C89 compatible atomics. Choice of public domain or MIT-0. See license statements at the end of this file.

David Reid - mackron@gmail.com
*/

/*
Introduction
============
This library aims to implement an equivalent to the C11 atomics library. It's intended to be used as a way to
enable the use of atomics in a mostly consistent manner to modern C, while still enabling compatibility with
older compilers. This is *not* a drop-in replacement for C11 atomics, but is very similar. Only limited testing
has been done so use at your own risk. I'm happy to accept feedback and pull requests with bug fixes.

When compiling with GCC and Clang, this library will translate to a one-to-one wrapper around the __atomic_*
intrinsics provided by the compiler.

When compiling with Visual C++ things are a bit more complicated because it does not have support for C11 style
atomic intrinsics. This library will try to use the _Interlocked* intrinsics instead, and if unavailable will
use inlined assembly (x86 only).

Supported compilers are Visual Studio back to VC6, GCC and Clang. If you need support for a different compiler
I'm happy to add support (pull requests appreciated). This library currently assumes the `int` data type is
32 bits.


Differences With C11
--------------------
For practicality, this is not a drop-in replacement for C11's `stdatomic.h`. Below are the main differences
between c89atomic and stdatomic.

    * All operations require an explicit size which is specified by the name of the function, and only 8-,
      16-, 32- and 64-bit operations are supported. Objects of an arbitrary sizes are not supported.
    * Some extra APIs are included:
      - `c89atomic_compare_and_swap_*()`
      - `c89atomic_test_and_set_*()`
      - `c89atomic_clear_*()`
    * All APIs are namespaced with `c89`.
    * `c89atomic_*` data types are undecorated.


Compare Exchange
----------------
This library implements a simple compare-and-swap function called `c89atomic_compare_and_swap_*()` which is
slightly different to C11's `atomic_compare_exchange_*()`. This is named differently to distinguish between
the two. `c89atomic_compare_and_swap_*()` returns the old value as the return value, whereas
`atomic_compare_exchange_*()` will return it through a parameter and supports explicit memory orders for
success and failure cases.

With Visual Studio and versions of GCC earlier than 4.7, an implementation of `atomic_compare_exchange_*()`
is included which is implemented in terms of `c89atomic_compare_and_swap_*()`, but there's subtle details to be
aware of with this implementation. Note that the following only applies for Visual Studio and versions of GCC
earlier than 4.7. Later versions of GCC and Clang use the `__atomic_compare_exchange_n()` intrinsic directly
and are not subject to the following.

Below is the 32-bit implementation of `c89atomic_compare_exchange_strong_explicit_32()` which is implemented
the same for the weak versions and other sizes, and only for Visual Studio and old versions of GCC (prior to
4.7):

```c
c89atomic_bool c89atomic_compare_exchange_strong_explicit_32(volatile c89atomic_uint32* dst,
                                                             volatile c89atomic_uint32* expected,
                                                             c89atomic_uint32 desired,
                                                             c89atomic_memory_order successOrder,
                                                             c89atomic_memory_order failureOrder)
{
    c89atomic_uint32 expectedValue;
    c89atomic_uint32 result;

    expectedValue = c89atomic_load_explicit_32(expected, c89atomic_memory_order_seq_cst);
    result = c89atomic_compare_and_swap_32(dst, expectedValue, desired);
    if (result == expectedValue) {
        return 1;
    } else {
        c89atomic_store_explicit_32(expected, result, failureOrder);
        return 0;
    }
}
```

The call to `c89atomic_store_explicit_32()` is not atomic with respect to the main compare-and-swap operation
which may cause problems when `expected` points to memory that is shared between threads. This only becomes an
issue if `expected` can be accessed from multiple threads at the same time which for the most part will never
happen because a compare-and-swap will almost always be used in a loop with a local variable being used for the
expected value.

If the above is a concern, you should consider reworking your code to use `c89atomic_compare_and_swap_*()`
directly, which is atomic and more efficient. Alternatively you'll need to use a lock to synchronize access
to `expected`, upgrade your compiler, or use a different library.


Types and Functions
-------------------
The following types and functions are implemented:

+-----------------------------------------+-----------------------------------------------+
| C11 Atomics                             | C89 Atomics                                   |
+-----------------------------------------+-----------------------------------------------+
| #include <stdatomic.h>                  | #include "c89atomic.h"                        |
+-----------------------------------------+-----------------------------------------------+
| memory_order                            | c89atomic_memory_order                        |
|     memory_order_relaxed                |     c89atomic_memory_order_relaxed            |
|     memory_order_consume                |     c89atomic_memory_order_consume            |
|     memory_order_acquire                |     c89atomic_memory_order_acquire            |
|     memory_order_release                |     c89atomic_memory_order_release            |
|     memory_order_acq_rel                |     c89atomic_memory_order_acq_rel            |
|     memory_order_seq_cst                |     c89atomic_memory_order_seq_cst            |
+-----------------------------------------+-----------------------------------------------+
| atomic_flag                             | c89atomic_flag                                |
| atomic_bool                             | c89atomic_bool                                |
| atomic_int8                             | c89atomic_int8                                |
| atomic_uint8                            | c89atomic_uint8                               |
| atomic_int16                            | c89atomic_int16                               |
| atomic_uint16                           | c89atomic_uint16                              |
| atomic_int32                            | c89atomic_int32                               |
| atomic_uint32                           | c89atomic_uint32                              |
| atomic_int64                            | c89atomic_int64                               |
| atomic_uint64                           | c89atomic_uint64                              |
+-----------------------------------------+-----------------------------------------------+
| atomic_flag_test_and_set                | c89atomic_flag_test_and_set                   |
| atomic_flag_test_and_set_explicit       | c89atomic_flag_test_and_set_explicit          |
|                                         | c89atomic_test_and_set_8                      |
|                                         | c89atomic_test_and_set_16                     |
|                                         | c89atomic_test_and_set_32                     |
|                                         | c89atomic_test_and_set_64                     |
|                                         | c89atomic_test_and_set_explicit_8             |
|                                         | c89atomic_test_and_set_explicit_16            |
|                                         | c89atomic_test_and_set_explicit_32            |
|                                         | c89atomic_test_and_set_explicit_64            |
+-----------------------------------------+-----------------------------------------------+
| atomic_flag_clear                       | c89atomic_flag_clear                          |
| atomic_flag_clear_explicit              | c89atomic_flag_clear_explicit                 |
|                                         | c89atomic_clear_8                             |
|                                         | c89atomic_clear_16                            |
|                                         | c89atomic_clear_32                            |
|                                         | c89atomic_clear_64                            |
|                                         | c89atomic_clear_explicit_8                    |
|                                         | c89atomic_clear_explicit_16                   |
|                                         | c89atomic_clear_explicit_32                   |
|                                         | c89atomic_clear_explicit_64                   |
+-----------------------------------------+-----------------------------------------------+
| atomic_store                            | c89atomic_store_8                             |
| atomic_store_explicit                   | c89atomic_store_16                            |
|                                         | c89atomic_store_32                            |
|                                         | c89atomic_store_64                            |
|                                         | c89atomic_store_explicit_8                    |
|                                         | c89atomic_store_explicit_16                   |
|                                         | c89atomic_store_explicit_32                   |
|                                         | c89atomic_store_explicit_64                   |
+-----------------------------------------+-----------------------------------------------+
| atomic_load                             | c89atomic_load_8                              |
| atomic_load_explicit                    | c89atomic_load_16                             |
|                                         | c89atomic_load_32                             |
|                                         | c89atomic_load_64                             |
|                                         | c89atomic_load_explicit_8                     |
|                                         | c89atomic_load_explicit_16                    |
|                                         | c89atomic_load_explicit_32                    |
|                                         | c89atomic_load_explicit_64                    |
+-----------------------------------------+-----------------------------------------------+
| atomic_exchange                         | c89atomic_exchange_8                          |
| atomic_exchange_explicit                | c89atomic_exchange_16                         |
|                                         | c89atomic_exchange_32                         |
|                                         | c89atomic_exchange_64                         |
|                                         | c89atomic_exchange_explicit_8                 |
|                                         | c89atomic_exchange_explicit_16                |
|                                         | c89atomic_exchange_explicit_32                |
|                                         | c89atomic_exchange_explicit_64                |
+-----------------------------------------+-----------------------------------------------+
| atomic_compare_exchange_weak            | c89atomic_compare_exchange_weak_8             |
| atomic_compare_exchange_weak_explicit   | c89atomic_compare_exchange_weak_16            |
| atomic_compare_exchange_strong          | c89atomic_compare_exchange_weak_32            |
| atomic_compare_exchange_strong_explicit | c89atomic_compare_exchange_weak_64            |
|                                         | c89atomic_compare_exchange_weak_explicit_8    |
|                                         | c89atomic_compare_exchange_weak_explicit_16   |
|                                         | c89atomic_compare_exchange_weak_explicit_32   |
|                                         | c89atomic_compare_exchange_weak_explicit_64   |
|                                         | c89atomic_compare_exchange_strong_8           |
|                                         | c89atomic_compare_exchange_strong_16          |
|                                         | c89atomic_compare_exchange_strong_32          |
|                                         | c89atomic_compare_exchange_strong_64          |
|                                         | c89atomic_compare_exchange_strong_explicit_8  |
|                                         | c89atomic_compare_exchange_strong_explicit_16 |
|                                         | c89atomic_compare_exchange_strong_explicit_32 |
|                                         | c89atomic_compare_exchange_strong_explicit_64 |
+-----------------------------------------+-----------------------------------------------+
| atomic_fetch_add                        | c89atomic_fetch_add_8                         |
| atomic_fetch_add_explicit               | c89atomic_fetch_add_16                        |
|                                         | c89atomic_fetch_add_32                        |
|                                         | c89atomic_fetch_add_64                        |
|                                         | c89atomic_fetch_add_explicit_8                |
|                                         | c89atomic_fetch_add_explicit_16               |
|                                         | c89atomic_fetch_add_explicit_32               |
|                                         | c89atomic_fetch_add_explicit_64               |
+-----------------------------------------+-----------------------------------------------+
| atomic_fetch_sub                        | c89atomic_fetch_sub_8                         |
| atomic_fetch_sub_explicit               | c89atomic_fetch_sub_16                        |
|                                         | c89atomic_fetch_sub_32                        |
|                                         | c89atomic_fetch_sub_64                        |
|                                         | c89atomic_fetch_sub_explicit_8                |
|                                         | c89atomic_fetch_sub_explicit_16               |
|                                         | c89atomic_fetch_sub_explicit_32               |
|                                         | c89atomic_fetch_sub_explicit_64               |
+-----------------------------------------+-----------------------------------------------+
| atomic_fetch_or                         | c89atomic_fetch_or_8                          |
| atomic_fetch_or_explicit                | c89atomic_fetch_or_16                         |
|                                         | c89atomic_fetch_or_32                         |
|                                         | c89atomic_fetch_or_64                         |
|                                         | c89atomic_fetch_or_explicit_8                 |
|                                         | c89atomic_fetch_or_explicit_16                |
|                                         | c89atomic_fetch_or_explicit_32                |
|                                         | c89atomic_fetch_or_explicit_64                |
+-----------------------------------------+-----------------------------------------------+
| atomic_fetch_xor                        | c89atomic_fetch_xor_8                         |
| atomic_fetch_xor_explicit               | c89atomic_fetch_xor_16                        |
|                                         | c89atomic_fetch_xor_32                        |
|                                         | c89atomic_fetch_xor_64                        |
|                                         | c89atomic_fetch_xor_explicit_8                |
|                                         | c89atomic_fetch_xor_explicit_16               |
|                                         | c89atomic_fetch_xor_explicit_32               |
|                                         | c89atomic_fetch_xor_explicit_64               |
+-----------------------------------------+-----------------------------------------------+
| atomic_fetch_and                        | c89atomic_fetch_and_8                         |
| atomic_fetch_and_explicit               | c89atomic_fetch_and_16                        |
|                                         | c89atomic_fetch_and_32                        |
|                                         | c89atomic_fetch_and_64                        |
|                                         | c89atomic_fetch_and_explicit_8                |
|                                         | c89atomic_fetch_and_explicit_16               |
|                                         | c89atomic_fetch_and_explicit_32               |
|                                         | c89atomic_fetch_and_explicit_64               |
+-----------------------------------------+-----------------------------------------------+
| atomic_thread_fence()                   | c89atomic_thread_fence                        |
| atomic_signal_fence()                   | c89atomic_signal_fence                        |
+-----------------------------------------+-----------------------------------------------+
| atomic_is_lock_free                     | c89atomic_is_lock_free_8                      |
|                                         | c89atomic_is_lock_free_16                     |
|                                         | c89atomic_is_lock_free_32                     |
|                                         | c89atomic_is_lock_free_64                     |
+-----------------------------------------+-----------------------------------------------+
| (Not Defined)                           | c89atomic_compare_and_swap_8                  |
|                                         | c89atomic_compare_and_swap_16                 |
|                                         | c89atomic_compare_and_swap_32                 |
|                                         | c89atomic_compare_and_swap_64                 |
|                                         | c89atomic_compare_and_swap_ptr                |
|                                         | c89atomic_compiler_fence                      |
+-----------------------------------------+-----------------------------------------------+
*/

#ifndef c89atomic_h
#define c89atomic_h

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wlong-long"
    #if defined(__clang__)
        #pragma GCC diagnostic ignored "-Wc++11-long-long"
    #endif
#endif

typedef   signed char           c89atomic_int8;
typedef unsigned char           c89atomic_uint8;
typedef   signed short          c89atomic_int16;
typedef unsigned short          c89atomic_uint16;
typedef   signed int            c89atomic_int32;
typedef unsigned int            c89atomic_uint32;
#if defined(_MSC_VER) && !defined(__clang__)
    typedef   signed __int64    c89atomic_int64;
    typedef unsigned __int64    c89atomic_uint64;
#else
    typedef   signed long long  c89atomic_int64;
    typedef unsigned long long  c89atomic_uint64;
#endif

typedef int                     c89atomic_memory_order;
typedef unsigned char           c89atomic_bool;

/* Architecture Detection */
#if !defined(C89ATOMIC_64BIT) && !defined(C89ATOMIC_32BIT)
#ifdef _WIN32
#ifdef _WIN64
#define C89ATOMIC_64BIT
#else
#define C89ATOMIC_32BIT
#endif
#endif
#endif

#if !defined(C89ATOMIC_64BIT) && !defined(C89ATOMIC_32BIT)
#ifdef __GNUC__
#ifdef __LP64__
#define C89ATOMIC_64BIT
#else
#define C89ATOMIC_32BIT
#endif
#endif
#endif

#if !defined(C89ATOMIC_64BIT) && !defined(C89ATOMIC_32BIT)
#include <stdint.h>
#if INTPTR_MAX == INT64_MAX
#define C89ATOMIC_64BIT
#else
#define C89ATOMIC_32BIT
#endif
#endif

#if defined(__arm__) || defined(_M_ARM)
#define C89ATOMIC_ARM32
#endif
#if defined(__arm64) || defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM64)
#define C89ATOMIC_ARM64
#endif

#if defined(__x86_64__) || defined(_M_X64)
#define C89ATOMIC_X64
#elif defined(__i386) || defined(_M_IX86)
#define C89ATOMIC_X86
#elif defined(C89ATOMIC_ARM32) || defined(C89ATOMIC_ARM64)
#define C89ATOMIC_ARM
#endif

/* We want to encourage the compiler to inline. When adding support for a new compiler, make sure it's handled here. */
#if defined(_MSC_VER)
    #define C89ATOMIC_INLINE __forceinline
#elif defined(__GNUC__)
    /*
    I've had a bug report where GCC is emitting warnings about functions possibly not being inlineable. This warning happens when
    the __attribute__((always_inline)) attribute is defined without an "inline" statement. I think therefore there must be some
    case where "__inline__" is not always defined, thus the compiler emitting these warnings. When using -std=c89 or -ansi on the
    command line, we cannot use the "inline" keyword and instead need to use "__inline__". In an attempt to work around this issue
    I am using "__inline__" only when we're compiling in strict ANSI mode.
    */
    #if defined(__STRICT_ANSI__)
        #define C89ATOMIC_INLINE __inline__ __attribute__((always_inline))
    #else
        #define C89ATOMIC_INLINE inline __attribute__((always_inline))
    #endif
#elif defined(__WATCOMC__) || defined(__DMC__)
    #define C89ATOMIC_INLINE __inline
#else
    #define C89ATOMIC_INLINE
#endif

/* Assume everything supports all standard sized atomics by default. We'll #undef these when not supported. */
#define C89ATOMIC_HAS_8
#define C89ATOMIC_HAS_16
#define C89ATOMIC_HAS_32
#define C89ATOMIC_HAS_64

#if (defined(_MSC_VER) /*&& !defined(__clang__)*/) || defined(__WATCOMC__) || defined(__DMC__)
    /* Visual C++. */
    #define C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, intrin, c89atomicType, msvcType)   \
        c89atomicType result; \
        switch (order) \
        { \
            case c89atomic_memory_order_relaxed: \
            { \
                result = (c89atomicType)intrin##_nf((volatile msvcType*)dst, (msvcType)src); \
            } break; \
            case c89atomic_memory_order_consume: \
            case c89atomic_memory_order_acquire: \
            { \
                result = (c89atomicType)intrin##_acq((volatile msvcType*)dst, (msvcType)src); \
            } break; \
            case c89atomic_memory_order_release: \
            { \
                result = (c89atomicType)intrin##_rel((volatile msvcType*)dst, (msvcType)src); \
            } break; \
            case c89atomic_memory_order_acq_rel: \
            case c89atomic_memory_order_seq_cst: \
            default: \
            { \
                result = (c89atomicType)intrin((volatile msvcType*)dst, (msvcType)src); \
            } break; \
        } \
        return result;

    #define C89ATOMIC_MSVC_ARM_INTRINSIC_COMPARE_EXCHANGE(ptr, expected, desired, order, intrin, c89atomicType, msvcType)   \
        c89atomicType result; \
        switch (order) \
        { \
            case c89atomic_memory_order_relaxed: \
            { \
                result = (c89atomicType)intrin##_nf((volatile msvcType*)ptr, (msvcType)expected, (msvcType)desired); \
            } break; \
            case c89atomic_memory_order_consume: \
            case c89atomic_memory_order_acquire: \
            { \
                result = (c89atomicType)intrin##_acq((volatile msvcType*)ptr, (msvcType)expected, (msvcType)desired); \
            } break; \
            case c89atomic_memory_order_release: \
            { \
                result = (c89atomicType)intrin##_rel((volatile msvcType*)ptr, (msvcType)expected, (msvcType)desired); \
            } break; \
            case c89atomic_memory_order_acq_rel: \
            case c89atomic_memory_order_seq_cst: \
            default: \
            { \
                result = (c89atomicType)intrin((volatile msvcType*)ptr, (msvcType)expected, (msvcType)desired); \
            } break; \
        } \
        return result;

    #define c89atomic_memory_order_relaxed  0
    #define c89atomic_memory_order_consume  1
    #define c89atomic_memory_order_acquire  2
    #define c89atomic_memory_order_release  3
    #define c89atomic_memory_order_acq_rel  4
    #define c89atomic_memory_order_seq_cst  5

    /*
    Visual Studio 2003 (_MSC_VER 1300) and earlier have no support for sized atomic operations.
    We'll need to use inlined assembly for these compilers.

    I've also had a report that 8-bit and 16-bit interlocked intrinsics were only added in Visual
    Studio 2010 (_MSC_VER 1600). We'll need to disable these on the 64-bit build because there's
    no way to implement them with inlined assembly since Microsoft has decided to drop support for
    it from their 64-bit compilers.

    To simplify the implementation, any older MSVC compilers targeting 32-bit will use inlined
    assembly for everything. I'm not going to use inlined assembly wholesale for all 32-bit builds
    regardless of the age of the compiler because I don't trust the compiler will optimize the
    inlined assembly properly.

    The inlined assembly path supports both MSVC, Digital Mars and OpenWatcom. OpenWatcom is a little
    bit too pedantic with it's warnings. A few notes:
      - The return value of these functions are defined by the AL/AX/EAX/EAX:EDX registers which
        means an explicit return statement is not actually necessary. This is helpful for performance
        reasons because it means we can avoid the cost of a declaring a local variable and moving the
        value in EAX into that variable, only to then return it. However, unfortunately OpenWatcom
        thinks this is a mistake and tries to be helpful by throwing a warning. To work around we're
        going to declare a "result" variable and incur this theoretical cost. Most likely the
        compiler will optimize this away and make it a non-issue.
      - Variables that are assigned within the inline assembly will not be detected as such, and
        OpenWatcom will throw a warning about the variable being used without being assigned. To work
        around this we just initialize our local variables to 0.
    */
    #if _MSC_VER < 1600 && defined(C89ATOMIC_X86)   /* 1600 = Visual Studio 2010 */
        #define C89ATOMIC_MSVC_USE_INLINED_ASSEMBLY
    #endif
    #if _MSC_VER < 1600
        #undef C89ATOMIC_HAS_8
        #undef C89ATOMIC_HAS_16
    #endif

    /* We need <intrin.h>, but only if we're not using inlined assembly. */
    #if !defined(C89ATOMIC_MSVC_USE_INLINED_ASSEMBLY)
        #include <intrin.h>
    #endif

    /* atomic_compare_and_swap */
    #if defined(C89ATOMIC_MSVC_USE_INLINED_ASSEMBLY)
        #if defined(C89ATOMIC_HAS_8)
            static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_compare_and_swap_8(volatile c89atomic_uint8* dst, c89atomic_uint8 expected, c89atomic_uint8 desired)
            {
                c89atomic_uint8 result = 0;
                
                __asm {
                    mov ecx, dst
                    mov al,  expected
                    mov dl,  desired
                    lock cmpxchg [ecx], dl  /* Writes to EAX which MSVC will treat as the return value. */
                    mov result, al
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_16)
            static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_compare_and_swap_16(volatile c89atomic_uint16* dst, c89atomic_uint16 expected, c89atomic_uint16 desired)
            {
                c89atomic_uint16 result = 0;
                
                __asm {
                    mov ecx, dst
                    mov ax,  expected
                    mov dx,  desired
                    lock cmpxchg [ecx], dx  /* Writes to EAX which MSVC will treat as the return value. */
                    mov result, ax
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_32)
            static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_compare_and_swap_32(volatile c89atomic_uint32* dst, c89atomic_uint32 expected, c89atomic_uint32 desired)
            {
                c89atomic_uint32 result = 0;
                
                __asm {
                    mov ecx, dst
                    mov eax, expected
                    mov edx, desired
                    lock cmpxchg [ecx], edx /* Writes to EAX which MSVC will treat as the return value. */
                    mov result, eax
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_64)
            static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_compare_and_swap_64(volatile c89atomic_uint64* dst, c89atomic_uint64 expected, c89atomic_uint64 desired)
            {
                c89atomic_uint32 resultEAX = 0;
                c89atomic_uint32 resultEDX = 0;
                
                __asm {
                    mov esi, dst    /* From Microsoft documentation: "... you don't need to preserve the EAX, EBX, ECX, EDX, ESI, or EDI registers." Choosing ESI since it's the next available one in their list. */
                    mov eax, dword ptr expected
                    mov edx, dword ptr expected + 4
                    mov ebx, dword ptr desired
                    mov ecx, dword ptr desired + 4
                    lock cmpxchg8b qword ptr [esi]  /* Writes to EAX:EDX which MSVC will treat as the return value. */
                    mov resultEAX, eax
                    mov resultEDX, edx
                }

                return ((c89atomic_uint64)resultEDX << 32) | resultEAX;
            }
        #endif
    #else
        #if defined(C89ATOMIC_HAS_8)
            #define c89atomic_compare_and_swap_8( dst, expected, desired) (c89atomic_uint8 )_InterlockedCompareExchange8((volatile char*)dst, (char)desired, (char)expected)
        #endif
        #if defined(C89ATOMIC_HAS_16)
            #define c89atomic_compare_and_swap_16(dst, expected, desired) (c89atomic_uint16)_InterlockedCompareExchange16((volatile short*)dst, (short)desired, (short)expected)
        #endif
        #if defined(C89ATOMIC_HAS_32)
            #define c89atomic_compare_and_swap_32(dst, expected, desired) (c89atomic_uint32)_InterlockedCompareExchange((volatile long*)dst, (long)desired, (long)expected)
        #endif
        #if defined(C89ATOMIC_HAS_64)
            #define c89atomic_compare_and_swap_64(dst, expected, desired) (c89atomic_uint64)_InterlockedCompareExchange64((volatile c89atomic_int64*)dst, (c89atomic_int64)desired, (c89atomic_int64)expected)
        #endif
    #endif


    /* atomic_exchange_explicit */
    #if defined(C89ATOMIC_MSVC_USE_INLINED_ASSEMBLY)
        #if defined(C89ATOMIC_HAS_8)
            static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_exchange_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
            {
                c89atomic_uint8 result = 0;
                
                (void)order;
                __asm {
                    mov ecx, dst
                    mov al,  src
                    lock xchg [ecx], al
                    mov result, al
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_16)
            static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_exchange_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
            {
                c89atomic_uint16 result = 0;
                
                (void)order;
                __asm {
                    mov ecx, dst
                    mov ax,  src
                    lock xchg [ecx], ax
                    mov result, ax
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_32)
            static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_exchange_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
            {
                c89atomic_uint32 result = 0;
                
                (void)order;
                __asm {
                    mov ecx, dst
                    mov eax, src
                    lock xchg [ecx], eax
                    mov result, eax
                }

                return result;
            }
        #endif
    #else
        #if defined(C89ATOMIC_HAS_8)
            static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_exchange_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchange8, c89atomic_uint8, char);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint8)_InterlockedExchange8((volatile char*)dst, (char)src);
            #endif
            }
        #endif
        #if defined(C89ATOMIC_HAS_16)
            static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_exchange_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchange16, c89atomic_uint16, short);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint16)_InterlockedExchange16((volatile short*)dst, (short)src);
            #endif
            }
        #endif
        #if defined(C89ATOMIC_HAS_32)
            static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_exchange_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchange, c89atomic_uint32, long);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint32)_InterlockedExchange((volatile long*)dst, (long)src);
            #endif
            }
        #endif
        #if defined(C89ATOMIC_HAS_64) && defined(C89ATOMIC_64BIT)
            static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_exchange_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchange64, c89atomic_uint64, long long);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint64)_InterlockedExchange64((volatile long long*)dst, (long long)src);
            #endif
            }
        #else
            /* Implemented below. */
        #endif
    #endif
    #if defined(C89ATOMIC_HAS_64) && !defined(C89ATOMIC_64BIT)   /* atomic_exchange_explicit_64() must be implemented in terms of atomic_compare_and_swap() on 32-bit builds, no matter the version of Visual Studio. */
        static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_exchange_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
        
            do {
                oldValue = *dst;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, src) != oldValue);
        
            (void)order;    /* Always using the strongest memory order. */
            return oldValue;
        }
    #endif


    /* atomic_fetch_add */
    #if defined(C89ATOMIC_MSVC_USE_INLINED_ASSEMBLY)
        #if defined(C89ATOMIC_HAS_8)
            static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_fetch_add_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
            {
                c89atomic_uint8 result = 0;
                
                (void)order;
                __asm {
                    mov ecx, dst
                    mov al,  src
                    lock xadd [ecx], al
                    mov result, al
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_16)
            static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_fetch_add_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
            {
                c89atomic_uint16 result = 0;
                
                (void)order;
                __asm {
                    mov ecx, dst
                    mov ax,  src
                    lock xadd [ecx], ax
                    mov result, ax
                }

                return result;
            }
        #endif
        #if defined(C89ATOMIC_HAS_32)
            static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_fetch_add_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
            {
                c89atomic_uint32 result = 0;
                
                (void)order;
                __asm {
                    mov ecx, dst
                    mov eax, src
                    lock xadd [ecx], eax
                    mov result, eax
                }

                return result;
            }
        #endif
    #else
        #if defined(C89ATOMIC_HAS_8)
            static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_fetch_add_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchangeAdd8, c89atomic_uint8, char);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint8)_InterlockedExchangeAdd8((volatile char*)dst, (char)src);
            #endif
            }
        #endif
        #if defined(C89ATOMIC_HAS_16)
            static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_fetch_add_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchangeAdd16, c89atomic_uint16, short);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint16)_InterlockedExchangeAdd16((volatile short*)dst, (short)src);
            #endif
            }
        #endif
        #if defined(C89ATOMIC_HAS_32)
            static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_fetch_add_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchangeAdd, c89atomic_uint32, long);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint32)_InterlockedExchangeAdd((volatile long*)dst, (long)src);
            #endif
            }
        #endif
        #if defined(C89ATOMIC_HAS_64) && defined(C89ATOMIC_64BIT)
            static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_fetch_add_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
            {
            #if defined(C89ATOMIC_ARM)
                C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedExchangeAdd64, c89atomic_uint64, long long);
            #else
                (void)order;    /* Always using the strongest memory order. */
                return (c89atomic_uint64)_InterlockedExchangeAdd64((volatile long long*)dst, (long long)src);
            #endif
            }
        #else
            /* Implemented below. */
        #endif
    #endif
    #if defined(C89ATOMIC_HAS_64) && !defined(C89ATOMIC_64BIT)   /* 9atomic_fetch_add_explicit_64() must be implemented in terms of atomic_compare_and_swap() on 32-bit builds, no matter the version of Visual Studio. */
        static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_fetch_add_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue + src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }
    #endif


    /* atomic_thread_fence */
    #if defined(C89ATOMIC_MSVC_USE_INLINED_ASSEMBLY)
        static C89ATOMIC_INLINE void __stdcall c89atomic_thread_fence(c89atomic_memory_order order)
        {
            (void)order;
            __asm {
                lock add [esp], 0
            }
        }
    #else
        /* Can't use MemoryBarrier() for this as it require Windows headers which we want to avoid in the header section of c89atomic. */
        #if defined(C89ATOMIC_X64)
            #define c89atomic_thread_fence(order)   __faststorefence(), (void)order
        #elif defined(C89ATOMIC_ARM64)
            #define c89atomic_thread_fence(order)   __dmb(_ARM64_BARRIER_ISH), (void)order
        #else
            static C89ATOMIC_INLINE void c89atomic_thread_fence(c89atomic_memory_order order)
            {
                volatile c89atomic_uint32 barrier = 0;
                c89atomic_fetch_add_explicit_32(&barrier, 0, order);
            }
        #endif  /* C89ATOMIC_X64 */
    #endif


    /*
    I'm not sure how to implement a compiler barrier for old MSVC so I'm just making it a thread_fence() and hopefully the compiler will see the volatile and not do
    any reshuffling. If anybody has a better idea on this please let me know! Cannot use _ReadWriteBarrier() as it has been marked as deprecated.
    */
    #define c89atomic_compiler_fence()      c89atomic_thread_fence(c89atomic_memory_order_seq_cst)

    /* I'm not sure how to implement this for MSVC. For now just using thread_fence(). */
    #define c89atomic_signal_fence(order)   c89atomic_thread_fence(order)


    /* Atomic loads can be implemented in terms of a compare-and-swap. Need to implement as functions to silence warnings about `order` being unused. */
    #if defined(C89ATOMIC_HAS_8)
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_load_explicit_8(volatile const c89atomic_uint8* ptr, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC_COMPARE_EXCHANGE(ptr, 0, 0, order, _InterlockedCompareExchange8, c89atomic_uint8, char);
        #else
            (void)order;    /* Always using the strongest memory order. */
            return c89atomic_compare_and_swap_8((volatile c89atomic_uint8*)ptr, 0, 0);
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_16)
        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_load_explicit_16(volatile const c89atomic_uint16* ptr, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC_COMPARE_EXCHANGE(ptr, 0, 0, order, _InterlockedCompareExchange16, c89atomic_uint16, short);
        #else
            (void)order;    /* Always using the strongest memory order. */
            return c89atomic_compare_and_swap_16((volatile c89atomic_uint16*)ptr, 0, 0);
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_32)
        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_load_explicit_32(volatile const c89atomic_uint32* ptr, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC_COMPARE_EXCHANGE(ptr, 0, 0, order, _InterlockedCompareExchange, c89atomic_uint32, long);
        #else
            (void)order;    /* Always using the strongest memory order. */
            return c89atomic_compare_and_swap_32((volatile c89atomic_uint32*)ptr, 0, 0);
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_64)
        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_load_explicit_64(volatile const c89atomic_uint64* ptr, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC_COMPARE_EXCHANGE(ptr, 0, 0, order, _InterlockedCompareExchange64, c89atomic_uint64, long long);
        #else
            (void)order;    /* Always using the strongest memory order. */
            return c89atomic_compare_and_swap_64((volatile c89atomic_uint64*)ptr, 0, 0);
        #endif
        }
    #endif


    /* atomic_store() is the same as atomic_exchange() but returns void. */
    #if defined(C89ATOMIC_HAS_8)
        #define c89atomic_store_explicit_8( dst, src, order) (void)c89atomic_exchange_explicit_8 (dst, src, order)
    #endif
    #if defined(C89ATOMIC_HAS_16)
        #define c89atomic_store_explicit_16(dst, src, order) (void)c89atomic_exchange_explicit_16(dst, src, order)
    #endif
    #if defined(C89ATOMIC_HAS_32)
        #define c89atomic_store_explicit_32(dst, src, order) (void)c89atomic_exchange_explicit_32(dst, src, order)
    #endif
    #if defined(C89ATOMIC_HAS_64)
        #define c89atomic_store_explicit_64(dst, src, order) (void)c89atomic_exchange_explicit_64(dst, src, order)
    #endif


    /* fetch_sub() */
    #if defined(C89ATOMIC_HAS_8)
        static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_fetch_sub_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue - src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }
    #endif
    #if defined(C89ATOMIC_HAS_16)
        static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_fetch_sub_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue - src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }
    #endif
    #if defined(C89ATOMIC_HAS_32)
        static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_fetch_sub_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue - src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }
    #endif
    #if defined(C89ATOMIC_HAS_64)
        static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_fetch_sub_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue - src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }
    #endif


    /* fetch_and() */
    #if defined(C89ATOMIC_HAS_8)
        static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_fetch_and_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedAnd8, c89atomic_uint8, char);
        #else
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue & src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_16)
        static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_fetch_and_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedAnd16, c89atomic_uint16, short);
        #else
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue & src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_32)
        static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_fetch_and_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedAnd, c89atomic_uint32, long);
        #else
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue & src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_64)
        static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_fetch_and_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedAnd64, c89atomic_uint64, long long);
        #else
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue & src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif


    /* fetch_xor() */
    #if defined(C89ATOMIC_HAS_8)
        static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_fetch_xor_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedXor8, c89atomic_uint8, char);
        #else
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue ^ src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_16)
        static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_fetch_xor_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedXor16, c89atomic_uint16, short);
        #else
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue ^ src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_32)
        static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_fetch_xor_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedXor, c89atomic_uint32, long);
        #else
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue ^ src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_64)
        static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_fetch_xor_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedXor64, c89atomic_uint64, long long);
        #else
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue ^ src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif


    /* fetch_or() */
    #if defined(C89ATOMIC_HAS_8)
        static C89ATOMIC_INLINE c89atomic_uint8 __stdcall c89atomic_fetch_or_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedOr8, c89atomic_uint8, char);
        #else
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue | src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_16)
        static C89ATOMIC_INLINE c89atomic_uint16 __stdcall c89atomic_fetch_or_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedOr16, c89atomic_uint16, short);
        #else
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue | src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_32)
        static C89ATOMIC_INLINE c89atomic_uint32 __stdcall c89atomic_fetch_or_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedOr, c89atomic_uint32, long);
        #else
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue | src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif
    #if defined(C89ATOMIC_HAS_64)
        static C89ATOMIC_INLINE c89atomic_uint64 __stdcall c89atomic_fetch_or_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_ARM)
            C89ATOMIC_MSVC_ARM_INTRINSIC(dst, src, order, _InterlockedOr64, c89atomic_uint64, long long);
        #else
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue | src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        #endif
        }
    #endif

    /* test_and_set() */
    #if defined(C89ATOMIC_HAS_8)
        #define c89atomic_test_and_set_explicit_8( dst, order) c89atomic_exchange_explicit_8 (dst, 1, order)
    #endif
    #if defined(C89ATOMIC_HAS_16)
        #define c89atomic_test_and_set_explicit_16(dst, order) c89atomic_exchange_explicit_16(dst, 1, order)
    #endif
    #if defined(C89ATOMIC_HAS_32)
        #define c89atomic_test_and_set_explicit_32(dst, order) c89atomic_exchange_explicit_32(dst, 1, order)
    #endif
    #if defined(C89ATOMIC_HAS_64)
        #define c89atomic_test_and_set_explicit_64(dst, order) c89atomic_exchange_explicit_64(dst, 1, order)
    #endif

    /* clear() */
    #if defined(C89ATOMIC_HAS_8)
        #define c89atomic_clear_explicit_8( dst, order) c89atomic_store_explicit_8 (dst, 0, order)
    #endif
    #if defined(C89ATOMIC_HAS_16)
        #define c89atomic_clear_explicit_16(dst, order) c89atomic_store_explicit_16(dst, 0, order)
    #endif
    #if defined(C89ATOMIC_HAS_32)
        #define c89atomic_clear_explicit_32(dst, order) c89atomic_store_explicit_32(dst, 0, order)
    #endif
    #if defined(C89ATOMIC_HAS_64)
        #define c89atomic_clear_explicit_64(dst, order) c89atomic_store_explicit_64(dst, 0, order)
    #endif

    /* Prefer 8-bit flags, but fall back to 32-bit if we don't support 8-bit atomics (possible on 64-bit MSVC prior to Visual Studio 2010). */
    #if defined(C89ATOMIC_HAS_8)
        typedef c89atomic_uint8 c89atomic_flag;
        #define c89atomic_flag_test_and_set_explicit(ptr, order)    (c89atomic_bool)c89atomic_test_and_set_explicit_8(ptr, order)
        #define c89atomic_flag_clear_explicit(ptr, order)           c89atomic_clear_explicit_8(ptr, order)
        #define c89atoimc_flag_load_explicit(ptr, order)            c89atomic_load_explicit_8(ptr, order)
    #else
        typedef c89atomic_uint32 c89atomic_flag;
        #define c89atomic_flag_test_and_set_explicit(ptr, order)    (c89atomic_bool)c89atomic_test_and_set_explicit_32(ptr, order)
        #define c89atomic_flag_clear_explicit(ptr, order)           c89atomic_clear_explicit_32(ptr, order)
        #define c89atoimc_flag_load_explicit(ptr, order)            c89atomic_load_explicit_32(ptr, order)
    #endif
#elif defined(__clang__) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)))
    /* Modern GCC atomic built-ins. */
    #define C89ATOMIC_HAS_NATIVE_COMPARE_EXCHANGE
    #define C89ATOMIC_HAS_NATIVE_IS_LOCK_FREE

    #define c89atomic_memory_order_relaxed                          __ATOMIC_RELAXED
    #define c89atomic_memory_order_consume                          __ATOMIC_CONSUME
    #define c89atomic_memory_order_acquire                          __ATOMIC_ACQUIRE
    #define c89atomic_memory_order_release                          __ATOMIC_RELEASE
    #define c89atomic_memory_order_acq_rel                          __ATOMIC_ACQ_REL
    #define c89atomic_memory_order_seq_cst                          __ATOMIC_SEQ_CST

    #define c89atomic_compiler_fence()                              __asm__ __volatile__("":::"memory")
    #define c89atomic_thread_fence(order)                           __atomic_thread_fence(order)
    #define c89atomic_signal_fence(order)                           __atomic_signal_fence(order)

    #define c89atomic_is_lock_free_8(ptr)                           __atomic_is_lock_free(1, ptr)
    #define c89atomic_is_lock_free_16(ptr)                          __atomic_is_lock_free(2, ptr)
    #define c89atomic_is_lock_free_32(ptr)                          __atomic_is_lock_free(4, ptr)
    #define c89atomic_is_lock_free_64(ptr)                          __atomic_is_lock_free(8, ptr)

    #define c89atomic_test_and_set_explicit_8( dst, order)          __atomic_exchange_n(dst, 1, order)
    #define c89atomic_test_and_set_explicit_16(dst, order)          __atomic_exchange_n(dst, 1, order)
    #define c89atomic_test_and_set_explicit_32(dst, order)          __atomic_exchange_n(dst, 1, order)
    #define c89atomic_test_and_set_explicit_64(dst, order)          __atomic_exchange_n(dst, 1, order)
    
    #define c89atomic_clear_explicit_8( dst, order)                 __atomic_store_n(dst, 0, order)
    #define c89atomic_clear_explicit_16(dst, order)                 __atomic_store_n(dst, 0, order)
    #define c89atomic_clear_explicit_32(dst, order)                 __atomic_store_n(dst, 0, order)
    #define c89atomic_clear_explicit_64(dst, order)                 __atomic_store_n(dst, 0, order)
    
    #define c89atomic_store_explicit_8( dst, src, order)            __atomic_store_n(dst, src, order)
    #define c89atomic_store_explicit_16(dst, src, order)            __atomic_store_n(dst, src, order)
    #define c89atomic_store_explicit_32(dst, src, order)            __atomic_store_n(dst, src, order)
    #define c89atomic_store_explicit_64(dst, src, order)            __atomic_store_n(dst, src, order)
    
    #define c89atomic_load_explicit_8( dst, order)                  __atomic_load_n(dst, order)
    #define c89atomic_load_explicit_16(dst, order)                  __atomic_load_n(dst, order)
    #define c89atomic_load_explicit_32(dst, order)                  __atomic_load_n(dst, order)
    #define c89atomic_load_explicit_64(dst, order)                  __atomic_load_n(dst, order)
    
    #define c89atomic_exchange_explicit_8( dst, src, order)         __atomic_exchange_n(dst, src, order)
    #define c89atomic_exchange_explicit_16(dst, src, order)         __atomic_exchange_n(dst, src, order)
    #define c89atomic_exchange_explicit_32(dst, src, order)         __atomic_exchange_n(dst, src, order)
    #define c89atomic_exchange_explicit_64(dst, src, order)         __atomic_exchange_n(dst, src, order)

    #define c89atomic_compare_exchange_strong_explicit_8( dst, expected, desired, successOrder, failureOrder)   __atomic_compare_exchange_n(dst, expected, desired, 0, successOrder, failureOrder)
    #define c89atomic_compare_exchange_strong_explicit_16(dst, expected, desired, successOrder, failureOrder)   __atomic_compare_exchange_n(dst, expected, desired, 0, successOrder, failureOrder)
    #define c89atomic_compare_exchange_strong_explicit_32(dst, expected, desired, successOrder, failureOrder)   __atomic_compare_exchange_n(dst, expected, desired, 0, successOrder, failureOrder)
    #define c89atomic_compare_exchange_strong_explicit_64(dst, expected, desired, successOrder, failureOrder)   __atomic_compare_exchange_n(dst, expected, desired, 0, successOrder, failureOrder)

    #define c89atomic_compare_exchange_weak_explicit_8( dst, expected, desired, successOrder, failureOrder)     __atomic_compare_exchange_n(dst, expected, desired, 1, successOrder, failureOrder)
    #define c89atomic_compare_exchange_weak_explicit_16(dst, expected, desired, successOrder, failureOrder)     __atomic_compare_exchange_n(dst, expected, desired, 1, successOrder, failureOrder)
    #define c89atomic_compare_exchange_weak_explicit_32(dst, expected, desired, successOrder, failureOrder)     __atomic_compare_exchange_n(dst, expected, desired, 1, successOrder, failureOrder)
    #define c89atomic_compare_exchange_weak_explicit_64(dst, expected, desired, successOrder, failureOrder)     __atomic_compare_exchange_n(dst, expected, desired, 1, successOrder, failureOrder)
    
    #define c89atomic_fetch_add_explicit_8( dst, src, order)        __atomic_fetch_add(dst, src, order)
    #define c89atomic_fetch_add_explicit_16(dst, src, order)        __atomic_fetch_add(dst, src, order)
    #define c89atomic_fetch_add_explicit_32(dst, src, order)        __atomic_fetch_add(dst, src, order)
    #define c89atomic_fetch_add_explicit_64(dst, src, order)        __atomic_fetch_add(dst, src, order)
    
    #define c89atomic_fetch_sub_explicit_8( dst, src, order)        __atomic_fetch_sub(dst, src, order)
    #define c89atomic_fetch_sub_explicit_16(dst, src, order)        __atomic_fetch_sub(dst, src, order)
    #define c89atomic_fetch_sub_explicit_32(dst, src, order)        __atomic_fetch_sub(dst, src, order)
    #define c89atomic_fetch_sub_explicit_64(dst, src, order)        __atomic_fetch_sub(dst, src, order)
    
    #define c89atomic_fetch_or_explicit_8( dst, src, order)         __atomic_fetch_or(dst, src, order)
    #define c89atomic_fetch_or_explicit_16(dst, src, order)         __atomic_fetch_or(dst, src, order)
    #define c89atomic_fetch_or_explicit_32(dst, src, order)         __atomic_fetch_or(dst, src, order)
    #define c89atomic_fetch_or_explicit_64(dst, src, order)         __atomic_fetch_or(dst, src, order)
    
    #define c89atomic_fetch_xor_explicit_8( dst, src, order)        __atomic_fetch_xor(dst, src, order)
    #define c89atomic_fetch_xor_explicit_16(dst, src, order)        __atomic_fetch_xor(dst, src, order)
    #define c89atomic_fetch_xor_explicit_32(dst, src, order)        __atomic_fetch_xor(dst, src, order)
    #define c89atomic_fetch_xor_explicit_64(dst, src, order)        __atomic_fetch_xor(dst, src, order)
    
    #define c89atomic_fetch_and_explicit_8( dst, src, order)        __atomic_fetch_and(dst, src, order)
    #define c89atomic_fetch_and_explicit_16(dst, src, order)        __atomic_fetch_and(dst, src, order)
    #define c89atomic_fetch_and_explicit_32(dst, src, order)        __atomic_fetch_and(dst, src, order)
    #define c89atomic_fetch_and_explicit_64(dst, src, order)        __atomic_fetch_and(dst, src, order)

    /* CAS needs to be implemented as a function because _atomic_compare_exchange_n() needs to take the address of the expected value. */
    static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_compare_and_swap_8(volatile c89atomic_uint8* dst, c89atomic_uint8 expected, c89atomic_uint8 desired)
    {
        __atomic_compare_exchange_n(dst, &expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
        return expected;
    }

    static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_compare_and_swap_16(volatile c89atomic_uint16* dst, c89atomic_uint16 expected, c89atomic_uint16 desired)
    {
        __atomic_compare_exchange_n(dst, &expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
        return expected;
    }

    static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_compare_and_swap_32(volatile c89atomic_uint32* dst, c89atomic_uint32 expected, c89atomic_uint32 desired)
    {
        __atomic_compare_exchange_n(dst, &expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
        return expected;
    }

    static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_compare_and_swap_64(volatile c89atomic_uint64* dst, c89atomic_uint64 expected, c89atomic_uint64 desired)
    {
        __atomic_compare_exchange_n(dst, &expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
        return expected;
    }

    typedef c89atomic_uint8 c89atomic_flag;
    #define c89atomic_flag_test_and_set_explicit(dst, order)        (c89atomic_bool)__atomic_test_and_set(dst, order)
    #define c89atomic_flag_clear_explicit(dst, order)               __atomic_clear(dst, order)
    #define c89atoimc_flag_load_explicit(ptr, order)                c89atomic_load_explicit_8(ptr, order)
#else
    /* GCC and compilers supporting GCC-style inlined assembly. */
    #define c89atomic_memory_order_relaxed  1
    #define c89atomic_memory_order_consume  2
    #define c89atomic_memory_order_acquire  3
    #define c89atomic_memory_order_release  4
    #define c89atomic_memory_order_acq_rel  5
    #define c89atomic_memory_order_seq_cst  6

    #define c89atomic_compiler_fence() __asm__ __volatile__("":::"memory")

    #if defined(__GNUC__)
        /* Legacy GCC atomic built-ins. Everything is a full memory barrier. */    
        #define c89atomic_thread_fence(order) __sync_synchronize(), (void)order

        /* exchange() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_exchange_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            if (order > c89atomic_memory_order_acquire) {
                __sync_synchronize();
            }

            return __sync_lock_test_and_set(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_exchange_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 oldValue;
        
            do {
                oldValue = *dst;
            } while (__sync_val_compare_and_swap(dst, oldValue, src) != oldValue);
        
            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_exchange_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 oldValue;
        
            do {
                oldValue = *dst;
            } while (__sync_val_compare_and_swap(dst, oldValue, src) != oldValue);
        
            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_exchange_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
        
            do {
                oldValue = *dst;
            } while (__sync_val_compare_and_swap(dst, oldValue, src) != oldValue);
        
            (void)order;
            return oldValue;
        }


        /* fetch_add() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_add_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_add(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_add_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_add(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_add_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_add(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_add_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_add(dst, src);
        }


        /* fetch_sub() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_sub_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_sub(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_sub_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_sub(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_sub_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_sub(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_sub_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_sub(dst, src);
        }


        /* fetch_or() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_or_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_or(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_or_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_or(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_or_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_or(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_or_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_or(dst, src);
        }


        /* fetch_xor() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_xor_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_xor(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_xor_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_xor(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_xor_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_xor(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_xor_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_xor(dst, src);
        }

        /* fetch_and() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_and_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_and(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_and_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_and(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_and_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_and(dst, src);
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_and_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            (void)order;
            return __sync_fetch_and_and(dst, src);
        }

        #define c89atomic_compare_and_swap_8( dst, expected, desired)   __sync_val_compare_and_swap(dst, expected, desired)
        #define c89atomic_compare_and_swap_16(dst, expected, desired)   __sync_val_compare_and_swap(dst, expected, desired)
        #define c89atomic_compare_and_swap_32(dst, expected, desired)   __sync_val_compare_and_swap(dst, expected, desired)
        #define c89atomic_compare_and_swap_64(dst, expected, desired)   __sync_val_compare_and_swap(dst, expected, desired) 
    #else
        /* Non-GCC compilers supporting GCC-style inlined assembly. The inlined assembly below uses Gas syntax. */

        /*
        It's actually kind of confusing as to the best way to implement a memory barrier on x86/64. From my quick research, it looks like
        there's a few options:
            - SFENCE/LFENCE/MFENCE
            - LOCK ADD
            - XCHG (with a memory operand, not two register operands)

        It looks like the SFENCE instruction was added in the Pentium III series, whereas the LFENCE and MFENCE instructions were added in
        the Pentium 4 series. It's not clear how this actually differs to a LOCK-prefixed instruction or an XCHG instruction with a memory
        operand. For simplicity and compatibility, I'm just using a LOCK-prefixed ADD instruction which adds 0 to the value pointed to by
        the ESP register. The use of the ESP register is that it should theoretically have a high likelyhood to be in cache. For now, just
        to keep things simple, this is always doing a full memory barrier which means the `order` parameter is ignored on x86/64.
        
        I want a thread fence to also act as a compiler fence, so therefore I'm forcing this to be inlined by implementing it as a define.
        */
        #if defined(C89ATOMIC_X86)
            #define c89atomic_thread_fence(order) __asm__ __volatile__("lock; addl $0, (%%esp)" ::: "memory", "cc")
        #elif defined(C89ATOMIC_X64)
            #define c89atomic_thread_fence(order) __asm__ __volatile__("lock; addq $0, (%%rsp)" ::: "memory", "cc")
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

        /* compare_and_swap() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_compare_and_swap_8(volatile c89atomic_uint8* dst, c89atomic_uint8 expected, c89atomic_uint8 desired)
        {
            c89atomic_uint8 result;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; cmpxchg %3, %0" : "+m"(*dst), "=a"(result) : "a"(expected), "d"(desired) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_compare_and_swap_16(volatile c89atomic_uint16* dst, c89atomic_uint16 expected, c89atomic_uint16 desired)
        {
            c89atomic_uint16 result;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; cmpxchg %3, %0" : "+m"(*dst), "=a"(result) : "a"(expected), "d"(desired) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_compare_and_swap_32(volatile c89atomic_uint32* dst, c89atomic_uint32 expected, c89atomic_uint32 desired)
        {
            c89atomic_uint32 result;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; cmpxchg %3, %0" : "+m"(*dst), "=a"(result) : "a"(expected), "d"(desired) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_compare_and_swap_64(volatile c89atomic_uint64* dst, c89atomic_uint64 expected, c89atomic_uint64 desired)
        {
            volatile c89atomic_uint64 result;

        #if defined(C89ATOMIC_X86)
            /*
            We can't use the standard CMPXCHG here because x86 does not support it with 64-bit values. We need to instead use CMPXCHG8B
            which is a bit harder to use. The annoying part with this is the use of the -fPIC compiler switch which requires the EBX
            register never be modified. The problem is that CMPXCHG8B requires us to write our desired value to it. I'm resolving this
            by just pushing and popping the EBX register manually.
            */
            c89atomic_uint32 resultEAX;
            c89atomic_uint32 resultEDX;
            __asm__ __volatile__("push %%ebx; xchg %5, %%ebx; lock; cmpxchg8b %0; pop %%ebx" : "+m"(*dst), "=a"(resultEAX), "=d"(resultEDX) : "a"(expected & 0xFFFFFFFF), "d"(expected >> 32), "r"(desired & 0xFFFFFFFF), "c"(desired >> 32) : "cc");
            result = ((c89atomic_uint64)resultEDX << 32) | resultEAX;
        #elif defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; cmpxchg %3, %0" : "+m"(*dst), "=a"(result) : "a"(expected), "d"(desired) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }


        /* exchange() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_exchange_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 result = 0;
                
            (void)order;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xchg %1, %0" : "+m"(*dst), "=a"(result) : "a"(src));
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_exchange_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 result = 0;
                
            (void)order;
            
        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xchg %1, %0" : "+m"(*dst), "=a"(result) : "a"(src));
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_exchange_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 result;
                
            (void)order;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xchg %1, %0" : "+m"(*dst), "=a"(result) : "a"(src));
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_exchange_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 result;
                
            (void)order;

        #if defined(C89ATOMIC_X86)
            do {
                result = *dst;
            } while (c89atomic_compare_and_swap_64(dst, result, src) != result);
        #elif defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xchg %1, %0" : "+m"(*dst), "=a"(result) : "a"(src));
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }


        /* fetch_add() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_add_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 result;
                
            (void)order;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xadd %1, %0" : "+m"(*dst), "=a"(result) : "a"(src) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_add_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 result;
                
            (void)order;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xadd %1, %0" : "+m"(*dst), "=a"(result) : "a"(src) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_add_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 result;
                
            (void)order;

        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            __asm__ __volatile__("lock; xadd %1, %0" : "+m"(*dst), "=a"(result) : "a"(src) : "cc");
        #else
            #error Unsupported architecture. Please submit a feature request.
        #endif

            return result;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_add_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
        #if defined(C89ATOMIC_X86)
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            (void)order;

            do {
                oldValue = *dst;
                newValue = oldValue + src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            return oldValue;
        #elif defined(C89ATOMIC_X64)
            c89atomic_uint64 result;

            (void)order;

            __asm__ __volatile__("lock; xadd %1, %0" : "+m"(*dst), "=a"(result) : "a"(src) : "cc");

            return result;
        #endif
        }

        /* fetch_sub() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_sub_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue - src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_sub_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue - src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_sub_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue - src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_sub_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue - src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }


        /* fetch_and() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_and_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue & src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_and_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue & src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_and_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue & src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_and_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue & src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }


        /* fetch_xor() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_xor_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue ^ src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_xor_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue ^ src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_xor_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue ^ src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_xor_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue ^ src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }


        /* fetch_or() */
        static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_fetch_or_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8 src, c89atomic_memory_order order)
        {
            c89atomic_uint8 oldValue;
            c89atomic_uint8 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint8)(oldValue | src);
            } while (c89atomic_compare_and_swap_8(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_fetch_or_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16 src, c89atomic_memory_order order)
        {
            c89atomic_uint16 oldValue;
            c89atomic_uint16 newValue;

            do {
                oldValue = *dst;
                newValue = (c89atomic_uint16)(oldValue | src);
            } while (c89atomic_compare_and_swap_16(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_fetch_or_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32 src, c89atomic_memory_order order)
        {
            c89atomic_uint32 oldValue;
            c89atomic_uint32 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue | src;
            } while (c89atomic_compare_and_swap_32(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }

        static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_fetch_or_explicit_64(volatile c89atomic_uint64* dst, c89atomic_uint64 src, c89atomic_memory_order order)
        {
            c89atomic_uint64 oldValue;
            c89atomic_uint64 newValue;

            do {
                oldValue = *dst;
                newValue = oldValue | src;
            } while (c89atomic_compare_and_swap_64(dst, oldValue, newValue) != oldValue);

            (void)order;
            return oldValue;
        }
    #endif

    #define c89atomic_signal_fence(order)                           c89atomic_thread_fence(order)

    /* Atomic loads can be implemented in terms of a compare-and-swap. Need to implement as functions to silence warnings about `order` being unused. */
    static C89ATOMIC_INLINE c89atomic_uint8 c89atomic_load_explicit_8(volatile const c89atomic_uint8* ptr, c89atomic_memory_order order)
    {
        (void)order;    /* Always using the strongest memory order. */
        return c89atomic_compare_and_swap_8((c89atomic_uint8*)ptr, 0, 0);
    }

    static C89ATOMIC_INLINE c89atomic_uint16 c89atomic_load_explicit_16(volatile const c89atomic_uint16* ptr, c89atomic_memory_order order)
    {
        (void)order;    /* Always using the strongest memory order. */
        return c89atomic_compare_and_swap_16((c89atomic_uint16*)ptr, 0, 0);
    }

    static C89ATOMIC_INLINE c89atomic_uint32 c89atomic_load_explicit_32(volatile const c89atomic_uint32* ptr, c89atomic_memory_order order)
    {
        (void)order;    /* Always using the strongest memory order. */
        return c89atomic_compare_and_swap_32((c89atomic_uint32*)ptr, 0, 0);
    }

    static C89ATOMIC_INLINE c89atomic_uint64 c89atomic_load_explicit_64(volatile const c89atomic_uint64* ptr, c89atomic_memory_order order)
    {
        (void)order;    /* Always using the strongest memory order. */
        return c89atomic_compare_and_swap_64((c89atomic_uint64*)ptr, 0, 0);
    }

    #define c89atomic_store_explicit_8( dst, src, order)            (void)c89atomic_exchange_explicit_8 (dst, src, order)
    #define c89atomic_store_explicit_16(dst, src, order)            (void)c89atomic_exchange_explicit_16(dst, src, order)
    #define c89atomic_store_explicit_32(dst, src, order)            (void)c89atomic_exchange_explicit_32(dst, src, order)
    #define c89atomic_store_explicit_64(dst, src, order)            (void)c89atomic_exchange_explicit_64(dst, src, order)

    #define c89atomic_test_and_set_explicit_8( dst, order)          c89atomic_exchange_explicit_8 (dst, 1, order)
    #define c89atomic_test_and_set_explicit_16(dst, order)          c89atomic_exchange_explicit_16(dst, 1, order)
    #define c89atomic_test_and_set_explicit_32(dst, order)          c89atomic_exchange_explicit_32(dst, 1, order)
    #define c89atomic_test_and_set_explicit_64(dst, order)          c89atomic_exchange_explicit_64(dst, 1, order)

    #define c89atomic_clear_explicit_8( dst, order)                 c89atomic_store_explicit_8 (dst, 0, order)
    #define c89atomic_clear_explicit_16(dst, order)                 c89atomic_store_explicit_16(dst, 0, order)
    #define c89atomic_clear_explicit_32(dst, order)                 c89atomic_store_explicit_32(dst, 0, order)
    #define c89atomic_clear_explicit_64(dst, order)                 c89atomic_store_explicit_64(dst, 0, order)

    typedef c89atomic_uint8 c89atomic_flag;
    #define c89atomic_flag_test_and_set_explicit(ptr, order)        (c89atomic_bool)c89atomic_test_and_set_explicit_8(ptr, order)
    #define c89atomic_flag_clear_explicit(ptr, order)               c89atomic_clear_explicit_8(ptr, order)
    #define c89atoimc_flag_load_explicit(ptr, order)                c89atomic_load_explicit_8(ptr, order)
#endif

/* compare_exchange() */
#if !defined(C89ATOMIC_HAS_NATIVE_COMPARE_EXCHANGE)
    #if defined(C89ATOMIC_HAS_8)
        static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_8(volatile c89atomic_uint8* dst, c89atomic_uint8* expected, c89atomic_uint8 desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
        {
            c89atomic_uint8 expectedValue;
            c89atomic_uint8 result;

            (void)successOrder;
            (void)failureOrder;

            expectedValue = c89atomic_load_explicit_8(expected, c89atomic_memory_order_seq_cst);
            result = c89atomic_compare_and_swap_8(dst, expectedValue, desired);
            if (result == expectedValue) {
                return 1;
            } else {
                c89atomic_store_explicit_8(expected, result, failureOrder);
                return 0;
            }
        }
    #endif
    #if defined(C89ATOMIC_HAS_16)
        static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_16(volatile c89atomic_uint16* dst, c89atomic_uint16* expected, c89atomic_uint16 desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
        {
            c89atomic_uint16 expectedValue;
            c89atomic_uint16 result;

            (void)successOrder;
            (void)failureOrder;

            expectedValue = c89atomic_load_explicit_16(expected, c89atomic_memory_order_seq_cst);
            result = c89atomic_compare_and_swap_16(dst, expectedValue, desired);
            if (result == expectedValue) {
                return 1;
            } else {
                c89atomic_store_explicit_16(expected, result, failureOrder);
                return 0;
            }
        }
    #endif
    #if defined(C89ATOMIC_HAS_32)
        static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_32(volatile c89atomic_uint32* dst, c89atomic_uint32* expected, c89atomic_uint32 desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
        {
            c89atomic_uint32 expectedValue;
            c89atomic_uint32 result;

            (void)successOrder;
            (void)failureOrder;

            expectedValue = c89atomic_load_explicit_32(expected, c89atomic_memory_order_seq_cst);
            result = c89atomic_compare_and_swap_32(dst, expectedValue, desired);
            if (result == expectedValue) {
                return 1;
            } else {
                c89atomic_store_explicit_32(expected, result, failureOrder);
                return 0;
            }
        }
    #endif
    #if defined(C89ATOMIC_HAS_64)
        static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_64(volatile c89atomic_uint64* dst, volatile c89atomic_uint64* expected, c89atomic_uint64 desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
        {
            c89atomic_uint64 expectedValue;
            c89atomic_uint64 result;

            (void)successOrder;
            (void)failureOrder;

            expectedValue = c89atomic_load_explicit_64(expected, c89atomic_memory_order_seq_cst);
            result = c89atomic_compare_and_swap_64(dst, expectedValue, desired);
            if (result == expectedValue) {
                return 1;
            } else {
                c89atomic_store_explicit_64(expected, result, failureOrder);
                return 0;
            }
        }
    #endif

    #define c89atomic_compare_exchange_weak_explicit_8( dst, expected, desired, successOrder, failureOrder) c89atomic_compare_exchange_strong_explicit_8 (dst, expected, desired, successOrder, failureOrder)
    #define c89atomic_compare_exchange_weak_explicit_16(dst, expected, desired, successOrder, failureOrder) c89atomic_compare_exchange_strong_explicit_16(dst, expected, desired, successOrder, failureOrder)
    #define c89atomic_compare_exchange_weak_explicit_32(dst, expected, desired, successOrder, failureOrder) c89atomic_compare_exchange_strong_explicit_32(dst, expected, desired, successOrder, failureOrder)
    #define c89atomic_compare_exchange_weak_explicit_64(dst, expected, desired, successOrder, failureOrder) c89atomic_compare_exchange_strong_explicit_64(dst, expected, desired, successOrder, failureOrder)
#endif  /* C89ATOMIC_HAS_NATIVE_COMPARE_EXCHANGE */

#if !defined(C89ATOMIC_HAS_NATIVE_IS_LOCK_FREE)
    static C89ATOMIC_INLINE c89atomic_bool c89atomic_is_lock_free_8(volatile void* ptr)
    {
        (void)ptr;
        return 1;
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_is_lock_free_16(volatile void* ptr)
    {
        (void)ptr;
        return 1;
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_is_lock_free_32(volatile void* ptr)
    {
        (void)ptr;
        return 1;
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_is_lock_free_64(volatile void* ptr)
    {
        (void)ptr;
    
        /* For 64-bit atomics, we can only safely say atomics are lock free on 64-bit architectures or x86. Otherwise we need to be conservative and assume not lock free. */
    #if defined(C89ATOMIC_64BIT)
        return 1;
    #else
        #if defined(C89ATOMIC_X86) || defined(C89ATOMIC_X64)
            return 1;
        #else
            return 0;
        #endif
    #endif
    }
#endif  /* C89ATOMIC_HAS_NATIVE_IS_LOCK_FREE */

/*
Pointer versions of relevant operations. Note that some functions cannot be implemented as #defines because for some reason, some compilers
complain with a warning if you don't use the return value. I'm not fully sure why this happens, but to work around this, those particular
functions are just implemented as inlined functions.
*/
#if defined(C89ATOMIC_64BIT)
    static C89ATOMIC_INLINE c89atomic_bool c89atomic_is_lock_free_ptr(volatile void** ptr)
    {
        return c89atomic_is_lock_free_64((volatile c89atomic_uint64*)ptr);
    }

    static C89ATOMIC_INLINE void* c89atomic_load_explicit_ptr(volatile void** ptr, c89atomic_memory_order order)
    {
        return (void*)c89atomic_load_explicit_64((volatile c89atomic_uint64*)ptr, order);
    }

    static C89ATOMIC_INLINE void c89atomic_store_explicit_ptr(volatile void** dst, void* src, c89atomic_memory_order order)
    {
        c89atomic_store_explicit_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64)src, order);
    }

    static C89ATOMIC_INLINE void* c89atomic_exchange_explicit_ptr(volatile void** dst, void* src, c89atomic_memory_order order)
    {
        return (void*)c89atomic_exchange_explicit_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64)src, order);
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_ptr(volatile void** dst, void** expected, void* desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
    {
        return c89atomic_compare_exchange_strong_explicit_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64*)expected, (c89atomic_uint64)desired, successOrder, failureOrder);
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_weak_explicit_ptr(volatile void** dst, void** expected, void* desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
    {
        return c89atomic_compare_exchange_weak_explicit_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64*)expected, (c89atomic_uint64)desired, successOrder, failureOrder);
    }

    static C89ATOMIC_INLINE void* c89atomic_compare_and_swap_ptr(volatile void** dst, void* expected, void* desired)
    {
        return (void*)c89atomic_compare_and_swap_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64)expected, (c89atomic_uint64)desired);
    }
#elif defined(C89ATOMIC_32BIT)
    static C89ATOMIC_INLINE c89atomic_bool c89atomic_is_lock_free_ptr(volatile void** ptr)
    {
        return c89atomic_is_lock_free_32((volatile c89atomic_uint32*)ptr);
    }

    static C89ATOMIC_INLINE void* c89atomic_load_explicit_ptr(volatile void** ptr, c89atomic_memory_order order)
    {
        return (void*)c89atomic_load_explicit_32((volatile c89atomic_uint32*)ptr, order);
    }

    static C89ATOMIC_INLINE void c89atomic_store_explicit_ptr(volatile void** dst, void* src, c89atomic_memory_order order)
    {
        c89atomic_store_explicit_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32)src, order);
    }

    static C89ATOMIC_INLINE void* c89atomic_exchange_explicit_ptr(volatile void** dst, void* src, c89atomic_memory_order order)
    {
        return (void*)c89atomic_exchange_explicit_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32)src, order);
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_ptr(volatile void** dst, void** expected, void* desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
    {
        return c89atomic_compare_exchange_strong_explicit_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32*)expected, (c89atomic_uint32)desired, successOrder, failureOrder);
    }

    static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_weak_explicit_ptr(volatile void** dst, void** expected, void* desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
    {
        return c89atomic_compare_exchange_weak_explicit_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32*)expected, (c89atomic_uint32)desired, successOrder, failureOrder);
    }

    static C89ATOMIC_INLINE void* c89atomic_compare_and_swap_ptr(volatile void** dst, void* expected, void* desired)
    {
        return (void*)c89atomic_compare_and_swap_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32)expected, (c89atomic_uint32)desired);
    }
#else
    #error Unsupported architecture.
#endif


/* Implicit Flags. */
#define c89atomic_flag_test_and_set(ptr)                                c89atomic_flag_test_and_set_explicit(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_flag_clear(ptr)                                       c89atomic_flag_clear_explicit(ptr, c89atomic_memory_order_seq_cst)


/* Implicit Pointer. */
#define c89atomic_store_ptr(dst, src)                                   c89atomic_store_explicit_ptr((volatile void**)dst, (void*)src, c89atomic_memory_order_seq_cst)
#define c89atomic_load_ptr(ptr)                                         c89atomic_load_explicit_ptr((volatile void**)ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_ptr(dst, src)                                c89atomic_exchange_explicit_ptr((volatile void**)dst, (void*)src, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_ptr(dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_ptr((volatile void**)dst, (void**)expected, (void*)desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_ptr(dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_ptr((volatile void**)dst, (void**)expected, (void*)desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)


/* Implicit Unsigned Integer. */
#define c89atomic_test_and_set_8( ptr)                                  c89atomic_test_and_set_explicit_8( ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_test_and_set_16(ptr)                                  c89atomic_test_and_set_explicit_16(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_test_and_set_32(ptr)                                  c89atomic_test_and_set_explicit_32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_test_and_set_64(ptr)                                  c89atomic_test_and_set_explicit_64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_clear_8( ptr)                                         c89atomic_clear_explicit_8( ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_16(ptr)                                         c89atomic_clear_explicit_16(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_32(ptr)                                         c89atomic_clear_explicit_32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_64(ptr)                                         c89atomic_clear_explicit_64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_store_8( dst, src)                                    c89atomic_store_explicit_8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_16(dst, src)                                    c89atomic_store_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_32(dst, src)                                    c89atomic_store_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_64(dst, src)                                    c89atomic_store_explicit_64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_load_8( ptr)                                          c89atomic_load_explicit_8( ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_16(ptr)                                          c89atomic_load_explicit_16(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_32(ptr)                                          c89atomic_load_explicit_32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_64(ptr)                                          c89atomic_load_explicit_64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_exchange_8( dst, src)                                 c89atomic_exchange_explicit_8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_16(dst, src)                                 c89atomic_exchange_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_32(dst, src)                                 c89atomic_exchange_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_64(dst, src)                                 c89atomic_exchange_explicit_64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_exchange_strong_8( dst, expected, desired)    c89atomic_compare_exchange_strong_explicit_8( dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_16(dst, expected, desired)    c89atomic_compare_exchange_strong_explicit_16(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_32(dst, expected, desired)    c89atomic_compare_exchange_strong_explicit_32(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_64(dst, expected, desired)    c89atomic_compare_exchange_strong_explicit_64(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_exchange_weak_8(  dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_8( dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_16( dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_16(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_32( dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_32(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_64( dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_64(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_add_8( dst, src)                                c89atomic_fetch_add_explicit_8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_16(dst, src)                                c89atomic_fetch_add_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_32(dst, src)                                c89atomic_fetch_add_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_64(dst, src)                                c89atomic_fetch_add_explicit_64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_sub_8( dst, src)                                c89atomic_fetch_sub_explicit_8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_16(dst, src)                                c89atomic_fetch_sub_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_32(dst, src)                                c89atomic_fetch_sub_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_64(dst, src)                                c89atomic_fetch_sub_explicit_64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_or_8( dst, src)                                 c89atomic_fetch_or_explicit_8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_16(dst, src)                                 c89atomic_fetch_or_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_32(dst, src)                                 c89atomic_fetch_or_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_64(dst, src)                                 c89atomic_fetch_or_explicit_64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_xor_8( dst, src)                                c89atomic_fetch_xor_explicit_8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_16(dst, src)                                c89atomic_fetch_xor_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_32(dst, src)                                c89atomic_fetch_xor_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_64(dst, src)                                c89atomic_fetch_xor_explicit_64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_and_8( dst, src)                                c89atomic_fetch_and_explicit_8 (dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_16(dst, src)                                c89atomic_fetch_and_explicit_16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_32(dst, src)                                c89atomic_fetch_and_explicit_32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_64(dst, src)                                c89atomic_fetch_and_explicit_64(dst, src, c89atomic_memory_order_seq_cst)


/* Explicit Signed Integer. */
#define c89atomic_test_and_set_explicit_i8( ptr, order)                 (c89atomic_int8 )c89atomic_test_and_set_explicit_8( (c89atomic_uint8* )ptr, order)
#define c89atomic_test_and_set_explicit_i16(ptr, order)                 (c89atomic_int16)c89atomic_test_and_set_explicit_16((c89atomic_uint16*)ptr, order)
#define c89atomic_test_and_set_explicit_i32(ptr, order)                 (c89atomic_int32)c89atomic_test_and_set_explicit_32((c89atomic_uint32*)ptr, order)
#define c89atomic_test_and_set_explicit_i64(ptr, order)                 (c89atomic_int64)c89atomic_test_and_set_explicit_64((c89atomic_uint64*)ptr, order)

#define c89atomic_clear_explicit_i8( ptr, order)                        c89atomic_clear_explicit_8( (c89atomic_uint8* )ptr, order)
#define c89atomic_clear_explicit_i16(ptr, order)                        c89atomic_clear_explicit_16((c89atomic_uint16*)ptr, order)
#define c89atomic_clear_explicit_i32(ptr, order)                        c89atomic_clear_explicit_32((c89atomic_uint32*)ptr, order)
#define c89atomic_clear_explicit_i64(ptr, order)                        c89atomic_clear_explicit_64((c89atomic_uint64*)ptr, order)

#define c89atomic_store_explicit_i8( dst, src, order)                   c89atomic_store_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_store_explicit_i16(dst, src, order)                   c89atomic_store_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_store_explicit_i32(dst, src, order)                   c89atomic_store_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_store_explicit_i64(dst, src, order)                   c89atomic_store_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)

#define c89atomic_load_explicit_i8( ptr, order)                         (c89atomic_int8 )c89atomic_load_explicit_8( (c89atomic_uint8* )ptr, order)
#define c89atomic_load_explicit_i16(ptr, order)                         (c89atomic_int16)c89atomic_load_explicit_16((c89atomic_uint16*)ptr, order)
#define c89atomic_load_explicit_i32(ptr, order)                         (c89atomic_int32)c89atomic_load_explicit_32((c89atomic_uint32*)ptr, order)
#define c89atomic_load_explicit_i64(ptr, order)                         (c89atomic_int64)c89atomic_load_explicit_64((c89atomic_uint64*)ptr, order)

#define c89atomic_exchange_explicit_i8( dst, src, order)                (c89atomic_int8 )c89atomic_exchange_explicit_8 ((c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_exchange_explicit_i16(dst, src, order)                (c89atomic_int16)c89atomic_exchange_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_exchange_explicit_i32(dst, src, order)                (c89atomic_int32)c89atomic_exchange_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_exchange_explicit_i64(dst, src, order)                (c89atomic_int64)c89atomic_exchange_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)

#define c89atomic_compare_exchange_strong_explicit_i8( dst, expected, desired, successOrder, failureOrder)  c89atomic_compare_exchange_strong_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8* )expected, (c89atomic_uint8 )desired, successOrder, failureOrder)
#define c89atomic_compare_exchange_strong_explicit_i16(dst, expected, desired, successOrder, failureOrder)  c89atomic_compare_exchange_strong_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16*)expected, (c89atomic_uint16)desired, successOrder, failureOrder)
#define c89atomic_compare_exchange_strong_explicit_i32(dst, expected, desired, successOrder, failureOrder)  c89atomic_compare_exchange_strong_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32*)expected, (c89atomic_uint32)desired, successOrder, failureOrder)
#define c89atomic_compare_exchange_strong_explicit_i64(dst, expected, desired, successOrder, failureOrder)  c89atomic_compare_exchange_strong_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64*)expected, (c89atomic_uint64)desired, successOrder, failureOrder)

#define c89atomic_compare_exchange_weak_explicit_i8( dst, expected, desired, successOrder, failureOrder)    c89atomic_compare_exchange_weak_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8* )expected, (c89atomic_uint8 )desired, successOrder, failureOrder)
#define c89atomic_compare_exchange_weak_explicit_i16(dst, expected, desired, successOrder, failureOrder)    c89atomic_compare_exchange_weak_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16*)expected, (c89atomic_uint16)desired, successOrder, failureOrder)
#define c89atomic_compare_exchange_weak_explicit_i32(dst, expected, desired, successOrder, failureOrder)    c89atomic_compare_exchange_weak_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32*)expected, (c89atomic_uint32)desired, successOrder, failureOrder)
#define c89atomic_compare_exchange_weak_explicit_i64(dst, expected, desired, successOrder, failureOrder)    c89atomic_compare_exchange_weak_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64*)expected, (c89atomic_uint64)desired, successOrder, failureOrder)

#define c89atomic_fetch_add_explicit_i8( dst, src, order)               (c89atomic_int8 )c89atomic_fetch_add_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_fetch_add_explicit_i16(dst, src, order)               (c89atomic_int16)c89atomic_fetch_add_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_fetch_add_explicit_i32(dst, src, order)               (c89atomic_int32)c89atomic_fetch_add_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_fetch_add_explicit_i64(dst, src, order)               (c89atomic_int64)c89atomic_fetch_add_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)

#define c89atomic_fetch_sub_explicit_i8( dst, src, order)               (c89atomic_int8 )c89atomic_fetch_sub_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_fetch_sub_explicit_i16(dst, src, order)               (c89atomic_int16)c89atomic_fetch_sub_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_fetch_sub_explicit_i32(dst, src, order)               (c89atomic_int32)c89atomic_fetch_sub_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_fetch_sub_explicit_i64(dst, src, order)               (c89atomic_int64)c89atomic_fetch_sub_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)

#define c89atomic_fetch_or_explicit_i8( dst, src, order)                (c89atomic_int8 )c89atomic_fetch_or_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_fetch_or_explicit_i16(dst, src, order)                (c89atomic_int16)c89atomic_fetch_or_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_fetch_or_explicit_i32(dst, src, order)                (c89atomic_int32)c89atomic_fetch_or_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_fetch_or_explicit_i64(dst, src, order)                (c89atomic_int64)c89atomic_fetch_or_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)

#define c89atomic_fetch_xor_explicit_i8( dst, src, order)               (c89atomic_int8 )c89atomic_fetch_xor_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_fetch_xor_explicit_i16(dst, src, order)               (c89atomic_int16)c89atomic_fetch_xor_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_fetch_xor_explicit_i32(dst, src, order)               (c89atomic_int32)c89atomic_fetch_xor_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_fetch_xor_explicit_i64(dst, src, order)               (c89atomic_int64)c89atomic_fetch_xor_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)

#define c89atomic_fetch_and_explicit_i8( dst, src, order)               (c89atomic_int8 )c89atomic_fetch_and_explicit_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )src, order)
#define c89atomic_fetch_and_explicit_i16(dst, src, order)               (c89atomic_int16)c89atomic_fetch_and_explicit_16((c89atomic_uint16*)dst, (c89atomic_uint16)src, order)
#define c89atomic_fetch_and_explicit_i32(dst, src, order)               (c89atomic_int32)c89atomic_fetch_and_explicit_32((c89atomic_uint32*)dst, (c89atomic_uint32)src, order)
#define c89atomic_fetch_and_explicit_i64(dst, src, order)               (c89atomic_int64)c89atomic_fetch_and_explicit_64((c89atomic_uint64*)dst, (c89atomic_uint64)src, order)


/* Implicit Signed Integer. */
#define c89atomic_test_and_set_i8( ptr)                                 c89atomic_test_and_set_explicit_i8( ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_test_and_set_i16(ptr)                                 c89atomic_test_and_set_explicit_i16(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_test_and_set_i32(ptr)                                 c89atomic_test_and_set_explicit_i32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_test_and_set_i64(ptr)                                 c89atomic_test_and_set_explicit_i64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_clear_i8( ptr)                                        c89atomic_clear_explicit_i8( ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_i16(ptr)                                        c89atomic_clear_explicit_i16(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_i32(ptr)                                        c89atomic_clear_explicit_i32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_i64(ptr)                                        c89atomic_clear_explicit_i64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_store_i8( dst, src)                                   c89atomic_store_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_i16(dst, src)                                   c89atomic_store_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_i32(dst, src)                                   c89atomic_store_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_i64(dst, src)                                   c89atomic_store_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_load_i8( ptr)                                         c89atomic_load_explicit_i8( ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_i16(ptr)                                         c89atomic_load_explicit_i16(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_i32(ptr)                                         c89atomic_load_explicit_i32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_i64(ptr)                                         c89atomic_load_explicit_i64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_exchange_i8( dst, src)                                c89atomic_exchange_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_i16(dst, src)                                c89atomic_exchange_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_i32(dst, src)                                c89atomic_exchange_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_i64(dst, src)                                c89atomic_exchange_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_exchange_strong_i8( dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_i8( dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_i16(dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_i16(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_i32(dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_i32(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_i64(dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_i64(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_exchange_weak_i8( dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_i8( dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_i16(dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_i16(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_i32(dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_i32(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_i64(dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_i64(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_add_i8( dst, src)                               c89atomic_fetch_add_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_i16(dst, src)                               c89atomic_fetch_add_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_i32(dst, src)                               c89atomic_fetch_add_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_i64(dst, src)                               c89atomic_fetch_add_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_sub_i8( dst, src)                               c89atomic_fetch_sub_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_i16(dst, src)                               c89atomic_fetch_sub_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_i32(dst, src)                               c89atomic_fetch_sub_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_i64(dst, src)                               c89atomic_fetch_sub_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_or_i8( dst, src)                                c89atomic_fetch_or_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_i16(dst, src)                                c89atomic_fetch_or_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_i32(dst, src)                                c89atomic_fetch_or_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_i64(dst, src)                                c89atomic_fetch_or_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_xor_i8( dst, src)                               c89atomic_fetch_xor_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_i16(dst, src)                               c89atomic_fetch_xor_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_i32(dst, src)                               c89atomic_fetch_xor_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_i64(dst, src)                               c89atomic_fetch_xor_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_and_i8( dst, src)                               c89atomic_fetch_and_explicit_i8( dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_i16(dst, src)                               c89atomic_fetch_and_explicit_i16(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_i32(dst, src)                               c89atomic_fetch_and_explicit_i32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_i64(dst, src)                               c89atomic_fetch_and_explicit_i64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_and_swap_i8( dst, expected, dedsired)         (c89atomic_int8 )c89atomic_compare_and_swap_8( (c89atomic_uint8* )dst, (c89atomic_uint8 )expected, (c89atomic_uint8 )dedsired)
#define c89atomic_compare_and_swap_i16(dst, expected, dedsired)         (c89atomic_int16)c89atomic_compare_and_swap_16((c89atomic_uint16*)dst, (c89atomic_uint16)expected, (c89atomic_uint16)dedsired)
#define c89atomic_compare_and_swap_i32(dst, expected, dedsired)         (c89atomic_int32)c89atomic_compare_and_swap_32((c89atomic_uint32*)dst, (c89atomic_uint32)expected, (c89atomic_uint32)dedsired)
#define c89atomic_compare_and_swap_i64(dst, expected, dedsired)         (c89atomic_int64)c89atomic_compare_and_swap_64((c89atomic_uint64*)dst, (c89atomic_uint64)expected, (c89atomic_uint64)dedsired)


/* Floating Point Explicit. */
typedef union
{
    c89atomic_uint32 i;
    float f;
} c89atomic_if32;

typedef union
{
    c89atomic_uint64 i;
    double f;
} c89atomic_if64;

#define c89atomic_clear_explicit_f32(ptr, order)                        c89atomic_clear_explicit_32((c89atomic_uint32*)ptr, order)
#define c89atomic_clear_explicit_f64(ptr, order)                        c89atomic_clear_explicit_64((c89atomic_uint64*)ptr, order)

static C89ATOMIC_INLINE void c89atomic_store_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 x;
    x.f = src;
    c89atomic_store_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
}

static C89ATOMIC_INLINE void c89atomic_store_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 x;
    x.f = src;
    c89atomic_store_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
}


static C89ATOMIC_INLINE float c89atomic_load_explicit_f32(volatile const float* ptr, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    r.i = c89atomic_load_explicit_32((volatile const c89atomic_uint32*)ptr, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_load_explicit_f64(volatile const double* ptr, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    r.i = c89atomic_load_explicit_64((volatile const c89atomic_uint64*)ptr, order);
    return r.f;
}


static C89ATOMIC_INLINE float c89atomic_exchange_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    c89atomic_if32 x;
    x.f = src;
    r.i = c89atomic_exchange_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_exchange_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    c89atomic_if64 x;
    x.f = src;
    r.i = c89atomic_exchange_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
    return r.f;
}


static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_f32(volatile float* dst, float* expected, float desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
{
    c89atomic_if32 d;
    d.f = desired;
    return c89atomic_compare_exchange_strong_explicit_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32*)expected, d.i, successOrder, failureOrder);
}

static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_strong_explicit_f64(volatile double* dst, double* expected, double desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
{
    c89atomic_if64 d;
    d.f = desired;
    return c89atomic_compare_exchange_strong_explicit_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64*)expected, d.i, successOrder, failureOrder);
}


static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_weak_explicit_f32(volatile float* dst, float* expected, float desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
{
    c89atomic_if32 d;
    d.f = desired;
    return c89atomic_compare_exchange_weak_explicit_32((volatile c89atomic_uint32*)dst, (c89atomic_uint32*)expected, d.i, successOrder, failureOrder);
}

static C89ATOMIC_INLINE c89atomic_bool c89atomic_compare_exchange_weak_explicit_f64(volatile double* dst, double* expected, double desired, c89atomic_memory_order successOrder, c89atomic_memory_order failureOrder)
{
    c89atomic_if64 d;
    d.f = desired;
    return c89atomic_compare_exchange_weak_explicit_64((volatile c89atomic_uint64*)dst, (c89atomic_uint64*)expected, d.i, successOrder, failureOrder);
}


static C89ATOMIC_INLINE float c89atomic_fetch_add_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    c89atomic_if32 x;
    x.f = src;
    r.i = c89atomic_fetch_add_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_fetch_add_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    c89atomic_if64 x;
    x.f = src;
    r.i = c89atomic_fetch_add_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
    return r.f;
}


static C89ATOMIC_INLINE float c89atomic_fetch_sub_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    c89atomic_if32 x;
    x.f = src;
    r.i = c89atomic_fetch_sub_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_fetch_sub_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    c89atomic_if64 x;
    x.f = src;
    r.i = c89atomic_fetch_sub_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
    return r.f;
}


static C89ATOMIC_INLINE float c89atomic_fetch_or_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    c89atomic_if32 x;
    x.f = src;
    r.i = c89atomic_fetch_or_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_fetch_or_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    c89atomic_if64 x;
    x.f = src;
    r.i = c89atomic_fetch_or_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
    return r.f;
}


static C89ATOMIC_INLINE float c89atomic_fetch_xor_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    c89atomic_if32 x;
    x.f = src;
    r.i = c89atomic_fetch_xor_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_fetch_xor_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    c89atomic_if64 x;
    x.f = src;
    r.i = c89atomic_fetch_xor_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
    return r.f;
}


static C89ATOMIC_INLINE float c89atomic_fetch_and_explicit_f32(volatile float* dst, float src, c89atomic_memory_order order)
{
    c89atomic_if32 r;
    c89atomic_if32 x;
    x.f = src;
    r.i = c89atomic_fetch_and_explicit_32((volatile c89atomic_uint32*)dst, x.i, order);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_fetch_and_explicit_f64(volatile double* dst, double src, c89atomic_memory_order order)
{
    c89atomic_if64 r;
    c89atomic_if64 x;
    x.f = src;
    r.i = c89atomic_fetch_and_explicit_64((volatile c89atomic_uint64*)dst, x.i, order);
    return r.f;
}



/* Float Point Implicit */
#define c89atomic_clear_f32(ptr)                                        (float )c89atomic_clear_explicit_f32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_clear_f64(ptr)                                        (double)c89atomic_clear_explicit_f64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_store_f32(dst, src)                                   c89atomic_store_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_store_f64(dst, src)                                   c89atomic_store_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_load_f32(ptr)                                         (float )c89atomic_load_explicit_f32(ptr, c89atomic_memory_order_seq_cst)
#define c89atomic_load_f64(ptr)                                         (double)c89atomic_load_explicit_f64(ptr, c89atomic_memory_order_seq_cst)

#define c89atomic_exchange_f32(dst, src)                                (float )c89atomic_exchange_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_exchange_f64(dst, src)                                (double)c89atomic_exchange_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_exchange_strong_f32(dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_f32(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_strong_f64(dst, expected, desired)   c89atomic_compare_exchange_strong_explicit_f64(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)

#define c89atomic_compare_exchange_weak_f32(dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_f32(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)
#define c89atomic_compare_exchange_weak_f64(dst, expected, desired)     c89atomic_compare_exchange_weak_explicit_f64(dst, expected, desired, c89atomic_memory_order_seq_cst, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_add_f32(dst, src)                               c89atomic_fetch_add_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_add_f64(dst, src)                               c89atomic_fetch_add_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_sub_f32(dst, src)                               c89atomic_fetch_sub_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_sub_f64(dst, src)                               c89atomic_fetch_sub_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_or_f32(dst, src)                                c89atomic_fetch_or_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_or_f64(dst, src)                                c89atomic_fetch_or_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_xor_f32(dst, src)                               c89atomic_fetch_xor_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_xor_f64(dst, src)                               c89atomic_fetch_xor_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

#define c89atomic_fetch_and_f32(dst, src)                               c89atomic_fetch_and_explicit_f32(dst, src, c89atomic_memory_order_seq_cst)
#define c89atomic_fetch_and_f64(dst, src)                               c89atomic_fetch_and_explicit_f64(dst, src, c89atomic_memory_order_seq_cst)

static C89ATOMIC_INLINE float c89atomic_compare_and_swap_f32(volatile float* dst, float expected, float desired)
{
    c89atomic_if32 r;
    c89atomic_if32 e, d;
    e.f = expected;
    d.f = desired;
    r.i = c89atomic_compare_and_swap_32((volatile c89atomic_uint32*)dst, e.i, d.i);
    return r.f;
}

static C89ATOMIC_INLINE double c89atomic_compare_and_swap_f64(volatile double* dst, double expected, double desired)
{
    c89atomic_if64 r;
    c89atomic_if64 e, d;
    e.f = expected;
    d.f = desired;
    r.i = c89atomic_compare_and_swap_64((volatile c89atomic_uint64*)dst, e.i, d.i);
    return r.f;
}



/* Spinlock */
typedef c89atomic_flag c89atomic_spinlock;

static C89ATOMIC_INLINE void c89atomic_spinlock_lock(volatile c89atomic_spinlock* pSpinlock)
{
    for (;;) {
        if (c89atomic_flag_test_and_set_explicit(pSpinlock, c89atomic_memory_order_acquire) == 0) {
            break;
        }

        while (c89atoimc_flag_load_explicit(pSpinlock, c89atomic_memory_order_relaxed) == 1) {
            /* Do nothing. */
        }
    }
}

static C89ATOMIC_INLINE void c89atomic_spinlock_unlock(volatile c89atomic_spinlock* pSpinlock)
{
    c89atomic_flag_clear_explicit(pSpinlock, c89atomic_memory_order_release);
}


#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
    #pragma GCC diagnostic pop  /* long long warnings with Clang. */
#endif

#if defined(__cplusplus)
}
#endif
#endif  /* c89atomic_h */

/*
This software is available as a choice of the following licenses. Choose
whichever you prefer.

===============================================================================
ALTERNATIVE 1 - Public Domain (www.unlicense.org)
===============================================================================
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

===============================================================================
ALTERNATIVE 2 - MIT No Attribution
===============================================================================
Copyright 2020 David Reid

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


using AtomicUint32 = c89atomic_uint32;
using AtomicUint64 = c89atomic_uint64;
#if ARCH_32BIT
using AtomicPtr = c89atomic_uint32;
#elif ARCH_64BIT
using AtomicPtr = c89atomic_uint64;
#endif

enum class AtomicMemoryOrder : uint32
{
    Relaxed = c89atomic_memory_order_relaxed,
    Consume = c89atomic_memory_order_consume,
    Acquire = c89atomic_memory_order_acquire,
    Release = c89atomic_memory_order_release,
    Acqrel  = c89atomic_memory_order_acq_rel,
    Seqcst  = c89atomic_memory_order_seq_cst
};

namespace Atomic 
{
    FORCE_INLINE void ThreadFence(AtomicMemoryOrder order);
    FORCE_INLINE void SignalFence(AtomicMemoryOrder order);

    FORCE_INLINE uint32 Load(AtomicUint32* a);
    FORCE_INLINE uint64 Load(AtomicUint64* a);
    FORCE_INLINE uint32 LoadExplicit(AtomicUint32* a, AtomicMemoryOrder order);
    FORCE_INLINE uint64 LoadExplicit(AtomicUint64* a, AtomicMemoryOrder order);
    
    FORCE_INLINE void Store(AtomicUint32* a, uint32 b);
    FORCE_INLINE void Store(AtomicUint64* a, uint64 b);
    FORCE_INLINE void StoreExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order);
    FORCE_INLINE void StoreExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order);

    FORCE_INLINE uint32 FetchAdd(AtomicUint32* a, uint32 b);
    FORCE_INLINE uint64 FetchAdd(AtomicUint64* a, uint64 b);
    FORCE_INLINE uint32 FetchAddExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order);
    FORCE_INLINE uint64 FetchAddExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order);
    
    FORCE_INLINE uint32 FetchSub(AtomicUint32* a, uint32 b);
    FORCE_INLINE uint64 FetchSub(AtomicUint64* a, uint64 b);
    FORCE_INLINE uint32 FetchSubExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order);
    FORCE_INLINE uint64 FetchSubExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order);
    
    FORCE_INLINE uint32 FetchOR(AtomicUint32* a, uint32 b);
    FORCE_INLINE uint64 FetchOR(AtomicUint64* a, uint64 b);
    FORCE_INLINE uint32 FetchORExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order);
    FORCE_INLINE uint64 FetchORExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order);
    
    FORCE_INLINE uint32 FetchAND(AtomicUint32* a, uint32 b);
    FORCE_INLINE uint64 FetchAND(AtomicUint64* a, uint64 b);
    FORCE_INLINE uint32 FetchANDExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order);
    FORCE_INLINE uint64 FetchANDExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order);
    
    FORCE_INLINE uint32 Exchange(AtomicUint32* a, uint32 b);
    FORCE_INLINE uint64 Exchange(AtomicUint64* a, uint64 b);
    FORCE_INLINE uint64 ExchangeExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order);
    FORCE_INLINE uint32 ExchangeExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order);

    FORCE_INLINE bool CompareExchange_Weak(AtomicUint32* a, AtomicUint32* expected, uint32 desired);
    FORCE_INLINE bool CompareExchange_Strong(AtomicUint32* a, AtomicUint32* expected, uint32 desired);
    FORCE_INLINE bool CompareExchange_Weak(AtomicUint64* a, unsigned long long* expected, uint64 desired);
    FORCE_INLINE bool CompareExchange_Strong(AtomicUint64* a, unsigned long long* expected, uint64 desired);

    FORCE_INLINE bool CompareExchangeExplicit_Weak(AtomicUint32* a, uint32* expected, uint32 desired, 
                                                   AtomicMemoryOrder success, AtomicMemoryOrder fail);
    FORCE_INLINE bool CompareExchangeExplicit_Strong(AtomicUint32* a, uint32* expected, uint32 desired,
                                                     AtomicMemoryOrder success, AtomicMemoryOrder fail);
    FORCE_INLINE bool CompareExchangeExplicit_Weak(AtomicUint64* a, unsigned long long* expected, uint64 desired,
                                                   AtomicMemoryOrder success, AtomicMemoryOrder fail);
    FORCE_INLINE bool CompareExchangeExplicit_Strong(AtomicUint64* a, unsigned long long* expected, uint64 desired,
                                                     AtomicMemoryOrder success, AtomicMemoryOrder fail);
} // Atomic

FORCE_INLINE void Atomic::ThreadFence(AtomicMemoryOrder order)
{
    c89atomic_thread_fence(static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE void Atomic::SignalFence(AtomicMemoryOrder order)
{
    c89atomic_signal_fence(static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint32 Atomic::Load(AtomicUint32* a)
{
    return c89atomic_load_32(a);
}

FORCE_INLINE uint64 Atomic::Load(AtomicUint64* a)
{
    return c89atomic_load_64(a);
}

FORCE_INLINE void Atomic::Store(AtomicUint32* a, uint32 b)
{
    c89atomic_store_32(a, b);
}

FORCE_INLINE void Atomic::Store(AtomicUint64* a, uint64 b)
{
    c89atomic_store_64(a, b); 
}

FORCE_INLINE uint32 Atomic::LoadExplicit(AtomicUint32* a, AtomicMemoryOrder order)
{
    return c89atomic_load_explicit_32(a, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint64 Atomic::LoadExplicit(AtomicUint64* a, AtomicMemoryOrder order)
{
    return c89atomic_load_explicit_64(a, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE void Atomic::StoreExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order)
{
    c89atomic_store_explicit_32(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE void Atomic::StoreExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order)
{
    c89atomic_store_explicit_64(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint32 Atomic::FetchAdd(AtomicUint32* a, uint32 b)
{
    return c89atomic_fetch_add_32(a, b);
}

FORCE_INLINE uint32 Atomic::FetchSub(AtomicUint32* a, uint32 b)
{
    return c89atomic_fetch_sub_32(a, b);
}

FORCE_INLINE uint32 Atomic::FetchOR(AtomicUint32* a, uint32 b)
{
    return c89atomic_fetch_or_32(a, b);
}

FORCE_INLINE uint32 Atomic::FetchAND(AtomicUint32* a, uint32 b)
{
    return c89atomic_fetch_and_32(a, b);
}

FORCE_INLINE uint32 Atomic::Exchange(AtomicUint32* a, uint32 b)
{
    return c89atomic_exchange_32(a, b);
}

FORCE_INLINE bool Atomic::CompareExchange_Weak(AtomicUint32* a, AtomicUint32* expected, uint32 desired)
{
    return c89atomic_compare_exchange_weak_32(a, expected, desired);
}

FORCE_INLINE bool Atomic::CompareExchange_Strong(AtomicUint32* a, AtomicUint32* expected, uint32 desired)
{
    return c89atomic_compare_exchange_strong_32(a, expected, desired);
}

FORCE_INLINE uint32 Atomic::FetchAddExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_add_explicit_32(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint32 Atomic::FetchSubExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_sub_explicit_32(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint32 Atomic::FetchORExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_or_explicit_32(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint32 Atomic::FetchANDExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_and_explicit_32(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint32 Atomic::ExchangeExplicit(AtomicUint32* a, uint32 b, AtomicMemoryOrder order)
{
    return c89atomic_exchange_explicit_32(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE bool Atomic::CompareExchangeExplicit_Weak(
    AtomicUint32* a, uint32* expected, uint32 desired,
    AtomicMemoryOrder success, AtomicMemoryOrder fail)
{
    return c89atomic_compare_exchange_weak_explicit_32(a, expected, desired, 
        static_cast<c89atomic_memory_order>(success), 
        static_cast<c89atomic_memory_order>(fail));
}

FORCE_INLINE bool Atomic::CompareExchangeExplicit_Strong(
    AtomicUint32* a, uint32* expected, uint32 desired,
    AtomicMemoryOrder success, AtomicMemoryOrder fail)
{
    return c89atomic_compare_exchange_strong_explicit_32(a, expected, desired, 
        static_cast<c89atomic_memory_order>(success), 
        static_cast<c89atomic_memory_order>(fail));
}

FORCE_INLINE uint64 Atomic::FetchAdd(AtomicUint64* a, uint64 b)
{
    return c89atomic_fetch_add_64(a, b);
}

FORCE_INLINE uint64 Atomic::FetchSub(AtomicUint64* a, uint64 b)
{
    return c89atomic_fetch_sub_64(a, b);
}

FORCE_INLINE uint64 Atomic::Exchange(AtomicUint64* a, uint64 b)
{
    return c89atomic_exchange_64(a, b);
}

FORCE_INLINE uint64 Atomic::FetchOR(AtomicUint64* a, uint64 b)
{
    return c89atomic_fetch_or_64(a, b);
}

FORCE_INLINE uint64 Atomic::FetchAND(AtomicUint64* a, uint64 b)
{
    return c89atomic_fetch_and_64(a, b);
}

FORCE_INLINE bool Atomic::CompareExchange_Weak(AtomicUint64* a, unsigned long long* expected, uint64 desired)
{
    return c89atomic_compare_exchange_weak_64(a, expected, desired);
}

FORCE_INLINE bool Atomic::CompareExchange_Strong(AtomicUint64* a, unsigned long long* expected, uint64 desired)
{
    return c89atomic_compare_exchange_strong_64(a, expected, desired);
}

FORCE_INLINE uint64 Atomic::FetchAddExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_add_explicit_64(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint64 Atomic::FetchSubExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_sub_explicit_64(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint64 Atomic::ExchangeExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order)
{
    return c89atomic_exchange_explicit_64(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint64 Atomic::FetchORExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_or_explicit_64(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE uint64 Atomic::FetchANDExplicit(AtomicUint64* a, uint64 b, AtomicMemoryOrder order)
{
    return c89atomic_fetch_and_explicit_64(a, b, static_cast<c89atomic_memory_order>(order));
}

FORCE_INLINE bool Atomic::CompareExchangeExplicit_Weak(
    AtomicUint64* a, unsigned long long* expected, uint64 desired,
    AtomicMemoryOrder success, AtomicMemoryOrder fail)
{
    return c89atomic_compare_exchange_weak_explicit_64(a, expected, desired, 
        static_cast<c89atomic_memory_order>(success), 
        static_cast<c89atomic_memory_order>(fail));
}

FORCE_INLINE bool Atomic::CompareExchangeExplicit_Strong(
    AtomicUint64* a, unsigned long long* expected, uint64 desired,
    AtomicMemoryOrder success, AtomicMemoryOrder fail)
{
    return c89atomic_compare_exchange_strong_explicit_64(a, expected, desired, 
        static_cast<c89atomic_memory_order>(success), 
        static_cast<c89atomic_memory_order>(fail));
}




/*
    Copyright (C) 2014-2022 Igor van den Hoven ivdhoven@gmail.com
*/

/*
    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    */

/*
    blitsort 1.1.5.3
*/



template <typename _T, typename _Cmp> void BlitSort(_T* array, size_t count, _Cmp cmp);

namespace _private 
{
    constexpr uint32 kBlitSortOut = 24;

    template <typename _T, typename _Cmp> 
    void blit_partition(_T *array, _T *swap, size_t swap_size, size_t nmemb, _Cmp cmp);

    template <typename _T, typename _Cmp> 
    void quadsort_swap(_T *array, _T *swap, size_t swap_size, size_t nmemb, _Cmp cmp);

    template <typename _T, typename _Cmp> 
    void blit_merge_block(_T *array, _T *swap, size_t swap_size, size_t lblock, size_t right, _Cmp cmp);

    template <typename _T, typename _Cmp>
    void trinity_rotation(_T *array, _T *swap, size_t swap_size, size_t nmemb, size_t left);


    template <typename _T, typename _Cmp> 
    void parity_merge_two(_T *array,  _T *swap, size_t x, size_t y, _T *ptl, _T *ptr, _T *pts, _Cmp cmp)  
    {  
        ptl = array + 0; ptr = array + 2; pts = swap + 0;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts[x] = *ptr; ptr += y; pts[y] = *ptl; ptl += x; pts++;  
        *pts = cmp(*ptl, *ptr) <= 0 ? *ptl : *ptr;  
        
        ptl = array + 1; ptr = array + 3; pts = swap + 3;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts--; pts[x] = *ptr; ptr -= x; pts[y] = *ptl; ptl -= y;  
        *pts = cmp(*ptl, *ptr)  > 0 ? *ptl : *ptr;  
    }

    template <typename _T, typename _Cmp> 
    void parity_merge_four(_T *array, _T *swap, size_t x, size_t y, _T *ptl, _T *ptr, _T *pts, _Cmp cmp)  
    {  
        ptl = array + 0; ptr = array + 4; pts = swap;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts[x] = *ptr; ptr += y; pts[y] = *ptl; ptl += x; pts++;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts[x] = *ptr; ptr += y; pts[y] = *ptl; ptl += x; pts++;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts[x] = *ptr; ptr += y; pts[y] = *ptl; ptl += x; pts++;  
        *pts = cmp(*ptl, *ptr) <= 0 ? *ptl : *ptr;  
        
        ptl = array + 3; ptr = array + 7; pts = swap + 7;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts--; pts[x] = *ptr; ptr -= x; pts[y] = *ptl; ptl -= y;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts--; pts[x] = *ptr; ptr -= x; pts[y] = *ptl; ptl -= y;  
        x = cmp(*ptl, *ptr) <= 0; y = !x; pts--; pts[x] = *ptr; ptr -= x; pts[y] = *ptl; ptl -= y;  
        *pts = cmp(*ptl, *ptr)  > 0 ? *ptl : *ptr;  
    }

    template <typename _T, typename _Cmp> 
    void blit_analyze(_T* array, _T* swap, size_t swap_size, size_t nmemb, _Cmp cmp)
    {
        char loop, asum, zsum;
        size_t cnt, abalance = 0, zbalance = 0, astreaks = 0, zstreaks = 0;
        _T *pta, *ptz, tmp;
    
        pta = array;
        ptz = array + nmemb - 2;
    
        for (cnt = nmemb ; cnt > 64 ; cnt -= 64)
        {
            for (asum = zsum = 0, loop = 32 ; loop ; loop--)
            {
                asum += cmp(*pta, *(pta + 1)) > 0; pta++;
                zsum += cmp(*ptz, *(ptz + 1)) > 0; ptz--;
            }
            astreaks += (asum == 0) | (asum == 32);
            zstreaks += (zsum == 0) | (zsum == 32);
            abalance += asum;
            zbalance += zsum;
        }
    
        while (--cnt)
        {
            zbalance += cmp(*ptz, *(ptz + 1)) > 0; ptz--;
        }
    
        if (abalance + zbalance == 0)
        {
            return;
        }
    
        if (abalance + zbalance == nmemb - 1)
        {
            ptz = array + nmemb;
            pta = array;
    
            cnt = nmemb / 2;
    
            do
            {
                tmp = *pta; *pta++ = *--ptz; *ptz = tmp;
            }
            while (--cnt);
    
            return;
        }
    
        if (astreaks + zstreaks > nmemb / 80)
        {
            if (nmemb >= 1024)
            {
                size_t block = pta - array;
    
                if (astreaks < nmemb / 128)
                {
                    blit_partition<_T, _Cmp>(array, swap, swap_size, block, cmp);
                }
                else if (abalance)
                {
                    quadsort_swap<_T, _Cmp>(array, swap, swap_size, block, cmp);
                }
    
                if (zstreaks < nmemb / 128)
                {
                    blit_partition<_T, _Cmp>(array + block, swap, swap_size, nmemb - block, cmp);
                }
                else if (zbalance)
                {
                    quadsort_swap<_T, _Cmp>(array + block, swap, swap_size, nmemb - block, cmp);
                }
                blit_merge_block<_T, _Cmp>(array, swap, swap_size, block, nmemb - block, cmp);
            }
            else
            {
                quadsort_swap<_T, _Cmp>(array, swap, swap_size, nmemb, cmp);
            }
            return;
        }
        blit_partition<_T, _Cmp>(array, swap, swap_size, nmemb, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    _T blit_median_of_sqrt(_T *array, _T *swap, size_t swap_size, size_t nmemb, _Cmp cmp)
    {
        UNUSED(swap_size);
        _T *pta, *pts;
        size_t cnt, sqrt, div;
    
        sqrt = nmemb > 262144 ? 256 : 128;
    
        div = nmemb / sqrt;
    
        pta = array + Random::Int() % sqrt;
        pts = swap;
    
        for (cnt = 0 ; cnt < sqrt ; cnt++)
        {
            pts[cnt] = pta[0];
    
            pta += div;
        }
        quadsort_swap<_T, _Cmp>(pts, pts + sqrt, sqrt, sqrt, cmp);
    
        return pts[sqrt / 2];
    }
    
    template <typename _T, typename _Cmp> 
    _T blit_median_of_five(_T *array, size_t v0, size_t v1, size_t v2, size_t v3, size_t v4, _Cmp cmp)
    {
        _T swap[6], *pta;
        size_t x, y, z;
    
        swap[2] = array[v0];
        swap[3] = array[v1];
        swap[4] = array[v2];
        swap[5] = array[v3];
    
        pta = swap + 2;
    
        x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap[0] = pta[y]; pta[0] = pta[x]; pta[1] = swap[0]; pta += 2;
        x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap[0] = pta[y]; pta[0] = pta[x]; pta[1] = swap[0]; pta -= 2;
        x = cmp(*pta, *(pta + 2)) > 0; y = !x; swap[0] = pta[0]; swap[1] = pta[2]; pta[0] = swap[x]; pta[2] = swap[y]; pta++;
        x = cmp(*pta, *(pta + 2)) > 0; y = !x; swap[0] = pta[0]; swap[1] = pta[2]; pta[0] = swap[x]; pta[2] = swap[y];
    
        pta[2] = array[v4];
    
        x = cmp(*pta, *(pta + 1)) > 0;
        y = cmp(*pta, *(pta + 2)) > 0;
        z = cmp(*(pta + 1), *(pta + 2)) > 0;
    
        return pta[(x == y) + (y ^ z)];
    }
    
    template <typename _T, typename _Cmp> 
    _T blit_median_of_twentyfive(_T *array, size_t nmemb, _Cmp cmp)
    {
        _T swap[5];
        size_t div = nmemb / 64;
    
        swap[0] = blit_median_of_five<_T, _Cmp>(array, div *  4, div *  1, div *  2, div *  8, div * 10, cmp);
        swap[1] = blit_median_of_five<_T, _Cmp>(array, div * 16, div * 12, div * 14, div * 18, div * 20, cmp);
        swap[2] = blit_median_of_five<_T, _Cmp>(array, div * 32, div * 24, div * 30, div * 34, div * 38, cmp);
        swap[3] = blit_median_of_five<_T, _Cmp>(array, div * 48, div * 42, div * 44, div * 50, div * 52, cmp);
        swap[4] = blit_median_of_five<_T, _Cmp>(array, div * 60, div * 54, div * 56, div * 62, div * 63, cmp);
    
        return blit_median_of_five<_T, _Cmp>(swap, 0, 1, 2, 3, 4, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    size_t blit_median_of_three(_T *array, size_t v0, size_t v1, size_t v2, _Cmp cmp)
    {
        size_t v[3] = {v0, v1, v2};
        char x, y, z;
    
        x = cmp(*(array + v0), *(array + v1)) > 0;
        y = cmp(*(array + v0), *(array + v2)) > 0;
        z = cmp(*(array + v1), *(array + v2)) > 0;
    
        return v[(x == y) + (y ^ z)];
    }
    
    template <typename _T, typename _Cmp> 
    _T blit_median_of_nine(_T *array, size_t nmemb, _Cmp cmp)
    {
        size_t x, y, z, div = nmemb / 16;
    
        x = blit_median_of_three<_T, _Cmp>(array, div * 2, div * 1, div * 4, cmp);
        y = blit_median_of_three<_T, _Cmp>(array, div * 8, div * 6, div * 10, cmp);
        z = blit_median_of_three<_T, _Cmp>(array, div * 14, div * 12, div * 15, cmp);
    
        return array[blit_median_of_three<_T, _Cmp>(array, x, y, z, cmp)];
    }
    
    template <typename _T, typename _Cmp> 
    size_t blit_reverse_partition(_T *array, _T *swap, _T *piv, size_t swap_size, size_t nmemb, _Cmp cmp)
    {
        if (nmemb > swap_size)
        {
            size_t l, r, h = nmemb / 2;
    
            l = blit_reverse_partition<_T, _Cmp>(array + 0, swap, piv, swap_size, h, cmp);
            r = blit_reverse_partition<_T, _Cmp>(array + h, swap, piv, swap_size, nmemb - h, cmp);
    
            trinity_rotation<_T, _Cmp>(array + l, swap, swap_size, h - l + r, h - l);
    
            return l + r;
        }
        size_t cnt, val, m;
        _T *pta = array;
    
        for (m = 0, cnt = nmemb / 4 ; cnt ; cnt--)
        {
            val = cmp(*piv, *pta) > 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
            val = cmp(*piv, *pta) > 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
            val = cmp(*piv, *pta) > 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
            val = cmp(*piv, *pta) > 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
        }
    
        for (cnt = nmemb % 4 ; cnt ; cnt--)
        {
            val = cmp(*piv, *pta) > 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
        }
    
        memcpy(array + m, swap - nmemb, (nmemb - m) * sizeof(_T));
    
        return m;
    }

    template <typename _T, typename _Cmp> 
    size_t blit_default_partition(_T *array, _T *swap, _T *piv, size_t swap_size, size_t nmemb, _Cmp cmp)
    {
        if (nmemb > swap_size)
        {
            size_t l, r, h = nmemb / 2;
    
            l = blit_default_partition<_T, _Cmp>(array + 0, swap, piv, swap_size, h, cmp);
            r = blit_default_partition<_T, _Cmp>(array + h, swap, piv, swap_size, nmemb - h, cmp);
    
            trinity_rotation<_T, _Cmp>(array + l, swap, swap_size, h - l + r, h - l);
    
            return l + r;
        }
        size_t cnt, val, m = 0;
        _T *pta = array;
    
        for (cnt = nmemb / 4 ; cnt ; cnt--)
        {
            val = cmp(*pta, *piv) <= 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
            val = cmp(*pta, *piv) <= 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
            val = cmp(*pta, *piv) <= 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
            val = cmp(*pta, *piv) <= 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
        }
    
        for (cnt = nmemb % 4 ; cnt ; cnt--)
        {
            val = cmp(*pta, *piv) <= 0; swap[-(int64)m] = array[m] = *pta++; m += val; swap++;
        }
    
        memcpy(array + m, swap - nmemb, sizeof(_T) * (nmemb - m));
    
        return m;
    }
    
    template <typename _T, typename _Cmp> 
    void blit_partition(_T *array, _T *swap, size_t swap_size, size_t nmemb, _Cmp cmp)
    {
        size_t a_size = 0, s_size;
        _T piv, max {};
    
        while (1)
        {
            if (nmemb <= 2048)
            {
                piv = blit_median_of_nine<_T, _Cmp>(array, nmemb, cmp);
            }
            else if (nmemb <= 65536 || swap_size < 512)
            {
                piv = blit_median_of_twentyfive<_T, _Cmp>(array, nmemb, cmp);
            }
            else
            {
                piv = blit_median_of_sqrt<_T, _Cmp>(array, swap, swap_size, nmemb, cmp);
            }
    
            if (a_size && cmp(max, piv) <= 0)
            {
                a_size = blit_reverse_partition<_T, _Cmp>(array, swap, &piv, swap_size, nmemb, cmp);
                s_size = nmemb - a_size;
    
                if (s_size <= a_size / 16 || a_size <= kBlitSortOut)
                {
                    return quadsort_swap<_T, _Cmp>(array, swap, swap_size, a_size, cmp);
                }
                nmemb = a_size; a_size = 0;
                continue;
            }
    
            a_size = blit_default_partition<_T, _Cmp>(array, swap, &piv, swap_size, nmemb, cmp);
            s_size = nmemb - a_size;
    
            if (a_size <= s_size / 16 || s_size <= kBlitSortOut)
            {
                if (s_size == 0)
                {
                    a_size = blit_reverse_partition<_T, _Cmp>(array, swap, &piv, swap_size, a_size, cmp);
                    s_size = nmemb - a_size;
    
                    if (s_size <= a_size / 16 || a_size <= kBlitSortOut)
                    {
                        return quadsort_swap<_T, _Cmp>(array, swap, swap_size, a_size, cmp);
                    }
                    nmemb = a_size; a_size = 0;
                    continue;
                }
                quadsort_swap<_T, _Cmp>(array + a_size, swap, swap_size, s_size, cmp);
            }
            else
            {
                blit_partition<_T, _Cmp>(array + a_size, swap, swap_size, s_size, cmp);
            }
    
            if (s_size <= a_size / 16 || a_size <= kBlitSortOut)
            {
                return quadsort_swap<_T, _Cmp>(array, swap, swap_size, a_size, cmp);
            }
            nmemb = a_size;
            max = piv;
        }
    }
    
    template <typename _T, typename _Cmp>     
    void unguarded_insert(_T *array, size_t offset, size_t nmemb, _Cmp cmp)
    {
        _T key, *pta, *end;
        size_t i, top, x, y;
    
        for (i = offset ; i < nmemb ; i++)
        {
            pta = end = array + i;
    
            if (cmp(*(--pta), *end) <= 0)
            {
                continue;
            }
    
            key = *end;
    
            if (cmp(*(array + 1), key) > 0)
            {
                top = i - 1;
    
                do
                {
                    *end-- = *pta--;
                }
                while (--top);
    
                *end-- = key;
            }
            else
            {
                do
                {
                    *end-- = *pta--;
                    *end-- = *pta--;
                }
                while (cmp(*pta, key) > 0);
    
                end[0] = end[1];
                end[1] = key;
            }
            x = cmp(*end, *(end + 1)) > 0; y = !x; key = end[y]; end[0] = end[x]; end[1] = key;
        }
    }
    
    template <typename _T, typename _Cmp> 
    void bubble_sort(_T *array, size_t nmemb, _Cmp cmp)
    {
        _T swap, *pta;
        size_t x, y;
    
        if (nmemb > 1)
        {
            pta = array;
    
            if (nmemb > 2)
            {
                x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap; pta++;
                x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap; pta--;
            }
            x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap;
        }
    }
    
    template <typename _T, typename _Cmp> 
    void quad_swap_four(_T *array, _Cmp cmp)
    {
        _T *pta, swap;
        size_t x, y;
    
        pta = array;
        x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap; pta += 2;
        x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap; pta--;
    
        if (cmp(*pta, *(pta + 1)) > 0)
        {
            swap = pta[0]; pta[0] = pta[1]; pta[1] = swap; pta--;
    
            x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap; pta += 2;
            x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap; pta--;
            x = cmp(*pta, *(pta + 1)) > 0; y = !x; swap = pta[y]; pta[0] = pta[x]; pta[1] = swap;
        }
    }
    
    template <typename _T, typename _Cmp> 
    void parity_swap_eight(_T *array, _Cmp cmp)
    {
        _T swap[8], *ptl = nullptr, *ptr = nullptr, *pts = nullptr;
        unsigned char x, y;
    
        ptl = array;
        x = cmp(*ptl, *(ptl + 1)) > 0; y = !x; swap[0] = ptl[y]; ptl[0] = ptl[x]; ptl[1] = swap[0]; ptl += 2;
        x = cmp(*ptl, *(ptl + 1)) > 0; y = !x; swap[0] = ptl[y]; ptl[0] = ptl[x]; ptl[1] = swap[0]; ptl += 2;
        x = cmp(*ptl, *(ptl + 1)) > 0; y = !x; swap[0] = ptl[y]; ptl[0] = ptl[x]; ptl[1] = swap[0]; ptl += 2;
        x = cmp(*ptl, *(ptl + 1)) > 0; y = !x; swap[0] = ptl[y]; ptl[0] = ptl[x]; ptl[1] = swap[0];
    
        if (cmp(*(array + 1), *(array + 2)) <= 0 && cmp(*(array + 3), *(array + 4)) <= 0 && cmp(*(array + 5), *(array + 6)) <= 0)
        {
            return;
        }
        parity_merge_two<_T, _Cmp>(array + 0, swap + 0, x, y, ptl, ptr, pts, cmp);
        parity_merge_two<_T, _Cmp>(array + 4, swap + 4, x, y, ptl, ptr, pts, cmp);
    
        parity_merge_four<_T, _Cmp>(swap, array, x, y, ptl, ptr, pts, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    void parity_merge(_T *dest, _T *from, size_t block, size_t nmemb, _Cmp cmp)
    {
        _T *ptl, *ptr, *tpl, *tpr, *tpd, *ptd;
        unsigned char x, y;
    
        ptl = from;
        ptr = from + block;
        ptd = dest;
        tpl = from + block - 1;
        tpr = from + nmemb - 1;
        tpd = dest + nmemb - 1;
    
        while (--block)
        {
            x = cmp(*ptl, *ptr) <= 0; y = !x; ptd[x] = *ptr; ptr += y; ptd[y] = *ptl; ptl += x; ptd++;
            x = cmp(*tpl, *tpr) <= 0; y = !x; tpd--; tpd[x] = *tpr; tpr -= x; tpd[y] = *tpl; tpl -= y;
        }
        *ptd = cmp(*ptl, *ptr) <= 0 ? *ptl : *ptr;
        *tpd = cmp(*tpl, *tpr)  > 0 ? *tpl : *tpr;
    }

    template <typename _T, typename _Cmp> 
    void parity_swap_sixteen(_T *array, _Cmp cmp)
    {
        _T swap[16], *ptl = nullptr, *ptr = nullptr, *pts = nullptr;
        unsigned char x = 0, y = 0;
    
        quad_swap_four<_T, _Cmp>(array +  0, cmp);
        quad_swap_four<_T, _Cmp>(array +  4, cmp);
        quad_swap_four<_T, _Cmp>(array +  8, cmp);
        quad_swap_four<_T, _Cmp>(array + 12, cmp);
    
        if (cmp(*(array + 3), *(array + 4)) <= 0 && cmp(*(array + 7), *(array + 8)) <= 0 && cmp(*(array + 11), *(array + 12)) <= 0)
        {
            return;
        }
        parity_merge_four<_T, _Cmp>(array + 0, swap + 0, x, y, ptl, ptr, pts, cmp);
        parity_merge_four<_T, _Cmp>(array + 8, swap + 8, x, y, ptl, ptr, pts, cmp);
    
        parity_merge<_T, _Cmp>(array, swap, 8, 16, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    void tail_swap(_T *array, size_t nmemb, _Cmp cmp)
    {
        if (nmemb < 4)
        {
            bubble_sort<_T, _Cmp>(array, nmemb, cmp);
            return;
        }
        if (nmemb < 8)
        {
            quad_swap_four<_T, _Cmp>(array, cmp);
            unguarded_insert<_T, _Cmp>(array, 4, nmemb, cmp);
            return;
        }
        if (nmemb < 16)
        {
            parity_swap_eight<_T, _Cmp>(array, cmp);
            unguarded_insert<_T, _Cmp>(array, 8, nmemb, cmp);
            return;
        }
        parity_swap_sixteen<_T, _Cmp>(array, cmp);
        unguarded_insert<_T, _Cmp>(array, 16, nmemb, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    void parity_tail_swap_eight(_T *array, _Cmp cmp)
    {
        _T swap[8], *ptl = nullptr, *ptr = nullptr, *pts = nullptr;
        unsigned char x = 0, y = 0;
    
        if (cmp(*(array + 4), *(array + 5)) > 0) { swap[5] = array[4]; array[4] = array[5]; array[5] = swap[5]; }
        if (cmp(*(array + 6), *(array + 7)) > 0) { swap[7] = array[6]; array[6] = array[7]; array[7] = swap[7]; } else
    
            if (cmp(*(array + 3), *(array + 4)) <= 0 && cmp(*(array + 5), *(array + 6)) <= 0)
            {
                return;
            }
            swap[0] = array[0]; swap[1] = array[1]; swap[2] = array[2]; swap[3] = array[3];
    
            parity_merge_two<_T, _Cmp>(array + 4, swap + 4, x, y, ptl, ptr, pts, cmp);
    
            parity_merge_four<_T, _Cmp>(swap, array, x, y, ptl, ptr, pts, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    void parity_tail_flip_eight(_T *array, _Cmp cmp)
    {
        _T swap[8], *ptl = nullptr, *ptr = nullptr, *pts = nullptr;
        unsigned char x = 0, y = 0;
    
        if (cmp(*(array + 3), *(array + 4)) <= 0)
        {
            return;
        }
        swap[0] = array[0]; swap[1] = array[1]; swap[2] = array[2]; swap[3] = array[3];
        swap[4] = array[4]; swap[5] = array[5]; swap[6] = array[6]; swap[7] = array[7];
    
        parity_merge_four<_T, _Cmp>(swap, array, x, y, ptl, ptr, pts, cmp);
    }
    
    template <typename _T, typename _Cmp> 
    void tail_merge(_T *array, _T *swap, size_t swap_size, size_t nmemb, size_t block, _Cmp cmp);
    
    template <typename _T, typename _Cmp> 
    size_t quad_swap(_T *array, size_t nmemb, _Cmp cmp)
    {
        _T swap[32];
        size_t count, reverse, x, y;
        _T *pta, *pts, *pte, tmp;
    
        pta = array;
    
        count = nmemb / 8 * 2;
    
        while (count--)
        {
            switch ((cmp(*pta, *(pta + 1)) > 0) | (cmp(*(pta + 1), *(pta + 2)) > 0) * 2 | (cmp(*(pta + 2), *(pta + 3)) > 0) * 4)
            {
            case 0:
                break;
            case 1:
                tmp = pta[0]; pta[0] = pta[1]; pta[1] = tmp;
                pta += 1; x = cmp(*pta, *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta += 1; x = cmp(*pta, *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 2;
                break;
            case 2:
                tmp = pta[1]; pta[1] = pta[2]; pta[2] = tmp;
                x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta += 2; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 1;
                break;
            case 3:
                tmp = pta[0]; pta[0] = pta[2]; pta[2] = tmp;
                pta += 2; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 1;
                break;
            case 4:
                tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
                pta += 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                break;
            case 5:
                tmp = pta[0]; pta[0] = pta[1]; pta[1] = tmp;
                tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
                pta += 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta += 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 2; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                break;
            case 6:
                tmp = pta[1]; pta[1] = pta[3]; pta[3] = tmp;
                x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta += 1; x = cmp(*(pta), *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp;
                pta -= 1;
                break;
            case 7:
                pts = pta;
                goto swapper;
            }
            count--;
    
            parity_tail_swap_eight<_T, _Cmp>(pta, cmp);
    
            pta += 8;
    
            continue;
    
            swapper:
    
                pta += 4;
    
            if (count--)
            {
                if (cmp(pta[0], pta[1]) > 0)
                {
                    if (cmp(pta[2], pta[3]) > 0)
                    {
                        if (cmp(pta[1], pta[2]) > 0)
                        {
                            if (cmp(pta[-1], pta[0]) > 0)
                            {
                                goto swapper;
                            }
                        }
                        tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
                    }
                    tmp = pta[0]; pta[0] = pta[1]; pta[1] = tmp;
                }
                else if (cmp(pta[2], pta[3]) > 0)
                {
                    tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
                }
    
                if (cmp(pta[1], pta[2]) > 0)
                {
                    tmp = pta[1]; pta[1] = pta[2]; pta[2] = tmp;
    
                    x = cmp(*pta, *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp; pta += 2;
                    x = cmp(*pta, *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp; pta -= 1;
                    x = cmp(*pta, *(pta + 1)) > 0; y = !x; tmp = pta[y]; pta[0] = pta[x]; pta[1] = tmp; pta -= 1;
                }
                pte = pta - 1;
    
                reverse = (pte - pts) / 2;
    
                do
                {
                    tmp = *pts; *pts++ = *pte; *pte-- = tmp;
                }
                while (reverse--);
    
                if (count % 2 == 0)
                {
                    pta -= 4;
    
                    parity_tail_flip_eight<_T, _Cmp>(pta, cmp);
                }
                else
                {
                    count--;
    
                    parity_tail_swap_eight<_T, _Cmp>(pta, cmp);
                }
                pta += 8;
    
                continue;
            }
    
            if (pts == array)
            {
                switch (nmemb % 8)
                {
                case 7: if (cmp(*(pta + 5), *(pta + 6)) <= 0) break;
                case 6: if (cmp(*(pta + 4), *(pta + 5)) <= 0) break;
                case 5: if (cmp(*(pta + 3), *(pta + 4)) <= 0) break;
                case 4: if (cmp(*(pta + 2), *(pta + 3)) <= 0) break;
                case 3: if (cmp(*(pta + 1), *(pta + 2)) <= 0) break;
                case 2: if (cmp(*(pta + 0), *(pta + 1)) <= 0) break;
                case 1: if (cmp(*(pta - 1), *(pta + 0)) <= 0) break;
                case 0:
                    pte = pts + nmemb - 1;
    
                    reverse = (pte - pts) / 2;
    
                    do
                    {
                        tmp = *pts; *pts++ = *pte; *pte-- = tmp;
                    }
                    while (reverse--);
    
                    return 1;
                }
            }
            pte = pta - 1;
    
            reverse = (pte - pts) / 2;
    
            do
            {
                tmp = *pts; *pts++ = *pte; *pte-- = tmp;
            }
            while (reverse--);
    
            break;
        }
    
        tail_swap<_T, _Cmp>(pta, nmemb % 8, cmp);
    
        pta = array;
    
        for (count = nmemb / 32 ; count-- ; pta += 32)
        {
            if (cmp(*(pta + 7), *(pta + 8)) <= 0 && cmp(*(pta + 15), *(pta + 16)) <= 0 && cmp(*(pta + 23), *(pta + 24)) <= 0)
            {
                continue;
            }
            parity_merge<_T, _Cmp>(swap, pta, 8, 16, cmp);
            parity_merge<_T, _Cmp>(swap + 16, pta + 16, 8, 16, cmp);
            parity_merge<_T, _Cmp>(pta, swap, 16, 32, cmp);
        }
    
        if (nmemb % 32 > 8)
        {
            tail_merge<_T, _Cmp>(pta, swap, 32, nmemb % 32, 8, cmp);
        }
        return 0;
    }
    
    template <typename _T, typename _Cmp> 
    void forward_merge(_T *dest, _T *from, size_t block, _Cmp cmp)
    {
        _T *ptl, *ptr, *m, *e; // left, right, middle, end
        size_t x, y;
    
        ptl = from;
        ptr = from + block;
        m = ptr - 1;
        e = ptr + block - 1;
    
        if (cmp(*m, *(e - block / 4)) <= 0)
        {
            while (ptl < m - 1)
            {
                if (cmp(*(ptl + 1), *ptr) <= 0)
                {
                    *dest++ = *ptl++; *dest++ = *ptl++;
                }
                else if (cmp(*ptl, *(ptr + 1)) > 0)
                {
                    *dest++ = *ptr++; *dest++ = *ptr++;
                }
                else 
                {
                    x = cmp(*ptl, *ptr) <= 0; y = !x; dest[x] = *ptr; ptr += 1; dest[y] = *ptl; ptl += 1; dest += 2;
                    x = cmp(*ptl, *ptr) <= 0; y = !x; dest[x] = *ptr; ptr += y; dest[y] = *ptl; ptl += x; dest++;
                }
            }
    
            while (ptl <= m)
            {
                *dest++ = cmp(*ptl, *ptr) <= 0 ? *ptl++ : *ptr++;
            }
    
            do *dest++ = *ptr++; while (ptr <= e);
        }
        else if (cmp(*(m - block / 4), *e) > 0)
        {
            while (ptr < e - 1)
            {
                if (cmp(*ptl, *(ptr + 1)) > 0)
                {
                    *dest++ = *ptr++; *dest++ = *ptr++;
                }
                else if (cmp(*(ptl + 1), *ptr) <= 0)
                {
                    *dest++ = *ptl++; *dest++ = *ptl++;
                }
                else 
                {
                    x = cmp(*ptl, *ptr) <= 0; y = !x; dest[x] = *ptr; ptr += 1; dest[y] = *ptl; ptl += 1; dest += 2;
                    x = cmp(*ptl, *ptr) <= 0; y = !x; dest[x] = *ptr; ptr += y; dest[y] = *ptl; ptl += x; dest++;
                }
            }
    
            while (ptr <= e)
            {
                *dest++ = cmp(*ptl, *ptr) > 0 ? *ptr++ : *ptl++;
            }
    
            do *dest++ = *ptl++; while (ptl <= m);
        }
        else
        {
            parity_merge<_T, _Cmp>(dest, from, block, block * 2, cmp);
        }
    }
    
    template <typename _T, typename _Cmp> 
    void quad_merge_block(_T *array, _T *swap, size_t block, _Cmp cmp)
    {
        _T *pts = nullptr, *c, *c_max;
        size_t block_x_2 = block * 2;
    
        c_max = array + block;
    
        if (cmp(*(c_max - 1), *c_max) <= 0)
        {
            c_max += block_x_2;
    
            if (cmp(*(c_max - 1), *c_max) <= 0)
            {
                c_max -= block;
    
                if (cmp(*(c_max - 1), *c_max) <= 0)
                {
                    return;
                }
                pts = swap;
    
                c = array;
    
                do *pts++ = *c++; while (c < c_max); // step 1
    
                c_max = c + block_x_2;
    
                do *pts++ = *c++; while (c < c_max); // step 2
    
                return forward_merge<_T, _Cmp>(array, swap, block_x_2, cmp); // step 3
            }
            pts = swap;
    
            c = array;
            c_max = array + block_x_2;
    
            do *pts++ = *c++; while (c < c_max); // step 1
        }
        else
        {
            forward_merge<_T, _Cmp>(swap, array, block, cmp); // step 1
        }
        forward_merge<_T, _Cmp>(swap + block_x_2, array + block_x_2, block, cmp); // step 2
    
        forward_merge<_T, _Cmp>(array, swap, block_x_2, cmp); // step 3
    }
    
    template <typename _T, typename _Cmp> 
    size_t quad_merge(_T *array, _T *swap, size_t swap_size, size_t nmemb, size_t block, _Cmp cmp)
    {
        _T *pta, *pte;
    
        pte = array + nmemb;
    
        block *= 4;
    
        while (block <= nmemb && block <= swap_size)
        {
            pta = array;
    
            do
            {
                quad_merge_block<_T, _Cmp>(pta, swap, block / 4, cmp);
    
                pta += block;
            }
            while (pta + block <= pte);
    
            tail_merge<_T, _Cmp>(pta, swap, swap_size, pte - pta, block / 4, cmp);
    
            block *= 4;
        }
    
        tail_merge<_T, _Cmp>(array, swap, swap_size, nmemb, block / 4, cmp);
    
        return block / 2;
    }
    
    template <typename _T, typename _Cmp> 
    void partial_forward_merge(_T *array, _T *swap, size_t nmemb, size_t block, _Cmp cmp)
    {
        _T *r, *m, *e, *s; // right, middle, end, swap
        size_t x, y;
    
        r = array + block;
        e = array + nmemb - 1;
    
        memcpy(swap, array, block * sizeof(_T));
    
        s = swap;
        m = swap + block - 1;
    
        while (s < m - 1 && r < e - 1)
        {
            if (cmp(*s, *(r + 1)) > 0)
            {
                *array++ = *r++; *array++ = *r++;
            }
            else if (cmp(*(s + 1), *r) <= 0)
            {
                *array++ = *s++; *array++ = *s++;
            }
            else 
            {
                x = cmp(*s, *r) <= 0; y = !x; array[x] = *r; r += 1; array[y] = *s; s += 1; array += 2;
                x = cmp(*s, *r) <= 0; y = !x; array[x] = *r; r += y; array[y] = *s; s += x; array++;
            }
        }
    
        while (s <= m && r <= e)
        {
            *array++ = cmp(*s, *r) <= 0 ? *s++ : *r++;
        }
    
        while (s <= m)
        {
            *array++ = *s++;
        }
    }
    
    template <typename _T, typename _Cmp> 
    void partial_backward_merge(_T *array, _T *swap, size_t nmemb, size_t block, _Cmp cmp)
    {
        _T *m, *e, *s; // middle, end, swap
        size_t x, y;
    
        m = array + block - 1;
        e = array + nmemb - 1;
    
        if (cmp(*m, *(m + 1)) <= 0)
        {
            return;
        }
    
        memcpy(swap, array + block, (nmemb - block) * sizeof(_T));
    
        s = swap + nmemb - block - 1;
    
        while (s > swap + 1 && m > array + 1)
        {
            if (cmp(*(m - 1), *s) > 0)
            {
                *e-- = *m--;
                *e-- = *m--;
            }
            else if (cmp(*m, *(s - 1)) <= 0)
            {
                *e-- = *s--;
                *e-- = *s--;
            }
            else
            {
                x = cmp(*m, *s) <= 0; y = !x; e--; e[x] = *s; s -= 1; e[y] = *m; m -= 1; e--;
                x = cmp(*m, *s) <= 0; y = !x; e--; e[x] = *s; s -= x; e[y] = *m; m -= y;
            }
        }
    
        while (s >= swap && m >= array)
        {
            *e-- = cmp(*m, *s) > 0 ? *m-- : *s--;
        }
    
        while (s >= swap)
        {
            *e-- = *s--;
        }
    }
    
    template <typename _T, typename _Cmp> 
    void tail_merge(_T *array, _T *swap, size_t swap_size, size_t nmemb, size_t block, _Cmp cmp)
    {
        _T *pta, *pte;
    
        pte = array + nmemb;
    
        while (block < nmemb && block <= swap_size)
        {
            for (pta = array ; pta + block < pte ; pta += block * 2)
            {
                if (pta + block * 2 < pte)
                {
                    partial_backward_merge<_T, _Cmp>(pta, swap, block * 2, block, cmp);
    
                    continue;
                }
                partial_backward_merge<_T, _Cmp>(pta, swap, pte - pta, block, cmp);
    
                break;
            }
            block *= 2;
        }
    }
    
    template <typename _T, typename _Cmp>
    void trinity_rotation(_T *array, _T *swap, size_t swap_size, size_t nmemb, size_t left)
    {
        size_t bridge, right = nmemb - left;
    
        if (left < right)
        {
            if (left <= swap_size)
            {
                memcpy(swap, array, left * sizeof(_T));
                memmove(array, array + left, right * sizeof(_T));
                memcpy(array + right, swap, left * sizeof(_T));
            }
            else
            {
                _T *pta, *ptb, *ptc, *ptd;
    
                pta = array;
                ptb = pta + left;
    
                bridge = right - left;
    
                if (bridge <= swap_size && bridge > 3)
                {
                    ptc = pta + right;
                    ptd = ptc + left;
    
                    memcpy(swap, ptb, bridge * sizeof(_T));
    
                    while (left--)
                    {
                        *--ptc = *--ptd; *ptd = *--ptb;
                    }
                    memcpy(pta, swap, bridge * sizeof(_T));
                }
                else
                {
                    ptc = ptb;
                    ptd = ptc + right;
    
                    bridge = left / 2;
    
                    while (bridge--)
                    {
                        *swap = *--ptb; *ptb = *pta; *pta++ = *ptc; *ptc++ = *--ptd; *ptd = *swap;
                    }
    
                    bridge = (ptd - ptc) / 2;
    
                    while (bridge--)
                    {
                        *swap = *ptc; *ptc++ = *--ptd; *ptd = *pta; *pta++ = *swap;
                    }
    
                    bridge = (ptd - pta) / 2;
    
                    while (bridge--)
                    {
                        *swap = *pta; *pta++ = *--ptd; *ptd = *swap;
                    }
                }
            }
        }
        else if (right < left)
        {
            if (right <= swap_size)
            {
                memcpy(swap, array + left, right * sizeof(_T));
                memmove(array + right, array, left * sizeof(_T));
                memcpy(array, swap, right * sizeof(_T));
            }
            else
            {
                _T *pta, *ptb, *ptc, *ptd;
    
                pta = array;
                ptb = pta + left;
    
                bridge = left - right;
    
                if (bridge <= swap_size && bridge > 3)
                {
                    ptc = pta + right;
                    ptd = ptc + left;
    
                    memcpy(swap, ptc, bridge * sizeof(_T));
    
                    while (right--)
                    {
                        *ptc++ = *pta; *pta++ = *ptb++;
                    }
                    memcpy(ptd - bridge, swap, bridge * sizeof(_T));
                }
                else
                {
                    ptc = ptb;
                    ptd = ptc + right;
    
                    bridge = right / 2;
    
                    while (bridge--)
                    {
                        *swap = *--ptb; *ptb = *pta; *pta++ = *ptc; *ptc++ = *--ptd; *ptd = *swap;
                    }
    
                    bridge = (ptb - pta) / 2;
    
                    while (bridge--)
                    {
                        *swap = *--ptb; *ptb = *pta; *pta++ = *--ptd; *ptd = *swap;
                    }
    
                    bridge = (ptd - pta) / 2;
    
                    while (bridge--)
                    {
                        *swap = *pta; *pta++ = *--ptd; *ptd = *swap;
                    }
                }
            }
        }
        else
        {
            _T *pta, *ptb;
    
            pta = array;
            ptb = pta + left;
    
            while (left--)
            {
                *swap = *pta; *pta++ = *ptb; *ptb++ = *swap;
            }
        }
    }
    
    template <typename _T, typename _Cmp> 
    size_t monobound_binary_first(_T *array, _T *value, size_t top, _Cmp cmp)
    {
        _T *end;
        size_t mid;
    
        end = array + top;
    
        while (top > 1)
        {
            mid = top / 2;
    
            if (cmp(*value, *(end - mid)) <= 0)
            {
                end -= mid;
            }
            top -= mid;
        }
    
        if (cmp(*value, *(end - 1)) <= 0)
        {
            end--;
        }
        return (end - array);
    }
    
    template <typename _T, typename _Cmp> 
    void blit_merge_block(_T *array, _T *swap, size_t swap_size, size_t lblock, size_t right, _Cmp cmp)
    {
        size_t left, rblock;
    
        if (cmp(*(array + lblock - 1), *(array + lblock)) <= 0)
        {
            return;
        }
    
        rblock = lblock / 2;
        lblock -= rblock;
    
        left = monobound_binary_first<_T, _Cmp>(array + lblock + rblock, array + lblock, right, cmp);
    
        right -= left;
    
        if (left)
        {
            trinity_rotation<_T, _Cmp>(array + lblock, swap, swap_size, rblock + left, rblock);
    
            if (left <= swap_size)
            {
                partial_backward_merge<_T, _Cmp>(array, swap, lblock + left, lblock, cmp);
            }
            else if (lblock <= swap_size)
            {
                partial_forward_merge<_T, _Cmp>(array, swap, lblock + left, lblock, cmp);
            }
            else
            {
                blit_merge_block<_T, _Cmp>(array, swap, swap_size, lblock, left, cmp);
            }
        }
    
        if (right)
        {
            if (right <= swap_size)
            {
                partial_backward_merge<_T, _Cmp>(array + lblock + left, swap, rblock + right, rblock, cmp);
            }
            else if (rblock <= swap_size)
            {
                partial_forward_merge<_T, _Cmp>(array + lblock + left, swap, rblock + right, rblock, cmp);
            }
            else
            {
                blit_merge_block<_T, _Cmp>(array + lblock + left, swap, swap_size, rblock, right, cmp);
            }
        }
    }
    
    template <typename _T, typename _Cmp> 
    void blit_merge(_T *array, _T *swap, size_t swap_size, size_t nmemb, size_t block, _Cmp cmp)
    {
        _T *pta, *pte;
    
        pte = array + nmemb;
    
        while (block < nmemb)
        {
            for (pta = array ; pta + block < pte ; pta += block * 2)
            {
                if (pta + block * 2 < pte)
                {
                    blit_merge_block<_T, _Cmp>(pta, swap, swap_size, block, block, cmp);
    
                    continue;
                }
                blit_merge_block<_T, _Cmp>(pta, swap, swap_size, block, pte - pta - block, cmp);
    
                break;
            }
            block *= 2;
        }
    }

    template <typename _T, typename _Cmp> 
    void quadsort_swap(_T *array, _T *swap, size_t swap_size, size_t nmemb, _Cmp cmp)
    {
        if (nmemb < 32)
        {
            tail_swap<_T, _Cmp>(array, nmemb, cmp);
        }
        else if (quad_swap<_T, _Cmp>(array, nmemb, cmp) == 0)
        {
            size_t block;

            block = quad_merge<_T, _Cmp>(array, swap, swap_size, nmemb, 32, cmp);

            blit_merge<_T, _Cmp>(array, swap, swap_size, nmemb, block, cmp);
        }
    }

} // _private

template <typename _T, typename _Cmp> 
void BlitSort(_T *array, size_t count, _Cmp cmp)
{
    if (count < 32)
    {
        return _private::tail_swap<_T, _Cmp>(array, count, cmp);
    }
    else
    {
        constexpr size_t swap_size = 512;
        _T swap[swap_size];
    
        _private::blit_analyze<_T, _Cmp>(array, swap, swap_size, count, cmp);
    }
}


//----------------------------------------------------------------------------------------------------------------------
// StringUtil.h


#include <string.h>
#include <stdarg.h>


struct MemAllocator;

namespace Str
{
    API char* Copy(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src);
    API char* CopyCount(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src, uint32 count);
    API char* Concat(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src);
    API char* ConcatCount(char* RESTRICT dst, uint32 dstSize, const char* RESTRICT src, uint32 count);
    NO_ASAN API uint32 Len(const char* str);
    FORCE_INLINE constexpr uint32 LenStringLiteral(const char* str);
    API uint32 PrintFmt(char* str, uint32 size, const char* fmt, ...);
    API uint32 PrintFmtArgs(char* str, uint32 size, const char* fmt, va_list args);
    API char* PrintFmtAlloc(MemAllocator* alloc, const char* fmt, ...);
    API char* PrintFmtAllocArgs(MemAllocator* alloc, const char* fmt, va_list args);
    API uint32 ScanFmt(const char* str, const char* fmt, ...);
    API uint32 ScanFmtArgs(const char* str, const char* fmt, va_list args);
    API bool Utf8ToWide(const char* src, wchar_t* dst, size_t dstNumBytes);
    API bool WideToUtf8(const wchar_t* src, char* dst, size_t dstNumBytes);
    API bool IsEqual(const char* s1, const char* s2);
    API bool IsEqualNoCase(const char* s1, const char* s2);
    API bool IsEqualCount(const char* s1, const char* s2, uint32 count);
    API bool IsEqualNoCaseCount(const char* s1, const char* s2, uint32 count);
    API int Compare(const char* a, const char* b);
    API int CompareNoCase(const char* a, const char* b);
    API uint32 CountMatchingFirstChars(const char* s1, const char* s2);
    API bool StartsWith(const char* str, const char* startsWith);
    API bool EndsWith(const char* str, const char* endsWith);
    API char* Trim(char* dst, uint32 dstSize, const char* src);
    API char* Trim(char* dst, uint32 dstSize, const char* src, char ch);
    API char* RemoveWhitespace(char* dst, uint32 dstSize, const char* src);
    API char* RemoveChar(char* dst, uint32 dstSize, const char* src, char ch);
    API char* ReplaceChar(char* dst, uint32 dstSize, char ch, char replaceWith);
    API char* SubStr(char* dst, uint32 dstSize, const char* str, uint32 startIdx, uint32 endIdx = 0);
    API bool ToBool(const char* str);
    API int ToInt(const char* str);
    API uint32 ToUint(const char* str, uint32 radix = 10);
    API uint64 ToUint64(const char* str, uint32 radix = 10);
    API double ToDouble(const char* str);

    API bool IsWhitespace(char ch);
    API char ToLower(char ch);
    API char ToUpper(char ch);
    API char IsInRange(char ch, char from, char to);
    API char IsNumber(char ch);

    API const char* SkipWhitespace(const char* str);
    API const char* SkipChar(const char* str, char ch);
    API char* ToUpper(char* dst, uint32 dstSize, const char* src);
    API char* ToLower(char* dst, uint32 dstSize, const char* src);

    NO_ASAN API const char* FindChar(const char* str, char ch);
    NO_ASAN API const char* FindCharRev(const char* str, char ch);
    NO_ASAN API const char* FindStr(const char* RESTRICT str, const char* RESTRICT find);

    
    struct SplitResult
    {
        char* buffer;
        Span<char*> splits;
    };

    API SplitResult Split(const char* str, char ch, MemAllocator* alloc, bool acceptEmptySplits = false);
    API SplitResult SplitWhitespace(const char* str, MemAllocator* alloc);
    API void FreeSplitResult(SplitResult& sres, MemAllocator* alloc);
} // Str


template <uint32 _Size>
struct String 
{
    String();
    String(const char* cstr);
    String(char ch);
    String(const String<_Size>& str);

    String<_Size>& operator=(const String<_Size>& str);
    String<_Size>& operator=(const char* cstr);

    bool operator==(const char* str) const;
    bool operator==(const String<_Size>& str) const;
    bool operator!=(const char* str) const;
    bool operator!=(const String<_Size>& str) const;

    bool IsEmpty() const;
    uint32 Length() const;
    uint32 Capacity() const;
    char* Ptr();
    const char* CStr() const;
    uint32 CalcLength();
    char operator[](uint32 index) const;
    char& operator[](uint32 index);

    String<_Size>& FormatSelf(const char* fmt, ...);
    String<_Size>& FormatArgsSelf(const char* fmt, va_list args);

    static String<_Size> Format(const char* fmt, ...);

    bool IsEqual(const char* cstr) const;
    bool IsEqualNoCase(const char* cstr) const;
    bool IsEqual(const char* cstr, uint32 count) const;

    uint32 FindChar(char ch, uint32 startIndex = 0) const;
    uint32 FindCharRev(char ch) const;
    uint32 FindString(const char* cstr) const;
    bool StartsWith(char ch) const;
    bool StartsWith(const char* cstr) const;
    bool EndsWith(char ch) const;
    bool EndsWith(const char* cstr) const;

    String<_Size>& Append(const char* cstr);
    String<_Size>& Append(const char* cstr, uint32 count);
    String<_Size>& Append(const String<_Size>& str);

    String<_Size>& Trim();
    String<_Size>& Trim(char ch);

    String<_Size> SubStr(uint32 start, uint32 end = 0);

protected:
    char mStr[_Size];
    uint32 mLen;
};

using String32 = String<32>;
using String64 = String<64>;


template <uint32 _Size>
inline String<_Size>::String() : mLen(0)
{
    memset(mStr, 0x0, sizeof(mStr));
}

template <uint32 _Size>
inline String<_Size>::String(const char* cstr)
{
    char* end = Str::Copy(mStr, _Size, cstr);
    mLen = PtrToInt<uint32>(reinterpret_cast<void*>(end - mStr));
    memset(end, 0x0, _Size - mLen);
}

template <uint32 _Size> 
inline String<_Size>::String(char ch)
{
    memset(mStr, 0x0, sizeof(mStr));
    mStr[0] = ch;
    mLen = 1;
}

template <uint32 _Size> 
inline String<_Size>::String(const String<_Size>& str)
{
    memcpy(this, &str, sizeof(str));
    mLen = str.mLen;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::operator=(const String<_Size>& str)
{
    memcpy(this, &str, sizeof(str));
    return *this;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::operator=(const char* cstr)
{
    char* end = Str::Copy(mStr, _Size, cstr);
    mLen = PtrToInt<uint32>(reinterpret_cast<void*>(end - mStr));
    return *this;
}

template <uint32 _Size> 
inline bool String<_Size>::operator==(const char* str) const
{
    return Str::IsEqual(mStr, str);
}

template <uint32 _Size> 
inline bool String<_Size>::operator==(const String<_Size>& str) const
{
    return mLen == str.mLen && memcmp(mStr, str.mStr, mLen) == 0;
}

template <uint32 _Size> 
inline bool String<_Size>::operator!=(const char* str) const
{
    return !Str::IsEqual(mStr, str);
}

template <uint32 _Size> 
inline bool String<_Size>::operator!=(const String<_Size>& str) const
{
    return mLen != str.mLen || memcmp(mStr, str.mStr, mLen) != 0;
}

template <uint32 _Size> 
inline bool String<_Size>::IsEmpty() const
{
    return mLen == 0;
}

template <uint32 _Size> 
inline uint32 String<_Size>::Length() const
{
    return mLen;
}

template <uint32 _Size> 
inline uint32 String<_Size>::Capacity() const
{
    return _Size;
}

template <uint32 _Size> 
inline char* String<_Size>::Ptr()
{
    return mStr;
}

template <uint32 _Size> 
inline const char* String<_Size>::CStr() const
{
    return mStr;
}

template <uint32 _Size> 
inline char String<_Size>::operator[](uint32 index) const
{
    ASSERT(index < mLen);
    return mStr[index];
}

template <uint32 _Size> 
inline char& String<_Size>::operator[](uint32 index)
{
    ASSERT(index < mLen);
    return mStr[index];
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::FormatSelf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    Str::PrintFmtArgs(mStr, _Size, fmt, args);
    va_end(args);
    mLen = Str::Len(mStr);
    return *this;
}

template <uint32 _Size> 
inline String<_Size> String<_Size>::Format(const char* fmt, ...)
{
    String<_Size> str;
    va_list args;
    va_start(args, fmt);
    Str::PrintFmtArgs(str.mStr, _Size, fmt, args);
    va_end(args);
    str.mLen = Str::Len(str.mStr);
    return str;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::FormatArgsSelf(const char* fmt, va_list args)
{
    Str::PrintFmtArgs(mStr, _Size, fmt, args);
    return *this;
}

template <uint32 _Size> 
inline bool String<_Size>::IsEqual(const char* cstr) const
{
    return Str::IsEqual(mStr, cstr);
}

template <uint32 _Size>
inline bool String<_Size>::IsEqualNoCase(const char* cstr) const
{
    return Str::IsEqualNoCase(mStr, cstr);
}

template <uint32 _Size> 
inline bool String<_Size>::IsEqual(const char* cstr, uint32 count) const
{
    return Str::IsEqualCount(mStr, cstr, count);
}

template <uint32 _Size> 
inline uint32 String<_Size>::FindChar(char ch, uint32 startIndex) const
{
    ASSERT(startIndex <= mLen);
    const char* r = Str::FindChar(mStr + startIndex, ch);
    if (r)
        return PtrToInt<uint32>((void*)(r - mStr));
    else
        return UINT32_MAX;
}

template <uint32 _Size> 
inline uint32 String<_Size>::FindCharRev(char ch) const
{
    const char* r = Str::FindCharRev(mStr, ch);
    if (r)
        return PtrToInt<uint32>(r - mStr);
    else
        return UINT32_MAX;
}

template <uint32 _Size> 
inline uint32 String<_Size>::FindString(const char* cstr) const
{
    const char* r = Str::FindStr(mStr, cstr);
    if (r)
        return PtrToInt<uint32>(r - mStr);
    else
        return UINT32_MAX;
}

template <uint32 _Size> 
bool String<_Size>::StartsWith(char ch) const
{
    return mLen > 0 && mStr[0] == ch;
}

template <uint32 _Size> 
bool String<_Size>::StartsWith(const char* cstr) const
{
    uint32 cstrLen = Str::Len(cstr);
    return mLen >= cstrLen && Str::IsEqualCount(mStr, cstr, cstrLen);
}

template <uint32 _Size> 
inline bool String<_Size>::EndsWith(char ch) const
{
    return mLen > 0 && mStr[mLen-1] == ch;
}

template <uint32 _Size> 
inline bool String<_Size>::EndsWith(const char* cstr) const
{
    uint32 cstrLen = Str::Len(cstr);
    return mLen >= cstrLen && Str::FindStr(&mStr[mLen - cstrLen], cstr) != nullptr;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::Append(const char* cstr)
{
    Str::Copy(mStr + mLen, _Size - mLen, cstr);
    mLen += Str::Len(cstr);
    return *this;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::Append(const char* cstr, uint32 count)
{
    ASSERT(mLen + count < _Size);
    Str::CopyCount(mStr + mLen, _Size - mLen, cstr, count);
    mLen += count;
    return *this;
}

template <uint32 _Size>
inline String<_Size>& String<_Size>::Append(const String<_Size>& str)
{
    ASSERT(mLen + str.mLen < _Size);
    Str::CopyCount(mStr + mLen, _Size - mLen, str.mStr, str.mLen);
    mLen += str.mLen;
    return *this;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::Trim()
{
    Str::Trim(mStr, _Size, mStr);
    mLen = Str::Len(mStr);
    return *this;
}

template <uint32 _Size> 
inline String<_Size>& String<_Size>::Trim(char ch)
{
    Str::Trim(mStr, _Size, mStr, ch);
    mLen = Str::Len(mStr);
    return *this;
}

template <uint32 _Size>
inline String<_Size> String<_Size>::SubStr(uint32 start, uint32 end)
{
    end = (end == 0) ? mLen : end;

    String<_Size> r;
    Str::CopyCount(r.mStr, _Size, mStr + start, end - start);
    r.mLen = end - start;

    return r;
}

template <uint32 _Size>
inline uint32 String<_Size>::CalcLength()
{
    mLen = Str::Len(mStr);
    return mLen;
}

FORCE_INLINE constexpr uint32 Str::LenStringLiteral(const char* str)
{
    uint32 count = 0;
    while (*(str++)) 
        ++count;
    return count;
}


struct Blob
{
    enum class GrowPolicy : uint32
    {
        None = 0,
        Linear,
        Multiply
    };

    inline Blob() : Blob(Mem::GetDefaultAlloc()) { SetGrowPolicy(GrowPolicy::Linear); }
    inline explicit Blob(MemAllocator* alloc) : mAlloc(alloc) { SetGrowPolicy(GrowPolicy::Linear); }
    inline explicit Blob(void* buffer, size_t size);
    inline Blob& operator=(const Blob&) = default;
    inline Blob(const Blob&) = default;

    inline void Attach(void* data, size_t size, MemAllocator* alloc);
    inline void Detach(void** outData, size_t* outSize);

    inline void SetAllocator(MemAllocator* alloc);
    inline void SetGrowPolicy(GrowPolicy policy, uint32 growSize = 4096);
    inline void SetAlignment(uint8 align);
    inline void SetSize(size_t size);
    inline void Reserve(size_t capacity);
    inline void Reserve(void* buffer, size_t size);
    inline void Free();
    inline void ResetRead();
    inline void ResetWrite();
    inline void Reset();
    inline void SetOffset(size_t offset);
    inline void CopyTo(Blob* otherBlob) const;
    inline void MoveTo(Blob* otherBlob);

    inline size_t Write(const void* src, size_t size);
    inline size_t Read(void* dst, size_t size) const;
    template <typename _T> size_t Write(const _T& src);
    template <typename _T> size_t Read(_T* dst) const;
    size_t WriteStringBinary(const char* str, uint32 len = 0);
    size_t ReadStringBinary(char* outStr, uint32 outStrSize) const;
    size_t WriteStringBinary16(const char* str, uint32 len = 0);
    size_t ReadStringBinary16(char* outStr, uint32 outStrSize) const;
    
    inline size_t Size() const;
    inline size_t Capacity() const;
    inline size_t ReadOffset() const;
    inline const void* Data() const;
    inline bool IsValid() const;
    inline const Span<uint8> Slice() const;


private:
    MemAllocator* mAlloc = nullptr;
    void*      mBuffer = nullptr;
    size_t     mSize = 0;
    size_t     mOffset = 0;
    size_t     mCapacity = 0;
    uint32     mAlign = CONFIG_MACHINE_ALIGNMENT;
    GrowPolicy mGrowPolicy = GrowPolicy::None;
    uint32     mGrowSize = 4096u;
};


struct RingBlob
{
    RingBlob() : RingBlob(Mem::GetDefaultAlloc()) {}
    explicit RingBlob(MemAllocator* alloc) : mAlloc(alloc) {}
    explicit RingBlob(void* buffer, size_t size);
    
    void SetAllocator(MemAllocator* alloc);
    void Reserve(size_t capacity);
    void Reserve(void* buffer, size_t size);
    void Free();
    static size_t GetMemoryRequirement(size_t capacity);
    
    size_t ExpectWrite() const;

    void Write(const void* src, size_t size);
    size_t Read(void* dst, size_t size);
    size_t Peek(void* dst, size_t size, size_t* pOffset = nullptr);

    template <typename _T> void Write(const _T& src);
    template <typename _T> size_t Read(_T* dst);

    size_t Capacity() const;

private:
    MemAllocator* mAlloc = nullptr;
    uint8* mBuffer = nullptr;
    size_t mCapacity = 0;
    size_t mSize = 0;
    size_t mStart = 0;
    size_t mEnd = 0;
};


inline RingBlob::RingBlob(void* buffer, size_t size)
{
    ASSERT(buffer);
    ASSERT(size);

    mCapacity = size;
    mBuffer = reinterpret_cast<uint8*>(buffer);
}

inline void RingBlob::SetAllocator(MemAllocator* alloc)
{
    ASSERT_MSG(mBuffer == nullptr, "buffer should be freed/uninitialized before setting allocator");
    mAlloc = alloc;
}

inline void RingBlob::Reserve(size_t capacity)
{
    ASSERT(mAlloc);
    mCapacity = Max(capacity, mCapacity);
    mBuffer = reinterpret_cast<uint8*>(Mem::Realloc(mBuffer, mCapacity, mAlloc));
    ASSERT(mBuffer);
}

inline void RingBlob::Reserve(void* buffer, size_t size)
{
    ASSERT_MSG(mBuffer == nullptr, "RingBlob must not get used before setting buffer pointer");
    ASSERT(buffer);
    
    mCapacity = size;
    mBuffer = reinterpret_cast<uint8*>(buffer);
    mAlloc = nullptr;
}

inline void RingBlob::Free()
{
    if (mAlloc) {
        Mem::Free(mBuffer, mAlloc);
        mCapacity = mSize = mStart = mEnd = 0;
        mBuffer = nullptr;
    }
}

inline size_t RingBlob::GetMemoryRequirement(size_t capacity)
{
    return capacity;
}

inline size_t RingBlob::ExpectWrite() const
{
    return mCapacity - mSize;
}

inline void RingBlob::Write(const void* src, size_t size)
{
    ASSERT(size <= ExpectWrite());
    
    uint8* buff = mBuffer;
    const uint8* udata = reinterpret_cast<const uint8*>(src);
    size_t remain = mCapacity - mEnd;
    if (remain >= size) {
        memcpy(&buff[mEnd], udata, size);
    } else {
        memcpy(&buff[mEnd], udata, remain);
        memcpy(buff, &udata[remain], size - remain);
    }
    
    mEnd = (mEnd + size) % mCapacity;
    mSize += size;
}

inline size_t RingBlob::Read(void* dst, size_t size)
{
    ASSERT(size > 0);
    
    size = Min(size, mSize);
    if (size == 0)
        return 0;
    
    if (dst) {
        uint8* buff = mBuffer;
        uint8* udata = reinterpret_cast<uint8*>(dst);
        size_t remain = mCapacity - mStart;
        if (remain >= size) {
            memcpy(udata, &buff[mStart], size);
        } else {
            memcpy(udata, &buff[mStart], remain);
            memcpy(&udata[remain], buff, size - remain);
        }
    }
    
    mStart = (mStart + size) % mCapacity;
    mSize -= size;
    return size;
}

inline size_t RingBlob::Peek(void* dst, size_t size, size_t* pOffset)
{
    ASSERT(size > 0);
    
    size = Min(size, mSize);
    if (size == 0)
        return 0;
    
    ASSERT(dst);
    uint8* buff = mBuffer;
    uint8* udata = reinterpret_cast<uint8*>(dst);
    size_t _offset = pOffset ? *pOffset : mStart;
    size_t remain = mCapacity - _offset;
    if (remain >= size) {
        memcpy(udata, &buff[_offset], size);
    } else {
        memcpy(udata, &buff[_offset], remain);
        memcpy(&udata[remain], buff, (size_t)size - (size_t)remain);
    }
    
    if (pOffset)
        *pOffset = (*pOffset + size) % mCapacity;

    return size;
}

template <typename _T> inline void RingBlob::Write(const _T& src)
{
    Write(&src, sizeof(_T));
}

template <typename _T> inline size_t RingBlob::Read(_T* dst)
{
    return Read(dst, sizeof(_T));
}

inline size_t RingBlob::Capacity() const
{
    return mCapacity;
}

inline Blob::Blob(void* buffer, size_t size)
{
    ASSERT(buffer && size);
    mBuffer = buffer;
    mCapacity = size;
}

inline void Blob::Attach(void* data, size_t size, MemAllocator* alloc)
{
    ASSERT(data);
    ASSERT_MSG(!mBuffer, "buffer should be freed before attach");
    mAlloc = alloc;
    mGrowPolicy = GrowPolicy::None;
    mBuffer = data;
    mOffset = 0;
    mSize = size;
    mCapacity = size;
}

inline void Blob::Detach(void** outData, size_t* outSize)
{
    ASSERT(outData);
    ASSERT(outSize);

    *outData = mBuffer;
    *outSize = mSize;

    mBuffer = nullptr;
    mSize = 0;
    mOffset = 0;
    mCapacity = 0;
}

inline void Blob::SetAllocator(MemAllocator* alloc)
{
    ASSERT_MSG(!mBuffer, "SetAllocator must be called before using/initializing the Blob");
    mAlloc = alloc;
}

inline void Blob::SetSize(size_t size)
{
    ASSERT_MSG(size <= mCapacity, "Size cannot be larger than capacity");
    mSize = size;
}

inline void Blob::Reserve(size_t capacity)
{
    ASSERT_MSG(mAlloc, "Allocator must be set for dynamic Reserve");
    ASSERT(capacity > mSize);

    mBuffer = Mem::ReallocAligned(mBuffer, capacity, mAlign, mAlloc);
    mCapacity = capacity;
}

inline void Blob::Reserve(void* buffer, size_t size)
{
    ASSERT(size > mSize);
    ASSERT(PtrToInt<uint64>(buffer) % mAlign == 0);
    ASSERT(mBuffer == nullptr);

    mBuffer = buffer;
    mCapacity = size;
    mAlloc = nullptr;
}

inline void Blob::Free()
{
    if (mAlloc)
        Mem::FreeAligned(mBuffer, mAlign, mAlloc);
    mBuffer = nullptr;
    mSize = 0;
    mCapacity = 0;
    mAlloc = nullptr;
}

inline void Blob::ResetRead() 
{
    mOffset = 0;
}

inline void Blob::ResetWrite()
{
    mSize = 0;
}

inline void Blob::Reset()
{
    mOffset = 0;
    mSize = 0;
}

inline void Blob::SetOffset(size_t offset) 
{
    ASSERT(mOffset < mSize);
    mOffset = offset;
}

inline size_t Blob::Write(const void* src, size_t size)
{
    ASSERT(src);
    ASSERT(size);

    size_t requiredCapacity = mSize + size;
    size_t writeBytes = size;
    if (requiredCapacity > mCapacity && mAlloc) {
        ASSERT_MSG(mGrowPolicy != GrowPolicy::None, "Growable blobs should have a grow policy");
        ASSERT(mGrowSize);

        size_t targetCapacity = mCapacity;
        if (mGrowPolicy == GrowPolicy::Linear) 
            targetCapacity += mGrowSize;
        else if (mGrowPolicy == GrowPolicy::Multiply)
            targetCapacity = targetCapacity ? (targetCapacity << 1) : mGrowSize;

        mCapacity = (requiredCapacity > targetCapacity) ? AlignValue(requiredCapacity, size_t(mGrowSize)) : targetCapacity;        
        mBuffer = Mem::ReallocAligned(mBuffer, mCapacity, mAlign, mAlloc);
    }
    else {
        writeBytes = Min(mCapacity - mSize, size);  
    }

    if (writeBytes) {
        uint8* buff = reinterpret_cast<uint8*>(mBuffer);
        memcpy(buff + mSize, src, size);
        mSize += size;
    }

    #if CONFIG_VALIDATE_IO_READ_WRITES
    ASSERT(writeBytes == size);     
    #endif
    return writeBytes;
}

inline size_t Blob::Read(void* dst, size_t size) const
{
    ASSERT(dst);
    ASSERT(size);

    size_t readBytes = Min(mSize - mOffset, size);
    if (readBytes) {
        uint8* buff = reinterpret_cast<uint8*>(mBuffer);
        memcpy(dst, buff + mOffset, readBytes);
        const_cast<Blob*>(this)->mOffset += readBytes;
    }

    #if CONFIG_VALIDATE_IO_READ_WRITES
    ASSERT(size == readBytes);
    #endif

    return readBytes;
}

template <typename _T> 
inline size_t Blob::Write(const _T& src)
{
    return static_cast<uint32>(Write(&src, sizeof(_T)));
}

template <typename _T> 
inline size_t Blob::Read(_T* dst) const
{
    return static_cast<uint32>(Read(dst, sizeof(_T)));
}

inline size_t Blob::Size() const
{
    return mSize;
}

inline size_t Blob::ReadOffset() const
{
    return mOffset;
}

inline size_t Blob::Capacity() const
{
    return mCapacity;
}

inline const void* Blob::Data() const
{
    return mBuffer;
}

inline bool Blob::IsValid() const
{
    return mBuffer && mSize;
}

inline const Span<uint8> Blob::Slice() const
{
    ASSERT(mSize <= UINT32_MAX);
    return Span<uint8>((uint8*)mBuffer, uint32(mSize));
}

inline void Blob::CopyTo(Blob* otherBlob) const
{
    ASSERT(mSize);
    otherBlob->Reserve(mSize);
    otherBlob->SetSize(mSize);
    memcpy(otherBlob->mBuffer, mBuffer, mSize); 
}

inline void Blob::MoveTo(Blob* otherBlob)
{
    ASSERT(otherBlob->mBuffer == nullptr);

    *otherBlob = *this;
    
    mBuffer = nullptr;
    mSize = 0;
    mCapacity = 0;
}

inline void Blob::SetAlignment(uint8 align)
{
    ASSERT_MSG(mAlloc, "Alignment only workes for blobs with allocators");
    ASSERT_MSG(mBuffer == nullptr, "Cannot change alignment when buffer is already created");

    if (align < CONFIG_MACHINE_ALIGNMENT)
        align = CONFIG_MACHINE_ALIGNMENT;
    mAlign = align;
}

inline void Blob::SetGrowPolicy(GrowPolicy policy, uint32 growSize)
{
    ASSERT(growSize);
    mGrowPolicy = policy;
    mGrowSize = AlignValue(growSize, CACHE_LINE_SIZE);
}

inline size_t Blob::ReadStringBinary(char* outStr, [[maybe_unused]] uint32 outStrSize) const
{
    uint32 len = 0;
    size_t readStrBytes = 0;
    size_t readBytes = Read<uint32>(&len);
    ASSERT(readBytes == sizeof(len));
    ASSERT(len < outStrSize);
    if (len) {
        readStrBytes = Read(outStr, len);
        ASSERT(readStrBytes == len);
    }
    outStr[len] = '\0';
    return readStrBytes + readBytes;
}

inline size_t Blob::ReadStringBinary16(char* outStr, [[maybe_unused]] uint32 outStrSize) const
{
    uint16 len = 0;
    size_t readStrBytes = 0;
    size_t readBytes = Read<uint16>(&len);
    ASSERT(readBytes == sizeof(len));
    ASSERT(len < outStrSize);
    if (len) {
        readStrBytes = Read(outStr, len);
        ASSERT(readStrBytes == len);
    }
    outStr[len] = '\0';
    return readStrBytes + readBytes;
}

inline size_t Blob::WriteStringBinary(const char* str, uint32 len)
{
    ASSERT(str);
    if (len == 0)
        len = Str::Len(str);
    size_t writtenBytes = Write<uint32>(len);
    if (len) 
        writtenBytes += Write(str, len);
    return writtenBytes;
}

inline size_t Blob::WriteStringBinary16(const char* str, uint32 len)
{
    ASSERT(str);
    if (len == 0)
        len = Str::Len(str);
    ASSERT(len < UINT16_MAX);
    size_t writtenBytes = Write<uint16>(uint16(len));
    if (len) 
        writtenBytes += Write(str, len);
    return writtenBytes;
}




struct DebugStacktraceEntry
{
    char name[PATH_CHARS_MAX];
    char filename[PATH_CHARS_MAX];
    uint64 offsetFromSymbol;
    uint32 offsetFromLine;
    uint32 line;
};

using DebugFiberScopeProtectorCallback = bool(*)(void* userData);

namespace Debug
{
    API void PrintLine(const char* text);
    API void PrintLineFmt(const char* fmt, ...);
    API void SetCaptureStacktraceForFiberProtector(bool capture);
    API uint16 CaptureStacktrace(void** stackframes, uint16 maxStackframes, uint16 framesToSkip = 1, uint32* pHash = nullptr);
    API void ResolveStacktrace(uint16 numStacktrace, void* const* stackframes, DebugStacktraceEntry* entries);

    API void StacktraceSaveStopPoint(void* funcPtr);

    API void FiberScopeProtector_RegisterCallback(DebugFiberScopeProtectorCallback callback, void* userData = nullptr);
    API uint16 FiberScopeProtector_Push(const char* name);
    API void FiberScopeProtector_Pop(uint16 id);
    API void FiberScopeProtector_Check();
}

#if PLATFORM_WINDOWS && defined(TRACY_ENABLE)
    #ifdef __cplusplus
    extern "C" {
    #endif
        void DebugDbgHelpInit();
        void DebugDbgHelpLock();
        void DebugDbgHelpUnlock();
    #ifdef __cplusplus
    }
    #endif
#endif


#if PLATFORM_WINDOWS 
using RDBG_Id = uint32;

enum class RDBG_ProcessorBreakpointType : uint8
{
    Write = 1,
    ReadWrite = 2,
    Execute = 3
};

namespace RDBG
{
    API bool Initialize(const char* serverName, const char* remedybgPath);
    API void Release();
    API bool AttachToProcess(uint32 id = 0);
    API bool DetachFromProcess();
    API bool Break();
    API bool Continue();
    API bool RunToFileAtLine(const char* filename, uint32 line);
    API RDBG_Id AddFunctionBreakpoint(const char* funcName, const char* conditionExpr = nullptr, uint32 overloadId = 0);
    API RDBG_Id AddFileLineBreakpoint(const char* filename, uint32 line, const char* conditionExpr = nullptr);
    API RDBG_Id AddAddressBreakpoint(uintptr_t addr, const char* conditionExpr = nullptr);
    API RDBG_Id AddProcessorBreakpoint(const void* addr, uint8 numBytes, 
                                       RDBG_ProcessorBreakpointType type, const char* conditionExpr = nullptr);
    API bool EnableBreakpoint(RDBG_Id bId, bool enable);
    API bool SetBreakpointCondition(RDBG_Id bId, const char* conditionExpr);
    API bool DeleteBreakpoint(RDBG_Id bId);
    API bool DeleteAllBreakpoints();
    API RDBG_Id AddWatch(const char* expr, const char* comment, uint8 windowNum);
    API RDBG_Id DeleteWatch(RDBG_Id wId);
    bool DeleteAllWatches();
}

#endif // PLATFORM_WINDOWS





struct HashResult128
{
    uint64 h1;
    uint64 h2;

    bool operator==(const HashResult128& h) const { return h1 == h.h1 && h2 == h.h2; }
    bool operator!=(const HashResult128& h) const { return h1 != h.h1 || h2 != h.h2; }
};

namespace Hash
{
    INLINE constexpr uint32 Fnv32(const void* data, size_t len);
    INLINE constexpr uint32 Fnv32Str(const char* str);
    template <typename _T> constexpr uint32 Fnv32(const _T& data);

    INLINE constexpr uint32 Uint32(uint32 key);
    INLINE constexpr uint64 Uint64(uint64 key);
    INLINE constexpr uint32 Int64To32(uint64 key);

    API uint32 CRC32(const void* data, size_t len, uint32 seed = 0);

    #if CPU_X86 && defined(__SSE4_2__)
    API uint32 CRC32_x86_Aligned(const void* data, size_t len);
    #endif

    API uint32 Murmur32(const void* key, uint32 len, uint32 seed = 0);
    API HashResult128 Murmur128(const void* key, size_t len, uint32 seed = 0);
}

struct HashStringLiteral
{
    inline constexpr HashStringLiteral(const char* _cstr) :
#if CONFIG_ENABLE_ASSERT
        cstr(_cstr),
#endif
        hash(Hash::Fnv32Str(_cstr))
    {        
    }

    inline constexpr HashStringLiteral& operator=(const char* _cstr)
    {
    #if CONFIG_ENABLE_ASSERT
        cstr = _cstr;
    #endif
        hash = Hash::Fnv32Str(_cstr);
        return *this;
    }

#if CONFIG_ENABLE_ASSERT
    const char* cstr;
#endif
    uint32 hash;
};

struct HashMurmur32Incremental
{
    HashMurmur32Incremental(uint32 seed = 0);

    template <typename _T> 
    HashMurmur32Incremental& Add(const _T& data) { return AddAny(&data, sizeof(_T)); }
    
    template <typename _T> 
    HashMurmur32Incremental& Add(const _T* data, uint32 count) { return AddAny(data, sizeof(_T)*count); }

    uint32 Hash();
    HashMurmur32Incremental& AddAny(const void* data, uint32 size);
    HashMurmur32Incremental& AddCStringArray(const char** strs, uint32 numStrings);

    uint32 mHash;
    uint32 mTail;
    uint32 mCount;
    uint32 mSize;

private:
    void Murmur32MixTail(const uint8** pData, uint32* pSize);
};



namespace _private { struct HashTableData; };

template <typename _T>
struct HashTable
{
    HashTable() : mHashTable(nullptr), mAlloc(Mem::GetDefaultAlloc()) {}
    explicit HashTable(MemAllocator* alloc) : mHashTable(nullptr), mAlloc(alloc) {}
    explicit HashTable(uint32 capacity, void* buff, size_t size);

    void SetAllocator(MemAllocator* alloc);
    bool Reserve(uint32 capacity);
    bool Reserve(uint32 capacity, void* buff, size_t size);
    void Free();

    bool Grow(uint32 newCapacity);
    bool Grow(uint32 newCapacity, void* buff, size_t size);

    static size_t GetMemoryRequirement(uint32 capacity);
    
    _T* Add(uint32 key);
    uint32 Add(uint32 key, const _T& value);

    uint32 AddUnique(uint32 key, const _T& value);

    void AddReplaceUnique(uint32 key, const _T& value);

    uint32 Find(uint32 key) const;
    void Clear();

    const _T& Get(uint32 index) const;
    void Set(uint32 index, const _T& value);
    _T& GetMutable(uint32 index);
    void Remove(uint32 index);

    const _T& FindAndFetch(uint32 key, const _T& notFoundValue = {}) const;
    void FindAndRemove(uint32 key);

    uint32 Capacity() const;
    uint32 Count() const;
    const uint32* Keys() const;
    const _T* Values() const;
    bool IsFull() const;

public:
    _private::HashTableData* mHashTable;
    MemAllocator* mAlloc;
};

using HashTableUint = HashTable<uint32>;

namespace _private
{
    struct HashTableData
    {
        uint32* keys;
        uint8* 	values;      // Can be any POD data or opaque type
        uint32	bitshift;
        uint32	valueStride;
        uint32	count;
        uint32	capacity;
    };

    API [[nodiscard]] HashTableData* hashtableCreate(uint32 capacity, 
                                                     uint32 valueStride,
                                                     MemAllocator* alloc = Mem::GetDefaultAlloc());
    API void hashtableDestroy(HashTableData* tbl, MemAllocator* alloc = Mem::GetDefaultAlloc());
    API bool hashtableGrow(HashTableData** pTbl, MemAllocator* alloc = Mem::GetDefaultAlloc());
    
    API uint32 hashtableAdd(HashTableData* tbl, uint32 key, const void* value);
    API uint32 hashtableAddKey(HashTableData* tbl, uint32 key);
    API uint32 hashtableFind(const HashTableData* tbl, uint32 key);
    API void hashtableClear(HashTableData* tbl);

    API size_t hashtableGetMemoryRequirement(uint32 capacity, uint32 valueStride);
    API HashTableData* hashtableCreateWithBuffer(uint32 capacity, uint32 valueStride, void* buff, size_t size);
    API bool hashtableGrowWithBuffer(HashTableData** pTbl, void* buff, size_t size);
} // _private


inline constexpr uint32 kFnv1Init = 0x811c9dc5;
inline constexpr uint32 kFnv1Prime = 0x01000193;

INLINE constexpr 
uint32 Hash::Fnv32(const void* data, size_t len)
{
    const char* bp = (const char*)data;
    const char* be = bp + len;
    
    uint32 hval = kFnv1Init;
    while (bp < be) {
        hval ^= (uint32)*bp++;
        hval *= kFnv1Prime;
    }
    
    return hval;
}

INLINE constexpr 
uint32 Hash::Fnv32Str(const char* str)
{
    const char* s = str;
    
    uint32 hval = kFnv1Init;
    while (*s) {
        hval ^= (uint32)*s++;
        hval *= kFnv1Prime;
    }
    
    return hval;
}

#ifdef __cplusplus
template <typename _T> constexpr 
uint32 Hash::Fnv32(const _T& data)
{
    return Hash::Fnv32(&data, sizeof(data));
}
#endif

INLINE constexpr 
uint32 Hash::Uint32(uint32 key)
{
    const uint32 c2 = 0x27d4eb2d;    // a prime or an odd constant
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * c2;
    key = key ^ (key >> 15);
    return key;
}

INLINE constexpr 
uint64 Hash::Uint64(uint64 key)
{
    key = (~key) + (key << 21);    // key = (key << 21) - key - 1;
    key = key ^ (key >> 24);
    key = (key + (key << 3)) + (key << 8);    // key * 265
    key = key ^ (key >> 14);
    key = (key + (key << 2)) + (key << 4);    // key * 21
    key = key ^ (key >> 28);
    key = key + (key << 31);
    return key;
}

INLINE constexpr 
uint32 Hash::Int64To32(uint64 key)
{
    key = (~key) + (key << 18);
    key = key ^ (key >> 31);
    key = key * 21;
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);
    return (uint32)key;
}

template <typename _T>
inline HashTable<_T>::HashTable(uint32 capacity, void* buff, size_t size)
{
    mHashTable = _private::hashtableCreateWithBuffer(capacity, sizeof(_T), buff, size);
    mAlloc = nullptr;
    ASSERT(mHashTable);
}    

template <typename _T>
inline void HashTable<_T>::SetAllocator(MemAllocator* alloc)
{
    ASSERT_MSG(!mHashTable, "hash-table already initialized with another allocator");
    mAlloc = alloc;
}

template <typename _T>
inline bool HashTable<_T>::Reserve(uint32 capacity)
{
    ASSERT_MSG(!mHashTable, "hash-table already initialized");
    ASSERT(mAlloc);
    mHashTable = _private::hashtableCreate(capacity, sizeof(_T), mAlloc);
    return mHashTable ? true : false;
}

template <typename _T>
inline bool HashTable<_T>::Reserve(uint32 capacity, void* buff, size_t size)
{
    ASSERT_MSG(!mHashTable, "hash-table already initialized");
    mHashTable = _private::hashtableCreateWithBuffer(capacity, sizeof(_T), buff, size);
    mAlloc = nullptr;
    return mHashTable ? true : false;
}    

template <typename _T>
inline void HashTable<_T>::Free()
{
    if (mHashTable && mAlloc)
        _private::hashtableDestroy(mHashTable, mAlloc);
    mHashTable = nullptr;
}

template <typename _T>
inline const _T* HashTable<_T>::Values() const
{
    if (!mHashTable)
        return nullptr;
    return reinterpret_cast<const _T*> (mHashTable->values);
}

template <typename _T>
inline const uint32* HashTable<_T>::Keys() const
{
    if (!mHashTable)
        return nullptr;
    return mHashTable->keys;
}

template <typename _T>
inline uint32 HashTable<_T>::Count() const
{
    if (!mHashTable)
        return 0;

    return mHashTable->count;
}

template <typename _T>
inline uint32 HashTable<_T>::Capacity() const
{
    if (!mHashTable)
        return 0;

    return mHashTable->capacity;
}

template <typename _T>
inline const _T& HashTable<_T>::Get(uint32 index) const
{
    ASSERT(mHashTable);
    return reinterpret_cast<_T*>(mHashTable->values)[index];
}

template <typename _T>
inline void HashTable<_T>::Set(uint32 index, const _T& value)
{
    ASSERT(mHashTable);
    reinterpret_cast<_T*>(mHashTable->values)[index] = value;
}

template <typename _T>
inline _T& HashTable<_T>::GetMutable(uint32 index)
{
    ASSERT(mHashTable);
    return reinterpret_cast<_T*>(mHashTable->values)[index];
}

template <typename _T>
inline void HashTable<_T>::Remove(uint32 index)
{
    ASSERT_MSG(index < mHashTable->capacity, "index out of range");

    if (mHashTable) {
        mHashTable->keys[index] = 0;
        --mHashTable->count;
    }
}

template <typename _T>
inline void HashTable<_T>::Clear()
{
    if (mHashTable)
        _private::hashtableClear(mHashTable);
}

template <typename _T>
inline uint32 HashTable<_T>::Find(uint32 key) const
{
    if (!mHashTable)
        return uint32(-1);

    return _private::hashtableFind(mHashTable, key);
}

template <typename _T>
inline void HashTable<_T>::AddReplaceUnique(uint32 key, const _T& value)
{
    uint32 index = Find(key);

    if (index == INVALID_INDEX)
        Add(key, value);
    else
        ((_T*)mHashTable->values)[index] = value;
}

template <typename _T>
inline uint32 HashTable<_T>::AddUnique(uint32 key, const _T& value)
{
    uint32 index = Find(key);

    if (index == INVALID_INDEX)
        return Add(key, value);
    else
        return index;
}


template <typename _T>
inline uint32 HashTable<_T>::Add(uint32 key, const _T& value)
{
    if (mHashTable == nullptr) {
        ASSERT(mAlloc);
        Reserve(32);
        ASSERT(mHashTable);
    }
    
    if (mHashTable->count == mHashTable->capacity) {
        ASSERT_MSG(mAlloc, "Only hashtables with allocators can grow");
        [[maybe_unused]] bool r = _private::hashtableGrow(&mHashTable, mAlloc);
        ASSERT_ALWAYS(r, "could not grow hash-table");
    }

    uint32 h = _private::hashtableAddKey(mHashTable, key);
    ((_T*)mHashTable->values)[h] = value;
    return h;
}

template <typename _T>
inline _T* HashTable<_T>::Add(uint32 key)
{
    if (mHashTable == nullptr) {
        ASSERT(mAlloc);
        Reserve(32);
        ASSERT(mHashTable);
    }

    if (mHashTable->count == mHashTable->capacity) {
        ASSERT_MSG(mAlloc, "HashTable full. Only hashtables with allocators can grow");
        [[maybe_unused]] bool r = _private::hashtableGrow(&mHashTable, mAlloc);
        ASSERT_ALWAYS(r, "could not grow hash-table");
    }
    uint32 h = _private::hashtableAddKey(mHashTable, key);

    return &((_T*)mHashTable->values)[h];
}

template <typename _T>
inline const _T& HashTable<_T>::FindAndFetch(uint32 key, const _T& not_found_value /*= {0}*/) const
{
    ASSERT(mHashTable);
    uint32 index = _private::hashtableFind(mHashTable, key);
    return index != UINT32_MAX ? Get(index) : not_found_value;
}

template <typename _T>
inline void HashTable<_T>::FindAndRemove(uint32 key)
{
    ASSERT(mHashTable);
    uint32 index = _private::hashtableFind(mHashTable, key);
    if (index != UINT32_MAX)
        Remove(index);
}

template <typename _T>
inline bool HashTable<_T>::IsFull() const
{
    ASSERT(mHashTable);
    return mHashTable->count == mHashTable->capacity;
}

template <typename _T>
inline size_t HashTable<_T>::GetMemoryRequirement(uint32 capacity)
{
    return _private::hashtableGetMemoryRequirement(capacity, sizeof(_T));
}

template <typename _T>
inline bool HashTable<_T>::Grow(uint32 newCapacity)
{
    ASSERT(mAlloc);
    ASSERT(mHashTable);
    ASSERT(newCapacity > mHashTable->capacity);

    return _private::hashtableGrow(&mHashTable, mAlloc);
}

template <typename _T>
inline bool HashTable<_T>::Grow(uint32 newCapacity, void* buff, size_t size)
{
    ASSERT(!mAlloc);
    ASSERT(mHashTable);
    ASSERT(newCapacity > mHashTable->capacity);

    return _private::hashtableGrowWithBuffer(&mHashTable, buff, size);
}




typedef struct ini_t ini_t;

struct INIFileProperty
{
    void SetName(const char* name);
    void SetValue(const char* value);

    const char* GetName();
    const char* GetValue();

    void Delete();

    inline bool IsValid() const    { return id != -1; }

    ini_t* ini = nullptr;
    int sectionId = -1;
    int id = -1;
};

struct INIFileSection
{
    uint32 GetPropertyCount();
    INIFileProperty GetProperty(uint32 index);
    const char* GetPropertyName(uint32 index);

    INIFileProperty NewProperty(const char* name, const char* value);
    INIFileProperty FindProperty(const char* name);

    void SetName(const char* name);
    const char* GetName();

    void Delete();

    inline bool IsValid() const    { return id != -1; }

    ini_t* ini = nullptr;
    int id = -1;
};

struct INIFileContext
{
    uint32 GetSectionCount() const;
    INIFileSection GetSection(uint32 index) const;
    const char* GetSectionName(uint32 index) const;

    INIFileSection GetRootSection() const;

    INIFileSection NewSection(const char* name) const;
    INIFileSection FindSection(const char* name) const;

    inline bool IsValid() const    { return ini != nullptr; }

    void Destroy();

    ini_t* ini = nullptr;
};

namespace INIFile
{
    API INIFileContext Create(MemAllocator* alloc = Mem::GetDefaultAlloc());
    API INIFileContext Load(const char* filepath, MemAllocator* alloc = Mem::GetDefaultAlloc());
    API INIFileContext LoadFromString(const char* data, MemAllocator* alloc = Mem::GetDefaultAlloc());
    API bool Save(const INIFileContext& ini, const char* filepath);
    API Blob SaveToMem(const INIFileContext& ini, MemAllocator* alloc);
}




struct JobsInstance;
using JobsHandle = JobsInstance*;
using JobsCallback = void(*)(uint32 groupIndex, void* userData);

enum class JobsPriority : uint32
{
    High = 0,
    Normal,
    Low,
    _Count
};

enum class JobsType : uint32
{
    ShortTask = 0,
    LongTask,
    _Count
};

enum class JobsStackSize : uint32
{
    Small = 0,  // 64kb
    Medium,     // 512kb
    Large,      // 2048kb
    _Count
};

struct alignas(CACHE_LINE_SIZE) JobsSignal
{
    JobsSignal();

    void Raise();
    void Wait();
    void Decrement();
    void Increment();
    void WaitOnCondition(bool(*condFn)(int value, int reference), int reference = 0);
    void Set(int value = 1);
    void Reset();

private:
    uint8 data[128];
};

struct JobsInitParams
{
    MemAllocator* alloc = Mem::GetDefaultAlloc();
    uint32 numShortTaskThreads = 0; // Default: total number of cores - 1
    uint32 numLongTaskThreads = 0;  // Default: total number of cores - 1
    uint32 defaultShortTaskStackSize = SIZE_MB;
    uint32 defaultLongTaskStackSize = SIZE_MB;
    bool debugAllocations = false;
};

namespace Jobs
{
    API void Initialize(const JobsInitParams& initParams);
    API void Release();

    API [[nodiscard]] JobsHandle Dispatch(JobsType type, JobsCallback callback, void* userData = nullptr, 
                                          uint32 groupSize = 1, JobsPriority prio = JobsPriority::Normal, 
                                          JobsStackSize stackSize = JobsStackSize::Medium);
    API void WaitForCompletionAndDelete(JobsHandle handle);
    API void YieldCurrent();

    API bool IsRunningOnCurrentThread();
    API bool IsRunning(JobsHandle handle);
    API void Delete(JobsHandle handle);

    API void DispatchAndForget(JobsType type, JobsCallback callback, void* userData = nullptr, 
                               uint32 groupSize = 1, JobsPriority prio = JobsPriority::Normal, 
                               JobsStackSize stackSize = JobsStackSize::Medium);

    API uint32 GetWorkerThreadsCount(JobsType type);
}



//----------------------------------------------------------------------------------------------------------------------
// MathTypes.h



PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4201)    // nonstandard extension used : nameless struct/union
PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4204)    // nonstandard extension used: non-constant aggregate initializer

struct Float2 
{
    union {
        struct 
        {
            float x;
            float y;
        };

        float f[2];
    };

    Float2() = default;
    explicit constexpr Float2(float _x, float _y) : x(_x), y(_y) {}
    explicit constexpr Float2(float _xx) : x(_xx), y(_xx) {}
    explicit constexpr Float2(const float* _f) : x(_f[0]), y(_f[1]) {}


    static float  Dot(Float2 _a, Float2 _b);
    static Float2 Norm(Float2 _a);
    static float  Len(Float2 _a);
    static Float2 NormLen(Float2 _a, float* outlen);
    static Float2 Min(Float2 _a, Float2 _b);
    static Float2 Max(Float2 _a, Float2 _b);
    static Float2 Lerp(Float2 _a, Float2 _b, float _t);
    static Float2 Abs(Float2 _a);
    static Float2 Neg(Float2 _a);
    static Float2 Add(Float2 _a, Float2 _b);
    static Float2 Add(Float2 _a, float _b);
    static Float2 Sub(Float2 _a, Float2 _b);
    static Float2 Sub(Float2 _a, float _b);
    static Float2 Mul(Float2 _a, Float2 _b);
    static Float2 Mul(Float2 _a, float _b);
    static Float2 CalcLinearFit2D(const Float2* _points, int _num);
};

struct Float3 
{
    union {
        struct 
        {
            float x;
            float y;
            float z;
        };

        float f[3];
    };

    Float3() = default;
    explicit constexpr Float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    explicit constexpr Float3(float _xxx) : x(_xxx), y(_xxx), z(_xxx) {}
    explicit constexpr Float3(const float* _f) : x(_f[0]), y(_f[1]), z(_f[2]) {}
    explicit constexpr Float3(Float2 v, float _z = 0) : x(v.x), y(v.y), z(_z) {}


    static Float3 Abs(Float3 _a);
    static Float3 Neg(Float3 _a);
    static Float3 Add(Float3 _a, Float3 _b);
    static Float3 Add(Float3 _a, float _b);
    static Float3 Sub(Float3 _a, Float3 _b);
    static Float3 Sub(Float3 _a, float _b);
    static Float3 Mul(Float3 _a, Float3 _b);
    static Float3 Mul(Float3 _a, float _b);
    static float  Dot(Float3 _a, Float3 _b);
    static Float3 Cross(Float3 _a, Float3 _b);
    static Float3 Lerp(Float3 _a, Float3 _b, float _t);
    static Float3 SmoothLerp(Float3 _a, Float3 _b, float _dt, float _h);
    static float  Len(Float3 _a);
    static Float3 Norm(Float3 _a);
    static Float3 NormLen(Float3 _a, float* _outlen);
    static Float3 Min(Float3 _a, Float3 _b);
    static Float3 Max(Float3 _a, Float3 _b);
    static Float3 Rcp(Float3 _a);
    static void   Tangent(Float3* _t, Float3* _b, Float3 _n);
    static void   TangentAngle(Float3* _t, Float3* _b, Float3 _n, float _angle);
    static Float3 FromLatLong(float _u, float _v);
    static Float2 ToLatLong(Float3 _dir);
    static Float3 CalcLinearFit3D(const Float3* _points, int _num);
};

struct Float4 
{
    union {
        struct 
        {
            float x;
            float y;
            float z;
            float w;
        };

        float f[4];
    };

    Float4() = default;
    explicit constexpr Float4(float _x, float _y, float _z, float _w = 1.0f) : x(_x), y(_y), z(_z), w(_w) {}
    explicit constexpr Float4(float _xxxx) : x(_xxxx), y(_xxxx), z(_xxxx), w(_xxxx) {}
    explicit constexpr Float4(const float* _f) : x(_f[0]), y(_f[1]), z(_f[2]), w(_f[3]) {}
    explicit constexpr Float4(Float3 v, float _w = 1.0f) : x(v.x), y(v.y), z(v.z), w(_w) {}
    explicit constexpr Float4(float v[3], float _w = 1.0f) : x(v[0]), y(v[1]), z(v[2]), w(_w) {}
    explicit constexpr Float4(Float2 v, float _z = 0, float _w = 1.0f) : x(v.x), y(v.y), z(_z), w(_w) {}

    static Float4 Mul(Float4 _a, Float4 _b);
    static Float4 Mul(Float4 _a, float _b);
    static Float4 Add(Float4 _a, Float4 _b);
    static Float4 Sub(Float4 _a, Float4 _b);
};

struct Color4u 
{
    union {
        struct 
        {
            uint8 r;
            uint8 g;
            uint8 b;
            uint8 a;
        };

        unsigned int n;
    };

    Color4u() = default;

    explicit constexpr Color4u(uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255)
        : r(_r), g(_g), b(_b), a(_a)
    {
    }

    explicit Color4u(const float* f) { *this = Color4u::FromFloat4(f[0], f[1], f[2], f[3]); }
    constexpr Color4u(uint32 _n) : n(_n) {}

    Color4u& operator=(uint32 _n) 
    {
        n = _n;
        return *this;
    }

    static float ValueToLinear(float _a);
    static float ValueToGamma(float _a);
    static Color4u FromFloat4(float _r, float _g, float _b, float _a = 1.0f);
    static Float4 ToFloat4(Color4u c);
    static Float4 ToFloat4(uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255);
    static Color4u Blend(Color4u _a, Color4u _b, float _t);
    static Float4 ToFloat4SRGB(Float4 cf);
    static Float4 ToFloat4Linear(Float4 c);
    static Float3 RGBtoHSV(Float3 rgb);
    static Float3 HSVtoRGB(Float3 hsv);
};

struct Int2 
{
    union {
        struct 
        {
            int x;
            int y;
        };

        int n[2];
    };

    Int2() = default;
    explicit constexpr Int2(int _x, int _y) : x(_x), y(_y) {}
    explicit constexpr Int2(const int* _i) : x(_i[0]), y(_i[1]) {}
    explicit constexpr Int2(int _xx) : x(_xx), y(_xx) {}

    static Int2 Add(Int2 _a, Int2 _b);
    static Int2 Sub(Int2 _a, Int2 _b);
    static Int2 Min(Int2 _a, Int2 _b);
    static Int2 Max(Int2 _a, Int2 _b);
};

struct Quat 
{
    union {
        struct 
        {
            float x;
            float y;
            float z;
            float w;
        };

        float f[4];
    };

    Quat() = default;
    explicit constexpr Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    explicit constexpr Quat(const float* _f) : x(_f[0]), y(_f[1]), z(_f[2]), w(_f[3]) {}

    static Float3 MulXYZ(Quat _qa, Quat _qb);
    static Quat   Mul(Quat p, Quat q);
    static Quat   Conjugate(Quat _q);       // Inverse = Conjucate if length of the quaternion = 1. (IsNorm() == true)
    static float  Dot(Quat _a, Quat _b);
    static float  Angle(Quat _a, Quat _b);
    static Quat   Norm(Quat _q);
    static bool   IsNorm(Quat _q);
    static Quat   RotateAxis(Float3 _axis, float _angle);
    static Quat   RotateX(float _ax);
    static Quat   RotateY(float _ay);
    static Quat   RotateZ(float _az);
    static Quat   Lerp(Quat _a, Quat _b, float t);
    static Quat   Slerp(Quat _a, Quat _b, float t);
    static Float3 ToEuler(Quat _q);
    static Quat   FromEuler(Float3 _float3);
    static Float3 TransformFloat3(Float3 v, Quat q);
};

struct Mat3 
{
    union {
        struct 
        {
            float m11, m21, m31;
            float m12, m22, m32;
            float m13, m23, m33;
        };

        struct 
        {
            float fc1[3];
            float fc2[3];
            float fc3[3];
        };

        float f[9];
    };


    Mat3() = default;
    explicit constexpr Mat3(float _m11, float _m12, float _m13, 
                            float _m21, float _m22, float _m23, 
                            float _m31, float _m32, float _m33) :
      m11(_m11),     m21(_m21),     m31(_m31),
      m12(_m12),     m22(_m22),     m32(_m32),
      m13(_m13),     m23(_m23),     m33(_m33) 
    {
    }

    explicit constexpr Mat3(const float* _col1, const float* _col2, const float* _col3) :
      m11(_col1[0]),     m21(_col1[1]),     m31(_col1[2]),
      m12(_col2[0]),     m22(_col2[1]),     m32(_col2[2]),
      m13(_col3[0]),     m23(_col3[1]),     m33(_col3[2])
    {
    }

    explicit constexpr Mat3(Float3 _col1, Float3 _col2, Float3 _col3) :
        Mat3(_col1.f, _col2.f, _col3.f)
    {
    }  

    Float3 Row1() const;
    Float3 Row2() const;
    Float3 Row3() const;
    
    static Mat3   Transpose(const Mat3& _a);
    static Float3 MulFloat3(const Mat3& _mat, Float3 _vec);
    static Mat3   MulInverse(const Mat3& _a, const Mat3& _b);
    static Float3 MulFloat3Inverse(const Mat3& mat, Float3 v);
    static Float2 MulFloat2(const Mat3& _mat, Float2 _vec);
    static Mat3   Translate(float x, float y);
    static Mat3   TranslateFloat2(Float2 p);
    static Mat3   Rotate(float theta);
    static Mat3   Scale(float sx, float sy);
    static Mat3   ScaleRotateTranslate(float sx, float sy, float angle, float tx, float ty);
    static Mat3   Inverse(const Mat3& _a);
    static Mat3   Mul(const Mat3& _a, const Mat3& _b);
    static Mat3   Abs(const Mat3& m);
    static Mat3   FromQuat(Quat q);
};

struct Mat4 
{
    union {
        struct 
        {
            float m11, m21, m31, m41;
            float m12, m22, m32, m42;
            float m13, m23, m33, m43;
            float m14, m24, m34, m44;
        };

        struct 
        {
            float fc1[4];
            float fc2[4];
            float fc3[4];
            float fc4[4];
        };

        float f[16];
    };

    Mat4() = default;
    explicit constexpr Mat4(float _m11, float _m12, float _m13, float _m14, 
                            float _m21, float _m22, float _m23, float _m24, 
                            float _m31, float _m32, float _m33, float _m34, 
                            float _m41, float _m42, float _m43, float _m44)
    :   m11(_m11),     m21(_m21),     m31(_m31),     m41(_m41),
        m12(_m12),     m22(_m22),     m32(_m32),     m42(_m42),
        m13(_m13),     m23(_m23),     m33(_m33),     m43(_m43),
        m14(_m14),     m24(_m24),     m34(_m34),     m44(_m44)
    {    
    }

    explicit constexpr Mat4(const float* _col1, const float* _col2, const float* _col3, const float* _col4)
    :   m11(_col1[0]),     m21(_col1[1]),     m31(_col1[2]),     m41(_col1[3]),
        m12(_col2[0]),     m22(_col2[1]),     m32(_col2[2]),     m42(_col2[3]),
        m13(_col3[0]),     m23(_col3[1]),     m33(_col3[2]),     m43(_col3[3]),
        m14(_col4[0]),     m24(_col4[1]),     m34(_col4[2]),     m44(_col4[3])
    {
    }

    explicit constexpr Mat4(Float4 _col1, Float4 _col2, Float4 _col3, Float4 _col4) : 
        Mat4(_col1.f, _col2.f, _col3.f, _col4.f)
    {
    }

    Float4 Row1() const;
    Float4 Row2() const;
    Float4 Row3() const;
    Float4 Row4() const;

    Float3 XAxis() const;
    Float3 YAxis() const;
    Float3 ZAxis() const;
    Float3 Position() const;

    void SetCol1(Float4 _col1);
    void SetCol2(Float4 _col2);
    void SetCol3(Float4 _col3);
    void SetCol4(Float4 _col4);

    static Mat4   Translate(float _tx, float _ty, float _tz);
    static Mat4   Translate(Float3 _t);
    static Mat4   Scale(float _sx, float _sy, float _sz);
    static Mat4   Scale(float _scale);
    static Mat4   RotateX(float _ax);
    static Mat4   RotateY(float _ay);
    static Mat4   RotateZ(float _az);
    static Mat4   RotateXY(float _ax, float _ay);
    static Mat4   RotateXYZ(float _ax, float _ay, float _az);
    static Mat4   RotateZYX(float _ax, float _ay, float _az);
    static Mat4   ToQuatTranslate(Quat _quat, Float3 _translation);
    static Mat4   ToQuatTranslateHMD(Quat _quat, Float3 _translation);
    static Float3 MulFloat3(const Mat4& _mat, Float3 _vec);
    static Float3 MulFloat3_xyz0(const Mat4& _mat, Float3 _vec);
    static Float3 MulFloat3H(const Mat4& _mat, Float3 _vec);
    static Float4 MulFloat4(const Mat4& _mat, Float4 _vec);
    static Mat4   Transpose(const Mat4& _a);
    static void   ProjFlipHandedness(Mat4* _dst, const Mat4& _src);
    static void   ViewFlipHandedness(Mat4* _dst, const Mat4& _src);
    static Mat4   FromNormal(Float3 _normal, float _scale, Float3 _pos);
    static Mat4   FromNormalAngle(Float3 _normal, float _scale, Float3 _pos, float _angle);
    static Mat4   ViewLookAt(Float3 eye, Float3 target, Float3 up);
    static Mat4   ViewLookAtLH(Float3 eye, Float3 target, Float3 up);
    static Mat4   ViewFPS(Float3 eye, float pitch, float yaw);
    static Mat4   ViewArcBall(Float3 move, Quat rot, Float3 target_pos);
    static Mat4   Perspective(float width, float height, float zn, float zf, bool d3dNdc = false);
    static Mat4   PerspectiveLH(float width, float height, float zn, float zf, bool d3dNdc = false);
    static Mat4   PerspectiveOffCenter(float xmin, float ymin, float xmax, float ymax,
                                       float zn, float zf, bool d3dNdc = false);
    static Mat4   PerspectiveOffCenterLH(float xmin, float ymin, float xmax, float ymax,
                                         float zn, float zf, bool d3dNdc = false);
    static Mat4   PerspectiveFOV(float fov_y, float aspect, float zn, float zf, bool d3dNdc = false);
    static Mat4   PerspectiveFOVLH(float fov_y, float aspect, float zn, float zf, bool d3dNdc = false);
    static Mat4   Ortho(float width, float height, float zn, float zf, float offset = 0, bool d3dNdc = false);
    static Mat4   OrthoLH(float width, float height, float zn, float zf, float offset = 0, bool d3dNdc = false);
    static Mat4   OrthoOffCenter(float xmin, float ymin, float xmax, float ymax, float zn,
                                 float zf, float offset = 0, bool d3dNdc = false);
    static Mat4   OrthoOffCenterLH(float xmin, float ymin, float xmax, float ymax, float zn,
                                   float zf, float offset = 0, bool d3dNdc = false);
    static Mat4   TransformMat(float _tx, float _ty, float _tz, 
                               float _ax, float _ay, float _az,
                               float _sx, float _sy, float _sz);
    static Mat4   TransformMat(Float3 translation, Quat rotation, Float3 scale);
    static Mat4   Mul(const Mat4& _a, const Mat4& _b);
    static Mat4   Inverse(const Mat4& _a);
    static Mat4   InverseTransformMat(const Mat4& _a);
    static Quat   ToQuat(const Mat4& _mat);     // Matrix should be Orthonormal (Pure rotation)
    static Mat4   FromQuat(Quat q);
    static Mat4   ProjectPlane(Float3 planeNormal);
    static Mat4   FromMat3(const Mat3& _mat);
};

struct RectFloat 
{
    union {
        struct 
        {
            float xmin, ymin;
            float xmax, ymax;
        };

        struct 
        {
            Float2 vmin;
            Float2 vmax;
        };

        float f[4];
    };

    RectFloat() = default;

    explicit constexpr RectFloat(float _xmin, float _ymin, float _xmax, float _ymax) 
    : xmin(_xmin), ymin(_ymin), xmax(_xmax), ymax(_ymax)
    {
    }

    explicit constexpr RectFloat(const float* _vmin, const float* _vmax) 
    : vmin { _vmin[0], _vmin[1] },
      vmax { _vmax[0], _vmax[1] }
    {
    }

    explicit constexpr RectFloat(Float2 _vmin, Float2 _vmax) :
        vmin(_vmin), vmax(_vmax)
    {
    }

    bool   IsEmpty() const;
    float  Width() const;
    float  Height() const;

    static RectFloat   CenterExtents(Float2 center, Float2 extents);
    static RectFloat   Expand(const RectFloat rc, Float2 expand);
    static bool   TestPoint(const RectFloat rc, Float2 pt);
    static bool   Test(const RectFloat rc1, const RectFloat rc2);
    static void   AddPoint(RectFloat& rc, Float2 pt);
    static Float2 GetCorner(const RectFloat* rc, int index);
    static void   GetCorners(const RectFloat* rc, Float2 corners[4]);
    static Float2 Extents(const RectFloat rc);
    static Float2 Center(const RectFloat rc);
    static RectFloat   Translate(const RectFloat rc, Float2 pos);
};

struct RectInt 
{
    union {
        struct 
        {
            int xmin, ymin;
            int xmax, ymax;
        };

        struct 
        {
            Int2 vmin;
            Int2 vmax;
        };

        int n[4];
    };


    RectInt() = default;

    explicit constexpr RectInt(int _xmin, int _ymin, int _xmax, int _ymax) 
        : xmin(_xmin),   ymin(_ymin),   xmax(_xmax),   ymax(_ymax)
    {
    }

    explicit constexpr RectInt(const int* _vmin, const int* _vmax) 
    : vmin { _vmin[0], _vmin[1] },
      vmax { _vmax[0], _vmax[1] }
    {
    }

    explicit constexpr RectInt(Int2 _vmin, Int2 _vmax) :
        vmin(_vmin), vmax(_vmax)
    { 
    }

    bool IsEmpty() const;
    int Width() const;
    int Height() const;
    void SetWidth(int width);
    void SetHeight(int height);

    static RectInt  Expand(const RectInt rc, Int2 expand);
    static bool   TestPoint(const RectInt rc, Int2 pt);
    static bool   Test(const RectInt rc1, const RectInt rc2);
    static void   AddPoint(RectInt& rc, Int2 pt);
    static Int2   GetCorner(const RectInt* rc, int index);
    static void   GetCorners(const RectInt* rc, Int2 corners[4]);
};

struct AABB 
{
    union {
        struct 
        {
            float xmin, ymin, zmin;
            float xmax, ymax, zmax;
        };

        struct 
        {
            Float3 vmin;
            Float3 vmax;
        };

        float f[6];
    };

    AABB() = default;
    explicit constexpr AABB(float _xmin, float _ymin, float _zmin, float _xmax, float _ymax, float _zmax) 
    :   xmin(_xmin), ymin(_ymin), zmin(_zmin),
        xmax(_xmax), ymax(_ymax), zmax(_zmax)
    { 
    }
    explicit constexpr AABB(const float* _vmin, const float* _vmax) 
    : vmin { _vmin[0],    _vmin[1],     _vmin[2] },
      vmax { _vmax[0],    _vmax[1],     _vmax[2] }
    {   
    }
    explicit constexpr AABB(Float3 _vmin, Float3 _vmax) :
        vmin(_vmin), vmax(_vmax)
    {
    }

    bool IsEmpty() const;
    Float3 Extents() const;
    Float3 Center() const;
    Float3 Dimensions() const;

    static AABB   CenterExtents(Float3 center, Float3 extents);
    static void   AddPoint(AABB& aabb, Float3 pt);
    static AABB   Unify(const AABB& aabb1, const AABB& aabb2);
    static bool   TestPoint(const AABB& aabb, Float3 pt);
    static bool   Test(const AABB& aabb1, const AABB& aabb2);
    static Float3 GetCorner(const AABB& aabb, int index);
    static void   GetCorners(const AABB& aabb, Float3 corners[8]);
    static AABB   Translate(const AABB& aabb, Float3 offset);
    static AABB   SetPos(const AABB& aabb, Float3 pos);
    static AABB   Expand(const AABB& aabb, Float3 expand);
    static AABB   Scale(const AABB& aabb, Float3 scale);
    static AABB   Transform(const AABB& aabb, const Mat4& mat);
};

struct Plane 
{
    union {
        Float4 p;

        struct {
            Float3 normal;
            float d;
        };

        float f[4];
    };

    Plane() = default;
    explicit constexpr Plane(float _nx, float _ny, float _nz, float _d) : p(_nx, _ny, _nz, _d) {}
    explicit constexpr Plane(Float3 _normal, float _d) :
        normal { _normal.x,     _normal.y,  _normal.z}, d(_d)
    {   
    }

    static Float3 CalcNormal(Float3 _va, Float3 _vb, Float3 _vc);
    static Plane  From3Points(Float3 _va, Float3 _vb, Float3 _vc);
    static Plane  FromNormalPoint(Float3 _normal, Float3 _p);
    static float  Distance(Plane _plane, Float3 _p);
    static Float3 ProjectPoint(Plane _plane, Float3 _p);
    static Float3 ClosestPointToOrigin(Plane _plane);
    static float  HitRay(Plane _plane, Float3 _origin, Float3 _direction);
};

namespace MathUtil
{
    Float2 ProjectPointToScreenPixels(Float3 pt, const Mat4& cameraWorldToClipMat, const RectFloat& viewport);
}


inline constexpr float M_PI           = 3.1415926535897932384626433832795f;
inline constexpr float M_PI2          = 6.2831853071795864769252867665590f;
inline constexpr float M_INVPI        = (1.0f / 3.1415926535897932384626433832795f);
inline constexpr float M_HALFPI       = 1.5707963267948966192313216916398f;
inline constexpr float M_QUARTERPI    = 0.7853981633974483096156608458199f;
inline constexpr float M_SQRT2        = 1.4142135623730950488016887242097f;
inline constexpr float M_LOGNAT10     = 2.3025850929940456840179914546844f;
inline constexpr float M_INVLOGNAT10   = 1.4426950408889634073599246810019f;
inline constexpr float M_LOGNAT2H     = 0.6931471805599453094172321214582f;
inline constexpr float M_LOGNAT2L     = 1.90821492927058770002e-10f;
inline constexpr float M_E            = 2.7182818284590452353602874713527f;
inline constexpr float M_NEARZERO     = (1.0f / (float)(1 << 28));
inline constexpr float M_FLOAT32_MIN  = 1.175494e-38f;
inline constexpr float M_FLOAT32_MAX  = 3.402823e+38f;
inline constexpr float M_FLOAT32_EPSILON = 1.192093e-07f;

inline constexpr Float2 FLOAT2_ZERO  { 0.0f, 0.0f };
inline constexpr Float2 FLOAT2_UNITX { 1.0f, 0.0f };
inline constexpr Float2 FLOAT2_UNITY { 0.0f, 1.0f };

inline constexpr Float3 FLOAT3_ZERO  { 0.0f, 0.0f, 0.0f };
inline constexpr Float3 FLOAT3_UNIX { 1.0f, 0.0f, 0.0f };
inline constexpr Float3 FLOAT3_UNITY { 0.0f, 1.0f, 0.0f };
inline constexpr Float3 FLOAT3_UNITZ { 0.0f, 0.0f, 1.0f };

inline constexpr Float4 FLOAT4_ZERO  { 0.0f, 0.0f, 0.0f, 1.0f };
inline constexpr Float4 FLOAT4_UNITX { 1.0f, 0.0f, 0.0f, 1.0f };
inline constexpr Float4 FLOAT4_UNITY { 0.0f, 1.0f, 0.0f, 1.0f };
inline constexpr Float4 FLOAT4_UNITZ { 0.0f, 0.0f, 1.0f, 1.0f };

inline constexpr Int2 INT2_ZERO {0, 0};
inline constexpr Int2 INT2_ONE {1, 1};

inline constexpr Mat3 MAT3_IDENT {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

inline constexpr Mat4 MAT4_IDENT {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f 
};

inline constexpr Quat QUAT_INDENT {0, 0, 0, 1.0f};

inline constexpr Color4u COLOR4U_WHITE  { uint8(255), uint8(255), uint8(255), uint8(255) };
inline constexpr Color4u COLOR4U_BLACK  { uint8(0), uint8(0), uint8(0), uint8(255) };
inline constexpr Color4u COLOR4U_RED    { uint8(255), uint8(0), uint8(0), uint8(255) };
inline constexpr Color4u COLOR4U_YELLOW { uint8(255), uint8(255), uint8(0), uint8(255) };
inline constexpr Color4u COLOR4U_GREEN  { uint8(0), uint8(255), uint8(0), uint8(255) };
inline constexpr Color4u COLOR4U_BLUE   { uint8(0), uint8(0), uint8(255), uint8(255) };
inline constexpr Color4u COLOR4U_PURPLE { uint8(255), uint8(0), uint8(255), uint8(255) };

inline constexpr RectFloat RECTFLOAT_EMPTY { M_FLOAT32_MAX, M_FLOAT32_MAX, -M_FLOAT32_MAX, -M_FLOAT32_MAX };
inline constexpr RectInt RECTINT_EMPTY { INT32_MAX, INT32_MAX, INT32_MIN, INT32_MIN };
inline constexpr AABB AABB_EMPTY { M_FLOAT32_MAX, M_FLOAT32_MAX, M_FLOAT32_MAX, -M_FLOAT32_MAX, -M_FLOAT32_MAX, -M_FLOAT32_MAX };

PRAGMA_DIAGNOSTIC_POP()    // ignore msvc warnings


struct JsonContext;

struct JsonErrorLocation
{
    uint32 line;
    uint32 col;
};

namespace Json
{
    API JsonContext* Parse(const char* json5, uint32 json5Len, JsonErrorLocation* outErrLoc, MemAllocator* alloc = Mem::GetDefaultAlloc());
    API void Destroy(JsonContext* ctx);
}

struct JsonNode
{
    JsonNode() = default;
    explicit JsonNode(JsonContext* _ctx);
    explicit JsonNode(JsonContext* _ctx, int _tokenId, int _itemIndex = 0);

    bool HasChild(const char* _childNode) const;    

    JsonNode GetChild(const char* _childNode) const;
    JsonNode GetChildItem(uint32 _index = 0) const;
    JsonNode GetNextChildItem(const JsonNode& curChildItem) const;
    uint32 GetChildCount() const;

    JsonNode GetArrayItem(uint32 _index = 0) const;
    JsonNode GetNextArrayItem(const JsonNode& curItem) const;
    uint32 GetArrayCount() const;

    bool IsValid() const;
    bool IsObject() const;
    bool IsArray() const;

    const char* GetKey(char* outKey, uint32 keySize) const;
    const char* GetValue(char* outValue, uint32 valueSize) const;

    template <typename _T> _T GetValue() const;
    template <typename _T> uint32 GetArrayValues(_T* _values, uint32 _maxValues) const;

    const char* GetChildValueString(const char* _childNode, char* _outValue, uint32 _valueSize, const char* _defaultValue);
    template <typename _T> _T GetChildValue(const char* _childNode, _T _defaultValue);
    template <typename _T> uint32 GetChildArrayValues(const char* _childNode, _T* _values, uint32 _maxValues);

private:
    JsonContext* mCtx = nullptr;
    int mTokenId = -1;
    int mItemIndex = 0;
};

typedef struct cj5_result cj5_result;
extern "C" {
    int cj5_seek(cj5_result* r, int parent_id, const char* key);
    int cj5_seek_hash(cj5_result* r, int parent_id, const uint32_t key_hash);
    int cj5_seek_recursive(cj5_result* r, int parent_id, const char* key);
    const char* cj5_get_string(cj5_result* r, int id, char* str, int max_str);
    double cj5_get_double(cj5_result* r, int id);
    float cj5_get_float(cj5_result* r, int id);
    int cj5_get_int(cj5_result* r, int id);
    uint32_t cj5_get_uint(cj5_result* r, int id);
    uint64_t cj5_get_uint64(cj5_result* r, int id);
    int64_t cj5_get_int64(cj5_result* r, int id);
    bool cj5_get_bool(cj5_result* r, int id);
    double cj5_seekget_double(cj5_result* r, int parent_id, const char* key, double def_val);
    float cj5_seekget_float(cj5_result* r, int parent_id, const char* key, float def_val);
    int cj5_seekget_array_int16(cj5_result* r, int parent_id, const char* key, int16_t* values, int max_values);
    int cj5_seekget_array_uint16(cj5_result* r, int parent_id, const char* key, uint16_t* values, int max_values);
    int cj5_seekget_int(cj5_result* r, int parent_id, const char* key, int def_val);
    uint32_t cj5_seekget_uint(cj5_result* r, int parent_id, const char* key, uint32_t def_val);
    uint64_t cj5_seekget_uint64(cj5_result* r, int parent_id, const char* key, uint64_t def_val);
    int64_t cj5_seekget_int64(cj5_result* r, int parent_id, const char* key, int64_t def_val);
    bool cj5_seekget_bool(cj5_result* r, int parent_id, const char* key, bool def_val);
    const char* cj5_seekget_string(cj5_result* r, int parent_id, const char* key, char* str, int max_str, const char* def_val);
    int cj5_seek(cj5_result* r, int parent_id, const char* key);
    int cj5_seekget_array_double(cj5_result* r, int parent_id, const char* key, double* values, int max_values);
    int cj5_seekget_array_float(cj5_result* r, int parent_id, const char* key, float* values, int max_values);
    int cj5_seekget_array_int(cj5_result* r, int parent_id, const char* key, int* values, int max_values);
    int cj5_seekget_array_uint(cj5_result* r, int parent_id, const char* key, uint32_t* values, int max_values);
    int cj5_seekget_array_uint64(cj5_result* r, int parent_id, const char* key, uint64_t* values, int max_values);
    int cj5_seekget_array_int64(cj5_result* r, int parent_id, const char* key, int64_t* values, int max_values);
    int cj5_seekget_array_bool(cj5_result* r, int parent_id, const char* key, bool* values, int max_values);
    int cj5_seekget_array_string(cj5_result* r, int parent_id, const char* key, char** strs, int max_str, int max_values);
    int cj5_get_array_elem(cj5_result* r, int id, int index);
    int cj5_get_array_elem_incremental(cj5_result* r, int id, int index, int prev_elem);
}

inline JsonNode::JsonNode(JsonContext* _ctx) : mCtx(_ctx), mTokenId(0), mItemIndex(0) 
{
    ASSERT(_ctx);
}

inline JsonNode::JsonNode(JsonContext* _ctx, int _tokenId, int _itemIndex) : mCtx(_ctx), mTokenId(_tokenId), mItemIndex(_itemIndex) 
{
    ASSERT(_ctx);
}

inline bool JsonNode::HasChild(const char* _childNode) const
{
    return cj5_seek(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode) != -1;
}

inline JsonNode JsonNode::GetChild(const char* _childNode) const
{
    int id = cj5_seek(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode);
    return JsonNode(mCtx, id);
}

inline bool JsonNode::IsValid() const
{
    return mCtx && mTokenId > -1;
}

template <> inline uint32 JsonNode::GetArrayValues(uint32* _values, uint32 _maxValues) const
{
    return (uint32)cj5_seekget_array_uint(reinterpret_cast<cj5_result*>(mCtx), mTokenId, nullptr, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetArrayValues(float* _values, uint32 _maxValues) const
{
    return (uint32)cj5_seekget_array_float(reinterpret_cast<cj5_result*>(mCtx), mTokenId, nullptr, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetArrayValues(double* _values, uint32 _maxValues) const
{
    return (uint32)cj5_seekget_array_double(reinterpret_cast<cj5_result*>(mCtx), mTokenId, nullptr, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetArrayValues(uint64* _values, uint32 _maxValues) const
{
    return (uint32)cj5_seekget_array_uint64(reinterpret_cast<cj5_result*>(mCtx), mTokenId, nullptr, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetArrayValues(int* _values, uint32 _maxValues) const
{
    return (uint32)cj5_seekget_array_int(reinterpret_cast<cj5_result*>(mCtx), mTokenId, nullptr, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetArrayValues(bool* _values, uint32 _maxValues) const
{
    return (uint32)cj5_seekget_array_bool(reinterpret_cast<cj5_result*>(mCtx), mTokenId, nullptr, _values, _maxValues);
}

template <> inline bool JsonNode::GetValue() const
{
    return cj5_get_bool(reinterpret_cast<cj5_result*>(mCtx), mTokenId);
}

template <> inline int JsonNode::GetValue() const
{
    return cj5_get_int(reinterpret_cast<cj5_result*>(mCtx), mTokenId);
}

template <> inline float JsonNode::GetValue() const
{
    return cj5_get_float(reinterpret_cast<cj5_result*>(mCtx), mTokenId);
}

template <> inline double JsonNode::GetValue() const
{
    return cj5_get_double(reinterpret_cast<cj5_result*>(mCtx), mTokenId);
}

template <> inline uint32 JsonNode::GetValue() const
{
    return cj5_get_uint(reinterpret_cast<cj5_result*>(mCtx), mTokenId);
}

template <> inline uint64 JsonNode::GetValue() const
{
    return cj5_get_uint64(reinterpret_cast<cj5_result*>(mCtx), mTokenId);
}

template <> inline Float4 JsonNode::GetValue() const
{
    Float4 v;
    [[maybe_unused]] uint32 n = GetArrayValues<float>(v.f, 4);
    ASSERT(n == 4);
    return v;
}

template <> inline Float2 JsonNode::GetValue() const
{
    Float2 v;
    [[maybe_unused]] uint32 n = GetArrayValues<float>(v.f, 2);
    ASSERT(n == 2);
    return v;
}

template <> inline Float3 JsonNode::GetValue() const
{
    Float3 v;
    [[maybe_unused]] uint32 n = GetArrayValues<float>(v.f, 3);
    ASSERT(n == 3);
    return v;
}

template <> inline Int2 JsonNode::GetValue() const
{
    Int2 v;
    [[maybe_unused]] uint32 n = GetArrayValues<int>(v.n, 2);
    ASSERT(n == 2);
    return v;
}

inline const char* JsonNode::GetChildValueString(const char* _childNode, char* _outValue, uint32 _valueSize, const char* _defaultValue)
{
    const char* r = cj5_seekget_string(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _outValue, _valueSize, _defaultValue);
    if (r == _defaultValue)
        Str::Copy(_outValue, (int)_valueSize, _defaultValue);
    return _outValue;
}

template <> inline uint32 JsonNode::GetChildValue(const char* _childNode, uint32 _defaultValue)
{
    return cj5_seekget_uint(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _defaultValue);
}

template <> inline uint64 JsonNode::GetChildValue(const char* _childNode, uint64 _defaultValue)
{
    return cj5_seekget_uint64(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _defaultValue);
}

template <> inline int JsonNode::GetChildValue(const char* _childNode, int _defaultValue)
{
    return cj5_seekget_int(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _defaultValue);
}

template <> inline float JsonNode::GetChildValue(const char* _childNode, float _defaultValue)
{
    return cj5_seekget_float(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _defaultValue);
}

template <> inline double JsonNode::GetChildValue(const char* _childNode, double _defaultValue)
{
    return cj5_seekget_double(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _defaultValue);
}

template <> inline bool JsonNode::GetChildValue(const char* _childNode, bool _defaultValue)
{
    return cj5_seekget_bool(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _defaultValue);
}

template <> inline Float4 JsonNode::GetChildValue(const char* _childNode, Float4 _defaultValue)
{
    JsonNode jArr = GetChild(_childNode);
    return jArr.IsValid() && jArr.IsArray() ? jArr.GetValue<Float4>() : _defaultValue;
}

template <> inline Float3 JsonNode::GetChildValue(const char* _childNode, Float3 _defaultValue)
{
    JsonNode jArr = GetChild(_childNode);
    return jArr.IsValid() && jArr.IsArray() ? jArr.GetValue<Float3>() : _defaultValue;
}

template <> inline Float2 JsonNode::GetChildValue(const char* _childNode, Float2 _defaultValue)
{
    JsonNode jArr = GetChild(_childNode);
    return jArr.IsValid() && jArr.IsArray() ? jArr.GetValue<Float2>() : _defaultValue;
}

template <> inline Int2 JsonNode::GetChildValue(const char* _childNode, Int2 _defaultValue)
{
    JsonNode jArr = GetChild(_childNode);
    return jArr.IsValid() && jArr.IsArray() ? jArr.GetValue<Int2>() : _defaultValue;
}

template <> inline uint32 JsonNode::GetChildArrayValues(const char* _childNode, uint32* _values, uint32 _maxValues)
{
    return (uint32)cj5_seekget_array_uint(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetChildArrayValues(const char* _childNode, int* _values, uint32 _maxValues)
{
    return (uint32)cj5_seekget_array_int(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetChildArrayValues(const char* _childNode, uint64* _values, uint32 _maxValues)
{
    return (uint32)cj5_seekget_array_uint64(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetChildArrayValues(const char* _childNode, bool* _values, uint32 _maxValues)
{
    return (uint32)cj5_seekget_array_bool(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetChildArrayValues(const char* _childNode, double* _values, uint32 _maxValues)
{
    return (uint32)cj5_seekget_array_double(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _values, _maxValues);
}

template <> inline uint32 JsonNode::GetChildArrayValues(const char* _childNode, float* _values, uint32 _maxValues)
{
    return (uint32)cj5_seekget_array_float(reinterpret_cast<cj5_result*>(mCtx), mTokenId, _childNode, _values, _maxValues);
}






enum class LogLevel
{
    Default = 0,
    Error,
    Warning,
    Info,
    Verbose,
    Debug,
    _Count
};

struct LogEntry
{
    LogLevel    type;
    uint32      channels;
    uint32      textLen;
    uint32      sourceFileLen;
    uint32      line;
    const char* text;
    const char* sourceFile;
};

using LogCallback = void(*)(const LogEntry& entry, void* userData);

namespace Log
{
    API void RegisterCallback(LogCallback callback, void* userData);
    API void UnregisterCallback(LogCallback callback);
    API void SetSettings(LogLevel logLevel, bool breakOnErrors, bool treatWarningsAsErrors);

    namespace _private
    {
        API void PrintInfo(uint32 channels, const char* source_file, uint32 line, const char* fmt, ...);
        API void PrintDebug(uint32 channels, const char* source_file, uint32 line, const char* fmt, ...);
        API void PrintVerbose(uint32 channels, const char* source_file, uint32 line, const char* fmt, ...);
        API void PrintWarning(uint32 channels, const char* source_file, uint32 line, const char* fmt, ...);
        API void PrintError(uint32 channels, const char* source_file, uint32 line, const char* fmt, ...);
    }
};

#define LOG_INFO(_text, ...)      Log::_private::PrintInfo(0, __FILE__, __LINE__, _text, ##__VA_ARGS__)
#define LOG_DEBUG(_text, ...)     Log::_private::PrintDebug(0, __FILE__, __LINE__, _text, ##__VA_ARGS__)
#define LOG_VERBOSE(_text, ...)   Log::_private::PrintVerbose(0, __FILE__, __LINE__, _text, ##__VA_ARGS__)
#define LOG_WARNING(_text, ...)   Log::_private::PrintWarning(0, __FILE__, __LINE__, _text, ##__VA_ARGS__)
#define LOG_ERROR(_text, ...)     Log::_private::PrintError(0, __FILE__, __LINE__, _text, ##__VA_ARGS__)
#define LOG_TEMP LOG_VERBOSE




//----------------------------------------------------------------------------------------------------------------------
// MathScalar.h



#if defined(__SSE2__) || (COMPILER_MSVC && (ARCH_64BIT || _M_IX86_FP >= 2))
    #include <xmmintrin.h>    // __m128
#endif

namespace M 
{
    #if defined(__SSE2__) || (COMPILER_MSVC && (ARCH_64BIT || _M_IX86_FP >= 2))
    FORCE_INLINE float Sqrt(float _a);
    FORCE_INLINE float Rsqrt(float _a);
    #else
    API  float Sqrt(float _a);
    API  float Rsqrt(float _a);
    #endif

    API float CopySign(float _x, float _y);
    API float Floor(float _f);
    API float Cos(float _a);
    API float ACos(float _a);
    API float Sin(float _a);
    API float ASin(float _a);
    API float ATan2(float _y, float _x);
    API float Exp(float _a);
    API float Log(float _a);
    FORCE_INLINE constexpr int NearestPow2(int n);
    FORCE_INLINE constexpr bool IsPow2(int n);
    FORCE_INLINE constexpr float ToRad(float _deg);
    FORCE_INLINE constexpr float ToDeg(float _rad);
    FORCE_INLINE uint32 FloatToBits(float _a);
    FORCE_INLINE float BitsToFloat(uint32 _a);
    FORCE_INLINE uint64 DoubleToBits(fl64 _a);
    FORCE_INLINE double BitsToDouble(uint64 _a);
    FORCE_INLINE uint32 Flip(uint32 _value);
    FORCE_INLINE bool IsNAN(float _f);
    FORCE_INLINE bool IsNAN64(double _f);
    FORCE_INLINE bool IsFIN(float _f);
    FORCE_INLINE bool IsFIN64(double _f);
    FORCE_INLINE bool IsINF(float _f);
    FORCE_INLINE bool IsINF64(double _f);
    FORCE_INLINE float Round(float _f);
    FORCE_INLINE float Ceil(float _f);
    FORCE_INLINE int CeilDiv(int n, int d);             // How many 'd' fits into 'n' (Ceiling division): ceil(float(f)/float(d))
    FORCE_INLINE uint32 CeilDiv(uint32 n, uint32 d);    
    FORCE_INLINE float Lerp(float _a, float _b, float _t);
    FORCE_INLINE float SmoothLerp(float _a, float _b, float _dt, float h);
    FORCE_INLINE float Sign(float _a);
    FORCE_INLINE float Abs(float _a);
    FORCE_INLINE int Abs(int _a);
    FORCE_INLINE int64 Abs(int64 _a);
    FORCE_INLINE float Tan(float _a);
    FORCE_INLINE float SinH(float _a);
    FORCE_INLINE float CosH(float _a);
    FORCE_INLINE float TanH(float _a);
    FORCE_INLINE float ATan(float _a);
    FORCE_INLINE float Pow(float _a, float _b);
    FORCE_INLINE float Exp2(float _a);
    FORCE_INLINE float Log2(float _a);
    FORCE_INLINE float Trunc(float _a);
    FORCE_INLINE float Fract(float _a);
    FORCE_INLINE float Mod(float _a, float _b);
    FORCE_INLINE bool IsEqual(float _a, float _b, float _epsilon = 0.00001f);
    FORCE_INLINE bool IsEqualArray(const float* _a, const float* _b, int _num, float _epsilon = 0.00001f);
    FORCE_INLINE float Wrap(float _a, float _wrap);
    FORCE_INLINE float WrapRange(float x, float fmin, float fmax);
    FORCE_INLINE int WrapRange(int x, int imin, int imax);
    FORCE_INLINE float Step(float _a, float _edge);
    FORCE_INLINE float Pulse(float _a, float _start, float _end);
    FORCE_INLINE float Saturate(float _n);
    FORCE_INLINE float SmoothStep(float _a, float _min, float _max);
    FORCE_INLINE float LinearStep(float t, float _min, float _max);
    FORCE_INLINE float NormalizeTime(float t, float _max);
    FORCE_INLINE float Bias(float _time, float _bias);
    FORCE_INLINE float Gain(float _time, float _gain);
    FORCE_INLINE float AngleDiff(float _a, float _b);
    FORCE_INLINE float AngleLerp(float _a, float _b, float _t);
} // M (Math)



                                                      
#if defined(__SSE2__) || (COMPILER_MSVC && ARCH_64BIT)
FORCE_INLINE float M::Sqrt(float x)
{
    float r;
    _mm_store_ss(&r, _mm_sqrt_ss( _mm_load_ss(&x)));
    return r;
}

FORCE_INLINE float M::Rsqrt(float x)
{
    float r;
    _mm_store_ss(&r, _mm_rsqrt_ss(_mm_load_ss(&x)));
    return r;
}
#endif   // __SSE2__

FORCE_INLINE constexpr int M::NearestPow2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

FORCE_INLINE constexpr bool M::IsPow2(int n)
{
    return (n & (n - 1)) == 0;
}

FORCE_INLINE constexpr float M::ToRad(float _deg)
{
    return _deg * M_PI / 180.0f;
}

FORCE_INLINE constexpr float M::ToDeg(float _rad)
{
    return _rad * 180.0f / M_PI;
}

FORCE_INLINE uint32 M::FloatToBits(float _a)
{
    union {
        float f;
        uint32 ui;
    } u = { _a };
    return u.ui;
}

FORCE_INLINE float M::BitsToFloat(uint32 _a)
{
    union {
        uint32 ui;
        float f;
    } u = { _a };
    return u.f;
}

FORCE_INLINE uint64 M::DoubleToBits(fl64 _a)
{
    union {
        fl64 f;
        uint64 ui;
    } u = { _a };
    return u.ui;
}

FORCE_INLINE fl64 M::BitsToDouble(uint64 _a)
{
    union {
        uint64 ui;
        fl64 f;
    } u = { _a };
    return u.f;
}

FORCE_INLINE uint32 M::Flip(uint32 _value)
{
    uint32 mask = -int32(_value >> 31) | 0x80000000;
    return _value ^ mask;
}

FORCE_INLINE bool M::IsNAN(float _f)
{
    const uint32 tmp = M::FloatToBits(_f) & INT32_MAX;
    return tmp > UINT32_C(0x7f800000);
}

FORCE_INLINE bool M::IsNAN64(fl64 _f)
{
    const uint64 tmp = M::DoubleToBits(_f) & INT64_MAX;
    return tmp > UINT64_C(0x7ff0000000000000);
}

FORCE_INLINE bool M::IsFIN(float _f)
{
    const uint32 tmp = M::FloatToBits(_f) & INT32_MAX;
    return tmp < UINT32_C(0x7f800000);
}

FORCE_INLINE bool M::IsFIN64(fl64 _f)
{
    const uint64 tmp = M::DoubleToBits(_f) & INT64_MAX;
    return tmp < UINT64_C(0x7ff0000000000000);
}

FORCE_INLINE bool M::IsINF(float _f)
{
    const uint32 tmp = M::FloatToBits(_f) & INT32_MAX;
    return tmp == UINT32_C(0x7f800000);
}

FORCE_INLINE bool M::IsINF64(fl64 _f)
{
    const uint64 tmp = M::DoubleToBits(_f) & INT64_MAX;
    return tmp == UINT64_C(0x7ff0000000000000);
}

FORCE_INLINE float M::Round(float _f)
{
    return M::Floor(_f + 0.5f);
}

FORCE_INLINE float M::Ceil(float _f)
{
    return -M::Floor(-_f);
}

FORCE_INLINE int M::CeilDiv(int n, int d)
{
    return (n + (d - 1))/d;
}

FORCE_INLINE uint32 M::CeilDiv(uint32 n, uint32 d)
{
    return (n + (d - 1))/d;
}

FORCE_INLINE float M::Lerp(float _a, float _b, float _t)
{
    return (1.0f - _t) * _a + _t * _b;
}

FORCE_INLINE float M::SmoothLerp(float _a, float _b, float _dt, float _h)
{
    return _b + (_a - _b)*M::Exp2(-_dt/_h);
}

FORCE_INLINE float M::Sign(float _a)
{
    return _a < 0.0f ? -1.0f : 1.0f;
}

FORCE_INLINE float M::Abs(float _a)
{
    union {
        float f;
        uint32 ui;
    } u = { _a };
    u.ui &= 0x7FFFFFFF;
    return u.f;
}

FORCE_INLINE int M::Abs(int _a)
{
    int mask = _a >> 31;
    return (mask^_a) - mask;
}

FORCE_INLINE int64 M::Abs(int64 _a)
{
    int64 mask = _a >> 63;
    return (mask^_a) - mask;
}

FORCE_INLINE float M::Tan(float _a)
{
    return M::Sin(_a) / M::Cos(_a);
}

FORCE_INLINE float M::SinH(float _a)
{
    return 0.5f * (M::Exp(_a) - M::Exp(-_a));
}

FORCE_INLINE float M::CosH(float _a)
{
    return 0.5f * (M::Exp(_a) + M::Exp(-_a));
}

FORCE_INLINE float M::TanH(float _a)
{
    const float tmp0 = M::Exp(2.0f * _a);
    const float tmp1 = tmp0 - 1.0f;
    const float tmp2 = tmp0 + 1.0f;
    const float result = tmp1 / tmp2;

    return result;
}

FORCE_INLINE float M::ATan(float _a)
{
    return M::ATan2(_a, 1.0f);
}

FORCE_INLINE float M::Pow(float _a, float _b)
{
    return M::Exp(_b * M::Log(_a));
}

FORCE_INLINE float M::Exp2(float _a)
{
    return M::Pow(2.0f, _a);
}

FORCE_INLINE float M::Log2(float _a)
{
    return M::Log(_a) * M_INVLOGNAT10;
}

FORCE_INLINE float M::Trunc(float _a)
{
    return (float)((int)_a);
}

FORCE_INLINE float M::Fract(float _a)
{
    return _a - M::Trunc(_a);
}

FORCE_INLINE float M::Mod(float _a, float _b)
{
    return _a - _b * M::Floor(_a / _b);
}

PRAGMA_DIAGNOSTIC_PUSH()
PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow")
FORCE_INLINE bool M::IsEqual(float _a, float _b, float _epsilon)
{
    const float lhs = M::Abs(_a - _b);
    float aa = M::Abs(_a);
    float ab = M::Abs(_b);
    float _max = aa > ab ? aa : ab;
    const float rhs = _epsilon * ((1.0f > _max ? 1.0f : _max));
    return lhs <= rhs;
}
PRAGMA_DIAGNOSTIC_POP()

FORCE_INLINE bool M::IsEqualArray(const float* _a, const float* _b, int _num,
                                             float _epsilon)
{
    bool result = M::IsEqual(_a[0], _b[0], _epsilon);
    for (int ii = 1; result && ii < _num; ++ii) {
        result = M::IsEqual(_a[ii], _b[ii], _epsilon);
    }
    return result;
}

FORCE_INLINE float M::Wrap(float _a, float _wrap)
{
    const float tmp0 = M::Mod(_a, _wrap);
    const float result = tmp0 < 0.0f ? _wrap + tmp0 : tmp0;
    return result;
}

FORCE_INLINE float M::WrapRange(float x, float fmin, float fmax)
{
    return M::Mod(x, fmax - fmin) + fmin;
}

FORCE_INLINE int M::WrapRange(int x, int imin, int imax)
{
    int range = imax - imin + 1;
    if (x < imin)
        x += range * ((imin - x) / range + 1);
    return imin + (x - imin) % range;
}

FORCE_INLINE float M::Step(float _a, float _edge)
{
    return _a < _edge ? 0.0f : 1.0f;
}

FORCE_INLINE float M::Pulse(float _a, float _start, float _end)
{
    return M::Step(_a, _start) - M::Step(_a, _end);
}

FORCE_INLINE float M::Saturate(float _n)
{
    if (_n < 0) 
        _n = 0;
    else if (_n > 1.0f)
        _n = 1.0f;
    return _n;
}

FORCE_INLINE float M::SmoothStep(float _a, float _min, float _max)
{
    ASSERT(_min < _max);
    float a = M::Saturate((_a - _min) / (_max - _min));
    return a * a * (3.0f - 2.0f * a);
}

FORCE_INLINE float M::LinearStep(float t, float _min, float _max)
{
    ASSERT(_min < _max);
    return M::Saturate((t - _min) / (_max - _min));
}

FORCE_INLINE float M::NormalizeTime(float t, float _max)
{
    ASSERT(_max > 0);
    float nt = t / _max;
    return nt < 1.0f ? nt : 1.0f;
}


FORCE_INLINE float M::Bias(float _time, float _bias)
{
    return _time / (((1.0f / _bias - 2.0f) * (1.0f - _time)) + 1.0f);
}

FORCE_INLINE float M::Gain(float _time, float _gain)
{
    if (_time < 0.5f)
        return M::Bias(_time * 2.0f, _gain) * 0.5f;

    return M::Bias(_time * 2.0f - 1.0f, 1.0f - _gain) * 0.5f + 0.5f;
}

FORCE_INLINE float M::AngleDiff(float _a, float _b)
{
    const float dist = M::Wrap(_b - _a, M_PI2);
    return M::Wrap(dist * 2.0f, M_PI2) - dist;
}

FORCE_INLINE float M::AngleLerp(float _a, float _b, float _t)
{
    return _a + M::AngleDiff(_a, _b) * _t;
}





FORCE_INLINE Float3 Quat::MulXYZ(Quat qa, Quat qb)
{
    const float ax = qa.x;
    const float ay = qa.y;
    const float az = qa.z;
    const float aw = qa.w;

    const float bx = qb.x;
    const float by = qb.y;
    const float bz = qb.z;
    const float bw = qb.w;

    return Float3(aw * bx + ax * bw + ay * bz - az * by, 
                       aw * by - ax * bz + ay * bw + az * bx,
                       aw * bz + ax * by - ay * bx + az * bw);
}

FORCE_INLINE Float3 Quat::TransformFloat3(Float3 v, Quat q)
{
    ASSERT(Quat::IsNorm(q));

    Quat tmp0 = Quat::Conjugate(q);
    Quat qv = Quat(v.x, v.y, v.z, 0.0f);
    Quat tmp1 = Quat::Mul(qv, tmp0);
    return Quat::MulXYZ(q, tmp1);
}

FORCE_INLINE Quat Quat::Mul(Quat p, Quat q)
{
    return Quat(
        p.f[3] * q.f[0] + p.f[0] * q.f[3] + p.f[1] * q.f[2] - p.f[2] * q.f[1],
        p.f[3] * q.f[1] - p.f[0] * q.f[2] + p.f[1] * q.f[3] + p.f[2] * q.f[0],
        p.f[3] * q.f[2] + p.f[0] * q.f[1] - p.f[1] * q.f[0] + p.f[2] * q.f[3],
        p.f[3] * q.f[3] - p.f[0] * q.f[0] - p.f[1] * q.f[1] - p.f[2] * q.f[2]
    );
}

FORCE_INLINE Quat Quat::Conjugate(Quat q)
{
    return Quat(-q.x, -q.y, -q.z, q.w);
}

FORCE_INLINE float Quat::Dot(Quat _a, Quat _b)
{
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z + _a.w * _b.w;
}

FORCE_INLINE float Quat::Angle(Quat qa, Quat qb)
{
    float a = M::Abs(Quat::Dot(qa, qb));
    return M::ACos((a < 1.0f ? a : 1.0f) * 2.0f);
}

FORCE_INLINE Quat Quat::Norm(Quat q)
{
    float d = Quat::Dot(q, q);
    if (d > M_FLOAT32_EPSILON) {
        float invNorm = M::Rsqrt(d);
        return Quat(q.x*invNorm, q.y*invNorm, q.z*invNorm, q.w*invNorm);
    }
    else {
        return QUAT_INDENT;    
    }
}

FORCE_INLINE bool Quat::IsNorm(Quat q)
{
    float d = Quat::Dot(q, q);
    return M::IsEqual(d, 1);
}

FORCE_INLINE Quat Quat::RotateAxis(Float3 _axis, float _angle)
{
    const float ha = _angle * 0.5f;
    const float ca = M::Cos(ha);
    const float sa = M::Sin(ha);
    return Quat(_axis.x * sa, _axis.y * sa, _axis.z * sa, ca);
}

FORCE_INLINE Quat Quat::RotateX(float ax)
{
    const float hx = ax * 0.5f;
    const float cx = M::Cos(hx);
    const float sx = M::Sin(hx);
    return Quat(sx, 0.0f, 0.0f, cx);
}

FORCE_INLINE Quat Quat::RotateY(float ay)
{
    const float hy = ay * 0.5f;
    const float cy = M::Cos(hy);
    const float sy = M::Sin(hy);
    return Quat(0.0f, sy, 0.0f, cy);
}

FORCE_INLINE Quat Quat::RotateZ(float az)
{
    const float hz = az * 0.5f;
    const float cz = M::Cos(hz);
    const float sz = M::Sin(hz);
    return Quat(0.0f, 0.0f, sz, cz);
}


FORCE_INLINE Float3 Float3::Abs(Float3 _a)
{
    return Float3(M::Abs(_a.x), M::Abs(_a.y), M::Abs(_a.z));
}

FORCE_INLINE Float3 Float3::Neg(Float3 _a)
{
    return Float3(-_a.x, -_a.y, -_a.z);
}

FORCE_INLINE Float3 Float3::Add(Float3 _a, Float3 _b)
{
    return Float3(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z);
}

FORCE_INLINE Float3 Float3::Add(Float3 _a, float _b)
{
    return Float3(_a.x + _b, _a.y + _b, _a.z + _b);
}

FORCE_INLINE Float3 Float3::Sub(Float3 _a, Float3 _b)
{
    return Float3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
}

FORCE_INLINE Float3 Float3::Sub(Float3 _a, float _b)
{
    return Float3(_a.x - _b, _a.y - _b, _a.z - _b);
}

FORCE_INLINE Float3 Float3::Mul(Float3 _a, Float3 _b)
{
    return Float3(_a.x * _b.x, _a.y * _b.y, _a.z * _b.z);
}

FORCE_INLINE Float3 Float3::Mul(Float3 _a, float _b)
{
    return Float3(_a.x * _b, _a.y * _b, _a.z * _b);
}

FORCE_INLINE float Float3::Dot(Float3 _a, Float3 _b)
{
    return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

FORCE_INLINE Float3 Float3::Cross(Float3 _a, Float3 _b)
{
    return Float3(_a.y * _b.z - _a.z * _b.y, 
                  _a.z * _b.x - _a.x * _b.z,
                  _a.x * _b.y - _a.y * _b.x);
}

FORCE_INLINE float Float3::Len(Float3 _a)
{
    return M::Sqrt(Float3::Dot(_a, _a));
}

FORCE_INLINE Float3 Float3::Lerp(Float3 _a, Float3 _b, float _t)
{
    return Float3(M::Lerp(_a.x, _b.x, _t), M::Lerp(_a.y, _b.y, _t), M::Lerp(_a.z, _b.z, _t));
}

FORCE_INLINE Float3 Float3::SmoothLerp(Float3 _a, Float3 _b, float _dt, float _h)
{
    float f = M::Exp2(-_dt/_h);
    return Float3(_b.x + (_a.x - _b.x)*f,
                  _b.y + (_a.y - _b.y)*f,
                  _b.z + (_a.z - _b.z)*f);
}

FORCE_INLINE Float3 Float3::Norm(Float3 _a)
{
    return Float3::Mul(_a, M::Rsqrt(Float3::Dot(_a, _a)));
}

FORCE_INLINE Float3 Float3::NormLen(Float3 _a, float* _outlen)
{
    ASSERT(_outlen);
    const float len = Float3::Len(_a);
    if (len > 0.0f) {
        const float invlen = 1.0f / len;
        *_outlen = len;
        return Float3(_a.x * invlen, _a.y * invlen, _a.z * invlen);
    } else {
        ASSERT_MSG(0, "Divide by zero");
        return Float3(0.0f, 0.0f, 0.0f);
    }
}

FORCE_INLINE Float3 Float3::Min(Float3 _a, Float3 _b)
{
    float xmin = _a.x < _b.x ? _a.x : _b.x;
    float ymin = _a.y < _b.y ? _a.y : _b.y;
    float zmin = _a.z < _b.z ? _a.z : _b.z;
    return Float3(xmin, ymin, zmin);
}

FORCE_INLINE Float3 Float3::Max(Float3 _a, Float3 _b)
{
    float xmax = _a.x > _b.x ? _a.x : _b.x;
    float ymax = _a.y > _b.y ? _a.y : _b.y;
    float zmax = _a.z > _b.z ? _a.z : _b.z;
    return Float3(xmax, ymax, zmax);
}

FORCE_INLINE Float3 Float3::Rcp(Float3 _a)
{
    return Float3(1.0f / _a.x, 1.0f / _a.y, 1.0f / _a.z);
}

FORCE_INLINE void Float3::Tangent(Float3* _t, Float3* _b, Float3 _n)
{
    const float nx = _n.x;
    const float ny = _n.y;
    const float nz = _n.z;

    if (M::Abs(nx) > M::Abs(nz)) {
        float inv_len = 1.0f / M::Sqrt(nx * nx + nz * nz);
        *_t = Float3(-nz * inv_len, 0.0f, nx * inv_len);
    } else {
        float inv_len = 1.0f / M::Sqrt(ny * ny + nz * nz);
        *_t = Float3(0.0f, nz * inv_len, -ny * inv_len);
    }

    *_b = Float3::Cross(_n, *_t);
}

FORCE_INLINE void Float3::TangentAngle(Float3* _t, Float3* _b, Float3 _n, float _angle)
{
    Float3::Tangent(_t, _b, _n);

    const float sa = M::Sin(_angle);
    const float ca = M::Cos(_angle);

    *_t = Float3(-sa * _b->x + ca * _t->x, -sa * _b->y + ca * _t->y, -sa * _b->z + ca * _t->z);

    *_b = Float3::Cross(_n, *_t);
}

FORCE_INLINE Float3 Float3::FromLatLong(float _u, float _v)
{
    const float phi = _u * M_PI2;
    const float theta = _v * M_PI;

    const float st = M::Sin(theta);
    const float sp = M::Sin(phi);
    const float ct = M::Cos(theta);
    const float cp = M::Cos(phi);

    return Float3(-st * sp, -st * cp, ct);
}

FORCE_INLINE Float2 Float3::ToLatLong(Float3 pos)
{
    const float phi = M::ATan2(pos.x, pos.y);
    const float theta = M::ACos(pos.z);

    return Float2((M_PI + phi) / M_PI2, theta * M_INVPI);
}


FORCE_INLINE Float4 Mat4::Row1() const 
{
    return Float4(m11, m12, m13, m14);
}

FORCE_INLINE Float4 Mat4::Row2() const
{
    return Float4(m21, m22, m23, m24);
}

FORCE_INLINE Float4 Mat4::Row3() const
{
    return Float4(m31, m32, m33, m34);
}

FORCE_INLINE Float4 Mat4::Row4() const
{
    return Float4(m41, m42, m43, m44);
}

FORCE_INLINE Float3 Mat4::XAxis() const
{
    return Float3(fc1);
}

FORCE_INLINE Float3 Mat4::YAxis() const
{
    return Float3(fc2);
}

FORCE_INLINE Float3 Mat4::ZAxis() const
{
    return Float3(fc3);
}

FORCE_INLINE Float3 Mat4::Position() const
{
    return Float3(fc4);
}

FORCE_INLINE void Mat4::SetCol1(Float4 _col1)
{
    fc1[0] = _col1.x;  
    fc1[1] = _col1.y;
    fc1[2] = _col1.z;
    fc1[3] = _col1.w;
}

FORCE_INLINE void Mat4::SetCol2(Float4 _col2)
{
    fc2[0] = _col2.x;  
    fc2[1] = _col2.y;
    fc2[2] = _col2.z;
    fc2[3] = _col2.w;
}

FORCE_INLINE void Mat4::SetCol3(Float4 _col3)
{
    fc3[0] = _col3.x;  
    fc3[1] = _col3.y;
    fc3[2] = _col3.z;
    fc3[3] = _col3.w;
}

FORCE_INLINE void Mat4::SetCol4(Float4 _col4)
{
    fc4[0] = _col4.x;  
    fc4[1] = _col4.y;
    fc4[2] = _col4.z;
    fc4[3] = _col4.w;
}

FORCE_INLINE Mat4 Mat4::Translate(float _tx, float _ty, float _tz)
{
    return Mat4(1.0f, 0.0f, 0.0f, _tx, 
                0.0f, 1.0f, 0.0f, _ty, 
                0.0f, 0.0f, 1.0f, _tz, 
                0.0f, 0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::Translate(Float3 _t)
{
    return Translate(_t.x, _t.y, _t.z);
}

FORCE_INLINE Mat4 Mat4::Scale(float _sx, float _sy, float _sz)
{
    return Mat4(_sx, 0.0f, 0.0f, 0.0f, 
                0.0f, _sy, 0.0f, 0.0f, 
                0.0f, 0.0f, _sz, 0.0f, 
                0.0f, 0.0f,0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::Scale(float _scale)
{
    return Mat4::Scale(_scale, _scale, _scale);
}

FORCE_INLINE Mat4 Mat4::RotateX(float _ax)
{
    const float sx = M::Sin(_ax);
    const float cx = M::Cos(_ax);

    return Mat4(1.0f, 0.0f, 0.0f, 0.0f, 
                0.0f, cx, -sx, 0.0f, 
                0.0f, sx, cx, 0.0f, 
                0.0f, 0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::RotateY(float _ay)
{
    const float sy = M::Sin(_ay);
    const float cy = M::Cos(_ay);

    return Mat4(cy, 0.0f, sy, 0.0f, 
                0.0f, 1.0f, 0.0f, 0.0f, 
                -sy, 0.0f, cy, 0.0f, 
                0.0f, 0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::RotateZ(float _az)
{
    const float sz = M::Sin(_az);
    const float cz = M::Cos(_az);

    return Mat4(cz, -sz, 0.0f, 0.0f, 
                sz, cz, 0.0f, 0.0f, 
                0.0f, 0.0f, 1.0f, 0.0f, 
                0.0f, 0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::RotateXY(float _ax, float _ay)
{
    const float sx = M::Sin(_ax);
    const float cx = M::Cos(_ax);
    const float sy = M::Sin(_ay);
    const float cy = M::Cos(_ay);

    return Mat4(cy, 0.0f, sy, 0.0f, 
                sx * sy, cx, -sx * cy, 0.0f, 
                -cx * sy, sx, cx * cy, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::RotateXYZ(float _ax, float _ay, float _az)
{
    const float sx = M::Sin(_ax);
    const float cx = M::Cos(_ax);
    const float sy = M::Sin(_ay);
    const float cy = M::Cos(_ay);
    const float sz = M::Sin(_az);
    const float cz = M::Cos(_az);

    return Mat4(cy * cz, -cy * sz, sy, 0.0f, 
                cz * sx * sy + cx * sz, cx * cz - sx * sy * sz, -cy * sx, 0.0f, 
                -cx * cz * sy + sx * sz, cz * sx + cx * sy * sz, cx * cy, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat4 Mat4::RotateZYX(float _ax, float _ay, float _az)
{
    const float sx = M::Sin(_ax);
    const float cx = M::Cos(_ax);
    const float sy = M::Sin(_ay);
    const float cy = M::Cos(_ay);
    const float sz = M::Sin(_az);
    const float cz = M::Cos(_az);

    return Mat4(cy * cz, cz * sx * sy - cx * sz, cx * cz * sy + sx * sz, 0.0f, 
                cy * sz, cx * cz + sx * sy * sz, -cz * sx + cx * sy * sz, 0.0f, 
                -sy, cy * sx, cx * cy, 0.0f, 
                0.0f, 0.0f, 0.0f, 1.0f);
};

FORCE_INLINE Mat4 Mat4::ToQuatTranslate(Quat q, Float3 translate)
{
    Mat4 mat = Mat4::FromQuat(q);
    mat.m14 = -(mat.m11 * translate.x + mat.m12 * translate.y + mat.m13 * translate.z);
    mat.m24 = -(mat.m21 * translate.x + mat.m22 * translate.y + mat.m23 * translate.z);
    mat.m34 = -(mat.m31 * translate.x + mat.m32 * translate.y + mat.m33 * translate.z);
    return mat;
}

FORCE_INLINE Mat4 Mat4::ToQuatTranslateHMD(Quat q, Float3 translate)
{
    return Mat4::ToQuatTranslate(Quat(-q.x, -q.y, q.z, q.w), translate);
}

FORCE_INLINE Float3 Mat4::MulFloat3(const Mat4& _mat, Float3 _vec)
{
    return Float3(_vec.x * _mat.m11 + _vec.y * _mat.m12 + _vec.z * _mat.m13 + _mat.m14,
                  _vec.x * _mat.m21 + _vec.y * _mat.m22 + _vec.z * _mat.m23 + _mat.m24,
                  _vec.x * _mat.m31 + _vec.y * _mat.m32 + _vec.z * _mat.m33 + _mat.m34);
}

FORCE_INLINE Float3 Mat4::MulFloat3_xyz0(const Mat4& _mat, Float3 _vec)
{
    return Float3(_vec.x * _mat.m11 + _vec.y * _mat.m12 + _vec.z * _mat.m13,
                  _vec.x * _mat.m21 + _vec.y * _mat.m22 + _vec.z * _mat.m23,
                  _vec.x * _mat.m31 + _vec.y * _mat.m32 + _vec.z * _mat.m33);
}

FORCE_INLINE Float3 Mat4::MulFloat3H(const Mat4& _mat, Float3 _vec)
{
    float xx = _vec.x * _mat.m11 + _vec.y * _mat.m12 + _vec.z * _mat.m13 + _mat.m14;
    float yy = _vec.x * _mat.m21 + _vec.y * _mat.m22 + _vec.z * _mat.m23 + _mat.m24;
    float zz = _vec.x * _mat.m31 + _vec.y * _mat.m32 + _vec.z * _mat.m33 + _mat.m34;
    float ww = _vec.x * _mat.m41 + _vec.y * _mat.m42 + _vec.z * _mat.m43 + _mat.m44;
    float iw = M::Sign(ww) / ww;
    return Float3(xx * iw, yy * iw, zz * iw);
}

FORCE_INLINE Float4 Mat4::MulFloat4(const Mat4& _mat, Float4 _vec)
{
    return Float4(
        _vec.x * _mat.m11 + _vec.y * _mat.m12 + _vec.z * _mat.m13 + _vec.w * _mat.m14,
        _vec.x * _mat.m21 + _vec.y * _mat.m22 + _vec.z * _mat.m23 + _vec.w * _mat.m24,
        _vec.x * _mat.m31 + _vec.y * _mat.m32 + _vec.z * _mat.m33 + _vec.w * _mat.m34,
        _vec.x * _mat.m41 + _vec.y * _mat.m42 + _vec.z * _mat.m43 + _vec.w * _mat.m44);
}

FORCE_INLINE void Mat4::ProjFlipHandedness(Mat4* _dst, const Mat4& _src)
{
    _dst->m11 = -_src.m11;
    _dst->m12 = -_src.m12;
    _dst->m13 = -_src.m13;
    _dst->m14 = -_src.m14;
    _dst->m21 = _src.m21;
    _dst->m22 = _src.m22;
    _dst->m23 = _src.m23;
    _dst->m24 = _src.m24;
    _dst->m31 = -_src.m31;
    _dst->m32 = -_src.m32;
    _dst->m33 = -_src.m33;
    _dst->m34 = -_src.m34;
    _dst->m41 = _src.m41;
    _dst->m42 = _src.m42;
    _dst->m43 = _src.m43;
    _dst->m44 = _src.m44;
}

FORCE_INLINE void Mat4::ViewFlipHandedness(Mat4* _dst, const Mat4& _src)
{
    _dst->m11 = -_src.m11;
    _dst->m12 = _src.m12;
    _dst->m13 = -_src.m13;
    _dst->m14 = _src.m14;
    _dst->m21 = -_src.m21;
    _dst->m22 = _src.m22;
    _dst->m23 = -_src.m23;
    _dst->m24 = _src.m24;
    _dst->m31 = -_src.m31;
    _dst->m32 = _src.m32;
    _dst->m33 = -_src.m33;
    _dst->m34 = _src.m34;
    _dst->m41 = -_src.m41;
    _dst->m42 = _src.m42;
    _dst->m43 = -_src.m43;
    _dst->m44 = _src.m44;
}

FORCE_INLINE Mat4 Mat4::Transpose(const Mat4& _a)
{
    return Mat4(_a.m11, _a.m21, _a.m31, _a.m41,
                _a.m12, _a.m22, _a.m32, _a.m42, 
                _a.m13, _a.m23, _a.m33, _a.m43, 
                _a.m14, _a.m24, _a.m34, _a.m44);
}


FORCE_INLINE Float4 Float4::Mul(Float4 _a, Float4 _b)
{
    return Float4(_a.x * _b.x, _a.y * _b.y, _a.z * _b.z, _a.w * _b.w);
}

FORCE_INLINE Float4 Float4::Mul(Float4 _a, float _b)
{
    return Float4(_a.x * _b, _a.y * _b, _a.z * _b, _a.w * _b);
}

FORCE_INLINE Float4 Float4::Add(Float4 _a, Float4 _b)
{
    return Float4(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z, _a.w + _b.w);
}

FORCE_INLINE Float4 Float4::Sub(Float4 _a, Float4 _b)
{
    return Float4(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z, _a.w - _b.w);
}

FORCE_INLINE float Color4u::ValueToLinear(float _a)
{
    const float lo = _a / 12.92f;
    const float hi = M::Pow((_a + 0.055f) / 1.055f, 2.4f);
    const float result = M::Lerp(hi, lo, _a <= 0.04045f ? 1.0f : 0.0f);
    return result;
}

FORCE_INLINE float Color4u::ValueToGamma(float _a)
{
    const float lo = _a * 12.92f;
    const float hi = M::Pow(M::Abs(_a), 1.0f / 2.4f) * 1.055f - 0.055f;
    const float result = M::Lerp(hi, lo, _a <= 0.0031308f ? 1.0f : 0.0f);
    return result;
}

FORCE_INLINE Color4u Color4u::FromFloat4(float r, float g, float b, float a)
{
    return Color4u(
        ((uint8)(r * 255.0f)),
        ((uint8)(g * 255.0f)),
        ((uint8)(b * 255.0f)),
        ((uint8)(a * 255.0f)));
}

FORCE_INLINE Float4 Color4u::ToFloat4(Color4u c)
{
    float rcp = 1.0f / 255.0f;
    return Float4((float)c.r * rcp, (float)c.g * rcp, (float)c.b * rcp, (float)c.a * rcp);
}

FORCE_INLINE Float4 Color4u::ToFloat4(uint8 _r, uint8 _g, uint8 _b, uint8 _a)
{
    return ToFloat4(Color4u(_r, _g, _b, _a));
}


FORCE_INLINE Float3 Mat3::Row1() const
{
    return Float3(m11, m12, m13);
}

FORCE_INLINE Float3 Mat3::Row2() const
{
    return Float3(m21, m22, m23);
}

FORCE_INLINE Float3 Mat3::Row3() const
{
    return Float3(m31, m32, m33);
}

FORCE_INLINE Mat3 Mat3::Transpose(const Mat3& _a)
{
    return Mat3(_a.m11, _a.m21, _a.m31, 
                _a.m12, _a.m22, _a.m32, 
                _a.m13, _a.m23, _a.m33);
}

FORCE_INLINE Float3 Mat3::MulFloat3(const Mat3& _mat, Float3 _vec)
{
    return Float3(_vec.x * _mat.m11 + _vec.y * _mat.m12 + _vec.z * _mat.m13,
                  _vec.x * _mat.m21 + _vec.y * _mat.m22 + _vec.z * _mat.m23,
                  _vec.x * _mat.m31 + _vec.y * _mat.m32 + _vec.z * _mat.m33);
}

FORCE_INLINE Mat3 Mat3::MulInverse(const Mat3& _a, const Mat3& _b)
{
    Mat3 _atrans = Mat3::Transpose(_a);
    return Mat3::Mul(_atrans, _b);
}

FORCE_INLINE Float3 Mat3::MulFloat3Inverse(const Mat3& mat, Float3 v)
{
    Mat3 rmat = Mat3::Transpose(mat);
    return Mat3::MulFloat3(rmat, v);
}

FORCE_INLINE Float2 Mat3::MulFloat2(const Mat3& _mat, Float2 _vec)
{
    return Float2(_vec.x * _mat.m11 + _vec.y * _mat.m12 + _mat.m13,
                  _vec.x * _mat.m21 + _vec.y * _mat.m22 + _mat.m23);
}

FORCE_INLINE Mat3 Mat3::Translate(float x, float y)
{
    return Mat3(1.0f, 0.0f, x, 
                0.0f, 1.0f, y, 
                0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat3 Mat3::TranslateFloat2(Float2 p)
{
    return Mat3::Translate(p.x, p.y);
}

FORCE_INLINE Mat3 Mat3::Rotate(float theta)
{
    float c = M::Cos(theta);
    float s = M::Sin(theta);
    return Mat3(c, -s, 0.0f, 
                       s, c, 0.0f, 
                       0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat3 Mat3::Scale(float sx, float sy)
{
    return Mat3(sx, 0.0f, 0.0f, 
                0.0f, sy, 0.0f, 
                0.0f, 0.0f, 1.0f);
}

FORCE_INLINE Mat3 Mat3::ScaleRotateTranslate(float sx, float sy, float angle, float tx, float ty)
{
    float c = M::Cos(angle);
    float s = M::Sin(angle);
    return Mat3(sx*c,  -sy*s,  tx, 
                sx*s,   sy*c,  ty, 
                0.0f,   0.0f,  1.0f);
}

FORCE_INLINE float Float2::Dot(Float2 _a, Float2 _b)
{
    return _a.x * _b.x + _a.y * _b.y;
}

FORCE_INLINE float Float2::Len(Float2 _a)
{
    return M::Sqrt(Float2::Dot(_a, _a));
}

FORCE_INLINE Float2 Float2::Norm(Float2 _a)
{
    return Float2::Mul(_a, M::Rsqrt(Float2::Dot(_a, _a)));
}

FORCE_INLINE Float2 Float2::NormLen(Float2 _a, float* outlen)
{
    const float len = Float2::Len(_a);
    if (len > 0.0f) {
        *outlen = len;
        return Float2(_a.x / len, _a.y / len);
    } else {
        ASSERT_MSG(0, "Divide by zero");
        return _a;
    }
}

FORCE_INLINE Float2 Float2::Min(Float2 _a, Float2 _b)
{
    return Float2(_a.x < _b.x ? _a.x : _b.x, _a.y < _b.y ? _a.y : _b.y);
}

FORCE_INLINE Float2 Float2::Max(Float2 _a, Float2 _b)
{
    return Float2(_a.x > _b.x ? _a.x : _b.x, _a.y > _b.y ? _a.y : _b.y );
}

FORCE_INLINE Float2 Float2::Lerp(Float2 _a, Float2 _b, float _t)
{
    return Float2(M::Lerp(_a.x, _b.x, _t), M::Lerp(_a.y, _b.y, _t));
}

FORCE_INLINE Float2 Float2::Abs(Float2 _a)
{
    return Float2(M::Abs(_a.x), M::Abs(_a.y));
}

FORCE_INLINE Float2 Float2::Neg(Float2 _a)
{
    return Float2(-_a.x, -_a.y);
}

FORCE_INLINE Float2 Float2::Add(Float2 _a, Float2 _b)
{
    return Float2(_a.x + _b.x, _a.y + _b.y);
}

FORCE_INLINE Float2 Float2::Add(Float2 _a, float _b)
{
    return Float2(_a.x + _b, _a.y + _b);
}

FORCE_INLINE Float2 Float2::Sub(Float2 _a, Float2 _b)
{
    return Float2(_a.x - _b.x, _a.y - _b.y);
}

FORCE_INLINE Float2 Float2::Sub(Float2 _a, float _b)
{
    return Float2(_a.x - _b, _a.y - _b);
}

FORCE_INLINE Float2 Float2::Mul(Float2 _a, Float2 _b)
{
    return Float2(_a.x * _b.x, _a.y * _b.y);
}

FORCE_INLINE Float2 Float2::Mul(Float2 _a, float _b)
{
    return Float2(_a.x * _b, _a.y * _b);
}

FORCE_INLINE Int2 Int2::Add(Int2 _a, Int2 _b)
{
    return Int2(_a.x + _b.x, _a.y + _b.y);
}

FORCE_INLINE Int2 Int2::Sub(Int2 _a, Int2 _b)
{
    return Int2(_a.x - _b.x, _a.y - _b.y);
}

FORCE_INLINE Int2 Int2::Min(Int2 _a, Int2 _b)
{
    return Int2(_a.x < _b.x ? _a.x : _b.x, _a.y < _b.y ? _a.y : _b.y);
}

FORCE_INLINE Int2 Int2::Max(Int2 _a, Int2 _b)
{
    return Int2(_a.x > _b.x ? _a.x : _b.x, _a.y > _b.y ? _a.y : _b.y);
}


FORCE_INLINE RectFloat RectFloat::CenterExtents(Float2 center, Float2 extents)
{
    return RectFloat(Float2::Sub(center, extents), Float2::Add(center, extents));
}

FORCE_INLINE RectFloat RectFloat::Expand(const RectFloat rc, Float2 expand)
{
    return RectFloat(rc.xmin - expand.x, rc.ymin - expand.y, rc.xmax + expand.x, rc.ymax + expand.y);
}

FORCE_INLINE bool RectFloat::TestPoint(const RectFloat rc, Float2 pt)
{
    if (pt.x < rc.xmin || pt.y < rc.ymin || pt.x > rc.xmax || pt.y > rc.ymax)
        return false;
    return true;
}

FORCE_INLINE bool RectFloat::Test(const RectFloat rc1, const RectFloat rc2)
{
    if (rc1.xmax < rc2.xmin || rc1.xmin > rc2.xmax)
        return false;
    if (rc1.ymax < rc2.ymin || rc1.ymin > rc2.ymax)
        return false;
    return true;
}

FORCE_INLINE void RectFloat::AddPoint(RectFloat& rc, Float2 pt)
{
    rc = RectFloat(Float2::Min(Float2(rc.vmin), pt), Float2::Max(Float2(rc.vmax), pt));
}

FORCE_INLINE bool RectFloat::IsEmpty() const
{
    return xmin >= xmax || ymin >= ymax;
}

/*
*   2               3
*   -----------------
*   |               |
*   |               |
*   |               |
*   |               |
*   |               |
*   -----------------
*   0               1
*/
FORCE_INLINE Float2 RectFloat::GetCorner(const RectFloat* rc, int index)
{
    return Float2((index & 1) ? rc->xmax : rc->xmin, (index & 2) ? rc->ymax : rc->ymin);
}

FORCE_INLINE void RectFloat::GetCorners(const RectFloat* rc, Float2 corners[4])
{
    for (int i = 0; i < 4; i++)
        corners[0] = RectFloat::GetCorner(rc, i);
}

FORCE_INLINE float RectFloat::Width() const
{
    return xmax - xmin;
}

FORCE_INLINE float RectFloat::Height() const
{
    return ymax - ymin;
}

FORCE_INLINE Float2 RectFloat::Extents(const RectFloat rc)
{
    return Float2::Mul(Float2::Sub(Float2(rc.vmax), Float2(rc.vmin)), 0.5f);
}

FORCE_INLINE Float2 RectFloat::Center(const RectFloat rc)
{
    return Float2::Mul(Float2::Add(Float2(rc.vmin), Float2(rc.vmax)), 0.5f);
}

FORCE_INLINE RectFloat RectFloat::Translate(const RectFloat rc, Float2 pos) 
{
    return RectFloat(Float2::Add(pos, Float2(rc.vmin)), Float2::Add(pos, Float2(rc.vmax)));
}

FORCE_INLINE RectInt RectInt::Expand(const RectInt rc, Int2 expand)
{
    return RectInt(rc.xmin - expand.x, rc.ymin - expand.y, rc.xmax + expand.x, rc.ymax + expand.y);
}

FORCE_INLINE bool RectInt::TestPoint(const RectInt rc, Int2 pt)
{
    if (pt.x < rc.xmin || pt.y < rc.ymin || pt.x > rc.xmax || pt.y > rc.ymax)
        return false;
    return true;
}

FORCE_INLINE bool RectInt::Test(const RectInt rc1, const RectInt rc2)
{
    if (rc1.xmax < rc2.xmin || rc1.xmin > rc2.xmax)
        return false;
    if (rc1.ymax < rc2.ymin || rc1.ymin > rc2.ymax)
        return false;
    return true;
}

FORCE_INLINE void RectInt::AddPoint(RectInt& rc, Int2 pt)
{
    rc = RectInt(Int2::Min(Int2(rc.vmin), pt), Int2::Max(Int2(rc.vmax), pt));
}

FORCE_INLINE bool RectInt::IsEmpty() const
{
    return xmin >= xmax || ymin >= ymax;
}    

FORCE_INLINE int RectInt::Width() const
{
    return xmax - xmin;
}

FORCE_INLINE int RectInt::Height() const
{
    return ymax - ymin;
}

FORCE_INLINE void RectInt::SetWidth(int width)
{
    xmax = xmin + width;
}

FORCE_INLINE void RectInt::SetHeight(int height)
{
    ymax = ymin + height;
}


/*
*   2               3 (max)
*   -----------------
*   |               |
*   |               |
*   |               |
*   |               |
*   |               |
*   -----------------
*   0 (min)         1
*/
FORCE_INLINE Int2 RectInt::GetCorner(const RectInt* rc, int index)
{
    return Int2((index & 1) ? rc->xmax : rc->xmin, (index & 2) ? rc->ymax : rc->ymin);
}

FORCE_INLINE void RectInt::GetCorners(const RectInt* rc, Int2 corners[4])
{
    for (int i = 0; i < 4; i++)
        corners[0] = GetCorner(rc, i);
}


FORCE_INLINE bool AABB::IsEmpty() const
{
    return xmin >= xmax || ymin >= ymax || zmin >= zmax;
}

FORCE_INLINE AABB AABB::CenterExtents(Float3 center, Float3 extents)
{
    return AABB(Float3::Sub(center, extents), Float3::Add(center, extents));
}

FORCE_INLINE void AABB::AddPoint(AABB& aabb, Float3 pt)
{
    aabb = AABB(Float3::Min(Float3(aabb.vmin), pt), Float3::Max(Float3(aabb.vmax), pt));
}

FORCE_INLINE AABB AABB::Unify(const AABB& aabb1, const AABB& aabb2)
{
    AABB r = aabb1;
    AABB::AddPoint(r, Float3(aabb2.vmin));
    AABB::AddPoint(r, Float3(aabb2.vmax));
    return r;
}

FORCE_INLINE bool AABB::TestPoint(const AABB& aabb, Float3 pt)
{
    if (aabb.xmax < pt.x || aabb.xmin > pt.x)
        return false;
    if (aabb.ymax < pt.y || aabb.ymin > pt.y)
        return false;
    if (aabb.zmax < pt.z || aabb.zmin > pt.z)
        return false;
    return true;
}

FORCE_INLINE bool AABB::Test(const AABB& aabb1, const AABB& aabb2)
{
    if (aabb1.xmax < aabb2.xmin || aabb1.xmin > aabb2.xmax)
        return false;
    if (aabb1.ymax < aabb2.ymin || aabb1.ymin > aabb2.ymax)
        return false;
    if (aabb1.zmax < aabb2.zmin || aabb1.zmin > aabb2.zmax)
        return false;
    return true;    
}

/*
 *        6                 7
 *        ------------------
 *       /|               /|
 *      / |              / |
 *     /  |             /  |
 *  2 /   |          3 /   |
 *   /----------------/    |
 *   |    |           |    |
 *   |    |           |    |      +Z
 *   |    |           |    |
 *   |    |-----------|----|     |
 *   |   / 4          |   / 5    |  / +Y
 *   |  /             |  /       | /
 *   | /              | /        |/
 *   |/               |/         --------- +X
 *   ------------------
 *  0                 1
 */
FORCE_INLINE Float3 AABB::GetCorner(const AABB& aabb, int index)
{
    ASSERT(index < 8);
    return Float3((index & 1) ? aabb.xmax : aabb.xmin,
                  (index & 4) ? aabb.ymax : aabb.ymin,
                  (index & 2) ? aabb.zmax : aabb.zmin);
}

FORCE_INLINE void AABB::GetCorners(const AABB& aabb, Float3 corners[8])
{
    for (int i = 0; i < 8; i++)
        corners[i] = AABB::GetCorner(aabb, i);
}

FORCE_INLINE Float3 AABB::Extents() const
{
    return Float3::Mul(Float3(xmax - xmin,  ymax - ymin, zmax - zmin), 0.5f);
}

FORCE_INLINE Float3 AABB::Dimensions() const
{
    return Float3(xmax - xmin,  ymax - ymin, zmax - zmin);
}

FORCE_INLINE Float3 AABB::Center() const
{
    return Float3::Mul(Float3::Add(Float3(vmin), Float3(vmax)), 0.5f);
}

FORCE_INLINE AABB AABB::Translate(const AABB& aabb, Float3 offset)
{
    return AABB(Float3::Add(Float3(aabb.vmin), offset), Float3::Add(Float3(aabb.vmax), offset));
}

FORCE_INLINE AABB AABB::SetPos(const AABB& aabb, Float3 pos)
{
    Float3 e = aabb.Extents();
    return AABB(pos.x - e.x, pos.y - e.y, pos.z - e.z, 
                pos.x + e.x, pos.y + e.y, pos.z + e.z);
}

FORCE_INLINE AABB AABB::Expand(const AABB& aabb, Float3 expand)
{
    Float3 p = aabb.Center();
    Float3 e = Float3::Add(aabb.Extents(), expand);
    return AABB(p.x - e.x, p.y - e.y, p.z - e.z, 
                p.x + e.x, p.y + e.y, p.z + e.z);
}

FORCE_INLINE AABB AABB::Scale(const AABB& aabb, Float3 scale)
{
    Float3 p = aabb.Center();
    Float3 e = Float3::Mul(aabb.Extents(), scale);
    return AABB(p.x - e.x, p.y - e.y, p.z - e.z, 
                p.x + e.x, p.y + e.y, p.z + e.z);
}

                                                                                                           
FORCE_INLINE Float2 operator+(Float2 a, Float2 b)
{
    return Float2::Add(a, b);
}

FORCE_INLINE Float2 operator-(Float2 a, Float2 b)
{
    return Float2::Sub(a, b);
}

FORCE_INLINE Float2 operator*(Float2 v, float k)
{
    return Float2::Mul(v, k);
}

FORCE_INLINE Float2 operator*(float k, Float2 v)
{
    return Float2::Mul(v, k);
}

FORCE_INLINE Float2 operator*(Float2 v0, Float2 v1)
{
    return Float2::Mul(v0, v1);
}

FORCE_INLINE Int2 operator+(Int2 a, Int2 b)
{
    return Int2::Add(a, b);
}

FORCE_INLINE Int2 operator-(Int2 a, Int2 b)
{
    return Int2::Sub(a, b);
}

FORCE_INLINE Float3 operator+(Float3 v1, Float3 v2)
{
    return Float3::Add(v1, v2);
}

FORCE_INLINE Float3 operator-(Float3 v1, Float3 v2)
{
    return Float3::Sub(v1, v2);
}

FORCE_INLINE Float3 operator*(Float3 v, float k)
{
    return Float3::Mul(v, k);
}

FORCE_INLINE Float3 operator*(float k, Float3 v)
{
    return Float3::Mul(v, k);
}

FORCE_INLINE Float4 operator+(Float4 v1, Float4 v2)
{
    return Float4::Add(v1, v2);
}

FORCE_INLINE Float4 operator-(Float4 v1, Float4 v2)
{
    return Float4::Sub(v1, v2);
}

FORCE_INLINE Float4 operator*(Float4 v, float k)
{
    return Float4::Mul(v, k);
}

FORCE_INLINE Float4 operator*(float k, Float4 v)
{
    return Float4::Mul(v, k);
}

FORCE_INLINE Mat4 operator*(const Mat4& a, const Mat4& b)
{
    return Mat4::Mul(a, b);
}

FORCE_INLINE Mat3 operator*(const Mat3& a, const Mat3& b)
{
    return Mat3::Mul(a, b);
}

FORCE_INLINE Quat operator*(const Quat& a, const Quat& b)
{
    return Quat::Mul(a, b);
}


namespace M
{
    FORCE_INLINE float  Float2Dot(Float2 _a, Float2 _b) { return Float2::Dot(_a, _b); }
    FORCE_INLINE float  Float2Len(Float2 _a) { return Float2::Len(_a); }
    FORCE_INLINE Float2 Float2Norm(Float2 _a) { return Float2::Norm(_a); }
    FORCE_INLINE Float2 Float2NormLen(Float2 _a, float* outlen) { return Float2::NormLen(_a, outlen); }
    FORCE_INLINE Float2 Float2Min(Float2 _a, Float2 _b) { return Float2::Min(_a, _b); }
    FORCE_INLINE Float2 Float2Max(Float2 _a, Float2 _b) { return Float2::Max(_a, _b); }
    FORCE_INLINE Float2 Float2Lerp(Float2 _a, Float2 _b, float _t) { return Float2::Lerp(_a, _b, _t); }
    FORCE_INLINE Float2 Float2Abs(Float2 _a) { return Float2::Abs(_a); }
    FORCE_INLINE Float2 Float2Neg(Float2 _a) { return Float2::Neg(_a); }
    FORCE_INLINE Float2 Float2Add(Float2 _a, Float2 _b) { return Float2::Add(_a, _b); }
    FORCE_INLINE Float2 Float2Add(Float2 _a, float _b) { return Float2::Add(_a, _b); }
    FORCE_INLINE Float2 Float2Sub(Float2 _a, Float2 _b) { return Float2::Sub(_a, _b); }
    FORCE_INLINE Float2 Float2Sub(Float2 _a, float _b) { return Float2::Sub(_a, _b); }
    FORCE_INLINE Float2 Float2Mul(Float2 _a, Float2 _b) { return Float2::Mul(_a, _b); }
    FORCE_INLINE Float2 Float2Mul(Float2 _a, float _b) { return Float2::Mul(_a, _b); }
    FORCE_INLINE Float2 Float2CalcLinearFit2D(const Float2* _points, int _num) { return Float2::CalcLinearFit2D(_points, _num); }

    FORCE_INLINE Float3 Float3Abs(Float3 _a) { return Float3::Abs(_a); }
    FORCE_INLINE Float3 Float3Neg(Float3 _a) { return Float3::Neg(_a); }
    FORCE_INLINE Float3 Float3Add(Float3 _a, Float3 _b) { return Float3::Add(_a, _b); }
    FORCE_INLINE Float3 Float3Add(Float3 _a, float _b) { return Float3::Add(_a, _b); }
    FORCE_INLINE Float3 Float3Sub(Float3 _a, Float3 _b) { return Float3::Sub(_a, _b); }
    FORCE_INLINE Float3 Float3Sub(Float3 _a, float _b) { return Float3::Sub(_a, _b); }
    FORCE_INLINE Float3 Float3Mul(Float3 _a, Float3 _b) { return Float3::Mul(_a, _b); }
    FORCE_INLINE Float3 Float3Mul(Float3 _a, float _b) { return Float3::Mul(_a, _b); }
    FORCE_INLINE float  Float3Dot(Float3 _a, Float3 _b) { return Float3::Dot(_a, _b); }
    FORCE_INLINE Float3 Float3Cross(Float3 _a, Float3 _b) { return Float3::Cross(_a, _b); }
    FORCE_INLINE float  Float3Len(Float3 _a) { return Float3::Len(_a); }
    FORCE_INLINE Float3 Float3Lerp(Float3 _a, Float3 _b, float _t) { return Float3::Lerp(_a, _b, _t); }
    FORCE_INLINE Float3 Float3SmoothLerp(Float3 _a, Float3 _b, float _dt, float _h) { return Float3::SmoothLerp(_a, _b, _dt, _h); }
    FORCE_INLINE Float3 Float3Norm(Float3 _a) { return Float3::Norm(_a); }
    FORCE_INLINE Float3 Float3NormLen(Float3 _a, float* _outlen) { return Float3::NormLen(_a, _outlen); }
    FORCE_INLINE Float3 Float3Min(Float3 _a, Float3 _b) { return Float3::Min(_a, _b); }
    FORCE_INLINE Float3 Float3Max(Float3 _a, Float3 _b) { return Float3::Max(_a, _b); }
    FORCE_INLINE Float3 Float3Rcp(Float3 _a) { return Float3::Rcp(_a); }
    FORCE_INLINE void   Float3Tangent(Float3* _t, Float3* _b, Float3 _n) { Float3::Tangent(_t, _b, _n); }
    FORCE_INLINE void   Float3TangentAngle(Float3* _t, Float3* _b, Float3 _n, float _angle) { Float3::TangentAngle(_t, _b, _n, _angle); }
    FORCE_INLINE Float3 Float3FromLatLong(float _u, float _v) { return Float3::FromLatLong(_u, _v); }
    FORCE_INLINE Float2 Float3ToLatLong(Float3 _dir) { return Float3::ToLatLong(_dir); }
    FORCE_INLINE Float3 Float3CalcLinearFit3D(const Float3* _points, int _num) { return Float3::CalcLinearFit3D(_points, _num); }

    FORCE_INLINE Float4 Float4Mul(Float4 _a, Float4 _b) { return Float4::Mul(_a, _b); }
    FORCE_INLINE Float4 Float4Mul(Float4 _a, float _b) { return Float4::Mul(_a, _b); }
    FORCE_INLINE Float4 Float4Add(Float4 _a, Float4 _b) { return Float4::Add(_a, _b); }
    FORCE_INLINE Float4 Float4Sub(Float4 _a, Float4 _b) { return Float4::Sub(_a, _b); }

    FORCE_INLINE float ColorValueToLinear(float _a) { return Color4u::ValueToLinear(_a); }
    FORCE_INLINE float ColorValueToGamma(float _a) { return Color4u::ValueToGamma(_a); }
    FORCE_INLINE Float4 ColorToFloat4(Color4u c) { return Color4u::ToFloat4(c); }
    FORCE_INLINE Color4u  ColorBlend(Color4u _a, Color4u _b, float _t) { return Color4u::Blend(_a, _b, _t); }
    FORCE_INLINE Float4 ColorToFloat4SRGB(Float4 cf) { return Color4u::ToFloat4SRGB(cf); }
    FORCE_INLINE Float4 ColorToFloat4Linear(Float4 c) { return Color4u::ToFloat4Linear(c); }
    FORCE_INLINE Float3 ColorRGBtoHSV(Float3 rgb) { return Color4u::RGBtoHSV(rgb); }
    FORCE_INLINE Float3 ColorHSVtoRGB(Float3 hsv) { return Color4u::HSVtoRGB(hsv); }

    FORCE_INLINE Int2 Int2Add(Int2 _a, Int2 _b) { return Int2::Add(_a, _b); }
    FORCE_INLINE Int2 Int2Sub(Int2 _a, Int2 _b) { return Int2::Sub(_a, _b); }
    FORCE_INLINE Int2 Int2Min(Int2 _a, Int2 _b) { return Int2::Min(_a, _b); }
    FORCE_INLINE Int2 Int2Max(Int2 _a, Int2 _b) { return Int2::Max(_a, _b); }

    FORCE_INLINE Float3 QuatMulXYZ(Quat _qa, Quat _qb) { return Quat::MulXYZ(_qa, _qb); }
    FORCE_INLINE Quat   QuatMul(Quat p, Quat q) { return Quat::Mul(p, q); }
    FORCE_INLINE Quat   QuatInverse(Quat _q) { return Quat::Conjugate(_q); }
    FORCE_INLINE float  QuatDot(Quat _a, Quat _b) { return Quat::Dot(_a, _b); }
    FORCE_INLINE float  QuatAngle(Quat _a, Quat _b) { return Quat::Angle(_a, _b); }
    FORCE_INLINE Quat   QuatNorm(Quat _q) { return Quat::Norm(_q); }
    FORCE_INLINE Quat   QuatRotateAxis(Float3 _axis, float _angle) { return Quat::RotateAxis(_axis, _angle); }
    FORCE_INLINE Quat   QuatRotateX(float _ax) { return Quat::RotateX(_ax); }
    FORCE_INLINE Quat   QuatRotateY(float _ay) { return Quat::RotateY(_ay); }
    FORCE_INLINE Quat   QuatRotateZ(float _az) { return Quat::RotateZ(_az); }
    FORCE_INLINE Quat   QuatLerp(Quat _a, Quat _b, float t) { return Quat::Lerp(_a, _b, t); }
    FORCE_INLINE Quat   QuatSlerp(Quat _a, Quat _b, float t) { return Quat::Slerp(_a, _b, t); }
    FORCE_INLINE Float3 QuatToEuler(Quat _q) { return Quat::ToEuler(_q); }
    FORCE_INLINE Quat   QuatFromEuler(Float3 _float3) { return Quat::FromEuler(_float3); }
    FORCE_INLINE Float3 QuatTransformFloat3(Float3 v, Quat q) { return Quat::TransformFloat3(v, q); }

    FORCE_INLINE Mat3   Mat3Transpose(const Mat3& _a) { return Mat3::Transpose(_a); }
    FORCE_INLINE Float3 Mat3MulFloat3(const Mat3& _mat, Float3 _vec) { return Mat3::MulFloat3(_mat, _vec); }
    FORCE_INLINE Mat3   Mat3MulInverse(const Mat3& _a, const Mat3& _b) { return Mat3::MulInverse(_a, _b); }
    FORCE_INLINE Float3 Mat3MulFloat3Inverse(const Mat3& mat, Float3 v) { return Mat3::MulFloat3Inverse(mat, v); }
    FORCE_INLINE Float2 Mat3MulFloat2(const Mat3& _mat, Float2 _vec) { return Mat3::MulFloat2(_mat, _vec); }
    FORCE_INLINE Mat3   Mat3Translate(float x, float y) { return Mat3::Translate(x, y); }
    FORCE_INLINE Mat3   Mat3TranslateFloat2(Float2 p) { return Mat3::TranslateFloat2(p); }
    FORCE_INLINE Mat3   Mat3Rotate(float theta) { return Mat3::Rotate(theta); }
    FORCE_INLINE Mat3   Mat3Scale(float sx, float sy) { return Mat3::Scale(sx, sy); }
    FORCE_INLINE Mat3   Mat3ScaleRotateTranslate(float sx, float sy, float angle, float tx, float ty) { return Mat3::ScaleRotateTranslate(sx, sy, angle, tx, ty); }
    FORCE_INLINE Mat3   Mat3Inverse(const Mat3& _a) { return Mat3::Inverse(_a); }
    FORCE_INLINE Mat3   Mat3Mul(const Mat3& _a, const Mat3& _b) { return Mat3::Mul(_a, _b); }
    FORCE_INLINE Mat3   Mat3Abs(const Mat3& m) { return Mat3::Abs(m); }
    FORCE_INLINE Mat3   Mat3FromQuat(Quat q) { return Mat3::FromQuat(q); }

    FORCE_INLINE Mat4   Mat4Translate(float _tx, float _ty, float _tz) { return Mat4::Translate(_tx, _ty, _tz); }
    FORCE_INLINE Mat4   Mat4Scale(float _sx, float _sy, float _sz) { return Mat4::Scale(_sx, _sy, _sz); }
    FORCE_INLINE Mat4   Mat4Scalef(float _scale) { return Mat4::Scale(_scale); }
    FORCE_INLINE Mat4   Mat4RotateX(float _ax) { return Mat4::RotateX(_ax); }
    FORCE_INLINE Mat4   Mat4RotateY(float _ay) { return Mat4::RotateY(_ay); }
    FORCE_INLINE Mat4   Mat4RotateZ(float _az) { return Mat4::RotateZ(_az); }
    FORCE_INLINE Mat4   Mat4RotateXY(float _ax, float _ay) { return Mat4::RotateXY(_ax, _ay); }
    FORCE_INLINE Mat4   Mat4RotateXYZ(float _ax, float _ay, float _az) { return Mat4::RotateXYZ(_ax, _ay, _az); }
    FORCE_INLINE Mat4   Mat4RotateZYX(float _ax, float _ay, float _az) { return Mat4::RotateZYX(_ax, _ay, _az); }
    FORCE_INLINE Mat4   Mat4ToQuatTranslate(Quat _quat, Float3 _translation) { return Mat4::ToQuatTranslate(_quat, _translation); }
    FORCE_INLINE Mat4   Mat4ToQuatTranslateHMD(Quat _quat, Float3 _translation) { return Mat4::ToQuatTranslateHMD(_quat, _translation); }
    FORCE_INLINE Float3 Mat4MulFloat3(const Mat4& _mat, Float3 _vec) { return Mat4::MulFloat3(_mat, _vec); }
    FORCE_INLINE Float3 Mat4MulFloat3_xyz0(const Mat4& _mat, Float3 _vec) { return Mat4::MulFloat3_xyz0(_mat, _vec); }
    FORCE_INLINE Float3 Mat4MulFloat3H(const Mat4& _mat, Float3 _vec) { return Mat4::MulFloat3H(_mat, _vec); }
    FORCE_INLINE Float4 Mat4MulFloat4(const Mat4& _mat, Float4 _vec) { return Mat4::MulFloat4(_mat, _vec); }
    FORCE_INLINE Mat4   Mat4Transpose(const Mat4& _a) { return Mat4::Transpose(_a); }
    FORCE_INLINE void   Mat4ProjFlipHandedness(Mat4* _dst, const Mat4& _src) { return Mat4::ProjFlipHandedness(_dst, _src); }
    FORCE_INLINE void   Mat4ViewFlipHandedness(Mat4* _dst, const Mat4& _src) { return Mat4::ViewFlipHandedness(_dst, _src); }
    FORCE_INLINE Mat4   Mat4FromNormal(Float3 _normal, float _scale, Float3 _pos) { return Mat4::FromNormal(_normal, _scale, _pos); }
    FORCE_INLINE Mat4   Mat4FromNormalAngle(Float3 _normal, float _scale, Float3 _pos, float _angle) { return Mat4::FromNormalAngle(_normal, _scale, _pos, _angle); }
    FORCE_INLINE Mat4   Mat4ViewLookAt(Float3 eye, Float3 target, Float3 up) { return Mat4::ViewLookAt(eye, target, up); }
    FORCE_INLINE Mat4   Mat4ViewLookAtLH(Float3 eye, Float3 target, Float3 up) { return Mat4::ViewLookAtLH(eye, target, up); }
    FORCE_INLINE Mat4   Mat4ViewFPS(Float3 eye, float pitch, float yaw) { return Mat4::ViewFPS(eye, pitch, yaw); }
    FORCE_INLINE Mat4   Mat4ViewArcBall(Float3 move, Quat rot, Float3 targetPos) { return Mat4::ViewArcBall(move, rot, targetPos); }
    FORCE_INLINE Mat4   Mat4Perspective(float width, float height, float zn, float zf, bool d3dNdc = false) { return Mat4::Perspective(width, height, zn, zf, d3dNdc); }
    FORCE_INLINE Mat4   Mat4PerspectiveLH(float width, float height, float zn, float zf, bool d3dNdc = false) { return Mat4::PerspectiveLH(width, height, zn, zf, d3dNdc); }
    FORCE_INLINE Mat4   Mat4PerspectiveOffCenter(float xmin, float ymin, float xmax, float ymax,
                                                 float zn, float zf, bool d3dNdc = false) { return Mat4::PerspectiveOffCenter(xmin, ymin, xmax, ymax, zn, zf, d3dNdc); }
    FORCE_INLINE Mat4   Mat4PerspectiveOffCenterLH(float xmin, float ymin, float xmax, float ymax,
                                                   float zn, float zf, bool d3dNdc = false) { return Mat4::PerspectiveOffCenterLH(xmin, ymin, xmax, ymax, zn, zf, d3dNdc); }
    FORCE_INLINE Mat4   Mat4PerspectiveFOV(float fov_y, float aspect, float zn, float zf, bool d3dNdc = false) { return Mat4::PerspectiveFOV(fov_y, aspect, zn, zf, d3dNdc); }
    FORCE_INLINE Mat4   Mat4PerspectiveFOVLH(float fov_y, float aspect, float zn, float zf, bool d3dNdc = false) { return Mat4::PerspectiveFOVLH(fov_y, aspect, zn, zf, d3dNdc); }
    FORCE_INLINE Mat4   Mat4Ortho(float width, float height, float zn, float zf, float offset = 0, bool d3dNdc = false) { return Mat4::Ortho(width, height, zn, zf, offset, d3dNdc); }
    FORCE_INLINE Mat4   Mat4OrthoLH(float width, float height, float zn, float zf, float offset = 0, bool d3dNdc = false) { return Mat4::OrthoLH(width, height, zn, zf, offset, d3dNdc); }
    FORCE_INLINE Mat4   Mat4OrthoOffCenter(float xmin, float ymin, float xmax, float ymax, float zn,
                                           float zf, float offset = 0, bool d3dNdc = false) { return Mat4::OrthoOffCenter(xmin, ymin, xmax, ymax, zn, zf, offset, d3dNdc); }
    FORCE_INLINE Mat4   Mat4OrthoOffCenterLH(float xmin, float ymin, float xmax, float ymax, float zn,
                                             float zf, float offset = 0, bool d3dNdc = false) { return Mat4::OrthoOffCenterLH(xmin, ymin, xmax, ymax, zn, zf, offset, d3dNdc); }
    FORCE_INLINE Mat4   Mat4ScaleRotateTranslate(float _sx, float _sy, float _sz, 
                                                 float _ax, float _ay, float _az,
                                                 float _tx, float _ty, float _tz) { return Mat4::TransformMat(_sx, _sy, _sz, _ax, _ay, _az, _tx, _ty, _tz); }
    FORCE_INLINE Mat4   Mat4Mul(const Mat4& _a, const Mat4& _b) { return Mat4::Mul(_a, _b); }
    FORCE_INLINE Mat4   Mat4Inverse(const Mat4& _a) { return Mat4::Inverse(_a); }
    FORCE_INLINE Mat4   Mat4InverseTransformMat(const Mat4& _a) { return Mat4::InverseTransformMat(_a); }
    FORCE_INLINE Quat   Mat4ToQuat(const Mat4& _mat) { return Mat4::ToQuat(_mat); }
    FORCE_INLINE Mat4   Mat4FromQuat(Quat q) { return Mat4::FromQuat(q); }
    FORCE_INLINE Mat4   Mat4ProjectPlane(Float3 planeNormal) { return Mat4::ProjectPlane(planeNormal); }

    FORCE_INLINE RectFloat   RectCenterExtents(Float2 center, Float2 extents) { return RectFloat::CenterExtents(center, extents); }
    FORCE_INLINE RectFloat   RectExpand(const RectFloat rc, Float2 expand) { return RectFloat::Expand(rc, expand); }
    FORCE_INLINE bool   RectTestPoint(const RectFloat rc, Float2 pt) { return RectFloat::TestPoint(rc, pt); }
    FORCE_INLINE bool   RectTest(const RectFloat rc1, const RectFloat rc2) { return RectFloat::Test(rc1, rc2); }
    FORCE_INLINE void   RectAddPoint(RectFloat& rc, Float2 pt) { RectFloat::AddPoint(rc, pt); }
    FORCE_INLINE Float2 RectGetCorner(const RectFloat* rc, int index) { return RectFloat::GetCorner(rc, index); }
    FORCE_INLINE void   RectGetCorners(const RectFloat* rc, Float2 corners[4]) { RectFloat::GetCorners(rc, corners); }
    FORCE_INLINE Float2 RectExtents(const RectFloat rc) { return RectFloat::Extents(rc); }
    FORCE_INLINE Float2 RectCenter(const RectFloat rc) { return RectFloat::Center(rc); }
    FORCE_INLINE RectFloat   RectTranslate(const RectFloat rc, Float2 pos) { return RectFloat::Translate(rc, pos); }

    FORCE_INLINE RectInt  RectIntExpand(const RectInt rc, Int2 expand) { return RectInt::Expand(rc, expand); }
    FORCE_INLINE bool     RectIntTestPoint(const RectInt rc, Int2 pt) { return RectInt::TestPoint(rc, pt); }
    FORCE_INLINE bool     RectIntTest(const RectInt rc1, const RectInt rc2) { return RectInt::Test(rc1, rc2); }
    FORCE_INLINE void     RectIntAddPoint(RectInt& rc, Int2 pt) { return RectInt::AddPoint(rc, pt); }
    FORCE_INLINE Int2     RectIntGetCorner(const RectInt* rc, int index) { return RectInt::GetCorner(rc, index); }
    FORCE_INLINE void     RectIntGetCorners(const RectInt* rc, Int2 corners[4]) { return RectInt::GetCorners(rc, corners); }

    FORCE_INLINE AABB   AABBCenterExtents(Float3 center, Float3 extents) { return AABB::CenterExtents(center, extents); }
    FORCE_INLINE void   AABBAddPoint(AABB& aabb, Float3 pt) { return AABB::AddPoint(aabb, pt); }
    FORCE_INLINE AABB   AABBUnify(const AABB& aabb1, const AABB& aabb2) { return AABB::Unify(aabb1, aabb2); }
    FORCE_INLINE bool   AABBTestPoint(const AABB& aabb, Float3 pt) { return AABB::TestPoint(aabb, pt); }
    FORCE_INLINE bool   AABBTest(const AABB& aabb1, const AABB& aabb2) { return AABB::Test(aabb1, aabb2); }
    FORCE_INLINE Float3 AABBGetCorner(const AABB& aabb, int index) { return AABB::GetCorner(aabb, index); }
    FORCE_INLINE void   AABBGetCorners(const AABB& aabb, Float3 corners[8]) { return AABB::GetCorners(aabb, corners); }
    FORCE_INLINE AABB   AABBTranslate(const AABB& aabb, Float3 offset) { return AABB::Translate(aabb, offset); }
    FORCE_INLINE AABB   AABBSetPos(const AABB& aabb, Float3 pos) { return AABB::SetPos(aabb, pos); }
    FORCE_INLINE AABB   AABBExpand(const AABB& aabb, Float3 expand) { return AABB::Expand(aabb, expand); }
    FORCE_INLINE AABB   AABBScale(const AABB& aabb, Float3 scale) { return AABB::Scale(aabb, scale); }
    FORCE_INLINE AABB   AABBTransform(const AABB& aabb, const Mat4& mat) { return AABB::Transform(aabb, mat); }

    FORCE_INLINE Float3 PlaneCalcNormal(Float3 _va, Float3 _vb, Float3 _vc) { return Plane::CalcNormal(_va, _vb, _vc); }
    FORCE_INLINE Plane  PlaneFrom3Points(Float3 _va, Float3 _vb, Float3 _vc) { return Plane::From3Points(_va, _vb, _vc); }
    FORCE_INLINE Plane  PlaneFromNormalPoint(Float3 _normal, Float3 _p) { return Plane::FromNormalPoint(_normal, _p); }
    FORCE_INLINE float  PlaneDistance(Plane _plane, Float3 _p) { return Plane::Distance(_plane, _p); }
    FORCE_INLINE Float3 PlaneProjectPoint(Plane _plane, Float3 _p) { return Plane::ProjectPoint(_plane, _p); }
    FORCE_INLINE Float3 PlaneOrigin(Plane _plane) { return Plane::ClosestPointToOrigin(_plane); }
}




namespace _private 
{
    static inline constexpr uint32 HANDLE_GEN_BITS = 14;
    static inline constexpr uint32 HANDLE_INDEX_MAX = (1 << (32 - HANDLE_GEN_BITS)) - 1;
    static inline constexpr uint32 HANDLE_GEN_MASK = (1 << HANDLE_GEN_BITS) - 1;
    static inline constexpr uint32 HANDLE_GEN_SHIFT  = 32 - HANDLE_GEN_BITS;

    struct alignas(16) HandlePoolTable
    {
        uint32  count;
        uint32  capacity;
        uint32* dense;          // actual handles are stored in 'dense' array [0..arrayCount]
        uint32* sparse;         // indices to dense for removal lookup [0..arrayCapacity]
        uint8   padding[sizeof(void*)];
    };

    API HandlePoolTable* handleCreatePoolTable(uint32 capacity, MemAllocator* alloc);
    API void handleDestroyPoolTable(HandlePoolTable* tbl, MemAllocator* alloc);
    API bool handleGrowPoolTable(HandlePoolTable** pTbl, MemAllocator* alloc);
    API HandlePoolTable* handleClone(HandlePoolTable* tbl, MemAllocator* alloc);

    API uint32 handleNew(HandlePoolTable* tbl);
    API void   handleDel(HandlePoolTable* tbl, uint32 handle);
    API void   handleResetPoolTable(HandlePoolTable* tbl);
    API bool   handleIsValid(const HandlePoolTable* tbl, uint32 handle);
    API uint32 handleAt(const HandlePoolTable* tbl, uint32 index);
    API bool   handleFull(const HandlePoolTable* tbl);

    API size_t handleGetMemoryRequirement(uint32 capacity);
    API HandlePoolTable* handleCreatePoolTableWithBuffer(uint32 capacity, void* buff, size_t size);
    API bool handleGrowPoolTableWithBuffer(HandlePoolTable** pTbl, void* buff, size_t size);
} // _private

#ifndef __OBJC__
template <typename _T>
struct Handle
{
    Handle() = default;
    Handle(const Handle<_T>&) = default;
    explicit Handle(uint32 _id) : mId(_id) {}
    Handle<_T>& operator=(const Handle<_T>&) = default;

    void Set(uint32 gen, uint32 index) { mId = ((gen & _private::HANDLE_GEN_MASK)<<_private::HANDLE_GEN_SHIFT) | (index&_private::HANDLE_INDEX_MAX); }
    explicit operator uint32() const { return mId; }
    uint32 GetSparseIndex() { return mId & _private::HANDLE_INDEX_MAX; }
    uint32 GetGen() { return (mId >> _private::HANDLE_GEN_SHIFT) & _private::HANDLE_GEN_MASK; }
    bool IsValid() const { return mId != 0; }
    bool operator==(const Handle<_T>& v) const { return mId == v.mId; }
    bool operator!=(const Handle<_T>& v) const { return mId != v.mId; }

    uint32 mId = 0;
};

#define DEFINE_HANDLE(_Name) struct _Name##T; using _Name = Handle<_Name##T>

template <typename _HandleType, typename _DataType>
struct HandlePool
{
    HandlePool() : HandlePool(Mem::GetDefaultAlloc()) {}
    explicit HandlePool(MemAllocator* alloc) : mAlloc(alloc), mItems(alloc) {}
    explicit HandlePool(void* data, size_t size); 

    void CopyTo(HandlePool<_HandleType, _DataType>* otherPool) const;

    [[nodiscard]] _HandleType Add(const _DataType& item, _DataType* prevItem = nullptr);
    void Remove(_HandleType handle);
    uint32 Count() const;
    void Clear();
    bool IsValid(_HandleType handle);
    _HandleType HandleAt(uint32 index);
    _DataType& Data(uint32 index);
    _DataType& Data(_HandleType handle);
    bool IsFull() const;
    uint32 Capacity() const;

    void Reserve(uint32 capacity, void* buffer, size_t size);
    void SetAllocator(MemAllocator* alloc);
    void Free();

    static size_t GetMemoryRequirement(uint32 capacity);
    bool Grow();
    bool Grow(void* data, size_t size);

    template <typename _Func> _HandleType FindIf(_Func findFunc);

    struct Iterator 
    {
        using HandlePool_t = HandlePool<_HandleType, _DataType>;

        Iterator(HandlePool_t* pool, uint32 index) : _pool(pool), mIndex(index) {}
        _DataType& operator*() { return _pool->Data(mIndex); }
        void operator++() { ++mIndex; }
        bool operator!=(Iterator it) { return mIndex != it.mIndex; }
        HandlePool_t* _pool;
        uint32 mIndex;
    };
    
    Iterator begin()    { return Iterator(this, 0); }
    Iterator end()      { return Iterator(this, mHandles ? mHandles->count : 0); }

private:
    MemAllocator* mAlloc = nullptr;
    _private::HandlePoolTable* mHandles = nullptr;
    Array<_DataType>  mItems;
};

#endif  // !__OBJC__


template <typename _T, uint32 _Align = CONFIG_MACHINE_ALIGNMENT>
struct FixedSizePool
{
    FixedSizePool() : FixedSizePool(Mem::GetDefaultAlloc()) {}
    explicit FixedSizePool(MemAllocator* alloc) : mAlloc(alloc) {}
    explicit FixedSizePool(void* buffer, size_t size);
    
    void SetAllocator(MemAllocator* alloc);
    void Reserve(uint32 pageSize);
    void Reserve(void* buffer, size_t size, uint32 pageSize);
    void Free();
    static size_t GetMemoryRequirement(uint32 pageSize);

    _T* New();
    void Delete(_T* item);
    bool IsFull() const;

private:
    struct Page
    {
        _T**    ptrs;
        _T*     data;
        Page*   next;
        uint32  index;
    };

    Page* CreatePage(void* buffer, size_t size);

public:
    struct Iterator 
    {
        Iterator(Page* page, uint32 index, uint32 pageSize) : mPage(page), mIndex(index), mPageSize(pageSize) {}
        _T& operator*() { return mPage->data[mIndex]; }
        void operator++() 
        { 
            ASSERT(mPage); 
            if (mIndex < mPageSize) 
            mIndex++; 
            else { 
                mPage = mPage->next; 
                mIndex = 0; 
            } 
        }
        bool operator!=(Iterator it) { return mPage != it.mPage || mIndex != it.mIndex; }

        Page* mPage;
        uint32 mIndex;
        uint32 mPageSize;
    };

    Iterator begin()    { return Iterator(mPages, 0, mPageSize); }
    Iterator end()      
    { 
        Page* page = mPages;
        while (page && page->index == 0 && page->next)
            page = page->next;

        return Iterator(page, 0, mPageSize); 
    }

    Iterator begin() const    { return Iterator(mPages, 0, mPageSize); }
    Iterator end() const     
    { 
        Page* page = mPages;
        while (page && page->index == 0 && page->next)
            page = page->next;

        return Iterator(page, 0, mPageSize); 
    }

private:
    MemAllocator*  mAlloc = nullptr;
    uint32      mPageSize = 32;      // maximum number of items that a page can hold
    Page*       mPages = nullptr;
};



#ifndef __OBJC__
template<typename _HandleType, typename _DataType>
void HandlePool<_HandleType, _DataType>::Reserve(uint32 capacity, void* buffer, size_t size)
{
    capacity = Max(capacity, 32u);
    ASSERT_MSG(mHandles == nullptr, "pool should be freed/uninitialized before reserve by pointer");
    mAlloc = nullptr;

    size_t tableSize = _private::handleGetMemoryRequirement(capacity);
    ASSERT(tableSize <= size);
    mHandles = _private::handleCreatePoolTableWithBuffer(capacity, buffer, tableSize);

    void* arrayBuffer = reinterpret_cast<uint8*>(buffer) + tableSize;
    ASSERT(reinterpret_cast<uintptr_t>(arrayBuffer)%CONFIG_MACHINE_ALIGNMENT == 0);
    mItems.Reserve(capacity, arrayBuffer, size - tableSize);
}

template<typename _HandleType, typename _DataType>
void HandlePool<_HandleType, _DataType>::SetAllocator(MemAllocator* alloc)
{
    ASSERT_MSG(mHandles == nullptr, "pool should be freed/uninitialized before setting allocator");
    mAlloc = alloc;
    mItems.SetAllocator(mAlloc);
}

template <typename _HandleType, typename _DataType>
void HandlePool<_HandleType, _DataType>::CopyTo(HandlePool<_HandleType, _DataType>* otherPool) const
{
    ASSERT_MSG(otherPool->mHandles == nullptr, "other pool should be uninitialized before cloning");
    otherPool->mHandles = _private::handleClone(mHandles, otherPool->mAlloc);
    mItems.CopyTo(&otherPool->mItems);
}

template<typename _HandleType, typename _DataType>
inline _HandleType HandlePool<_HandleType, _DataType>::Add(const _DataType& item, _DataType* prevItem)
{
    if (mHandles == nullptr) {
        ASSERT(mAlloc);
        mHandles = _private::handleCreatePoolTable(32u, mAlloc);
        mItems.Reserve(32u);
    } 
    else if (mHandles->count == mHandles->capacity) {
        if (mAlloc) {
            Grow();
        }
        else {
            ASSERT_MSG(0, "HandlePool overflow, capacity=%u", mHandles->capacity);
        }
    }

    _HandleType handle(_private::handleNew(mHandles));
    uint32 index = handle.GetSparseIndex();
    if (index >= mItems.Count()) {
        mItems.Push(item);
        if (prevItem)
            *prevItem = _DataType {};
    }
    else {
        if (prevItem) 
            *prevItem = mItems[index];
        mItems[index] = item;
    }

    return handle;
}

template<typename _HandleType, typename _DataType>
inline void HandlePool<_HandleType, _DataType>::Remove(_HandleType handle)
{
    ASSERT(mHandles);
    _private::handleDel(mHandles, static_cast<uint32>(handle));
}

template<typename _HandleType, typename _DataType>
inline uint32 HandlePool<_HandleType, _DataType>::Count() const
{
    return mHandles ? mHandles->count : 0;
}

template<typename _HandleType, typename _DataType>
inline void HandlePool<_HandleType, _DataType>::Clear()
{
    if (mHandles)
    _private::handleResetPoolTable(mHandles);
}

template<typename _HandleType, typename _DataType>
inline bool HandlePool<_HandleType, _DataType>::IsValid(_HandleType handle)
{
    ASSERT(mHandles);
    return _private::handleIsValid(mHandles, static_cast<uint32>(handle));
}

template<typename _HandleType, typename _DataType>
inline _HandleType HandlePool<_HandleType, _DataType>::HandleAt(uint32 index)
{
    ASSERT(mHandles);
    return _HandleType(_private::handleAt(mHandles, index));
}

template<typename _HandleType, typename _DataType>
inline _DataType& HandlePool<_HandleType, _DataType>::Data(uint32 index)
{
    _HandleType handle = HandleAt(index);
    return mItems[handle.GetSparseIndex()];
}

template<typename _HandleType, typename _DataType>
inline _DataType& HandlePool<_HandleType, _DataType>::Data(_HandleType handle)
{
    ASSERT(mHandles);
    ASSERT_MSG(IsValid(handle), "Invalid handle (%u): Generation=%u, SparseIndex=%u", 
               uint32(handle), handle.GetGen(), handle.GetSparseIndex());
    return mItems[handle.GetSparseIndex()];
}

template<typename _HandleType, typename _DataType>
inline void HandlePool<_HandleType, _DataType>::Free()
{
    if (mAlloc) {
        if (mHandles) 
            _private::handleDestroyPoolTable(mHandles, mAlloc);
        mItems.Free();
        mHandles = nullptr;
    }
}

template<typename _HandleType, typename _DataType>
template<typename _Func> inline _HandleType HandlePool<_HandleType, _DataType>::FindIf(_Func findFunc)
{
    if (mHandles) {
        for (uint32 i = 0, c = mHandles->count; i < c; i++) {
            _HandleType h = _HandleType(_private::handleAt(mHandles, i));
            if (findFunc(mItems[h.GetSparseIndex()]))
            return h;
        }
    }
    
    return _HandleType();
}

template<typename _HandleType, typename _DataType>
inline bool HandlePool<_HandleType, _DataType>::IsFull() const
{
    return !mHandles && mHandles->count == mHandles->capacity;
}

template<typename _HandleType, typename _DataType>
inline uint32 HandlePool<_HandleType, _DataType>::Capacity() const
{
    return mHandles ? mHandles->capacity : 32u;
}

template<typename _HandleType, typename _DataType>
inline size_t HandlePool<_HandleType, _DataType>::GetMemoryRequirement(uint32 capacity)
{
    return _private::handleGetMemoryRequirement(capacity) + Array<_DataType>::GetMemoryRequirement(capacity);
}

template<typename _HandleType, typename _DataType>
inline bool HandlePool<_HandleType, _DataType>::Grow()
{
    ASSERT(mAlloc);
    ASSERT(mHandles);
       
    mItems.Reserve(mHandles->capacity << 1);
    return _private::handleGrowPoolTable(&mHandles, mAlloc);
}

template<typename _HandleType, typename _DataType>
inline bool HandlePool<_HandleType, _DataType>::Grow(void* data, size_t size)
{
    ASSERT(!mAlloc);
    ASSERT(mHandles);

    uint32 newCapacity = mHandles->capacity << 1;
    size_t handleTableSize = GetMemoryRequirement(newCapacity);
    ASSERT(handleTableSize < size);

    mItems.Reserve(mHandles->capacity << 1, (uint8*)data + handleTableSize, size - handleTableSize);
    return _private::handleGrowPoolTableWithBuffer(&mHandles, data, handleTableSize);
}
#endif // !__OBJC__

template <typename _T, uint32 _Align>
inline FixedSizePool<_T, _Align>::FixedSizePool(void* buffer, size_t size)
{
    ASSERT(buffer);
    ASSERT(size > sizeof(Page));

    mPageSize = (size - sizeof(Page))/sizeof(_T);
    ASSERT_MSG(mPageSize, "Buffer size is too small");
    mPages = CreatePage(buffer, size);
}

template <typename _T, uint32 _Align>
inline void FixedSizePool<_T, _Align>::SetAllocator(MemAllocator* alloc)
{
    ASSERT_MSG(!mPages, "SetAllocator must be called before using/initializing the Blob");
    mAlloc = alloc;
}

template <typename _T, uint32 _Align>
inline void FixedSizePool<_T, _Align>::Reserve(uint32 pageSize)
{
    ASSERT(mAlloc);
    ASSERT(pageSize);

    mPageSize = pageSize;
    mPages = CreatePage(nullptr, 0);
}

template <typename _T, uint32 _Align>
inline void FixedSizePool<_T, _Align>::Reserve(void* buffer, size_t size, uint32 pageSize)
{
    ASSERT(buffer);
    ASSERT(size > sizeof(Page));
    ASSERT(mPages == nullptr);
    ASSERT(pageSize);
    
    mPageSize = pageSize;
    mAlloc = nullptr;
    mPages = CreatePage(buffer, size);
}

template <typename _T, uint32 _Align>
inline void FixedSizePool<_T, _Align>::Free()
{
    if (mAlloc) {
        Page* page = mPages;
        while (page) {
            Page* next = page->next; 
            if (mAlloc)
                MemSingleShotMalloc<Page>::Free(page, mAlloc);
            page = next;
        }
    }

    mPageSize = 0;
    mPages = nullptr;
}

template <typename _T, uint32 _Align>
inline size_t FixedSizePool<_T, _Align>::GetMemoryRequirement(uint32 pageSize)
{
    MemSingleShotMalloc<Page> pageBuffer;
    pageBuffer.template AddMemberArray<_T*>(offsetof(Page, ptrs), pageSize);
    pageBuffer.template AddMemberArray<_T>(offsetof(Page, data), pageSize, false, _Align);
    return pageBuffer.GetMemoryRequirement();
}

template <typename _T, uint32 _Align>
inline _T* FixedSizePool<_T, _Align>::New()
{
    Page* page = mPages;
    while (page && page->index == 0 && page->next)
        page = page->next;
    
    if (!page || page->index == 0) {
        if (!mAlloc) {
            ASSERT_MSG(0, "Cannot allocate anymore new objects. Pool is full");
            return nullptr;
        }

        page = CreatePage(nullptr, 0);
        if (mPages) {
            Page* lastPage = mPages;
            while (lastPage->next)
                lastPage = lastPage->next;
            lastPage->next = page;
        }
        else {
            mPages = page;
        }
    }

    ASSERT(page->index);
    return page->ptrs[--page->index];
}

template <typename _T, uint32 _Align>
inline void FixedSizePool<_T, _Align>::Delete(_T* item)
{
    uint64 uptr = PtrToInt<uint64>(item);
    Page* page = mPages;
    uint32 pageSize = mPageSize;

    while (page) {
        if (uptr >= PtrToInt<uint64>(page->data) && uptr < PtrToInt<uint64>(page->data + pageSize)) {
            ASSERT_MSG(page->index != pageSize, "Cannot delete more objects from this page, possible double delete");

            page->ptrs[page->index++] = item;
            return;
        }

        page = page->next;
    }

    ASSERT_MSG(0, "Pointer doesn't belong to this pool");
}

template <typename _T, uint32 _Align>
inline bool FixedSizePool<_T, _Align>::IsFull() const
{
    Page* page = mPages;
    while (page && page->index == 0 && page->next)
        page = page->next;
    
    return !page || page->index == 0;
}

template <typename _T, uint32 _Align>
inline typename FixedSizePool<_T, _Align>::Page* FixedSizePool<_T, _Align>::CreatePage(void* buffer, size_t size)
{
    ASSERT(mPageSize);

    MemSingleShotMalloc<Page> mallocator;
    mallocator.template AddMemberArray<_T*>(offsetof(Page, ptrs), mPageSize);
    mallocator.template AddMemberArray<_T>(offsetof(Page, data), mPageSize, false, _Align); // Only align data buffer

    Page* page = (buffer && size) ? mallocator.Calloc(buffer, size) : page = mallocator.Calloc(mAlloc);
    page->index = mPageSize;
    for (uint32 i = 0, c = mPageSize; i < c; i++)
        page->ptrs[c - i - 1] = page->data + i;
    return page;
}



template <typename _T> struct Array;
typedef struct AAssetManager AAssetManager;

struct SettingsKeyValue
{
    String32 key;
    String<CONFIG_MAX_PATH> value;
};

struct NO_VTABLE SettingsCustomCallbacks
{
    virtual uint32 GetCategoryCount() const = 0;
    virtual const char* GetCategory(uint32 id) const = 0;
    virtual bool ParseSetting(uint32 categoryId, const char* key, const char* value) = 0;

    virtual void SaveCategory(uint32 categoryId, Array<SettingsKeyValue>& items) = 0;   
};

namespace Settings
{
    API void AddCustomCallbacks(SettingsCustomCallbacks* callbacks);
    API void RemoveCustomCallbacks(SettingsCustomCallbacks* callbacks);

    API bool InitializeFromINI(const char* iniFilepath);
    API bool InitializeFromCommandLine(int argc, char* argv[]);

    #if PLATFORM_ANDROID
    API bool InitializeFromAndroidAsset(AAssetManager* assetMgr, const char* iniFilepath);
    #endif

    API void SaveToINI(const char* iniFilepath);
    API void Release();

    API void SetValue(const char* key, const char* value);
    API const char* GetValue(const char* key, const char* defaultValue = "");
}




enum class ThreadCreateFlags : uint32
{
    None = 0,
    Detached = 0x1
};
ENABLE_BITMASK(ThreadCreateFlags);

enum class ThreadPriority 
{
    Normal = 0,
    Idle,
    Realtime,
    High,
    Low
};

using ThreadEntryFunc = int(*)(void* userData);

struct ThreadDesc
{
    ThreadEntryFunc entryFn;
    void* userData;
    const char* name;
    size_t stackSize = SIZE_MB;
    ThreadCreateFlags flags = ThreadCreateFlags::None;
    ThreadPriority priority = ThreadPriority::Normal;
};

struct alignas(64) Thread
{
    Thread();

    bool Start(const ThreadDesc& desc);
    int  Stop();
    bool IsRunning();
    void SetPriority(ThreadPriority prio);

    static void SwitchContext();
    static uint32 GetCurrentId();
    static void SetCurrentThreadPriority(ThreadPriority prio);
    static void SetCurrentThreadName(const char* name);
    static void GetCurrentThreadName(char* nameOut, uint32 nameSize);
    static void Sleep(uint32 msecs);

private:
    uint8 mData[256];
};


struct Mutex
{
    void Initialize(uint32 spinCount = 32);
    void Release();

    void Enter();
    void Exit();
    bool TryEnter();

private:
    uint8 mData[64];
};

struct MutexScope
{
    MutexScope( ) = delete;
    MutexScope(const MutexScope& mtx) = delete;
    explicit MutexScope(Mutex& mtx) : mMtx(mtx) { mMtx.Enter(); }
    ~MutexScope( ) { mMtx.Exit(); }

private:
    Mutex& mMtx;
};


struct alignas(CACHE_LINE_SIZE) ReadWriteMutex
{
    void Initialize();
    void Release();

    bool TryRead();
    bool TryWrite();

    void EnterRead();
    void ExitRead();

    void EnterWrite();
    void ExitWrite();

private:
    #if !PLATFORM_APPLE
    uint8 mData[64];
    #else
    uint8 mData[256];
    #endif
};

struct ReadWriteMutexReadScope
{
    ReadWriteMutexReadScope() = delete;
    ReadWriteMutexReadScope(const ReadWriteMutexReadScope&) = delete;
    explicit ReadWriteMutexReadScope(ReadWriteMutex& mtx) : mMtx(mtx) { mMtx.EnterRead(); }
    ~ReadWriteMutexReadScope() { mMtx.ExitRead(); }

private:
    ReadWriteMutex& mMtx;
};

struct ReadWriteMutexWriteScope
{
    ReadWriteMutexWriteScope() = delete;
    ReadWriteMutexWriteScope(const ReadWriteMutexWriteScope&) = delete;
    explicit ReadWriteMutexWriteScope(ReadWriteMutex& mtx) : mMtx(mtx) { mMtx.EnterWrite(); }
    ~ReadWriteMutexWriteScope() { mMtx.ExitWrite(); }

private:
    ReadWriteMutex& mMtx;
};


struct alignas(CACHE_LINE_SIZE) SpinLockMutex
{
    void Enter();
    void Exit();
    bool TryEnter();

private:
    uint32 mLocked = 0;
    [[maybe_unused]] uint8 _padding[CACHE_LINE_SIZE - sizeof(uint32)];
};

struct SpinLockMutexScope
{
    SpinLockMutexScope() = delete;
    SpinLockMutexScope(const SpinLockMutexScope&) = delete;
    inline explicit SpinLockMutexScope(SpinLockMutex& lock) : mLock(lock) { mLock.Enter(); }
    inline ~SpinLockMutexScope() { mLock.Exit(); }
        
private:
    SpinLockMutex& mLock;
};


struct alignas(16) Semaphore
{
    void Initialize();
    void Release();

    void Post(uint32 count = 1);
    bool Wait(uint32 msecs = UINT32_MAX);

private:
    uint8 mData[128];
};


struct alignas(16) Signal
{
    void Initialize();
    void Release();

    void Raise();
    void RaiseAll();
    bool Wait(uint32 msecs = UINT32_MAX);
    void Decrement(uint32 count = 1);
    void Increment(uint32 count = 1);
    bool WaitOnCondition(bool(*condFn)(int value, int reference), int reference = 0, uint32 msecs = UINT32_MAX);
    void Set(int value = 1);

private:
    uint8 mData[128];
};



namespace Timer
{
    API void Initialize();
    API uint64 GetTicks();
    API uint64 LapTime(uint64* lastTime);
    INLINE uint64 Diff(uint64 newTick, uint64 oldTick);
    INLINE double ToSec(uint64 tick);
    INLINE double ToMS(uint64 tick);
    INLINE double ToUS(uint64 tick);
}

struct TimerStopWatch
{
    TimerStopWatch();

    void Reset();

    uint64 Elapsed() const;
    double ElapsedSec() const;
    double ElapsedMS() const;
    double ElapsedUS() const;

private:
    uint64 mStart;
};


enum class MemVirtualFlags : uint32
{
    None = 0,
    Watch = 0x1
};
ENABLE_BITMASK(MemVirtualFlags);

struct MemVirtualStats
{
    uint64 commitedBytes;
    uint64 reservedBytes;
};

namespace Mem
{
    API void* VirtualReserve(size_t size, MemVirtualFlags flags = MemVirtualFlags::None);
    API void* VirtualCommit(void* ptr, size_t size);
    API void VirtualDecommit(void* ptr, size_t size);
    API void VirtualRelease(void* ptr, size_t size);
    API MemVirtualStats VirtualGetStats();
    API bool VirtualEnableLargePages(size_t* largePageSize);
}

enum class PathType : uint32
{
    Invalid = 0,
    File,
    Directory
};

struct PathInfo
{
    PathType type;
    uint64 size;
    uint64 lastModified;
};

namespace PathUtils
{
    API char* ToUnix(const char* path, char* dst, size_t dstSize);
    API char* ToWin(const char* path, char* dst, size_t dstSize);
    API char* GetFileExtension(const char* path, char* dst, size_t dstSize);
    API char* GetFilenameAndExtension(const char* path, char* dst, size_t dstSize);
    API char* GetFilename(const char* path, char* dst, size_t dstSize);
    API char* GetDirectory(const char* path, char* dst, size_t dstSize);
    API char* Join(char* dst, size_t dstSize, const char* pathA, const char* pathB);
    API char* JoinUnixStyle(char* dst, size_t dstSize, const char* pathA, const char* pathB);
}

struct Path : String<PATH_CHARS_MAX>
{
    Path() = default;
    Path(const char* cstr) : String<PATH_CHARS_MAX>(cstr) {}
    Path(const String<PATH_CHARS_MAX>& str) : String<PATH_CHARS_MAX>(str) {}

    Path& SetToCurrentDir();

    Path& ConvertToUnix();
    Path& ConvertToWin();
    Path& ConvertToAbsolute();

    Path GetAbsolute() const;
    Path GetFileExtension() const;
    Path GetFileNameAndExt() const;
    Path GetFileName() const;
    Path GetDirectory() const;

    inline PathInfo Stat() const;
    inline bool Exists() const;
    inline bool IsFile() const;
    inline bool IsDir() const;

    Path& Join(const Path& path);
    Path& JoinUnix(const Path& path);

    static Path Join(const Path& pathA, const Path& pathB);
    static Path JoinUnix(const Path& pathA, const Path& pathB);
};

enum class FileOpenFlags : uint32
{
    None         = 0,
    Read         = 0x01, // Open for reading
    Write        = 0x02, // Open for writing
    Append       = 0x03, // Append to the end of the file (write-mode only)
    NoCache      = 0x08, // Disable IO cache, suitable for very large files, remember to align buffers to virtual memory pages
    Writethrough = 0x10, // Write-through writes meta information to disk immediately
    SeqScan      = 0x20, // Optimize cache for sequential read (not to be used with NOCACHE)
    RandomAccess = 0x40, // Optimize cache for random access read (not to be used with NOCACHE)
    Temp         = 0x80, // Indicate that the file is temperary
};
ENABLE_BITMASK(FileOpenFlags);

enum class FileSeekMode
{
    Start = 0,
    Current,
    End 
};

struct File
{
    File();

    bool Open(const char* filepath, FileOpenFlags flags);
    void Close();

    size_t Read(void* dst, size_t size);
    size_t Write(const void* src, size_t size);
    size_t Seek(size_t offset, FileSeekMode mode = FileSeekMode::Start);

    template <typename _T> uint32 Read(_T* dst, uint32 count);
    template <typename _T> uint32 Write(const _T* dst, uint32 count);

    size_t GetSize() const;
    uint64 GetLastModified() const;
    bool IsOpen() const;

private:
    uint8 mData[64];
};

struct AsyncFile
{
    void* data;
    void* userData;
    uint64 lastModifiedTime;
    uint32 size;
    Path filepath;
};

using AsyncFileCallback = void(*)(AsyncFile* file, bool failed);

struct AsyncFileRequest
{
    MemAllocator* alloc = Mem::GetDefaultAlloc();// Allocator to allocate a continous chunk of file data 
    AsyncFileCallback readFn = nullptr;  // Callback to receive async results. see 'AsyncFileCallback'. If this value is null, then you should use Wait and IsFinished to poll for data
    void* userData = nullptr;            // user-data. Can be allocated by async functions internally as well. See 'userDataAllocatedSize'
    uint32 userDataAllocateSize = 0;     // allocate user-data for this request and copy over the provdided userData instead of using userData pointer directly
    uint32 sizeHint = 0;                 // If you provide a size hint, then file info will not be queried and AsyncRead will allocate this size instead
};

namespace Async
{
    API bool Initialize();
    API void Release();

    API AsyncFile* ReadFile(const char* filepath, const AsyncFileRequest& request = AsyncFileRequest());
    API void Close(AsyncFile* file);
    API bool Wait(AsyncFile* file);
    API bool IsFinished(AsyncFile* file, bool* outError = nullptr);
};

struct SocketErrorCode 
{
    enum Enum
    {
        None = 0,
        AddressInUse,
        AddressNotAvailable,
        AddressUnsupported,
        AlreadyConnected,
        ConnectionRefused,
        Timeout,
        HostUnreachable,
        ConnectionReset,
        SocketShutdown,
        MessageTooLarge,
        NotConnected,
        Unknown
    };

    static const char* ToStr(Enum code)
    {
        switch (code) {
        case AddressInUse:         return "AddressInUse";
        case AddressNotAvailable:  return "AddressNotAvailable";
        case AddressUnsupported:   return "AddressUnsupported";
        case AlreadyConnected:     return "AlreadyConnected";
        case ConnectionRefused:    return "ConnectionRefused";        
        case Timeout:              return "Timeout";
        case HostUnreachable:      return "HostUnreachable";
        case ConnectionReset:      return "ConnectionReset";
        case SocketShutdown:       return "SocketShutdown";
        case MessageTooLarge:      return "MessageTooLarge";
        case NotConnected:         return "NotConnected";
        default:                   return "Unknown";
        }
    }
};

#if PLATFORM_WINDOWS
using SocketHandle = uint64;
#else 
using SocketHandle = int;
#endif

struct SocketTCP
{
    SocketTCP();

    void Close();
    bool IsValid() const;
    bool IsConnected() const { return mLive; }
    SocketErrorCode::Enum GetErrorCode() const { return mErrCode; }

    uint32 Write(const void* src, uint32 size);
    uint32 Read(void* dst, uint32 dstSize);

    static SocketTCP CreateListener();
    SocketTCP Accept(char* clientUrl = nullptr, uint32 clientUrlSize = 0);
    bool Listen(uint16 port, uint32 maxConnections = UINT32_MAX);

    static SocketTCP Connect(const char* url);

private:
    static bool ParseUrl(const char* url, char* address, size_t addressSize, char* port, size_t portSize, const char** pResource = nullptr);

private:
    SocketHandle mSock;
    SocketErrorCode::Enum mErrCode;
    uint16 mLive;
};

struct UniqueID
{
    uint8 data[16];

    bool operator==(const UniqueID& uuid) const;

    static bool Generate(UniqueID* uuid);
    static bool ToString(const UniqueID& uuid, char* str, uint32 size);
    static bool FromString(UniqueID* uuid, const char* str);
};

using OSDLL = void*;

struct SysInfo
{
    enum class CpuFamily 
    {
        Unknown = 0,
        ARM,
        x86_64,
        ARM64
    };

    struct CacheInfo
    {
        uint8 count;
        uint8 kway;
        uint16 lineSize;
        uint32 size;
    };

    char         cpuName[32];
    char         cpuModel[64];
    CpuFamily    cpuFamily;
    size_t       pageSize;
    size_t       physicalMemorySize;
    uint32       coreCount;
    CacheInfo    L1Cache;
    CacheInfo    L2Cache;
    CacheInfo    L3Cache;
    uint32       cpuCapsSSE : 1;
    uint32       cpuCapsSSE2 : 1;
    uint32       cpuCapsSSE3 : 1;
    uint32       cpuCapsSSE41 : 1;
    uint32       cpuCapsSSE42: 1;
    uint32       cpuCapsAVX : 1;
    uint32       cpuCapsAVX2 : 1;
    uint32       cpuCapsAVX512 : 1;
    uint32       cpuCapsNeon : 1;
};

namespace OS
{
    API void PauseCPU();
    uint64 GetCPUClock();

    API [[nodiscard]] OSDLL LoadDLL(const char* filepath, char** pErrorMsg = nullptr);
    API void UnloadDLL(OSDLL dll);
    API void* GetSymbolAddress(OSDLL dll, const char* symbolName);
    API size_t GetPageSize();
    API void GetSysInfo(SysInfo* info);
    API bool IsDebuggerPresent();
    API void GenerateCmdLineFromArgcArgv(int argc, const char* argv[], char** outString, uint32* outStringLen, 
                                             MemAllocator* alloc = Mem::GetDefaultAlloc(), const char* prefixCmd = nullptr);

    API bool SetEnvVar(const char* name, const char* value);
    API bool GetEnvVar(const char* name, char* outValue, uint32 valueSize);

    API char* GetMyPath(char* dst, size_t dstSize);
    API char* GetAbsolutePath(const char* path, char* dst, size_t dstSize);
    API char* GetCurrentDir(char* dst, size_t dstSize);
    API void  SetCurrentDir(const char* path);
    API char* GetHomeDir(char* dst, size_t dstSize);
    API char* GetCacheDir(char* dst, size_t dstSize, const char* appName);
    API PathInfo GetPathInfo(const char* path);
    API bool PathExists(const char* path);
    API bool IsPathFile(const char* path);
    API bool IsPathDir(const char* path);
    API bool CreateDir(const char* path);
    API bool MovePath(const char* src, const char* dest);
    API bool MakeTempPath(char* dst, size_t dstSize, const char* namePrefix, const char* dir = nullptr);
    API bool DeletePath(const char* path);
    API bool CopyPath(const char* srcPath, const char* destPath);
}

#if PLATFORM_PC
enum class OSProcessFlags : uint32
{
    None = 0,
    CaptureOutput = 0x1,
    InheritHandles = 0x2,
    DontCreateConsole = 0x4,
    ForceCreateConsole = 0x8
};
ENABLE_BITMASK(OSProcessFlags);

struct OSProcess
{
    OSProcess();
    ~OSProcess();

    bool Run(const char* cmdline, OSProcessFlags flags, const char* cwd = nullptr);
    void Wait() const;
    bool IsRunning() const;
    void Abort();
    bool IsValid() const;

    int GetExitCode() const;
    uint32 ReadStdOut(void* data, uint32 size) const;
    uint32 ReadStdErr(void* data, uint32 size) const;

private:
    void* mProcess;
    void* mStdOutPipeRead;
    void* mStdErrPipeRead;
    
#if PLATFORM_POSIX
    int mExitCode;
    int mTermSignalCode;
#endif
};

#endif // PLATFORM_PC

#if PLATFORM_WINDOWS

enum class OSWin32ShowWindow : int
{
    Hide = 0,
    Normal = 1,
    Minimized = 2,
    Maximized = 3,
    NotActive = 4,
    Show = 5,
    Minimize = 6,
    MinimizedNotActive = 7,
    Restore = 9,
    Default = 10,
    ForceMinimize = 11
};

enum class OSWin32ShellExecuteResult
{
    Ok,
    OutOfMemory,
    FileNotFound,
    PathNotFound,
    BadFormat,
    AccessDenied,
    NoAssociation,
    UnknownError
};

enum class OSWin32Folder
{
    Documents = 0,  // %USERPROFILE%\My Documents
    Fonts,          // %windir%\Fonts
    Downloads,      // %USERPROFILE%\Downloads
    AppData,        // %USERPROFILE%\AppData\Roaming
    LocalAppData,   // %USERPROFILE%\AppData\Local
    ProgramFiles,   // %SystemDrive%\Program Files
    System,         // %windir%\system32
    Startup,        // %APPDATA%\Microsoft\Windows\Start Menu\Programs\StartUp
    Desktop,        // %USERPROFILE%\Desktop
    _Count
};

struct OSWin32Pipe
{
	using ReadDataCallback = void(*)(OSWin32Pipe* pipe, const void* data, uint32 dataSize, void* userData);
	using ConnectCallback = void(*)(OSWin32Pipe* pipe, void* userData);
	using DisconnectCallback = void(*)(OSWin32Pipe* pipe, void* userData);
    using TimeoutCallback = bool(*)(OSWin32Pipe* pipe, void* userData);     // Return false to close the connection

	struct CreateServerDesc
	{
		ReadDataCallback handlerCallback;
		ConnectCallback connectCallback;
		DisconnectCallback disconnectCallback;
        TimeoutCallback timeoutCallback;
		const char* name = CONFIG_APP_NAME;
		size_t inputBufferSize = 32*SIZE_KB;
		size_t outputBufferSize = 32*SIZE_KB;
		void* handlerCallbackUserData = nullptr;
        uint32 readTimeout = 100;
		bool sendPing = true;
	};

	void Write(const void* data, uint32 size);
	template <typename _T> void Write(const _T& item) { Write(&item, sizeof(item)); }

	bool IsConnected() const;
	void Close();

	static OSWin32Pipe* CreateServer(const CreateServerDesc& desc);
	static void Destroy(OSWin32Pipe* pipe);
};

namespace OS
{
    API bool Win32IsProcessRunning(const char* execName);
    API bool Win32GetRegisterLocalMachineString(const char* subkey, const char* value, char* dst, size_t dstSize);
    API void Win32PrintToDebugger(const char* text); 
    API bool Win32SetPrivilege(const char* name, bool enable = true);
    API OSWin32ShellExecuteResult Win32ShellExecute(const char* filepath, const char* args = nullptr, 
                                                         const char* cwd = nullptr, 
                                                         OSWin32ShowWindow showFlag = OSWin32ShowWindow::Default, 
                                                         const char* operation = nullptr,
                                                         void** pInstance = nullptr);
    API char* Win32GetFolder(OSWin32Folder folder, char* dst, size_t dstSize);
    API void Win32EnableProgramConsoleCoding();
}

#elif PLATFORM_ANDROID
struct _JNIEnv;
typedef _JNIEnv JNIEnv;

typedef struct ANativeActivity ANativeActivity; // <android/native_activity.h>

enum class OSAndroidLogType 
{
    Unknown = 0,
    Default,
    Verbose,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,
    Silent,
};

namespace OS
{
    API void AndroidPrintToLog(OSAndroidLogType logType, const char* tag, const char* text);
    API JNIEnv* AndroidAcquireJniEnv(ANativeActivity* activity);
    API void AndroidReleaseJniEnv(ANativeActivity* activity);    
    API JNIEnv* AndroidGetJniEnv();
    API Path AndroidGetCacheDirectory(ANativeActivity* activity);
}
#endif

namespace _private
{
    void CountersAddThread(size_t stackSize);
    void CountersRemoveThread(size_t stackSize);
    void CountersAddMutex();
    void CountersRemoveMutex();
    void CountersAddSignal();
    void CountersRemoveSignal();
    void CountersAddSemaphore();
    void CountersRemoveSemaphore();
}

struct SysPrimitiveStats
{
    uint32 numMutexes;
    uint32 numSignals;
    uint32 numSemaphores;
    uint32 numThreads;
    uint64 threadStackSize;
};

SysPrimitiveStats GetSystemPrimitiveStats();

inline Path& Path::SetToCurrentDir()
{
    OS::GetCurrentDir(mStr, sizeof(mStr));
    mLen = Str::Len(mStr);
    return *this;
}

inline Path& Path::ConvertToUnix()
{
    PathUtils::ToUnix(mStr, mStr, sizeof(mStr));
    return *this;
}

inline Path& Path::ConvertToWin()
{
    PathUtils::ToWin(mStr, mStr, sizeof(mStr));
    return *this;
}

inline Path& Path::ConvertToAbsolute()
{
    char abspath[PATH_CHARS_MAX];
    OS::GetAbsolutePath(mStr, abspath, sizeof(abspath));
    return *this = abspath;
}

inline Path Path::GetAbsolute() const 
{
    Path p;
    OS::GetAbsolutePath(mStr, p.mStr, sizeof(p.mStr));
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline Path Path::GetFileExtension() const
{
    Path p;
    PathUtils::GetFileExtension(mStr, p.mStr, sizeof(p.mStr));
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline Path Path::GetFileNameAndExt() const
{
    Path p;
    PathUtils::GetFilenameAndExtension(mStr, p.mStr, sizeof(p.mStr));
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline Path Path::GetFileName() const
{
    Path p;
    PathUtils::GetFilename(mStr, p.mStr, sizeof(p.mStr));
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline Path Path::GetDirectory() const
{
    Path p;
    PathUtils::GetDirectory(mStr, p.mStr, sizeof(p.mStr));
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline Path& Path::Join(const Path& path)
{
    PathUtils::Join(mStr, sizeof(mStr), mStr, path.mStr);
    mLen = Str::Len(mStr);
    return *this;
}

inline Path& Path::JoinUnix(const Path& path)
{
    PathUtils::JoinUnixStyle(mStr, sizeof(mStr), mStr, path.mStr);
    mLen = Str::Len(mStr);
    return *this;
}

inline Path Path::Join(const Path& pathA, const Path& pathB)
{
    Path p;
    PathUtils::Join(p.mStr, sizeof(p.mStr), pathA.mStr, pathB.mStr);
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline Path Path::JoinUnix(const Path& pathA, const Path& pathB)
{
    Path p;
    PathUtils::JoinUnixStyle(p.mStr, sizeof(p.mStr), pathA.mStr, pathB.mStr);
    p.mLen = Str::Len(p.mStr);
    return p;
}

inline PathInfo Path::Stat() const
{
    return OS::GetPathInfo(mStr);
}

inline bool Path::Exists() const
{
    return OS::PathExists(mStr);
}

inline bool Path::IsFile() const
{
    return OS::GetPathInfo(mStr).type == PathType::File;
}

inline bool Path::IsDir() const
{
    return OS::GetPathInfo(mStr).type == PathType::Directory;
}

inline bool OS::PathExists(const char* path)
{
    return OS::GetPathInfo(path).type != PathType::Invalid;
}

inline bool OS::IsPathFile(const char* path)
{
    return OS::GetPathInfo(path).type == PathType::File;
}

inline bool OS::IsPathDir(const char* path)
{
    return OS::GetPathInfo(path).type == PathType::Directory;
}

INLINE uint64 Timer::Diff(uint64 newTick, uint64 oldTick)
{
    return (newTick > oldTick) ? (newTick - oldTick) : 1;
}

INLINE double Timer::ToSec(uint64 tick)
{
    return (double)tick / 1000000000.0;
}

INLINE double Timer::ToMS(uint64 tick)
{
    return (double)tick / 1000000.0;
}

INLINE double Timer::ToUS(uint64 tick)
{
    return (double)tick / 1000.0;
}

inline TimerStopWatch::TimerStopWatch()
{
    mStart = Timer::GetTicks();
}

inline void TimerStopWatch::Reset()
{
    mStart = Timer::GetTicks();
}

inline uint64 TimerStopWatch::Elapsed() const
{
    return Timer::Diff(Timer::GetTicks(), mStart);
}

inline double TimerStopWatch::ElapsedSec() const
{
    return Timer::ToSec(Elapsed());
}

inline double TimerStopWatch::ElapsedMS() const
{
    return Timer::ToMS(Elapsed());
}

inline double TimerStopWatch::ElapsedUS() const
{
    return Timer::ToUS(Elapsed());
}

template <typename _T> inline uint32 File::Read(_T* dst, uint32 count)
{
    return static_cast<uint32>(Read((void*)dst, sizeof(_T)*count)/sizeof(_T));
}

template <typename _T> inline uint32 File::Write(const _T* dst, uint32 count)
{
    return static_cast<uint32>(Write((const void*)dst, sizeof(_T)*count)/sizeof(_T));
}



