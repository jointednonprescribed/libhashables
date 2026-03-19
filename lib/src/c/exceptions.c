
#ifndef _LIBHASHABLES_
#	include <libhashables.h>
#endif


const char LHASH_EXCNAME_UNSPECIFIED[] = "<unspecified>";
const char LHASH_EXCNAME_GENERIC[]     = "Exception";
const char LHASH_EXCDESC_NONE[]        = "No error description provided.";

_lhash_ThreadLocal_ lhashException LAST_EXCEPTION = LHASH_NO_ERROR;


const lhashException* GetLastError( void )
{
	return &LAST_EXCEPTION;
}

lhashException  lhashException_Make(const char *exc_name, const char *exc_desc)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = NULL,
		.ec           = -1
	};
}
lhashException  lhashException_MakeN(const char *exc_name, const char *exc_desc, const char *func_name)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = NULL,
		.ec           = -1
	};
}
lhashException  lhashException_MakeF(const char *exc_name, const char *exc_desc, const void *function)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = function,
		.ec           = -1
	};
}
lhashException  lhashException_MakeFn(const char *exc_name, const char *exc_desc, const char *func_name, const void *function)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = function,
		.ec           = -1
	};
}
lhashException  lhashException_MakeE(const char *exc_name, const char *exc_desc, long long error_code)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = NULL,
		.ec           = error_code
	};
}
lhashException  lhashException_MakeNe(const char *exc_name, const char *exc_desc, const char *func_name, long long error_code)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = NULL,
		.ec           = error_code
	};
}
lhashException  lhashException_MakeFe(const char *exc_name, const char *exc_desc, const void *function, long long error_code)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = function,
		.ec           = error_code
	};
}
lhashException  lhashException_MakeFne(const char *exc_name, const char *exc_desc, const char *func_name, const void *function, long long error_code)
{
	return (lhashException) {
		.exc_name     = exc_name,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = function,
		.ec           = error_code
	};
}

lhashException  lhashException_MakeD(const char *exc_desc)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = NULL,
		.ec           = -1
	};
}
lhashException  lhashException_MakeDn(const char *exc_desc, const char *func_name)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = NULL,
		.ec           = -1
	};
}
lhashException  lhashException_MakeDf(const char *exc_desc, const void *function)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = function,
		.ec           = -1
	};
}
lhashException  lhashException_MakeDfn(const char *exc_desc, const char *func_name, const void *function)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = function,
		.ec           = -1
	};
}
lhashException  lhashException_MakeDe(const char *exc_desc, long long error_code)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = NULL,
		.ec           = error_code
	};
}
lhashException  lhashException_MakeDne(const char *exc_desc, const char *func_name, long long error_code)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = NULL,
		.ec           = error_code
	};
}
lhashException  lhashException_MakeDfe(const char *exc_desc, const void *function, long long error_code)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = LHASH_EXCNAME_UNSPECIFIED,
		.function     = function,
		.ec           = error_code
	};
}
lhashException  lhashException_MakeDfne(const char *exc_desc, const char *func_name, const void *function, long long error_code)
{
	return (lhashException) {
		.exc_name     = LHASH_EXCNAME_GENERIC,
		.exc_desc     = exc_desc,
		.exc_funcname = func_name,
		.function     = function,
		.ec           = error_code
	};
}

lhashException* lhashException_Init(lhashException *self, const char *exc_name, const char *exc_desc)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = NULL;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitN(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = NULL;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitF(lhashException *self, const char *exc_name, const char *exc_desc, const void *function)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = function;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitFn(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name, const void *function)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = function;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitE(lhashException *self, const char *exc_name, const char *exc_desc, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = NULL;
	self->ec           = error_code;

	return self;
}
lhashException* lhashException_InitNe(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = NULL;
	self->ec           = error_code;

	return self;
}
lhashException* lhashException_InitFe(lhashException *self, const char *exc_name, const char *exc_desc, const void *function, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = function;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitFne(lhashException *self, const char *exc_name, const char *exc_desc, const char *func_name, const void *function, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = exc_name;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = function;
	self->ec           = error_code;

	return self;
}

lhashException* lhashException_InitD(lhashException *self, const char *exc_desc)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = NULL;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitDn(lhashException *self, const char *exc_desc, const char *func_name)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = NULL;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitDf(lhashException *self, const char *exc_desc, const void *function)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = function;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitDfn(lhashException *self, const char *exc_desc, const char *func_name, const void *function)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = function;
	self->ec           = -1;

	return self;
}
lhashException* lhashException_InitDe(lhashException *self, const char *exc_desc, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = NULL;
	self->ec           = error_code;

	return self;
}
lhashException* lhashException_InitDne(lhashException *self, const char *exc_desc, const char *func_name, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = NULL;
	self->ec           = error_code;

	return self;
}
lhashException* lhashException_InitDfe(lhashException *self, const char *exc_desc, const void *function, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = LHASH_EXCNAME_UNSPECIFIED;
	self->function     = function;
	self->ec           = error_code;

	return self;
}
lhashException* lhashException_InitDfne(lhashException *self, const char *exc_desc, const char *func_name, const void *function, long long error_code)
{
	if (self == NULL)
		return NULL;

	self->exc_name     = LHASH_EXCNAME_GENERIC;
	self->exc_desc     = exc_desc;
	self->exc_funcname = func_name;
	self->function     = function;
	self->ec           = error_code;

	return self;
}

const lhashException* lhashException_Throw(const lhashException *self)
{
	if (self == NULL)
		return &LAST_EXCEPTION;

	LAST_EXCEPTION.exc_name     = self->exc_name;
	LAST_EXCEPTION.exc_desc     = self->exc_desc;
	LAST_EXCEPTION.exc_funcname = self->exc_funcname;
	LAST_EXCEPTION.function     = self->function;
	LAST_EXCEPTION.ec           = self->ec;

	if (LAST_EXCEPTION.function == NULL)
		lhashLogErrorF("%s occurred (code %lld)...\nIn function '%s' at <??>:\n\t%s",
			LAST_EXCEPTION.exc_name, LAST_EXCEPTION.ec, LAST_EXCEPTION.exc_funcname,
			LAST_EXCEPTION.exc_desc);
	else
		lhashLogErrorF("%s occurred (code %lld) in function '%s' at %p:\n\t%s",
			LAST_EXCEPTION.exc_name, LAST_EXCEPTION.ec, LAST_EXCEPTION.exc_funcname,
			LAST_EXCEPTION.function, LAST_EXCEPTION.exc_desc);

	return &LAST_EXCEPTION;
}

const lhashException* lhashThrow(const char *exc_name, const char *exc_desc)
{
	lhashException e;

	return lhashException_Throw(lhashException_Init(&e, exc_name, exc_desc));
}
const lhashException* lhashThrowN(const char *exc_name, const char *exc_desc, const char *func_name)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitN(&e, exc_name, exc_desc, func_name));
}
const lhashException* lhashThrowF(const char *exc_name, const char *exc_desc, const void *function)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitF(&e, exc_name, exc_desc, function));
}
const lhashException* lhashThrowFn(const char *exc_name, const char *exc_desc, const char *func_name, const void *function)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitFn(&e, exc_name, exc_desc, func_name, function));
}
const lhashException* lhashThrowE(const char *exc_name, const char *exc_desc, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitE(&e, exc_name, exc_desc, error_code));
}
const lhashException* lhashThrowNe(const char *exc_name, const char *exc_desc, const char *func_name, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitNe(&e, exc_name, exc_desc, func_name, error_code));
}
const lhashException* lhashThrowFe(const char *exc_name, const char *exc_desc, const void *function, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitFe(&e, exc_name, exc_desc, function, error_code));
}
const lhashException* lhashThrowFne(const char *exc_name, const char *exc_desc, const char *func_name, const void *function, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitFne(&e, exc_name, exc_desc, func_name, function, error_code));
}
const lhashException* lhashThrowD(const char *exc_desc)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitD(&e, exc_desc));
}
const lhashException* lhashThrowDn(const char *exc_desc, const char *func_name)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDn(&e, exc_desc, func_name));
}
const lhashException* lhashThrowDf(const char *exc_desc, const void *function)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDf(&e, exc_desc, function));
}
const lhashException* lhashThrowDfn(const char *exc_desc, const char *func_name, const void *function)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDfn(&e, exc_desc, func_name, function));
}
const lhashException* lhashThrowDe(const char *exc_desc, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDe(&e, exc_desc, error_code));
}
const lhashException* lhashThrowDne(const char *exc_desc, const char *func_name, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDne(&e, exc_desc, func_name, error_code));
}
const lhashException* lhashThrowDfe(const char *exc_desc, const void *function, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDfe(&e, exc_desc, function, error_code));
}
const lhashException* lhashThrowDfne(const char *exc_desc, const char *func_name, const void *function, long long error_code)
{
	lhashException e;

	return lhashException_Throw(lhashException_InitDfne(&e, exc_desc, func_name, function, error_code));
}
