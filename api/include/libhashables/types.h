
#ifndef _LIBHASHABLES__TYPES_H_
#define _LIBHASHABLES__TYPES_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#	include "includes.h"
#endif



/* A pointer-size integral type for pointers that can initialized with integer values. */
#ifdef __LP64__
typedef unsigned long long lhashUIntPtr_t;
typedef          long long lhashIntPtr_t;
#else
typedef unsigned long int  lhashUIntPtr_t;
typedef          long int  lhashIntPtr_t;
#endif


/* A process ID type */
#if LHASH_UNIXLIKE == 1
typedef pid_t lhashpid_t;
#elif LHASH_PLATFORM == LHASH_WINDOWS
typedef DWORD lhashpid_t;
#else
#	error "No Implementation!"
#endif



#endif // _LIBHASHABLES__TYPES_H_
