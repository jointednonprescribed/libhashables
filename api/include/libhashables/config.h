
#ifndef _LIBHASHABLES__CONFIG_H_
#define _LIBHASHABLES__CONFIG_H_ 1



#ifndef LHASH_SINGLE_THREADED
#	define LHASH_SINGLE_THREADED 0
#elif LHASH_SINGLE_THREADED > 1
#	define LHASH_SINGLE_THREADED 1
#elif LHASH_SINGLE_THREADED < 0
#	define LHASH_SINGLE_THREADED 0
#endif

#ifndef LHASH_NO_CXX
#	ifdef __cplusplus
#		define LHASH_NO_CXX 0
#	else
#		define LHASH_NO_CXX 1
#	endif
#elif LHASH_NO_CXX > 1
#	define LHASH_NO_CXX 1
#elif LHASH_NO_CXX < 0
#	define LHASH_NO_CXX 0
#endif


#ifndef _LIBHASHABLES_DEF_H_
#	include "def.h"
#endif



#endif // _LIBHASHABLES__CONFIG_H_
