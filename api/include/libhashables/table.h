
#ifndef _LIBHASHABLES__TABLE_H_
#define _LIBHASHABLES__TABLE_H_ 1

#ifndef _LIBHASHABLES__MEMORY_H_
#   include "memoryapi.h"
#endif



LHASH_EXTERN_C


/*
 * A table header structure type for storing table metadata
 * prefixed to the associated table data itself.
 */
typedef struct _lhashTableHeader lhashTableHeader;

/*
 * A column header structure type for storing required metadata
 * prefixed for each column, together forming the table's
 * "segment table".
 */
typedef struct _lhashTableColumnHeader lhashTableColumnHeader;

/*
 * A table structure type for storing row-by-column data.
 */
typedef struct _lhashTable lhashTable;

/*
 * Implementation for struct _lhashTableHeader.
 */
struct _lhashTableHeader
{
    int
        // Offset from the beginning of the table header of the data section of the table
        data_off,
        // Offset from the beginning of the table header of the segment table (this contains
        // info about where each column starts and ends as well as type/label info for each
        // column).
        segtable_off;

    // A container for remembering row size without having to iterate through the segment table.
    size_t rowsize;
};

/*
 * Implementation for struct _lhashTableColumnHeader.
 */
struct _lhashTableColumnHeader
{
    const char          *label;
    size_t               width, len; // width per cell in this column, type size, and array len
    lhashGCompleteType   gtype;
};

LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeader(const char *label, lhashGeneralizedType column_datatype);
LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeaderA(const char *label, size_t array_len, lhashGeneralizedType array_datatype);
LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeaderN(const char *label, size_t nbytes);
LHASH_API lhashTableColumnHeader  lhashTable_MakeColumnHeaderS(const char *label, size_t struct_size);

LHASH_API lhashTableColumnHeader* lhashTable_InitColumnHeader(
    lhashTableColumnHeader *self,
    const char *label, lhashGeneralizedType column_datatype
);
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

/*
 * Implementation for struct _lhashTable
 */
struct _lhashTable
{
    lhashMemRef              data;
    lhashTableColumnHeader *_addrcache;
    time_t                  _cachetime;
};

extern LHASH_API const lhashTable lhashTable_Null;

LHASH_API lhashTable lhashTable_Make();
LHASH_API lhashTable lhashTable_MakeC(size_t colc, const lhashTableColumnHeader *headers);
LHASH_API lhashTable lhashTable_MakeCd(size_t colc, lhashTableColumnHeader duplicate_header);
LHASH_API lhashTable lhashTable_MakeCr(size_t rowc, size_t colc, const lhashTableColumnHeader *headers);
LHASH_API lhashTable lhashTable_MakeCrd(size_t rowc, size_t colc, lhashTableColumnHeader duplicate_header);
LHASH_API lhashTable lhashTable_MakeAppendedC(
    ssize_t insertion_index, const lhashTable *base,
    size_t  header_count,    const lhashTableColumnHeader *headers
);
LHASH_API lhashTable lhashTable_MakeAppendedCd(
    ssize_t insertion_index, const lhashTable *base,
    size_t  header_count,    lhashTableColumnHeader duplicate_header
);

LHASH_API lhashTable* lhashTable_Init(lhashTable *self);
LHASH_API lhashTable* lhashTable_InitC(lhashTable *self, size_t colc, const lhashTableColumnHeader *headers);
LHASH_API lhashTable* lhashTable_InitCd(lhashTable *self, size_t colc, lhashTableColumnHeader duplicate_header);
LHASH_API lhashTable* lhashTable_InitCr(lhashTable *self, size_t rowc, size_t colc, const lhashTableColumnHeader *headers);
LHASH_API lhashTable* lhashTable_InitCrd(lhashTable *self, size_t rowc, size_t colc, lhashTableColumnHeader duplicate_header);
LHASH_API lhashTable* lhashTable_InitAppendedC(
    lhashTable *self,
    ssize_t insertion_index, const lhashTable *base,
    size_t  header_count,    const lhashTableColumnHeader *headers
);
LHASH_API lhashTable* lhashTable_InitAppendedCd(
    lhashTable *self,
    ssize_t insertion_index, const lhashTable *base,
    size_t  header_count,    lhashTableColumnHeader duplicate_header
);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__TABLE_H_
