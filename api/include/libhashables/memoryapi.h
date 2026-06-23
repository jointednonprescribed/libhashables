
#ifndef _LIBHASHABLES__MEMORYAPI_H_
#define _LIBHASHABLES__MEMORYAPI_H_ 1

#ifndef _LIBHASHABLES__LOGGINGAPI_H_
#	include "loggingapi.h"
#endif



LHASH_EXTERN_C


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

LHASH_API lhashMemRef lhashMemRefFromIntegral(lhashUIntPtr_t integral);


struct LHASH_API _lhashMemory
{
	lhashMemRef (*AllocateMemory)(size_t block_size, lhashMemoryDestructor destructor);
	lhashMemRef (*BorrowMemory)(lhashMemRef);
	lhashMemRef (*CopyMemory)(lhashMemRef from, lhashMemRef to);
	int         (*MoveMemory)(lhashMemRef from, lhashMemRef to);
	int         (*DeallocateMemory)(lhashMemRef reference); // deallocates the block
	// drops the reference counter and tests it to see if the block must be deallocated
	int         (*DropMemory)(lhashMemRef reference);
	bool        (*ReferenceIsNull)(lhashMemRef reference);
	bool        (*ReferenceIsValid)(lhashMemRef reference);
	bool        (*ReferenceIsOwner)(lhashMemRef reference);
	void*       (*ReferenceToAddress)(lhashMemRef reference);
	const void* (*CReferenceToCAddress)(lhashConstMemRef reference);
	lhashMemRef (*GetNullReference)( void );

	// Signifies that, whatever the user of library's memory implementation stores inside
	// of lhashMemRef objects, it is not a direct pointer to the begining of the block it
	// references, otherwise, this value should be false.
	bool          ReferenceIsNotAddress;
	time_t        CachePeriod;
	bool          CacheRefreshNotRequired;
};

LHASH_API bool lhashMemoryIsInitialized( void );
LHASH_API void lhashInitMemoryBasic( void );
LHASH_API void lhashInitMemory( const struct _lhashMemory *callbacks );

LHASH_API lhashMemRef lhashAllocateMemory(size_t block_size, lhashMemoryDestructor destructor);
LHASH_API lhashMemRef lhashBorrowMemory(lhashMemRef);
LHASH_API lhashMemRef lhashCopyMemory(lhashMemRef from, lhashMemRef to); // if 'to' is NULL, new memory will be allocated
LHASH_API int         lhashMoveMemory(lhashMemRef from, lhashMemRef to);
LHASH_API void        lhashDeallocateMemory(lhashMemRef reference);
LHASH_API bool        lhashReferenceIsNull(lhashMemRef reference);
LHASH_API bool        lhashReferenceIsValid(lhashMemRef reference);
LHASH_API bool        lhashReferenceIsOwner(lhashMemRef reference);
LHASH_API void*       lhashReferenceToAddress(lhashMemRef reference);
LHASH_API lhashMemRef lhashGetNullReference( void );

LHASH_API bool        lhashReferenceIsNotAddress( void );
LHASH_API time_t      lhashCachePeriod( void );
// Returns CacheRefreshNotRequired, outputs CachePeriod through the output parameter.
LHASH_API bool        lhashCachePeriodEx( time_t *cache_period_output );
LHASH_API bool        lhashCacheRefreshNotRequired( void );


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__MEMORYAPI_H_
