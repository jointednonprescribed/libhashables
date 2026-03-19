
#ifndef _LIBHASHABLES_
#	include <libhashables.h>
#endif


char LHASH_LOGGING_TIME_STR_BUF[256] = {0};

const struct _lhashLogging LHASH_BASIC_LOGGER = {
	.InfoF  = LHASH_LOGGING_BASIC_INFOF,
	.ErrorF = LHASH_LOGGING_BASIC_ERRORF,
	.WarnF  = LHASH_LOGGING_BASIC_WARNF,
	.DebugF = LHASH_LOGGING_BASIC_DEBUGF,
}, LHASH_NULL_LOGGER = {
	.InfoF  = LHASH_LOGGING_NULL_INFOF,
	.ErrorF = LHASH_LOGGING_NULL_ERRORF,
	.WarnF  = LHASH_LOGGING_NULL_WARNF,
	.DebugF = LHASH_LOGGING_NULL_DEBUGF,
};

struct _lhashLogging LHASH_LOGGER = LHASH_NULL_LOGGER;

int LHASH_LOGGING_INIT = 0;

int LHASH_LOGGING__count_format_codes(const char *fmt)
{
	if (fmt == NULL || fmt[0] == 0)
		return -1;

	char c = fmt[0];
	
	int count = 0;

	for (size_t i = 0; c != 0;) {
		if (c == '%')
			count++;

		c = fmt[++i];
	}

	return count;
}

bool LHASH_LOGGING__has_null_callbacks(const struct _lhashLogging *callbacks)
{
	return
		callbacks->InfoF  == NULL ||
		callbacks->ErrorF == NULL ||
		callbacks->WarnF  == NULL ||
		callbacks->DebugF == NULL;
}

void LHASH_LOGGING_BASIC_INFOF(const char *fmt, va_list ap)
{
	struct tm local;

	time_t t;

	// NULL strings and empty strings are not valid
	if (fmt == NULL || fmt[0] == 0)
		return;

	// print thread information...
	fprintf(stdout, "Thread <%lu> ", (unsigned long) lhashGetPid());

	// ...followed by the time
	t = time(NULL);
	localtime_r(&t, &local);
	LHASH_LOGGING_TIME_STR_BUF[255] = 0;
	if (strftime(LHASH_LOGGING_TIME_STR_BUF, 255, "%a %b %e, %Y %I:%M %p %Z (UTC %z) [INFO]: ", &local))
		fprintf(stdout, LHASH_LOGGING_TIME_STR_BUF);
	else
		fprintf(stdout, "(time-buffer-overflow) [INFO]: ");

	// print the variadic arguments based on the supplied format string
	vfprintf(stdout, fmt, ap);

	// print a final newline character so that the caller doesn't have to
	fprintf(stdout, "\n");
}
void LHASH_LOGGING_BASIC_ERRORF(const char *fmt, va_list ap)
{
	struct tm local;

	time_t t;

	// NULL strings and empty strings are not valid
	if (fmt == NULL || fmt[0] == 0)
		return;

	// print thread information...
	fprintf(stderr, "Thread <%lu> ", (unsigned long) lhashGetPid());

	// ...followed by the time
	t = time(NULL);
	localtime_r(&t, &local);
	LHASH_LOGGING_TIME_STR_BUF[255] = 0;
	if (strftime(LHASH_LOGGING_TIME_STR_BUF, 255, "%a %b %e, %Y %I:%M %p %Z (UTC %z) [ERROR]: ", &local))
		fprintf(stderr, LHASH_LOGGING_TIME_STR_BUF);
	else
		fprintf(stderr, "(time-buffer-overflow) [ERROR]: ");

	// print the variadic arguments based on the supplied format string
	vfprintf(stderr, fmt, ap);

	// print a final newline character so that the caller doesn't have to
	fprintf(stderr, "\n");
}
void LHASH_LOGGING_BASIC_WARNF(const char *fmt, va_list ap)
{
	struct tm local;

	time_t t;

	// NULL strings and empty strings are not valid
	if (fmt == NULL || fmt[0] == 0)
		return;

	// print thread information...
	fprintf(stdout, "Thread <%lu> ", (unsigned long) lhashGetPid());

	// ...followed by the time
	t = time(NULL);
	localtime_r(&t, &local);
	LHASH_LOGGING_TIME_STR_BUF[255] = 0;
	if (strftime(LHASH_LOGGING_TIME_STR_BUF, 255, "%a %b %e, %Y %I:%M %p %Z (UTC %z) [WARN]: ", &local))
		fprintf(stdout, LHASH_LOGGING_TIME_STR_BUF);
	else
		fprintf(stdout, "(time-buffer-overflow) [WARN]: ");

	// print the variadic arguments based on the supplied format string
	vfprintf(stdout, fmt, ap);

	// print a final newline character so that the caller doesn't have to
	fprintf(stdout, "\n");
}
void LHASH_LOGGING_BASIC_DEBUGF(const char *fmt, va_list ap)
{
	struct tm local;

	time_t t;

	// NULL strings and empty strings are not valid
	if (fmt == NULL || fmt[0] == 0)
		return;

	// print thread information...
	fprintf(stdout, "Thread <%lu> ", (unsigned long) lhashGetPid());

	// ...followed by the time
	t = time(NULL);
	localtime_r(&t, &local);
	LHASH_LOGGING_TIME_STR_BUF[255] = 0;
	if (strftime(LHASH_LOGGING_TIME_STR_BUF, 255, "%a %b %e, %Y %I:%M %p %Z (UTC %z) [DEBUG]: ", &local))
		fprintf(stdout, LHASH_LOGGING_TIME_STR_BUF);
	else
		fprintf(stdout, "(time-buffer-overflow) [DEBUG]: ");

	// print the variadic arguments based on the supplied format string
	vfprintf(stdout, fmt, ap);

	// print a final newline character so that the caller doesn't have to
	fprintf(stdout, "\n");
}

void LHASH_LOGGING_NULL_INFOF(const char *fmt, va_list ap)  {}
void LHASH_LOGGING_NULL_ERRORF(const char *fmt, va_list ap) {}
void LHASH_LOGGING_NULL_WARNF(const char *fmt, va_list ap)  {}
void LHASH_LOGGING_NULL_DEBUGF(const char *fmt, va_list ap) {}

bool lhashLoggingIsInitialized( void )
{
	return LHASH_LOGGING_INIT != 0;
}
bool lhashInitLoggingNull( void )
{
	if (LHASH_LOGGING_INIT)
		return lhashInitLogging(&LHASH_NULL_LOGGER);
	else
		return LHASH_LOGGING_INIT = true;
}
bool lhashInitLoggingBasic( void )
{
	return lhashInitLogging(&LHASH_BASIC_LOGGER);
}
bool lhashInitLogging( const struct _lhashLogging *callbacks )
{
	if (LHASH_LOGGING_INIT)
		return false;
	else if (LHASH_LOGGING__has_null_callbacks(callbacks))
		return false;
	else {
		LHASH_LOGGER = *callbacks;
		return LHASH_LOGGING_INIT = true;
	}
}

void lhashLogInfoF(const char *fmt, ...)
{
	if (!LHASH_LOGGING_INIT)
		return;
	
	va_list v;
	
	va_start(v, LHASH_LOGGING__count_format_codes(fmt));

	LHASH_LOGGER.InfoF(fmt, v);

	va_end(v);
}
void lhashLogErrorF(const char *fmt, ...)
{
	if (!LHASH_LOGGING_INIT)
		return;
	
	va_list v;
	
	va_start(v, LHASH_LOGGING__count_format_codes(fmt));

	LHASH_LOGGER.ErrorF(fmt, v);

	va_end(v);
}
void lhashLogWarnF(const char *fmt, ...)
{
	if (!LHASH_LOGGING_INIT)
		return;
	
	va_list v;
	
	va_start(v, LHASH_LOGGING__count_format_codes(fmt));

	LHASH_LOGGER.WarnF(fmt, v);

	va_end(v);
}
void lhashLogDebugF(const char *fmt, ...)
{
	if (!LHASH_LOGGING_INIT)
		return;
	
	va_list v;
	
	va_start(v, LHASH_LOGGING__count_format_codes(fmt));

	LHASH_LOGGER.DebugF(fmt, v);

	va_end(v);
}
