
#ifndef _LIBHASHABLES__LOGGINGAPI_H_
#define _LIBHASHABLES__LOGGINGAPI_H_ 1

#include "exceptions.h"



struct LHASH_API _lhashLogging
{
	void (*InfoF)(const char *fmt, va_list ap);
	void (*ErrorF)(const char *fmt, va_list ap);
	void (*WarnF)(const char *fmt, va_list ap);
	void (*DebugF)(const char *fmt, va_list ap);
};

LHASH_API bool lhashLoggingIsInitialized( void );
LHASH_API bool lhashInitLoggingNull( void );
LHASH_API bool lhashInitLoggingBasic( void );
LHASH_API bool lhashInitLogging( const struct _lhashLogging *callbacks );

LHASH_API void lhashLogInfoF(const char *fmt, ...);
LHASH_API void lhashLogErrorF(const char *fmt, ...);
LHASH_API void lhashLogWarnF(const char *fmt, ...);
LHASH_API void lhashLogDebugF(const char *fmt, ...);



#endif // _LIBHASHABLES__LOGGINGAPI_H_
