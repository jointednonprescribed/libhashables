
#ifndef _LIBHASHABLES_
#   include <libhashables.h>
#endif


char LHASH_TABLE_EMPTY_STR[] = "";

#define _LHASH_CHECK_CACHE(_metaref, outvar)                                        \
    time_t _LHASH_CHECK_CACHE__cacheperiod;                                         \
    if (                                                                            \
        !lhashCachePeriodEx(&_LHASH_CHECK_CACHE__cacheperiod) &&                    \
        (time(NULL) - _metaref->_cachetime) >= _LHASH_CHECK_CACHE__cacheperiod)     \
            outvar = _metaref->_addrcache = lhashReferenceToAddress(_metaref->data) \
    else                                                                            \
        outvar = _metaref->_addrcache;


LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeader(const char *label, lhashGeneralizedType column_datatype)
{
    const size_t sizeof_type = lhashGType_Sizeof(column_datatype);

    return (lhashTableColumnHeader) {
        .label =(label == NULL)? LHASH_TABLE_EMPTY_STR : label,
        .gtype = { .gtype=column_datatype, .sizeof_type=sizeof_type, ._handlerfuncs=lhashGTYpe_GetHandlerFunctions(column_datatype) },
        .width = sizeof_type,
        .len   = 1
    };
}
LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeaderA(const char *label, size_t array_len, lhashGeneralizedType array_datatype)
{
    const size_t sizeof_type = lhashGType_Sizeof(array_datatype);

    return (lhashTableColumnHeader) {
        .label = (label == NULL)? LHASH_TABLE_EMPTY_STR : label,
        .gtype = array_datatype,
        .width = array_len * sizeof_type,
        .tsz   = sizeof_type,
        .len   = array_len
    };
}
LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeaderN(const char *label, size_t nbytes)
{
    return (lhashTableColumnHeader) {
        .label = (label == NULL)? LHASH_TABLE_EMPTY_STR : label,
        .gtype = LHASH_TYPE_INT | LHASH_TYPE_HHQUAL, // byte type
        .width = nbytes,
        .tsz   = 1,
        .len   = nbytes
    };
}
LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeaderS(const char *label, size_t struct_size)
{
    return (lhashTableColumnHeader) {
        .label = (label == NULL)? LHASH_TABLE_EMPTY_STR : label,
        .gtype = LHASH_TYPE_STRUCT,
        .width = struct_size,
        .tsz   = struct_size,
        .len   = 1
    };
}

LHASH_API lhashTableColumnHeader* lhashTable_InitColumnHeader(
    lhashTableColumnHeader *self,
    const char *label, lhashGeneralizedType column_datatype
){
    if (self == NULL)
        return NULL;

    self->label = (label == NULL)? LHASH_TABLE_EMPTY_STR : label;
    self->gtype 
}
LHASH_API lhashTableColumnHeader* lhashTable_InitColumnHeaderA(
    lhashTableColumnHeader *self,
    const char *label, size_t array_len, lhashGeneralizedType array_datatype
);
LHASH_API lhashTableColumnHeader* lhashTable_InitColumnHeaderN(
    lhashTableColumnHeader *self, const char *label, size_t nbytes
);
LHASH_API lhashTableColumnHeader* lhashTable_InitColumnHeaderS(
    lhashTableColumnHeader *self, const char *label, size_t struct_size
);

LHASH_API const char*             lhashTableColumnHeader_GetLabel(const lhashTableColumnHeader *self);
LHASH_API lhashGeneralizedType    lhashTableColumnHeader_GetType(const lhashTableColumnHeader *self);
LHASH_API size_t                  lhashTableColumnHeader_GetFullWidth(const lhashTableColumnHeader *self);
LHASH_API size_t                  lhashTableColumnHeader_GetArrayLength(const lhashTableColumnHeader *self);
