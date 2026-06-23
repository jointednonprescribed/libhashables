
#ifndef _LIBHASHABLES_
#   include <libhashables.h>
#endif



bool _LHASH_VargReject(lhashGTypeHandler *handler, va_list ap)
{
	return false;
}
bool _LHASH_ExtrReject(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	return false;
}
bool _LHASH_InsReject(lhashGTypeHandler *handler, const void *const src, size_t max)
{
	return false;
}

bool _LHASH_VargPtr(lhashGTypeHandler *handler, va_list ap)
{
	if (handler == NULL || handler->_address == NULL)
		return false;

	void *const ptr = va_arg(ap, void*);

	size_t transferred = _LHASH_InsPtr(handler, (const void*) &ptr, 1);

	if (transferred != sizeof(void*))
		return false;
	else
		return true;
}
bool _LHASH_InsPtr(lhashGTypeHandler *handler, const void *const src, size_t len)
{
	if (handler == NULL || handler->_address == NULL || src == NULL || len == 0)
		return false;

	size_t pptr = handler->_pptr;

	// save initial state of the write ptr, and the amount of spots available at the destination
	const size_t _pptr = pptr, spots_available = handler->pavailable - pptr;

	if (spots_available == 0)
		return false;

	// if the length of the array is too big for the destination, cap it at the specified limit.
	if (len > spots_available)
		len = spots_available;

	const void **src_cursor  = (const void**) src;
	void       **dest_cursor = (void**)       handler->_address;

	if (len == 1)
		// transfer 1 element;
		dest_cursor[pptr++] = *src_cursor;
	
	// handle multiple elements
	else for (size_t i = 0; i < len;)
		dest_cursor[pptr++] = src_cursor[i++];
	
	// commit the final state of the write ptr
	handler->_pptr = pptr;

	// return based on whether any data was transferred (final write ptr > initial write ptr)
	return pptr > _pptr;
}
bool _LHASH_ExtrPtr(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL || dest == NULL || max == 0)
		return false;

	size_t gptr = handler->_gptr;

	// save initial state of the read ptr, and the amount of elements available in the source
	const size_t _gptr = gptr, elements_available = handler->gavailable - gptr;

	if (elements_available == 0)
		return false;

	// if the length of the array is too small for the source, cap it at the specified limit.
	if (max > elements_available)
		max = elements_available;

	const void **src_cursor  = (const void**) handler->_caddress;
	void       **dest_cursor = (void**)       dest;

	if (max == 1)
		// transfer 1 element;
		*dest_cursor = src_cursor[gptr++];

	// handle multiple elements
	else for (size_t i = 0; i < max;)
		dest_cursor[i++] = src_cursor[gptr++];
	
	// commit the final state of the read ptr
	handler->_gptr = gptr;

	// return based on whether any data was transferred (final write ptr > initial write ptr)
	return gptr > _gptr;
}

#define _LHASH_VargIntGeneric(handler, ap, inserter, type)    \
	if (handler == NULL)                                      \
		return false;                                         \
\
	type value = va_arg(ap, type);                            \
\
	return inserter(handler, &value, 1)

bool _LHASH_VargInt(lhashGTypeHandler *handler, va_list ap)
{
	_LHASH_VargIntGeneric(handler, ap, _LHASH_InsInt, int);
}
bool _LHASH_VargLong(lhashGTypeHandler *handler, va_list ap)
{
	_LHASH_VargIntGeneric(handler, ap, _LHASH_InsLong, long);
}
bool _LHASH_VargLLong(lhashGTypeHandler *handler, va_list ap)
{
	_LHASH_VargIntGeneric(handler, ap, _LHASH_InsLLong, long long);
}
bool _LHASH_VargLLLong(lhashGTypeHandler *handler, va_list ap)
{
	_LHASH_VargIntGeneric(handler, ap, _LHASH_InsLLLong, lhashint128_t);
}
bool _LHASH_VargShort(lhashGTypeHandler *handler, va_list ap)
{
	_LHASH_VargIntGeneric(handler, ap, _LHASH_InsShort, short);
}
bool _LHASH_VargChar(lhashGTypeHandler *handler, va_list ap)
{
	_LHASH_VargIntGeneric(handler, ap, _LHASH_InsChar, char);
}

#define _LHASH_ExtrByteByByte(handler, dest, count, nmemb)                           \
	if (handler == NULL || handler->_caddress == NULL || dest == NULL || count == 0) \
		return false;                                                                \
\
	const size_t elements_available = handler->gavailable - handler->_gptr;          \
\
	if (count > elements_available)                                                  \
		count = elements_available;                                                  \
\
	const size_t bytesc = count * nmemb;                                             \
\
	char       *destcurs = (char*) dest;                                             \
	const char *srccurs  = (const char*) handler->_caddress;                         \
\
	size_t i = 0;                                                                    \
\
	for (; i < bytesc; i++, srccurs++, destcurs++)                                   \
		*destcurs = *srccurs;                                                        \
\
	handler->_gptr += i / nmemb;                                                     \
\
	return true

bool _LHASH_ExtrInt(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrByteByByte(handler, dest, count, sizeof(int));
}
bool _LHASH_ExtrLong(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrByteByByte(handler, dest, count, sizeof(long));
}
bool _LHASH_ExtrLLong(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrByteByByte(handler, dest, count, sizeof(long long));
}
bool _LHASH_ExtrLLLong(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrByteByByte(handler, dest, count, sizeof(lhashint128_t));
}
bool _LHASH_ExtrShort(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrByteByByte(handler, dest, count, sizeof(short));
}
bool _LHASH_ExtrChar(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrByteByByte(handler, dest, count, sizeof(char));
}

#define _LHASH_InsByteByByte(handler, src, count, nmemb)                             \
	if (handler == NULL || handler->_address == NULL || src == NULL || count == 0)   \
		return false;                                                                \
\
	const size_t slots_available = handler->pavailable - handler->_pptr;             \
\
	if (count > slots_available)                                                     \
		count = slots_available;                                                     \
\
	const size_t bytesc = count * nmemb;                                             \
\
	char       *destcurs = (char*) handler->_address;                                \
	const char *srccurs  = (const char*) src;                                        \
\
	size_t i = 0;                                                                    \
\
	for (; i < bytesc; i++, srccurs++, destcurs++)                                   \
		*destcurs = *srccurs;                                                        \
\
	handler->_pptr += i / nmemb;                                                     \
\
	return true

bool _LHASH_InsInt(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsByteByByte(handler, dest, count, sizeof(int));
}
bool _LHASH_InsLong(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsByteByByte(handler, dest, count, sizeof(long));
}
bool _LHASH_InsLLong(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsByteByByte(handler, dest, count, sizeof(long long));
}
bool _LHASH_InsLLLong(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsByteByByte(handler, dest, count, sizeof(lhashint128_t));
}
bool _LHASH_InsShort(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsByteByByte(handler, dest, count, sizeof(short));
}
bool _LHASH_InsChar(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsByteByByte(handler, dest, count, sizeof(char));
}

#define _LHASH_ExtrQWordByQWord(handler, dest, count, nmemb)                         \
	if (handler == NULL || handler->_caddress == NULL || dest == NULL || count == 0) \
		return false;                                                                \
\
	const size_t elements_available = handler->gavailable - handler->_gptr;          \
\
	if (count > elements_available)                                                  \
		count = elements_available;                                                  \
\
	const size_t bytesc = count * nmemb;                                             \
\
	uint64_t       *destcurs = (uint64_t*) dest;                                     \
	const uint64_t *srccurs  = (const uint64_t*) handler->_caddress;                 \
\
	size_t i = 0;                                                                    \
\
	for (; i < bytesc; i++)                                                          \
		destcurs[i] = srccurs[i];                                                    \
\
	handler->_gptr += i / nmemb;                                                     \
\
	return true

bool _LHASH_ExtrHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrQWordByQWord(handler, dest, count, (sizeof(lhashint1024_t) / 8));
}
bool _LHASH_ExtrLHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrQWordByQWord(handler, dest, count, (sizeof(lhashint2048_t) / 8));
}
bool _LHASH_ExtrLLHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrQWordByQWord(handler, dest, count, (sizeof(lhashint4096_t) / 8));
}
bool _LHASH_ExtrHHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrQWordByQWord(handler, dest, count, (sizeof(lhashint512_t) / 8));
}
bool _LHASH_ExtrHHHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_ExtrQWordByQWord(handler, dest, count, (sizeof(lhashint256_t) / 8));
}

#define _LHASH_InsQWordByQWord(handler, src, count, nmemb)                           \
	if (handler == NULL || handler->_address == NULL || src == NULL || count == 0)   \
		return false;                                                                \
\
	const size_t slots_available = handler->pavailable - handler->_pptr;             \
\
	if (count > slots_available)                                                     \
		count = slots_available;                                                     \
\
	const size_t bytesc = count * nmemb;                                             \
\
	uint64_t       *destcurs = (uint64_t*) handler->_address;                        \
	const uint64_t *srccurs  = (const uint64_t*) src;                                \
\
	size_t i = 0;                                                                    \
\
	for (; i < bytesc; i++, srccurs++, destcurs++)                                   \
		*destcurs = *srccurs;                                                        \
\
	handler->_pptr += i / nmemb;                                                     \
\
	return true

bool _LHASH_InsHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsQWordByQWord(handler, dest, count, sizeof(int));
}
bool _LHASH_InsLHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsQWordByQWord(handler, dest, count, sizeof(long));
}
bool _LHASH_InsLLHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsQWordByQWord(handler, dest, count, sizeof(long long));
}
bool _LHASH_InsHHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsQWordByQWord(handler, dest, count, sizeof(short));
}
bool _LHASH_InsHHHash(lhashGTypeHandler *handler, void *const dest, size_t count)
{
	_LHASH_InsQWordByQWord(handler, dest, count, sizeof(char));
}

bool _LHASH_VargFloat(lhashGTypeHandler *handler, va_list ap)
{
	if (handler == NULL || handler->_address == NULL)
		return false;

	float f = va_arg(ap, float);

	return _LHASH_InsFloat(handler, &f, 1);
}
bool _LHASH_ExtrFloat(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	float       *destf = (float*) dest;
	const float *srcf  = (const float*) handler->_caddress;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}
bool _LHASH_InsFloat(lhashGTypeHandler *handler, const void *const src, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	float       *destf = (float*) handler->_address;
	const float *srcf  = (const float*) src;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}

bool _LHASH_VargDouble(lhashGTypeHandler *handler, va_list ap)
{
	if (handler == NULL || handler->_address == NULL)
		return false;

	double d = va_arg(ap, double);

	return _LHASH_InsDouble(handler, &d, 1);
}
bool _LHASH_ExtrDouble(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	double       *destf = (double*) dest;
	const double *srcf  = (const double*) handler->_caddress;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}
bool _LHASH_InsDouble(lhashGTypeHandler *handler, const void *const src, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	double       *destf = (double*) handler->_address;
	const double *srcf  = (const double*) src;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}

bool _LHASH_VargLDouble(lhashGTypeHandler *handler, va_list ap)
{
	if (handler == NULL || handler->_address == NULL)
		return false;

	long double d = va_arg(ap, long double);

	return _LHASH_InsLDouble(handler, &d, 1);
}
bool _LHASH_ExtrLDouble(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	long double       *destf = (long double*) dest;
	const long double *srcf  = (const long double*) handler->_caddress;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}
bool _LHASH_InsLDouble(lhashGTypeHandler *handler, const void *const src, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	long double       *destf = (long double*) handler->_address;
	const long double *srcf  = (const long double*) src;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}

bool _LHASH_VargTime(lhashGTypeHandler *handler, va_list ap)
{
	if (handler == NULL || handler->_address == NULL)
		return false;

	time_t t = va_arg(ap, time_t);

	return _LHASH_InsTime(handler, &t, 1);
}
bool _LHASH_ExtrTime(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	_LHASH_ExtrByteByByte(handler, dest, max, sizeof(time_t));
}
bool _LHASH_InsTime(lhashGTypeHandler *handler, const void *const src, size_t max)
{
	_LHASH_InsByteByByte(handler, src, max, sizeof(time_t));
}

bool _LHASH_VargLTime(lhashGTypeHandler *handler, va_list ap)
{
	if (handler == NULL || handler->_address == NULL)
		return false;

	lhashnseconds_t lt = va_arg(ap, lhashnseconds_t);

	return _LHASH_InsLTime(handler, &lt, 1);
}
bool _LHASH_ExtrLTime(lhashGTypeHandler *handler, void *const dest, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	lhashnseconds_t       *destf = (lhashnseconds_t*) dest;
	const lhashnseconds_t *srcf  = (const lhashnseconds_t*) handler->_caddress;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}
bool _LHASH_InsLTime(lhashGTypeHandler *handler, const void *const src, size_t max)
{
	if (handler == NULL || handler->_caddress == NULL)
		return false;

	const size_t available = handler->gavailable - handler->_gptr;

	if (max > available)
		max = available;

	lhashnseconds_t       *destf = (lhashnseconds_t*) handler->_address;
	const lhashnseconds_t *srcf  = (const lhashnseconds_t*) src;

	size_t i = 0;

	for (; i < max; i++)
		destf[i] = srcf[i];

	return true;
}

#undef _LHASH_VargIntGeneric
#undef _LHASH_ExtrByteByByte
#undef _LHASH_InsByteByByte

/* This structure is used so that attributes for each generalized type signature can be
 * indexed instead of decided from a myriad of comparatively slower comparison operations
 * to implement a branched pattern. */
struct {
	size_t Size
			// Base Type
			[_LHASH_TYPE_END_BASE_TYPES+1]
			// Size Specification
			[(_LHASH_TYPE_SIZESPEC_MASK>>_LHASH_TYPE_SIZESPEC_OFFSET)+1];

	struct _lhashGType_HandlerFunctions_t HandlerFunctions
			// Pointer Qualification
			[(_LHASH_TYPE_PTR_MASK>>_LHASH_TYPE_PTR_OFFSET)+1]
			// Base Type
			[_LHASH_TYPE_END_BASE_TYPES+1]
			// Size Specification
			[(_LHASH_TYPE_SIZESPEC_MASK>>_LHASH_TYPE_SIZESPEC_OFFSET)+1];
} lhashGeneralizedType_Microcode = {
	.Size = { //       Base                      L                         LL                        LLL                       HH                       HH                        HH                        H
		/* VOID     */ {1,                       1,                        1,                        1,                        1,                       1,                        1,                        1             },
		/* INT      */ {sizeof(int),             sizeof(long),             sizeof(long long),        16,                       1,                       1,                        1,                        sizeof(short) },
		/* HASH     */ {128,                     256,                      512,                      512,                      32,                      32,                       32,                       64            },
		/* FLOAT    */ {sizeof(float),           sizeof(double),           sizeof(long double),      sizeof(long double),      sizeof(float),           sizeof(float),            sizeof(float),            sizeof(float) },
		/* TIME     */ {sizeof(time_t),          sizeof(lhashnseconds_t),  sizeof(lhashnseconds_t),  sizeof(lhashnseconds_t),  sizeof(time_t),          sizeof(time_t),           sizeof(time_t),           sizeof(time_t)},
		/* STRUCT   */ {LHASH_TYPE_UNKNOWN_SIZE, LHASH_TYPE_UNKNOWN_SIZE,  LHASH_TYPE_UNKNOWN_SIZE,  LHASH_TYPE_UNKNOWN_SIZE,  LHASH_TYPE_UNKNOWN_SIZE, LHASH_TYPE_UNKNOWN_SIZE,  LHASH_TYPE_UNKNOWN_SIZE,  LHASH_TYPE_UNKNOWN_SIZE},
		/* DATETIME */ {sizeof(lhashdatetime_t), sizeof(lhashldatetime_t), sizeof(lhashldatetime_t), sizeof(lhashldatetime_t), sizeof(lhashdatetime_t), sizeof(lhashldatetime_t), sizeof(lhashldatetime_t), sizeof(lhashldatetime_t)},
		/* FILEPATH */ {0}
	},

	.HandlerFunctions = {
		// For non-pointer types
		{
			/* VOID     */ {0},
			/* INT      */ {
				/* Base */  {.VaArg=_LHASH_VargInt,     .Extract=_LHASH_ExtrInt,     .Insert=_LHASH_InsInt},
				/* L    */  {.VaArg=_LHASH_VargLong,    .Extract=_LHASH_ExtrLong,    .Insert=_LHASH_InsLong},
				/* LL   */  {.VaArg=_LHASH_VargLLong,   .Extract=_LHASH_ExtrLLong,   .Insert=_LHASH_InsLLong},
				/* LLL  */  {.VaArg=_LHASH_VargLLLong,  .Extract=_LHASH_ExtrLLLong,  .Insert=_LHASH_InsLLLong},
				/* HH   */  {.VaArg=_LHASH_VargChar,    .Extract=_LHASH_ExtrChar,    .Insert=_LHASH_InsChar},
				/* HH   */  {.VaArg=_LHASH_VargChar,    .Extract=_LHASH_ExtrChar,    .Insert=_LHASH_InsChar},
				/* HH   */  {.VaArg=_LHASH_VargChar,    .Extract=_LHASH_ExtrChar,    .Insert=_LHASH_InsChar},
				/* H    */  {.VaArg=_LHASH_VargShort,   .Extract=_LHASH_ExtrShort,   .Insert=_LHASH_InsShort}
			},
			/* HASH     */ {
				/* Base */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrHash,    .Insert=_LHASH_InsHash},
				/* L    */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrLHash,   .Insert=_LHASH_InsLHash},
				/* LL   */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrLLHash,  .Insert=_LHASH_InsLLHash},
				/* LLL  */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrLLHash,  .Insert=_LHASH_InsLLHash},
				/* HH   */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrHHHash,  .Insert=_LHASH_InsHHHash},
				/* HH   */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrHHHash,  .Insert=_LHASH_InsHHHash},
				/* HH   */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrHHHash,  .Insert=_LHASH_InsHHHash},
				/* H    */  {.VaArg=_LHASH_VargReject,  .Extract=_LHASH_ExtrHHash,   .Insert=_LHASH_InsHHash}
			},
			/* FLOAT    */ {
				/* Base */  {.VaArg=_LHASH_VargFloat,   .Extract=_LHASH_ExtrFloat,   .Insert=_LHASH_InsFloat},
				/* L    */  {.VaArg=_LHASH_VargDouble,  .Extract=_LHASH_ExtrDouble,  .Insert=_LHASH_InsDouble},
				/* LL   */  {.VaArg=_LHASH_VargLDouble, .Extract=_LHASH_ExtrLDouble, .Insert=_LHASH_InsLDouble},
				/* LLL  */  {.VaArg=_LHASH_VargLDouble, .Extract=_LHASH_ExtrLDouble, .Insert=_LHASH_InsLDouble},
				/* HH   */  {.VaArg=_LHASH_VargFloat,   .Extract=_LHASH_ExtrFloat,   .Insert=_LHASH_InsFloat},
				/* HH   */  {.VaArg=_LHASH_VargFloat,   .Extract=_LHASH_ExtrFloat,   .Insert=_LHASH_InsFloat},
				/* HH   */  {.VaArg=_LHASH_VargFloat,   .Extract=_LHASH_ExtrFloat,   .Insert=_LHASH_InsFloat},
				/* H    */  {.VaArg=_LHASH_VargFloat,   .Extract=_LHASH_ExtrFloat,   .Insert=_LHASH_InsFloat}
			},
			/* TIME     */ {
				/* Base */  {.VaArg=_LHASH_VargTime,    .Extract=_LHASH_ExtrTime,    .Insert=_LHASH_InsTime},
				/* L    */  {.VaArg=_LHASH_VargLTime,   .Extract=_LHASH_ExtrLTime,   .Insert=_LHASH_InsLTime},
				/* LL   */  {.VaArg=_LHASH_VargLTime,   .Extract=_LHASH_ExtrLTime,   .Insert=_LHASH_InsLTime},
				/* LLL  */  {.VaArg=_LHASH_VargLTime,   .Extract=_LHASH_ExtrLTime,   .Insert=_LHASH_InsLTime},
				/* HH   */  {.VaArg=_LHASH_VargTime,    .Extract=_LHASH_ExtrTime,    .Insert=_LHASH_InsTime},
				/* HH   */  {.VaArg=_LHASH_VargTime,    .Extract=_LHASH_ExtrTime,    .Insert=_LHASH_InsTime},
				/* HH   */  {.VaArg=_LHASH_VargTime,    .Extract=_LHASH_ExtrTime,    .Insert=_LHASH_InsTime},
				/* H    */  {.VaArg=_LHASH_VargTime,    .Extract=_LHASH_ExtrTime,    .Insert=_LHASH_InsTime}
			},
			/* STRUCT   */ {
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrReject, .Insert=_LHASH_InsReject}
			},
			/* DATETIME */ {
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrDatetime,  .Insert=_LHASH_InsDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrLDatetime, .Insert=_LHASH_InsLDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrLDatetime, .Insert=_LHASH_InsLDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrLDatetime, .Insert=_LHASH_InsLDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrDatetime,  .Insert=_LHASH_InsDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrDatetime,  .Insert=_LHASH_InsDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrDatetime,  .Insert=_LHASH_InsDatetime},
				{.VaArg=_LHASH_VargReject, .Extract=_LHASH_ExtrDatetime,  .Insert=_LHASH_InsDatetime}
			},
			/* FILEPATH */ {0}
		},
		// For 1st degree pointers (<type>*)
		{
			/* VOID     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* INT      */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* HASH     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* FLOAT    */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* TIME     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* STRUCT   */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* DATETIME */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* FILEPATH */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			}
		},
		// For 2nd degree pointers (<type>**)
		{
			/* VOID     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* INT      */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* HASH     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* FLOAT    */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* TIME     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* STRUCT   */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* DATETIME */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* FILEPATH */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			}
		},
		// For 3rd degree pointers (<type>***)
		{
			/* VOID     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* INT      */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* HASH     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* FLOAT    */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* TIME     */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* STRUCT   */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* DATETIME */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			},
			/* FILEPATH */ {
				/* Base */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* L    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LL   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* LLL  */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* HH   */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr},
				/* H    */  {.VaArg=_LHASH_VargPtr,     .Extract=_LHASH_ExtrPtr,     .Insert=_LHASH_InsPtr}
			}
		}
	}
};


LHASH_API lhashuint128_t lhashNanosecsToMicrosecs(lhashnseconds_t *self)
{
	lhashuint128_t v = lhashuint128(self->s);

	lhashuint128_multleq(&v, 1000ul);

	lhashuint128_addleq(&v, (long) (self->ns / 1000));

	return v;
}
LHASH_API lhashuint128_t lhashNanosecsToInt128(lhashnseconds_t *self)
{
	if (self == NULL)
		return lhashint128_0;
	lhashuint128_t v = lhashuint128(self->s);

	lhashuint128_multleq(&v, 1000000ul);

	lhashuint128_addleq(&v, (long) self->ns);

	return v;
}


LHASH_API lhashldatetime_t  lhashldatetime(lhashnseconds_t t)
{
	lhashldatetime_t dt;

	dt.time = t;

	localtime_r(&t.s, &dt.timeinfo);

	return dt;
}
LHASH_API lhashldatetime_t* lhashldatetime_init(lhashldatetime_t *self, lhashnseconds_t t)
{
	if (self == NULL)
		return NULL;
	
	self->time = t;

	localtime_r(&t.s, &self->timeinfo);

	return self;
}


LHASH_API size_t lhashGeneralizedType_Sizeof(lhashGeneralizedType t)
{
	return
		(((t & _LHASH_TYPE_PTR_MASK) >> _LHASH_TYPE_PTR_OFFSET) != 0)?            // if ptr qualification,
			sizeof(void*) :                                                       // use size of a pointer
			lhashGeneralizedType_Microcode.Size
				[(t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET]          // else, locate the size for
				[(t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET]; // the given base type and size specifier
}
LHASH_API int lhashGeneralizedType_BaseType(lhashGeneralizedType t)
{
	return (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;
}
LHASH_API int lhashGeneralizedType_PointerDegree(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_PTR_MASK) >> _LHASH_TYPE_PTR_OFFSET);
}
LHASH_API bool lhashGeneralizedType_IsConst(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_CONST) != 0;
}
LHASH_API bool lhashGeneralizedType_IsNonConst(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_CONST) == 0;
}
LHASH_API bool lhashGeneralizedType_IsVolatile(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_VOLATILE) != 0;
}
LHASH_API bool lhashGeneralizedType_IsNonvolatile(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_VOLATILE) == 0;
}
LHASH_API bool lhashGeneralizedType_IsCVUnqualified(lhashGeneralizedType t)
{
	return ((t & LHASH_TYPE_CONST) == 0) || ((t & LHASH_TYPE_VOLATILE) == 0);
}
LHASH_API bool lhashGeneralizedType_IsCVQualified(lhashGeneralizedType t)
{
	return ((t & LHASH_TYPE_CONST) != 0) && ((t & LHASH_TYPE_VOLATILE) != 0);
}
LHASH_API bool lhashGeneralizedType_IsRef(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_REF) != 0;
}
LHASH_API bool lhashGeneralizedType_IsNotRef(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_REF) == 0;
}
LHASH_API bool lhashGeneralizedType_IsPrimitive(lhashGeneralizedType t)
{
	uint32_t base = (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;

	return base >= _LHASH_TYPE_BEG_PRIMITIVES && base <= _LHASH_TYPE_END_PRIMITIVES;
}
LHASH_API bool lhashGeneralizedType_IsNotPrimitive(lhashGeneralizedType t)
{
	uint32_t base = (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;

	return base < _LHASH_TYPE_BEG_PRIMITIVES || base > _LHASH_TYPE_BEG_PRIMITIVES;
}
LHASH_API bool lhashGeneralizedType_IsTruePrimitive(lhashGeneralizedType t)
{
	uint32_t base = (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;

	return base >= _LHASH_TYPE_BEG_PRIMITIVES && base <= _LHASH_TYPE_END_PRIMITIVES && base != LHASH_TYPE_HASH;
}
LHASH_API bool lhashGeneralizedType_IsNotTruePrimitive(lhashGeneralizedType t)
{
	uint32_t base = (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;

	return base < _LHASH_TYPE_BEG_PRIMITIVES || base > _LHASH_TYPE_BEG_PRIMITIVES || base == LHASH_TYPE_HASH;
}
LHASH_API bool lhashGeneralizedType_IsNotNull(lhashGeneralizedType t)
{
	// A type is not-null if:
	//    1) It contains the NOTNULL bit.
	//    2) It is a reference (contains the REF bit).
	//    3) It is a struct (and not a pointer to a struct)
	return
		// t indicates NOTNULL or,
		(t & LHASH_TYPE_NOTNULL) != 0 ||
		// t indicates REF or,
		(t & LHASH_TYPE_REF) != 0 ||
		// t is indicates a struct and not a pointer to a struct
		(
			( (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET ) == LHASH_TYPE_STRUCT &&
			( (t & _LHASH_TYPE_PTR_MASK)  >> _LHASH_TYPE_PTR_OFFSET  ) == 0
		);
}
LHASH_API bool lhashGeneralizedType_IsNullable(lhashGeneralizedType t)
{
	// opposite condition to IsNotNull()
	return
		(t & LHASH_TYPE_NOTNULL) == 0 &&
		(t & LHASH_TYPE_REF)     == 0 &&
		(
			( (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET ) != LHASH_TYPE_STRUCT ||
			( (t & _LHASH_TYPE_PTR_MASK)  >> _LHASH_TYPE_PTR_OFFSET  ) != 0
		);
}
LHASH_API bool lhashGeneralizedType_IsIntegral(lhashGeneralizedType t)
{
	uint32_t base = (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;

	return base >= _LHASH_TYPE_END_INTEGRALS && base <= _LHASH_TYPE_END_INTEGRALS && base != LHASH_TYPE_HASH;
}
LHASH_API bool lhashGeneralizedType_IsNotIntegral(lhashGeneralizedType t)
{
	uint32_t base = (t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET;

	return base < _LHASH_TYPE_END_INTEGRALS || base > _LHASH_TYPE_END_INTEGRALS || base == LHASH_TYPE_HASH;
}
LHASH_API bool lhashGeneralizedType_IsFloatingPoint(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET) == LHASH_TYPE_FLOAT;
}
LHASH_API bool lhashGeneralizedType_IsNotFloatingPoint(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET) != LHASH_TYPE_FLOAT;
}
LHASH_API bool lhashGeneralizedType_IsStruct(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET) == LHASH_TYPE_STRUCT;
}
LHASH_API bool lhashGeneralizedType_IsNotStruct(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET) != LHASH_TYPE_STRUCT;
}
LHASH_API bool lhashGeneralizedType_IsPointer(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_PTR_MASK) >> _LHASH_TYPE_PTR_OFFSET) != 0;
}
LHASH_API bool lhashGeneralizedType_IsNotPointer(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_PTR_MASK) >> _LHASH_TYPE_PTR_OFFSET) == 0;
}
LHASH_API bool lhashGeneralizedType_HasSizeSpecifier(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET) != 0;
}
LHASH_API bool lhashGeneralizedType_NoSizeSpecifier(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET) == 0;
}
LHASH_API bool lhashGeneralizedType_IsLong(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET) == LHASH_TYPE_LQUAL;
}
LHASH_API bool lhashGeneralizedType_IsLLong(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET) == LHASH_TYPE_LLQUAL;
}
LHASH_API bool lhashGeneralizedType_IsLLLong(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET) == LHASH_TYPE_LLLQUAL;
}
LHASH_API bool lhashGeneralizedType_IsShort(lhashGeneralizedType t)
{
	return ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET) == LHASH_TYPE_HQUAL;
}
LHASH_API bool lhashGeneralizedType_IsHShort(lhashGeneralizedType t)
{
	const uint32_t sizespec = ((t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET);

	return sizespec <= LHASH_TYPE_HHQUAL && sizespec > LHASH_TYPE_LLLQUAL;
}
LHASH_API bool lhashGeneralizedType_IsSigned(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_UNSIGNED) == 0;
}
LHASH_API bool lhashGeneralizedType_IsUnsigned(lhashGeneralizedType t)
{
	return (t & LHASH_TYPE_UNSIGNED) != 0;
}

LHASH_API const struct _lhashGType_HandlerFunctions_t* lhashGType_GetHandlerFunctions(lhashGType t)
{
	return &lhashGeneralizedType_Microcode.HandlerFunctions
			[(t & _LHASH_TYPE_PTR_MASK) >> _LHASH_TYPE_PTR_OFFSET]
			[(t & _LHASH_TYPE_BASE_MASK) >> _LHASH_TYPE_BASE_OFFSET]
			[(t & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET];
}

LHASH_API bool lhashGeneralizedType_EffectiveAs(lhashGeneralizedType a, lhashGeneralizedType b)
{
	struct {
		const uint32_t base_type, ptr_qual, size_spec;
	} A = {
		.base_type = (a & _LHASH_TYPE_BASE_MASK)     >> _LHASH_TYPE_BASE_OFFSET,
		.ptr_qual  = (a & _LHASH_TYPE_PTR_MASK)      >> _LHASH_TYPE_PTR_OFFSET,
		.size_spec = (a & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET
	}, B = {
		.base_type = (b & _LHASH_TYPE_BASE_MASK)     >> _LHASH_TYPE_BASE_OFFSET,
		.ptr_qual  = (b & _LHASH_TYPE_PTR_MASK)      >> _LHASH_TYPE_PTR_OFFSET,
		.size_spec = (b & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET
	};

	bool result = true;

	if (B.ptr_qual != 0)
		result &=
			(
				( // B and A are the same exact kind of pointer, or
					B.ptr_qual  == A.ptr_qual  &&
					B.base_type == A.base_type &&
					B.size_spec == A.size_spec
				) ||
				// A is void*, or
				(A.base_type == LHASH_TYPE_VOID && A.ptr_qual == 1) ||
				// B is void*
				(B.base_type == LHASH_TYPE_VOID && B.ptr_qual == 1)
			) && // and either...
			(
				/* |  b is const  |  a is const  |  b is const or a is not const  |  if b is not const, a cannot be const  |
				 * |--------------+--------------+--------------------------------+----------------------------------------+
				 * |     T        |      T       |           T                    |                T                       |
				 * |     T        |      F       |           T                    |                T                       |
				 * |     F        |      T       |           F                    |                F                       |
				 * |     F        |      F       |           T                    |                T                       |
				 */
				// This condition affirms that a const ptr is never casted to a nonconst ptr,
				// if a is casted to b when b is nonconst but a is const, this would occur.
				(b & LHASH_TYPE_CONST) != 0 ||
				(b & LHASH_TYPE_CONST) == 0
			);
	else switch (B.base_type) {

	}
}

LHASH_API bool lhashGeneralizedType_VaArg(lhashGTypeHandler *output_handler, va_list ap)
{
	if (output_handler == NULL)
		return false;

	const lhashGeneralizedType gtype = output_handler->gtype.gtype;


	const int
		base_type = (gtype & _LHASH_TYPE_BASE_MASK)     >> _LHASH_TYPE_BASE_OFFSET, 
		ptr_qual  = (gtype & _LHASH_TYPE_PTR_MASK)      >> _LHASH_TYPE_PTR_OFFSET,
		size_spec = (gtype & _LHASH_TYPE_SIZESPEC_MASK) >> _LHASH_TYPE_SIZESPEC_OFFSET;


	const bool is_unsigned = gtype & LHASH_TYPE_UNSIGNED != 0;


	// non-primitive values cannot be pulled from va_list.
	if ((base_type < _LHASH_TYPE_BEG_PRIMITIVES || base_type > _LHASH_TYPE_END_PRIMITIVES) && ptr_qual == 0)
		return false;

	return lhashGeneralizedType_Microcode.HandlerFunctions[ptr_qual][base_type][size_spec].VaArg(output_handler, ap);
}


/* struct _lhashGeneralizedCompleteType */
lhashGCompleteType  lhashGCompleteType_Make(lhashGType t)
{
	return (lhashGCompleteType) {
		.gtype=t,
		.sizeof_type=lhashGType_Sizeof(t),
		._handlerfuncs=lhashGType_GetHandlerFunctions(t)
	};
}
lhashGCompleteType  lhashGCompleteType_MakeF(lhashGType t, const struct _lhashGType_HandlerFunctions_t *handler_functions)
{
	return (lhashGCompleteType) {
		.gtype=t,
		.sizeof_type=lhashGType_Sizeof(t),
		._handlerfuncs=handler_functions
	};
}
lhashGCompleteType  lhashGCompleteType_MakeS(size_t struct_size)
{
	return (lhashGCompleteType) {
		.gtype=LHASH_TYPE_STRUCT,
		.sizeof_type=struct_size,
		._handlerfuncs=&lhashGeneralizedType_Microcode.HandlerFunctions[0][LHASH_TYPE_STRUCT][0]
	};
}
lhashGCompleteType  lhashGCompleteType_MakeSf(size_t struct_size, const struct _lhashGType_HandlerFunctions_t *handler_functions)
{
	return (lhashGCompleteType) {
		.gtype=LHASH_TYPE_STRUCT,
		.sizeof_type=struct_size,
		._handlerfuncs=handler_functions
	};
}

lhashGCompleteType* lhashGCompleteType_Init(lhashGCompleteType *self, lhashGType t)
{
	if (self == NULL)
		return NULL;

	self->gtype = t;
	self->sizeof_type = lhashGType_Sizeof(t);
	self->_handlerfuncs = lhashGType_GetHandlerFunctions(t);

	return self;
}
lhashGCompleteType* lhashGCompleteType_InitF(lhashGCompleteType *self, lhashGType t, const struct _lhashGType_HandlerFunctions_t *handler_functions)
{
	if (self == NULL)
		return NULL;

	self->gtype = t;
	self->sizeof_type = lhashGType_Sizeof(t);
	self->_handlerfuncs = handler_functions;

	return self;
}
lhashGCompleteType* lhashGCompleteType_InitS(lhashGCompleteType *self, size_t struct_size)
{
	if (self == NULL)
		return NULL;

	self->gtype = LHASH_TYPE_STRUCT;
	self->sizeof_type = struct_size;
	self->_handlerfuncs = &lhashGeneralizedType_Microcode.HandlerFunctions[0][LHASH_TYPE_STRUCT][0];

	return self;
}
lhashGCompleteType* lhashGCompleteType_InitSf(lhashGCompleteType *self, size_t struct_size, const struct _lhashGType_HandlerFunctions_t *handler_functions)
{
	if (self == NULL)
		return NULL;

	self->gtype = LHASH_TYPE_STRUCT;
	self->sizeof_type = struct_size;
	self->_handlerfuncs = handler_functions;

	return self;
}


/* struct _lhashGTypeHandler */
LHASH_API lhashGTypeHandler  lhashGTypeHandler_MakeOutput(
	lhashGeneralizedType gtype,
	const void    *const address,
	size_t               amount_available
){
	return (lhashGTypeHandler) {
		._address   = NULL,
		._caddress  = address,
		.gavailable = amount_available,
		.pavailable = 0,
		._gptr      = 0,
		._pptr      = 0,
		.gtype      = gtype
	};
}
LHASH_API lhashGTypeHandler  lhashGTypeHandler_MakeInput(
	lhashGeneralizedType gtype,
	void          *const address,
	size_t               insertion_limit
){
	return (lhashGTypeHandler) {
		._address   = address,
		._caddress  = NULL,
		.gavailable = 0,
		.pavailable = insertion_limit,
		._gptr      = 0,
		._pptr      = 0,
		.gtype      = gtype
	};
}
LHASH_API lhashGTypeHandler  lhashGTypeHandler_MakeIO(
	lhashGeneralizedType gtype,
	void          *const input_dest_address,
	size_t               extraction_limit,
	const void    *const output_src_address,
	size_t               insertion_limit
){
	return (lhashGTypeHandler) {
		._address   = input_dest_address,
		._caddress  = output_src_address,
		.gavailable = extraction_limit,
		.pavailable = insertion_limit,
		._gptr      = 0,
		._pptr      = 0,
		.gtype      = gtype
	};
}

LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitOutput(
	lhashGTypeHandler *self,
	lhashGeneralizedType         gtype,
	const void            *const address,
	size_t                       amount_available
){
	if (self == NULL)
		return NULL;

	self->_address   = NULL;
	self->_caddress  = address;
	self->gavailable = amount_available;
	self->pavailable = 0;
	self->_gptr      = 0;
	self->_pptr      = 0;
	self->gtype.gtype      = gtype;

	return self;
}
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitInput(
	lhashGTypeHandler *self,
	lhashGeneralizedType         gtype,
	void                  *const address,
	size_t                       insertion_limit
){
	if (self == NULL)
		return NULL;

	self->_address   = address;
	self->_caddress  = NULL;
	self->gavailable = 0;
	self->pavailable = insertion_limit;
	self->_gptr      = 0;
	self->_pptr      = 0;
	self->gtype.gtype      = gtype;

	return self;
}
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitIO(
	lhashGTypeHandler *self,
	lhashGeneralizedType         gtype,
	void                  *const input_dest_address,
	size_t                       extraction_limit,
	const void            *const output_src_address,
	size_t                       insertion_limit
){
	if (self == NULL)
		return NULL;

	self->_address   = input_dest_address;
	self->_caddress  = output_src_address;
	self->gavailable = extraction_limit;
	self->pavailable = insertion_limit;
	self->_gptr      = 0;
	self->_pptr      = 0;
	self->gtype.gtype      = gtype;

	return self;
}

LHASH_API void lhashGTypeHandler_SetExtractionLocation(
	lhashGTypeHandler *self,
	const void *const address, size_t limit
){
	if (self == NULL)
		return;

	self->_caddress  = address;
	self->gavailable = limit;
}
LHASH_API void lhashGTypeHandler_SetInsertionLocation(
	lhashGTypeHandler *self,
	void *const address, size_t limit
){
	if (self == NULL)
		return;

	self->_address   = address;
	self->pavailable = limit;
}
LHASH_API void lhashGTypeHandler_SetType(lhashGTypeHandler *self, lhashGeneralizedType gtype)
{
	if (self != NULL)
		self->gtype.gtype = gtype;
}

LHASH_API const void* lhashGTypeHandler_GetExtractionAddress(const lhashGTypeHandler *self)
{
	return (self == NULL)? NULL : self->_caddress;
}
LHASH_API void* lhashGTypeHandler_GetInsertionAddress(const lhashGTypeHandler *self)
{
	return (self == NULL)? NULL : self->_address;
}
LHASH_API size_t lhashGTypeHandler_BytesAvailable(const lhashGTypeHandler *self)
{
	return (self == NULL)? 0 : self->gavailable;
}
LHASH_API size_t lhashGTypeHandler_GetInsertionLimit(const lhashGTypeHandler *self)
{
	return (self == NULL)? 0 : self->pavailable;
}
LHASH_API lhashGeneralizedType lhashGTypeHandler_GetType(const lhashGTypeHandler *self)
{
	return (self == NULL)? LHASH_TYPE_VOID : self->gtype.gtype;
}

LHASH_API size_t lhashGTypeHandler_SeekG(lhashGTypeHandler *self, size_t pos)
{
	if (self == NULL)
		return 0;
	else if (pos > self->gavailable)
		return self->_gptr = self->gavailable;
	else
		return self->_gptr = pos;
}
LHASH_API size_t lhashGTypeHandler_SeekP(lhashGTypeHandler *self, size_t pos)
{
	if (self == NULL)
		return 0;
	else if (pos > self->pavailable)
		return self->_pptr = self->pavailable;
	else
		return self->_pptr = pos;
}
LHASH_API size_t lhashGTypeHandler_RelSeekG(lhashGTypeHandler *self, ssize_t pos)
{
	size_t abs;

	if (self == NULL)
		return 0;
	else if (pos == 0)
		return self->_gptr;
	else if (pos < 0) {
		abs = (size_t) (-pos);
		if (abs >= self->_gptr)
			return self->_gptr = 0;
		else
			return self->_gptr -= abs;
	} else {
		abs = self->_gptr + pos;

		if (abs >= self->gavailable)
			return self->_gptr = self->gavailable;
		else
			return self->_gptr = abs;
	}
}
LHASH_API size_t lhashGTypeHandler_RelSeekP(lhashGTypeHandler *self, ssize_t pos)
{
	size_t abs;

	if (self == NULL)
		return 0;
	else if (pos == 0)
		return self->_pptr;
	else if (pos < 0) {
		abs = (size_t) (-pos);
		if (abs >= self->_pptr)
			return self->_pptr = 0;
		else
			return self->_pptr -= abs;
	} else {
		abs = self->_pptr + pos;

		if (abs >= self->pavailable)
			return self->_pptr = self->pavailable;
		else
			return self->_pptr = abs;
	}
}
LHASH_API size_t lhashGTypeHandler_TellG(lhashGTypeHandler *self)
{
	if (self == NULL)
		return 0;
	else
		return self->_gptr;
}
LHASH_API size_t lhashGTypeHandler_TellP(lhashGTypeHandler *self)
{
	if (self == NULL)
		return 0;
	else
		return self->_pptr;
}

LHASH_API size_t lhashGTypeHandler_Extract(
	lhashGTypeHandler *self,
	void *const to, size_t max
){
	if (self == NULL)
		return 0;

	size_t gptr = self->_gptr;

	const bool result = self->gtype._handlerfuncs->Extract(self, to, max);

	return result? 0 : (self->_gptr - gptr);
}
LHASH_API size_t lhashGTypeHandler_Insert(
	lhashGTypeHandler *self,
	const void *const from, size_t max
){
	if (self == NULL)
		return 0;

	size_t pptr = self->_pptr;

	const bool result = self->gtype._handlerfuncs->Insert(self, from, max);

	return result? 0 : (self->_pptr - pptr);
}

LHASH_API bool lhashGTypeHandler_InsertionEnabled(const lhashGTypeHandler *self)
{
	return self != NULL && self->_address != NULL;
}
LHASH_API bool lhashGTypeHandler_ExtractionEnabled(const lhashGTypeHandler *self)
{
	return self != NULL && self->_caddress != NULL;
}
LHASH_API bool lhashGTypeHandler_FullIOEnabled(const lhashGTypeHandler *self)
{
	return self != NULL && self->_address != NULL && self->_caddress != NULL;
}

LHASH_API bool lhashGTypeHandler_InvalidConfiguration(const lhashGTypeHandler *self, bool log_errors)
{
	static const char ERRNAME[]  = "InvalidObjectError<lhashables::GTypeHandler>";
	static const char FUNCNAME[] = "lhashGTypeHandler_InvalidConfiguration";

	bool result = self != NULL;

	if (log_errors && !result)
		lhashThrowFne(
			ERRNAME,
			"Null pointer passed to function call.",
			FUNCNAME,
			lhashGTypeHandler_InvalidConfiguration,
			1
		);

	result &= self->_gptr <= self->gavailable;
	if (log_errors && !result)
		lhashThrowFne(
			ERRNAME,
			"Get pointer moved beyond extraction limit.",
			FUNCNAME,
			lhashGTypeHandler_InvalidConfiguration,
			2
		);

	result &= self->_pptr <= self->pavailable;
	if (log_errors && !result)
		lhashThrowFne(
			ERRNAME,
			"Put pointer moved beyond insertion limit.",
			FUNCNAME,
			lhashGTypeHandler_InvalidConfiguration,
			3
		);

	

	return result;
}
