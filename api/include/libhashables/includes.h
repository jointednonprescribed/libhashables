
#ifndef _LIBHASHABLES__INCLUDES_H_
#define _LIBHASHABLES__INCLUDES_H_ 1

#ifndef _LIBHASHABLES__PLATFORM_H_
#	include "platform.h"
#endif



/* C/C++ Standard library Features */
#if LHASH_NO_CXX == 0
#	include <cstdarg>
#	include <cstdio>
#	include <cstddef>
#	include <cstdlib>
#	include <cstdint>
#	include <climits>
#	include <cfloat>
#	include <cstring>
#	define __STDC_WANT_LIB_EXT1__ 1
#	include <ctime>

#	include <string>
#	include <random>
#	include <chrono>
#	include <utility>
#	include <type_traits>
#	if __cplusplus >= 202000L
#		include <concepts>
#	endif
#else
LHASH_EXTERN_C
#	include <stdbool.h>
#	include <stdarg.h>
#	include <stdio.h>
#	include <stddef.h>
#	include <stdlib.h>
#	include <stdint.h>
#	include <limits.h>
#	include <float.h>
#	include <string.h>
#	define __STDC_WANT_LIB_EXT1__ 1
#	include <time.h>
LHASH_END_EXTERN_C
#endif

/* System Includes */
#if LHASH_PLATFORM == LHASH_WINDOWS
#	include <windows.h>
#	include <winnt.h>
#elif LHASH_UNIXLIKE == 1
#	include <sys/types.h>
#	include <unistd.h>
#endif

/* Project includes; This must go after System Includes */
#include "types.h"



#endif // _LIBHASHABLES__INCLUDES_H_
