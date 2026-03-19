
#ifndef _LIBHASHABLES__LOGGINGAPI_H_
#define _LIBHASHABLES__LOGGINGAPI_H_ 1

#include "exceptions.h"



struct _lhashLogging
{
	void (*InfoF)(const char *fmt, va_list ap);
	void (*ErrorF)(const char *fmt, va_list ap);
	void (*WarnF)(const char *fmt, va_list ap);
	void (*DebugF)(const char *fmt, va_list ap);
};

bool lhashLoggingIsInitialized( void );
bool lhashInitLoggingNull( void );
bool lhashInitLoggingBasic( void );
bool lhashInitLogging( const struct _lhashLogging *callbacks );

void lhashLogInfoF(const char *fmt, ...);
void lhashLogErrorF(const char *fmt, ...);
void lhashLogWarnF(const char *fmt, ...);
void lhashLogDebugF(const char *fmt, ...);



#endif // _LIBHASHABLES__LOGGINGAPI_H_
