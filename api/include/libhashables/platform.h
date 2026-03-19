
#ifndef _LIBHASHABLES__PLATFORM_H_
#define _LIBHASHABLES__PLATFORM_H_ 1

#ifndef _LIBHASHABLES__DEF_H_
#	include "def.h"
#endif



#define LHASH_UNKNOWN    0
/* Platform Selections */
#define LHASH_LINUX      1
#define LHASH_WINDOWS    2
#define LHASH_OSX        3
#define LHASH_BSD        4
#define LHASH_WASM       5
/* Compiler Selections */
#define LHASH_GCC        6
#define LHASH_MSVC       7
#define LHASH_CLANG      8
#define LHASH_EMSCRIPTEN 9


/* Detect Windows System */
#ifdef _WIN32
#	define LHASH_PLATFORM LHASH_WINDOWS
#	define LHASH_UNIXLIKE 0
#	ifdef __GNUC__
#		define LHASH_GNUC       1
#		define LHASH_COMPILER   LHASH_GCC
#	else
#		define LHASH_GNUC       0
#	endif
#	ifdef _WIN64
#		define LHASH_PLATFORM32 0
#	else
#		define LHASH_PLATFORM32 1
#	endif

/* Detect Linux System */
#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
#	define LHASH_PLATFORM LHASH_LINUX
#	define LHASH_UNIXLIKE 1
#	ifdef __GNUC__
#		define LHASH_GNUC       1
#		define LHASH_COMPILER   LHASH_GCC
#	else
#		define LHASH_GNUC       0
#	endif
#	if defined(__LP64__) || (defined(UINTPTR_MAX) && UINTPTR_MAX > 0xffffffffUL)
#		define LHASH_PLATFORM32 0
#	else
#		define LHASH_PLATFORM32 1
#	endif

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(BSD)
#	define LHASH_PLATFORM LHASH_BSD
#	define LHASH_UNIXLIKE 1
#	ifdef __GNUC__
#		define LHASH_GNUC       1
#		define LHASH_COMPILER   LHASH_GCC
#	else
#		define LHASH_GNUC       0
#	endif
#	if defined(__LP64__) || (defined(UINTPTR_MAX) && UINTPTR_MAX > 0xffffffffUL)
#		define LHASH_PLATFORM32 0
#	else
#		define LHASH_PLATFORM32 1
#	endif

#elif defined(__APPLE__) && defined(__MACH__)
#	define LHASH_PLATFORM LHASH_BSD
#	define LHASH_UNIXLIKE 1
#	ifdef __GNUC__
#		define LHASH_GNUC       1
#		define LHASH_COMPILER   LHASH_GCC
#	else
#		define LHASH_GNUC       0
#	endif
#	if defined(__LP64__) || (defined(UINTPTR_MAX) && UINTPTR_MAX > 0xffffffffUL)
#		define LHASH_PLATFORM32 0
#	else
#		define LHASH_PLATFORM32 1
#	endif

#else
#	error "libhashables: Unsupported Platform!"
#endif

#ifndef LHASH_COMPILER

/* Detect GCC */
#	ifdef __GNUC__
#		define LHASH_COMPILER LHASH_GCC

/* Detect CLang */
#	elif defined(__clang__)
#		define LHASH_COMPILER LHASH_CLANG

/* Detect Microsoft Visual C/C++ */
#	elif defined(_MSC_VER)
#		define LHASH_COMPILER LHASH_MSVC

/* Detect Emscripten */
#	elif defined(__wasm) || defined(__wasm__)
#		define LHASH_COMPILER LHASH_EMSCRIPTEN

#	else
#		define LHASH_COMPILER LHASH_UNKNOWN
#	endif

#endif

/* Provided macros for handling platform independence: */
#if LHASH_PLATFORM == LHASH_WINDOWS
#	define LHASH_API    __declspec(dllexport)
#	define LHASH_IMPORT __declspec(dllimport)

#	define lhashGetPid GetCurrentProcessId
#else
#	define LHASH_API
#	define LHASH_IMPORT

#	define lhashGetPid getpid
#endif



#endif // _LIBHASHABLES__PLATFORM_H_
