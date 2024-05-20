
#if !defined(GEM_BASE_H)
#define GEM_BASE_H 1

// Overritable macros
// ============================================================
// GEM_DEBUG          -- 0 (disable) or 1 (enable)
// GEM_ASSERT_ENABLED -- 0 (disable) or 1 (enable)
// GEM_BREAK()        -- Function

// ============================================================
// Pre-processor environment detection
// ============================================================

// Compiler
// ============================================================

#if defined(__clang__)
#  define GEM_COMPILER_CLANG 1
#elif defined(__GNUC__)
#  define GEM_COMPILER_GCC 1
#elif defined(_MSC_VER)
#  define GEM_COMPILER_MSVC 1
#else
#  error "Gem : Unknown compiler"
#endif

#if !defined(GEM_COMPILER_CLANG)
#  define GEM_COMPILER_CLANG 0
#endif
#if !defined(GEM_COMPILER_GCC)
#  define GEM_COMPILER_GCC 0
#endif
#if !defined(GEM_COMPILER_MSVC)
#  define GEM_COMPILER_MSVC 0
#endif

// Operating System
// ============================================================

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  define GEM_OS_WINDOWS 1
#elif defined(__gnu_linux__) || defined(__linux__)
#  define GEM_OS_LINUX 1
#  if defined(__ANDROID__)
#    define GEM_OS_ANDROID 1
#  endif
#elif defined(__unix__)
#  define GEM_OS_UNIX 1
#elif defined(__APPLE__)
#  define GEM_OS_APPLE 1
#else
#  error "Gem : Unknown operating system"
#endif

#if !defined(GEM_OS_WINDOWS)
#  define GEM_OS_WINDOWS 0
#endif
#if !defined(GEM_OS_LINUX)
#  define GEM_OS_LINUX 0
#endif
#if !defined(__ANDROID__)
#  define GEM_OS_ANDROID 0
#endif
#if !defined(GEM_OS_UNIX)
#  define GEM_OS_UNIX 0
#endif
#if !defined(GEM_OS_APPLE)
#  define GEM_OS_APPLE 0
#endif

// Architecture
// ============================================================

#if defined(_M_AMD64) || defined(__amd64) || defined(__amd64__)
#  define GEM_ARCH_X64 1
#elif defined (_M_I86) || defined(_M_IX86) || defined(i386)
#  define GEM_ARCH_X32 1
#else
#  error "Gem : Unknown architecture"
#endif

#if !defined(GEM_ARCH_X64)
#  define GEM_ARCH_X64 0
#endif
#if !defined(GEM_ARCH_X32)
#  define GEM_ARCH_X32 0
#endif

// Debug
// ============================================================

#if !defined(GEM_DEBUG)
#  if defined(_DEBUG)
#    define GEM_DEBUG 1
#  else
#    define GEM_DEBUG 0
#  endif
#endif

// ============================================================
// Assert
// ============================================================

#if !defined(GEM_BREAK)
#  define GEM_BREAK() (*((char*)0) = 0)
#endif

#if !defined(GEM_ASSERT_ENABLED) && GEM_DEBUG
#  define GEM_ASSERT_ENABLED 1
#endif

#if GEM_ASSERT_ENABLED
#  define GEM_ASSERT(x) ((!!(x)) || GEM_BREAK())
#else
#  define GEM_ASSERT(x)
#endif

// ============================================================
// Primitive types
// ============================================================

typedef signed char        i8;
typedef signed short       i16;
typedef signed int         i32;
typedef signed long long   i64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef float              f32;
typedef double             f64;

#define I8_MIN  -128
#define I16_MIN -32768
#define I32_MIN -2147483648
#define I64_MIN -9223372036854775808
#define I8_MAX  127
#define I16_MAX 32767
#define I32_MAX 2147483647
#define I64_MAX 9223372036854775807
#define U8_MAX  0xffu
#define U16_MAX 0xffffu
#define U32_MAX 0xffffffffu
#define U64_MAX 0xffffffffffffffffu

#endif // !GEM_BASE_H
