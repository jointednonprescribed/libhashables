
#ifndef _LIBHASHABLES__DEF_H_
#define _LIBHASHABLES__DEF_H_ 1

#ifndef _LIBHASHABLES__CONFIG_H_
#	include "config.h"
#endif



#ifdef __cplusplus
#	define LHASH_EXTERN_C     extern "C" {
#	define LHASH_END_EXTERN_C }
#	if NO_CXX == 0
#		define LHASH_CXX(...) __VA_ARGS__
#	else
#		define LHASH_CXX(...)
#	endif
#else
#	define LHASH_CXX(...)
#	define LHASH_EXTERN_C
#	define LHASH_END_EXTERN_C
#endif

#if LHASH_SINGLE_THREADED == 1
#	define _lhash_ThreadLocal_
#else
#	ifdef __cplusplus
#		define _lhash_ThreadLocal_ thread_local
#	elif LHASH_COMPILER == LHASH_GCC || LHASH_COMPILER == LHASH_CLANG || LHASH_COMPILER == LHASH_EMSCRIPTEN
#		define _lhash_ThreadLocal_ __thread
#	elif LHASH_COMPILER == LHASH_MSVC
#		define _lhash_ThreadLocal_ __declspec(thread)
#	endif
#endif



#endif // _LIBHASHABLES__DEF_H_
