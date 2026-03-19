
#ifndef _LIBHASHABLES__EXCEPTIONS_H_
#define _LIBHASHABLES__EXCEPTIONS_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#	include "includes.h"
#endif



/*
 * A structure type for producing exceptions to be handled/reported.
 */
typedef struct _lhashException lhashException;


/*
 * Implementation for struct _lhashException
 */
struct _lhashException
{
	const char *exc_name, *exc_desc, *exc_funcname;
	const void *function;
	long long   ec;
};

#define LHASH_NO_ERROR (lhashException) {      \
	.exc_name     = "NoErrorOcurred",          \
	.exc_desc     = "No error occurred.",      \
	.exc_funcname = LHASH_EXCNAME_UNSPECIFIED, \
	.function     = NULL,                      \
	.ec           = 0                          \
}

/*
 * Get the last error thrown on this thread.
 */
const lhashException* GetLastError( void );

/*
 * Initialize an lhashException object with multiple variants.
 */
lhashException  lhashException_Make(const char *exc_name, const char *exc_desc);
lhashException  lhashException_MakeN(const char *exc_name, const char *exc_desc, const char *func_name);
lhashException  lhashException_MakeF(const char *exc_name, const char *exc_desc, const void *function);
lhashException  lhashException_MakeFn(const char *exc_name, const char *exc_desc, const char *func_name, const void *function);
lhashException  lhashException_MakeE(const char *exc_name, const char *exc_desc, long long error_code);
lhashException  lhashException_MakeNe(const char *exc_name, const char *exc_desc, const char *func_name, long long error_code);
lhashException  lhashException_MakeFe(const char *exc_name, const char *exc_desc, const void *function, long long error_code);
lhashException  lhashException_MakeFne(const char *exc_name, const char *exc_desc, const char *func_name, const void *function, long long error_code);
/* These variants do not take an error name, only a description. */
lhashException  lhashException_MakeD(const char *exc_desc);
lhashException  lhashException_MakeDn(const char *exc_desc, const char *func_name);
lhashException  lhashException_MakeDf(const char *exc_desc, const void *function);
lhashException  lhashException_MakeDfn(const char *exc_desc, const char *func_name, const void *function);
lhashException  lhashException_MakeDe(const char *exc_desc, long long error_code);
lhashException  lhashException_MakeDne(const char *exc_desc, const char *func_name, long long error_code);
lhashException  lhashException_MakeDfe(const char *exc_desc, const void *function, long long error_code);
lhashException  lhashException_MakeDfne(const char *exc_desc, const char *func_name, const void *function, long long error_code);

/*
 * Initialize an lhashException object with multiple variants, mirroring
 * those of lhashException_Make().
 */
lhashException* lhashException_Init(lhashException *self, const char *exc_name, const char *exc_desc);
lhashException* lhashException_InitN(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name);
lhashException* lhashException_InitF(lhashException *self, const char *exc_name, const char *exc_desc, const void *function);
lhashException* lhashException_InitFn(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name, const void *function);
lhashException* lhashException_InitE(lhashException *self, const char *exc_name, const char *exc_desc, long long error_code);
lhashException* lhashException_InitNe(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name, long long error_code);
lhashException* lhashException_InitFe(lhashException *self, const char *exc_name, const char *exc_desc, const void *function, long long error_code);
lhashException* lhashException_InitFne(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name, const void *function, long long error_code);
/* These variants do not take an error name, only a description. */
lhashException* lhashException_InitD(lhashException *self, const char *exc_desc);
lhashException* lhashException_InitDn(lhashException *self, const char *exc_desc, const char *func_name);
lhashException* lhashException_InitDf(lhashException *self, const char *exc_desc, const void *function);
lhashException* lhashException_InitDfn(lhashException *self, const char *exc_desc, const char *func_name, const void *function);
lhashException* lhashException_InitDe(lhashException *self, const char *exc_desc, long long error_code);
lhashException* lhashException_InitDne(lhashException *self, const char *exc_desc, const char *func_name, long long error_code);
lhashException* lhashException_InitDfe(lhashException *self, const char *exc_desc, const void *function, long long error_code);
lhashException* lhashException_InitDfne(lhashException *self, const char *exc_desc, const char *func_name, const void *function, long long error_code);

/*
 * Throws an exception globally, returns a pointer to the global "Last Error Thrown"
 * container, or NULL if self is NULL.
 */
const lhashException* lhashException_Throw(const lhashException *self);

/*
 * Throw an anonymous exception, with multiple variants, mirroring those of
 * lhashException_Make() and lhashException_Init(), returns a pointer to the
 * global "Last Error Thrown" container.
 */
const lhashException* lhashThrow(const char *exc_name, const char *exc_desc);
const lhashException* lhashThrowN(const char *exc_name, const char *exc_desc, const char *func_name);
const lhashException* lhashThrowF(const char *exc_name, const char *exc_desc, const void *function);
const lhashException* lhashThrowFn(const char *exc_name, const char *exc_desc, const char *func_name, const void *function);
const lhashException* lhashThrowE(const char *exc_name, const char *exc_desc, long long error_code);
const lhashException* lhashThrowNe(const char *exc_name, const char *exc_desc, const char *func_name, long long error_code);
const lhashException* lhashThrowFe(const char *exc_name, const char *exc_desc, const void *function, long long error_code);
const lhashException* lhashThrowFne(const char *exc_name, const char *exc_desc, const char *func_name, const void *function, long long error_code);
/* These variants do not take an error name, only a description. */
const lhashException* lhashThrowD(const char *exc_desc);
const lhashException* lhashThrowDn(const char *exc_desc, const char *func_name);
const lhashException* lhashThrowDf(const char *exc_desc, const void *function);
const lhashException* lhashThrowDfn(const char *exc_desc, const char *func_name, const void *function);
const lhashException* lhashThrowDe(const char *exc_desc, long long error_code);
const lhashException* lhashThrowDne(const char *exc_desc, const char *func_name, long long error_code);
const lhashException* lhashThrowDfe(const char *exc_desc, const void *function, long long error_code);
const lhashException* lhashThrowDfne(const char *exc_desc, const char *func_name, const void *function, long long error_code);



#endif // _LIBHASHABLES__EXCEPTIONS_H_
