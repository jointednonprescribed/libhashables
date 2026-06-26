
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

/* Extended integer types */
#ifndef _LHASHABLES__types_EXT_INT_H_
#   include "types/ext-int.h"
#endif


LHASH_EXTERN_C


/* Extended time types */
typedef struct LHASH_API _lhashnseconds_t
{
    time_t   s;
    uint32_t ns;
} lhashnseconds_t;

LHASH_API lhashuint128_t lhashNanosecsToMicrosecs(lhashnseconds_t *self);
LHASH_API lhashuint128_t lhashNanosecsToInt128(lhashnseconds_t *self);


/* Standard date and time type. */
typedef struct tm lhashdatetime_t;

/* Extra long date and time type (date and time + nanoseconds). */
typedef struct LHASH_API _lhashldatetime_t
{
    struct tm timeinfo;

    lhashnseconds_t time;
} lhashldatetime_t;

LHASH_API lhashldatetime_t  lhashldatetime(lhashnseconds_t t);
LHASH_API lhashldatetime_t* lhashldatetime_init(lhashldatetime_t *self, lhashnseconds_t t);


/*
 * A structure type which is used by API elements to handle values of variable types.
 */
struct _lhashGType_HandlerFunctions_t
{
	bool (*Insert)(lhashGeneralizedTypeHandler *handler, const void *const src, size_t max_elements);
	bool (*Extract)(lhashGeneralizedTypeHandler *handler, void *const dest, size_t max_elements);
	bool (*VaArg)(lhashGeneralizedTypeHandler *handler, va_list ap);
};

/*
 * A structure type for handling the process of streaming data of varying possible
 * types on runtime using lhashGType as an indicator type. These structures
 * act as a "view" of some variable stored static storage (or local storage if the
 * function they are local to always ends after the view is done being used). 
 */
typedef struct LHASH_API _lhashGTypeHandler lhashGeneralizedTypeHandler, lhashGTypeHandler;

/*
 * An enumeration for the generalized type descriptors.
 */
enum _lhashGType
{
    LHASH_TYPE_INDETERMINATE_SIZE = -1,
    LHASH_TYPE_UNKNOWN_SIZE       = LHASH_TYPE_INDETERMINATE_SIZE,

    /*                                  17   15  13   11  9
     *                                     16  14   12  10   8 7 6 5  4 3 2 1
     * 0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0
     *                                  N  V C R *  ^ U L ^  ^ D ^ ^  ^ ^ ^ ^
     */

    // The first 7 bits of the enumeration are the generalized type descriptor,
    // the rest are used for indication of various supported specifiers.
    LHASH_TYPE_VOID = 0,
    LHASH_TYPE_INT,
    LHASH_TYPE_HASH,
    LHASH_TYPE_FLOAT,
    LHASH_TYPE_TIME,     // refers to time_t in <ctime> or <time.h>
    LHASH_TYPE_STRUCT,
    LHASH_TYPE_DATETIME, // refers to struct tm in <ctime> or <time.h>
    LHASH_TYPE_FILEPATH, // refers to lhashFilepath in "lhash/pathapi.h"

    // Upper and lower limits of the "integral" base types.
    _LHASH_TYPE_BEG_INTEGRALS  = LHASH_TYPE_INT,
    _LHASH_TYPE_END_INTEGRALS  = LHASH_TYPE_HASH,
    // Upper and lower limits of the "primitive" base types.
    // True primitive base types would exclude LHASH_TYPE_HASH.
    _LHASH_TYPE_BEG_PRIMITIVES = LHASH_TYPE_VOID,
    _LHASH_TYPE_END_PRIMITIVES = LHASH_TYPE_TIME,
    // The upper bound of the base types.
    _LHASH_TYPE_END_BASE_TYPES = LHASH_TYPE_FILEPATH,

    _LHASH_TYPE_BASE_MASK      = 0x7f,
    _LHASH_TYPE_BASE_OFFSET    = 0,

    // Bits used for long qualification are bits 8-10
    LHASH_TYPE_LQUAL    = 01 << 7,
    LHASH_TYPE_LLQUAL   = 02 << 7,
    LHASH_TYPE_LLLQUAL  = 03 << 7,
    LHASH_TYPE_HQUAL    = 07 << 7,
    LHASH_TYPE_HHQUAL   = 06 << 7,

    _LHASH_TYPE_SIZESPEC_MASK   = 07 << 7,
    _LHASH_TYPE_SIZESPEC_OFFSET = 7,

    // The bit used for "unsigned" qualification is bit 11
    LHASH_TYPE_UNSIGNED = 1 << 10,

    // The bits used for pointer qualification are bits 12 and 13
    LHASH_TYPE_PTR        = 1 << 11,
    LHASH_TYPE_PTR_SQUARE = 2 << 11,
    LHASH_TYPE_PTR_CUBIC  = 3 << 11,
    LHASH_TYPE_PTR_2      = LHASH_TYPE_PTR_SQUARE,
    LHASH_TYPE_PTR_3      = LHASH_TYPE_PTR_CUBIC,

    _LHASH_TYPE_PTR_MASK   = 03 << 11,
    _LHASH_TYPE_PTR_OFFSET = 11,

    // Bit 14 qualifies a pointer type as a reference (cannot be null, provides
    // direct access, not reassignable) to it's selected type, a multidimensional
    // pointer becomes a reference-to-pointer. This bit is ignored if the type is
    // not a pointer.
    LHASH_TYPE_REF        = 1 << 13,

    // Bit 15 qualifies a type (or in the case of a pointer type, this will be the
    // content type itself, even if that is another pointer type) as const, and will
    // not be modifiable.
    LHASH_TYPE_CONST      = 1 << 14,

    // Bit 16 qualifies a type (or in the case of a pointer type, this will be the
    // content type itself, even if that is another pointer type) as volatile, and
    // will not be saved and reused, instead its value will be updated at each use.
    LHASH_TYPE_VOLATILE   = 1 << 15,

    // Bit 17 qualifies a type as non-nullable (for pointers, this is the memory address
    // itself, not the content type).
    LHASH_TYPE_NOTNULL    = 1 << 16,

    LHASH_TYPE_CV         = LHASH_TYPE_CONST | LHASH_TYPE_VOLATILE,

    /* Built-in type descriptors. */
    LHASH_TYPE_DOUBLE     = LHASH_TYPE_FLOAT | LHASH_TYPE_LQUAL,
    LHASH_TYPE_LDOUBLE    = LHASH_TYPE_FLOAT | LHASH_TYPE_LLQUAL,
    LHASH_TYPE_LONG       = LHASH_TYPE_INT   | LHASH_TYPE_LQUAL,
    LHASH_TYPE_LLONG      = LHASH_TYPE_INT   | LHASH_TYPE_LLQUAL,
    LHASH_TYPE_INT128     = LHASH_TYPE_INT   | LHASH_TYPE_LLLQUAL,
    LHASH_TYPE_ULONG      = LHASH_TYPE_INT   | LHASH_TYPE_LQUAL   | LHASH_TYPE_UNSIGNED,
    LHASH_TYPE_ULLONG     = LHASH_TYPE_INT   | LHASH_TYPE_LLQUAL  | LHASH_TYPE_UNSIGNED,
    LHASH_TYPE_UINT128    = LHASH_TYPE_INT   | LHASH_TYPE_LLLQUAL | LHASH_TYPE_UNSIGNED,
};
typedef uint32_t lhashGeneralizedType, lhashGType;

LHASH_API size_t lhashGType_Sizeof(lhashGType t);
LHASH_API int    lhashGType_BaseType(lhashGType t);
LHASH_API int    lhashGType_PointerDegree(lhashGType t);
LHASH_API bool   lhashGType_IsConst(lhashGType t);
LHASH_API bool   lhashGType_IsNonConst(lhashGType t);
LHASH_API bool   lhashGType_IsVolatile(lhashGType t);
LHASH_API bool   lhashGType_IsNonVolatile(lhashGType t);
LHASH_API bool   lhashGType_IsCVUnqualified(lhashGType t);
LHASH_API bool   lhashGType_IsCVQualified(lhashGType t);
LHASH_API bool   lhashGType_IsRef(lhashGType t);
LHASH_API bool   lhashGType_IsNotRef(lhashGType t);
LHASH_API bool   lhashGType_IsTruePrimitive(lhashGType t);
LHASH_API bool   lhashGType_IsNotTruePrimitive(lhashGType t);
LHASH_API bool   lhashGType_IsPrimitive(lhashGType t);
LHASH_API bool   lhashGType_IsNotPrimitive(lhashGType t);
LHASH_API bool   lhashGType_IsNotNull(lhashGType t);
LHASH_API bool   lhashGType_IsNullable(lhashGType t);
LHASH_API bool   lhashGType_IsIntegral(lhashGType t);
LHASH_API bool   lhashGType_IsNotIntegral(lhashGType t);
LHASH_API bool   lhashGType_IsFloatingPoint(lhashGType t);
LHASH_API bool   lhashGType_IsNotFloatingPoint(lhashGType t);
LHASH_API bool   lhashGType_IsStruct(lhashGType t);
LHASH_API bool   lhashGType_IsNotStruct(lhashGType t);
LHASH_API bool   lhashGType_IsPointer(lhashGType t);
LHASH_API bool   lhashGType_IsNotPointer(lhashGType t);
LHASH_API bool   lhashGType_HasSizeSpecifier(lhashGType t);
LHASH_API bool   lhashGType_NoSizeSpecifier(lhashGType t);
LHASH_API bool   lhashGType_IsLong(lhashGType t);
LHASH_API bool   lhashGType_IsLLong(lhashGType t);
LHASH_API bool   lhashGType_IsLLLong(lhashGType t);
LHASH_API bool   lhashGType_IsShort(lhashGType t);
LHASH_API bool   lhashGType_IsHShort(lhashGType t);
LHASH_API bool   lhashGType_IsSigned(lhashGType t);
LHASH_API bool   lhashGType_IsUnsigned(lhashGType t);

LHASH_API const struct _lhashGType_HandlerFunctions_t* lhashGType_GetHandlerFunctions(lhashGType t);

// Check if type a is effective as (assignable to) type b.
LHASH_API bool   lhashGType_EffectiveAs(lhashGType a, lhashGType b);

LHASH_API bool   lhashGType_VaArg(lhashGTypeHandler *output_handler, va_list ap);


/*
 * A structure type for wrapping all necessary type information, even for handling
 * non-primitive types.
 */
typedef struct LHASH_API _lhashGeneralizedCompleteType
{
    lhashGType                                    gtype;
    size_t                                        sizeof_type;
    const struct _lhashGType_HandlerFunctions_t *_handlerfuncs;
} lhashGeneralizedCompleteType, lhashGCompleteType;

lhashGCompleteType  lhashGCompleteType_Make(lhashGType t);
lhashGCompleteType  lhashGCompleteType_MakeF(lhashGType t, const struct _lhashGType_HandlerFunctions_t *handler_functions);
lhashGCompleteType  lhashGCompleteType_MakeS(size_t struct_size);
lhashGCompleteType  lhashGCompleteType_MakeSf(size_t struct_size, const struct _lhashGType_HandlerFunctions_t *handler_functions);

lhashGCompleteType* lhashGCompleteType_Init(lhashGCompleteType *self, lhashGType t);
lhashGCompleteType* lhashGCompleteType_InitF(lhashGCompleteType *self, lhashGType t, const struct _lhashGType_HandlerFunctions_t *handler_functions);
lhashGCompleteType* lhashGCompleteType_InitS(lhashGCompleteType *self, size_t struct_size);
lhashGCompleteType* lhashGCompleteType_InitSf(lhashGCompleteType *self, size_t struct_size, const struct _lhashGType_HandlerFunctions_t *handler_functions);


/*
 * Implementation for struct _lhashGTypeHandler.
 */
struct LHASH_API _lhashGTypeHandler
{
    void               *_paddr;
    const void         *_gaddr;
    size_t               gavailable, pavailable, _gptr, _pptr;
    lhashGCompleteType   gtype;
};

#define lhashGTypeHandler_Make lhashGTypeHandler_MakeOutput
LHASH_API lhashGTypeHandler  lhashGTypeHandler_MakeOutput(
    lhashGType gtype,
    const void    *const address,
    size_t               amount_available
);
LHASH_API lhashGTypeHandler  lhashGTypeHandler_MakeInput(
    lhashGType gtype,
    void          *const address,
    size_t               insertion_limit
);
LHASH_API lhashGTypeHandler  lhashGTypeHandler_MakeIO(
    lhashGType gtype,
    void          *const input_dest_address,
    size_t               extraction_limit,
    const void    *const output_src_address,
    size_t               insertion_limit
);

#define lhashGTypeHandler_Init lhashGTypeHandler_InitOutput
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitOutput(
    lhashGTypeHandler *self,
    lhashGCompleteType gtype,
    const void  *const address,
    size_t             amount_available
);
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitInput(
    lhashGTypeHandler *self,
    lhashGCompleteType gtype,
    void        *const address,
    size_t             insertion_limit
);
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitIO(
    lhashGTypeHandler *self,
    lhashGCompleteType gtype,
    void        *const input_dest_address,
    size_t             extraction_limit,
    const void  *const output_src_address,
    size_t             insertion_limit
);
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitOutputT(
    lhashGTypeHandler *self,
    lhashGType         gtype,
    const void  *const address,
    size_t             amount_available
);
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitInputT(
    lhashGTypeHandler *self,
    lhashGType         gtype,
    void        *const address,
    size_t             insertion_limit
);
LHASH_API lhashGTypeHandler* lhashGTypeHandler_InitIOt(
    lhashGTypeHandler *self,
    lhashGType         gtype,
    void        *const input_dest_address,
    size_t             extraction_limit,
    const void  *const output_src_address,
    size_t             insertion_limit
);

LHASH_API void               lhashGTypeHandler_SetExtractionLocation(
    lhashGTypeHandler *self,
    const void *const address, size_t limit
);
LHASH_API void               lhashGTypeHandler_SetInsertionLocation(
    lhashGTypeHandler *self,
    void *const address, size_t limit
);
LHASH_API void               lhashGTypeHandler_SetType(lhashGTypeHandler *self, lhashGCompleteType gtype);
LHASH_API void               lhashGTypeHandler_SetTypeT(lhashGTypeHandler *self, lhashGType gtype);

LHASH_API const void*        lhashGTypeHandler_GetExtractionAddress(const lhashGTypeHandler *self);
LHASH_API void*              lhashGTypeHandler_GetInsertionAddress(const lhashGTypeHandler *self);
LHASH_API size_t             lhashGTypeHandler_BytesAvailable(const lhashGTypeHandler *self);
#define                      lhashGTypeHandler_GetExtractionLimit lhashGTypeHandler_BytesAvailable
LHASH_API size_t             lhashGTypeHandler_GetInsertionLimit(const lhashGTypeHandler *self);
LHASH_API lhashGType         lhashGTypeHandler_GetType(const lhashGTypeHandler *self);

LHASH_API size_t             lhashGTypeHandler_SeekG(lhashGTypeHandler *self, size_t pos);
LHASH_API size_t             lhashGTypeHandler_SeekP(lhashGTypeHandler *self, size_t pos);
LHASH_API size_t             lhashGTypeHandler_RelSeekG(lhashGTypeHandler *self, ssize_t pos);
LHASH_API size_t             lhashGTypeHandler_RelSeekP(lhashGTypeHandler *self, ssize_t pos);
LHASH_API size_t             lhashGTypeHandler_TellG(lhashGTypeHandler *self);
LHASH_API size_t             lhashGTypeHandler_TellP(lhashGTypeHandler *self);

LHASH_API size_t             lhashGTypeHandler_Extract(
    lhashGTypeHandler *self,
    void *const to, size_t max_elements
);
LHASH_API size_t             lhashGTypeHandler_Insert(
    lhashGTypeHandler *self,
    const void *const from, size_t array_len
);

LHASH_API bool               lhashGTypeHandler_InsertionEnabled(const lhashGTypeHandler *self);
LHASH_API bool               lhashGTypeHandler_ExtractionEnabled(const lhashGTypeHandler *self);
LHASH_API bool               lhashGTypeHandler_FullIOEnabled(const lhashGTypeHandler *self);

LHASH_API bool               lhashGeneralizedTypeHandler_InvalidConfiguration(const lhashGTypeHandler *self, bool log_errors);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__TYPES_H_
