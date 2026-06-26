
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
    lhashMemRef data;
    size_t cols, rows;
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

/* Push a row into the table from a type handler, chainable; return value is always self. */
LHASH_API lhashTable* lhashTable_Push(lhashTable *self, lhashGTypeHandler *row_streamer);
/* Push an unpadded tuple as a row into the table, nbytes is the total size (in bytes) of the
.  tuple. */
LHASH_API lhashTable* lhashTable_PushT(lhashTable *self, const void *tuple, size_t nbytes);

/* Push a row into the table from a type handler at a particular index, chainable; return
.  value is always self. */
LHASH_API lhashTable* lhashTable_PushI(lhashTable *self, size_t at, lhashGTypeHandler *row_streamer);
/* Push an unpadded tuple as a row into the table at a particular index, nbytes is the total
.  size (in bytes) of the tuple. */
LHASH_API lhashTable* lhashTable_PushTi(lhashTable *self, size_t at, const void *tuple, size_t nbytes);

/* Copy a row from the table into a type handler, chainable; return value is always
.  self. */
LHASH_API lhashTable* lhashTable_Get(lhashTable *self, size_t row, lhashGTypeHandler *row_streamer);
/* Copy a row from the table as an unpadded tuple, nbytes is the total size (in bytes) of the
.  buffer for this tuple. */
LHASH_API lhashTable* lhashTable_GetT(lhashTable *self, size_t row, void *buffer, size_t nbytes);

/* Pop (copy, then remove) a row from the table into a type handler, chainable; return value
.  is always self. */
LHASH_API lhashTable* lhashTable_Pop(lhashTable *self, size_t row, lhashGTypeHandler *row_streamer);
/* Pop a row from the table as an unpadded tuple, nbytes is the total size (in bytes) of the
.  buffer for this tuple. */
LHASH_API lhashTable* lhashTable_PopT(lhashTable *self, size_t row, void *buffer, size_t nbytes);

/* Remove a row from the table, chainable; return value is always self. */
LHASH_API lhashTable* lhashTable_Remove(lhashTable *self, size_t row);

LHASH_API size_t      lhashTable_GetColumnSize(lhashTable *self, size_t col);
LHASH_API size_t      lhashTable_GetTableWidth(lhashTable *self);
LHASH_API size_t      lhashTable_GetTableHeight(lhashTable *self);
#define               lhashTable_GetRowCount lhashTable_GetTableHeight
LHASH_API size_t      lhashTable_GetColumnCount(lhashTable *self);
LHASH_API size_t      lhashTable_GetCellCount(lhashTable *self);

LHASH_API lhashTableColumnHeader* lhashTable_GetColumnHeader(lhashTable *self, size_t col);

LHASH_API void*       lhashTable_GetRow(lhashTable *self, size_t row);

LHASH_API lhashTable* lhashTable_GetCell(lhashTable *self, size_t col, size_t row, void *output, size_t output_size);
LHASH_API lhashTable* lhashTable_GetCellH(lhashTable *self, size_t col, size_t row, lhashGTypeHandler *output);

LHASH_API lhashTable* lhashTable_SetCell(lhashTable *self, size_t col, size_t row, const void *input);
LHASH_API lhashTable* lhashTable_SetCellH(lhashTable *self, size_t col, size_t row, lhashGTypeHandler *input);

LHASH_API int         lhashTable_Drop(lhashTable *self);


LHASH_END_EXTERN_C

#ifdef __cplusplus && !defined(_LIBHASHABLES__TABLE_HPP_)
#   include "c++/table.hpp"
#endif



#endif // _LIBHASHABLES__TABLE_H_
