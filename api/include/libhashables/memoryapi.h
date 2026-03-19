
#ifndef _LIBHASHABLES__MEMORYAPI_H_
#define _LIBHASHABLES__MEMORYAPI_H_ 1

#ifndef _LIBHASHABLES__LOGGINGAPI_H_
#	include "loggingapi.h"
#endif



/*
 * A type alias for memory references which can be implemented as
 * integer indices or as raw addresses.
 */
typedef void *lhashMemRef;
typedef const void *lhashConstMemRef;

/*
 * A type alias for memory destructor functions.
 */
typedef void (*lhashMemoryDestructor)(lhashMemRef reference);

lhashMemRef lhashMemRefFromIntegral(lhashUIntPtr_t integral);


struct LHASH_API _lhashMemory
{
	lhashMemRef (*AllocateMemory)(size_t block_size, lhashMemoryDestructor destructor);
	lhashMemRef (*BorrowMemory)(lhashMemRef);
	lhashMemRef (*CopyMemory)(lhashMemRef from, lhashMemRef to);
	int         (*MoveMemory)(lhashMemRef from, lhashMemRef to);
	int         (*DeallocateMemory)(lhashMemRef reference); // deallocates the block
	int         (*DropMemory)(lhashMemRef reference); // drops the reference counter and tests it to see if the block must be deallocated
	bool        (*ReferenceIsNull)(lhashMemRef reference);
	bool        (*ReferenceIsValid)(lhashMemRef reference);
	bool        (*ReferenceIsOwner)(lhashMemRef reference);
	void*       (*ReferenceToAddress)(lhashMemRef reference);
	const void* (*CReferenceToCAddress)(lhashConstMemRef reference);
	lhashMemRef (*GetNullReference)( void );
};

bool lhashMemoryIsInitialized( void );
void lhashInitMemoryBasic( void );
void lhashInitMemory( const struct _lhashMemory *callbacks );

lhashMemRef lhashAllocateMemory(size_t block_size, lhashMemoryDestructor destructor);
lhashMemRef lhashBorrowMemory(lhashMemRef);
lhashMemRef lhashCopyMemory(lhashMemRef from, lhashMemRef to); // if 'to' is NULL, new memory will be allocated
int         lhashMoveMemory(lhashMemRef from, lhashMemRef to);
void        lhashDeallocateMemory(lhashMemRef reference);
bool        lhashReferenceIsNull(lhashMemRef reference);
bool        lhashReferenceIsValid(lhashMemRef reference);
bool        lhashReferenceIsOwner(lhashMemRef reference);
void*       lhashReferenceToAddress(lhashMemRef reference);
lhashMemRef lhashGetNullReference( void );



#endif // _LIBHASHABLES__MEMORYAPI_H_
