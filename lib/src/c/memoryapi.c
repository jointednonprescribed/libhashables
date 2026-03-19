
#ifndef _LIBHASHABLES_
#	include <libhashables.h>
#endif


struct _lhashMemory_Header
{
	long long             _validator;
	size_t                blksize;
	lhashMemoryDestructor destructor;
	lhashpid_t            pid;
	uint32_t              refc;
};

#define _LHASH_MEMORY_BASIC_HEADER_VALIDATOR 674357575910233ULL

int LHASH_MEMORY_INIT = 0;

char LHASH_EXCNAME_MEMORY_OPERATION_ERROR[] = "MemoryOperationError";

char LHASH_EXCNAME_NULL_REFERENCE_ERROR[] = "NullReferenceError";
char LHASH_EXCDESC_NULL_REFERENCE_ERROR[] = "BasicMemory: Illegal use of a null reference.";


lhashMemRef _lhashMemory_NullAllocateMemory(size_t)
{
	return NULL;
}
lhashMemRef _lhashMemory_NullBorrowMemory(lhashMemRef passthru)
{
	return passthru;
}
lhashMemRef _lhashMemory_NullCopyMemory(lhashMemRef, lhashMemRef)
{
	return NULL;
}
int _lhashMemory_NullMoveMemory(lhashMemRef, lhashMemRef)
{
	return -1;
}
void _lhashMemory_NullDeallocateMemory(lhashMemRef) {}
bool _lhashMemory_NullReferenceIsNull(lhashMemRef)
{
	return true;
}
bool _lhashMemory_NullReferenceIsValid(lhashMemRef)
{
	return false;
}
bool _lhashMemory_NullReferenceIsOwner(lhashMemRef)
{
	return false;
}
void* _lhashMemory_NullReferenceToAddress(lhashMemRef)
{
	return NULL;
}
const void* _lhashMemory_NullCReferenceToCAddress(lhashConstMemRef)
{
	return NULL;
}
lhashMemRef _lhashMemory_NullGetNullReference( void )
{
	return NULL;
}

const struct _lhashMemory LHASH_MEMORY_NULL = {
	.AllocateMemory = _lhashMemory_NullAllocateMemory,
	.BorrowMemory = _lhashMemory_NullBorrowMemory,
	.CopyMemory = _lhashMemory_NullCopyMemory,
	.MoveMemory = _lhashMemory_NullMoveMemory,
	.DeallocateMemory = _lhashMemory_NullDeallocateMemory,
	.ReferenceIsNull = _lhashMemory_NullReferenceIsNull,
	.ReferenceIsValid = _lhashMemory_NullReferenceIsValid,
	.ReferenceIsOwner = _lhashMemory_NullReferenceIsOwner,
	.ReferenceToAddress = _lhashMemory_NullReferenceToAddress,
	.CReferenceToCAddress = _lhashMemory_NullCReferenceToCAddress,
	.GetNullReference = _lhashMemory_NullGetNullReference
};


struct _lhashMemory LHASH_MEMORY = LHASH_MEMORY_NULL;


void _lhashMemory_NullDestructor(size_t, void*) {}

lhashMemRef _lhashMemory_BasicAllocateMemory(size_t block_size, lhashMemoryDestructor destructor)
{
	struct _lhashMemory_Header *block =
		(struct _lhashMemory_Header*)
		malloc(block_size + sizeof(struct _lhashMemory_Header));

	if (block == NULL)
		return NULL;
	
	block->_validator = _LHASH_MEMORY_BASIC_HEADER_VALIDATOR;
	block->destructor = (destructor == NULL)? _lhashMemory_NullDestructor : destructor;
	block->pid        = lhashGetPid();
	block->refc       = 1;
	block->blksize    = block_size;

	return (void*) &block[1];
}
lhashMemRef _lhashMemory_BasicBorrowMemory(lhashMemRef ref)
{
	if (ref == NULL)
		return NULL;

	char *curs = (char*) ref;

	struct _lhashMemory_Header *header =
		(struct _lhashMemory_Header*) (void*) (curs - sizeof(struct _lhashMemory_Header));

	if (header->_validator != _LHASH_MEMORY_BASIC_HEADER_VALIDATOR)
		return NULL;
	else {
		header->refc++;
		return ref;
	}
}
lhashMemRef _lhashMemory_BasicCopyMemory(lhashMemRef from, lhashMemRef to)
{
	if (from == NULL)
		return NULL;

	char *curs = (char*) from, *curs2 = NULL;

	struct _lhashMemory_Header *to_header, *header =
		(struct _lhashMemory_Header*)
		(void*)
		(curs - sizeof(struct _lhashMemory_Header));
	
	const size_t size = header->blksize;
	
	if (to != NULL) {
		to_header =
			(struct _lhashMemory_Header*)
			(void*)
			(((char*) to) - sizeof(struct _lhashMemory_Header));

		if (to_header->blksize < size)
			goto alloc_new_memory;

		to_header->destructor(to);

		to_header->destructor = header->destructor;
	} else {
	alloc_new_memory:
		to = _lhashMemory_BasicAllocateMemory(size, header->destructor);

		to_header =
			(struct _lhashMemory_Header*)
			(void*)
			(((char*) to) - sizeof(struct _lhashMemory_Header));
	}

	curs2 = (char*) to;

	for (size_t i = 0; i < size; i++, curs2++, curs++)
		*curs2 = *curs;

	return to;
}
int _lhashMemory_BasicMoveMemory(lhashMemRef from, lhashMemRef to)
{
	if (from == NULL || to == NULL) {
		lhashThrowFne(
			LHASH_EXCNAME_NULL_REFERENCE_ERROR,
			LHASH_EXCDESC_NULL_REFERENCE_ERROR,
			"_lhashMemory_BasicMoveMemory",
			_lhashMemory_BasicMoveMemory, -1);
		return -1;
	}

	char *curs = (char*) from, *curs2 = (char*) to;

	struct _lhashMemory_Header *to_header =
		(struct _lhashMemory_Header*)
		(void*)
		(curs2 - sizeof(struct _lhashMemory_Header)),
	*header =
		(struct _lhashMemory_Header*)
		(void*)
		(curs - sizeof(struct _lhashMemory_Header));

	if (header->_validator != _LHASH_MEMORY_BASIC_HEADER_VALIDATOR || to_header->_validator != _LHASH_MEMORY_BASIC_HEADER_VALIDATOR) {
		lhashThrowFne(
			LHASH_EXCNAME_MEMORY_OPERATION_ERROR,
			"BasicMemory: Illegal use of uncontrolled block(s).",
			"_lhashMemory_BasicMoveMemory",
			_lhashMemory_BasicMoveMemory, -1);
		return -1;
	}

	const size_t size = header->blksize, size2 = to_header->blksize;

	size_t i = 0;

	if (size2 < size) {
		lhashThrowFne(
			LHASH_EXCNAME_MEMORY_OPERATION_ERROR,
			"BasicMemory: Cannot move memory to a smaller block.",
			"_lhashMemory_BasicMoveMemory",
			_lhashMemory_BasicMoveMemory, -1);
		return -1;
	}

	for (; i < size; i++, curs2++, curs++)
		*curs2 = *curs;
	for (; i < size2; i++, curs2++)
		*curs2 = 0;

	to_header->destructor = header->destructor;

	header->destructor = _lhashMemory_NullDestructor;

	_lhashMemory_BasicDeallocateMemory(from);

	return 0;
}
void _lhashMemory_BasicDeallocateMemory(lhashMemRef reference)
{
	if (reference == NULL)
		return;

	struct _lhashMemory_Header *header =
		(struct _lhashMemory_Header*)
		(void*)
		(((char*)reference) - sizeof(struct _lhashMemory_Header));
	
	if (header->_validator != _LHASH_MEMORY_BASIC_HEADER_VALIDATOR)
		return;

	if (header->destructor != NULL)
		header->destructor(reference);

	free(header);
}
bool _lhashMemory_BasicReferenceIsNull(lhashConstMemRef reference)
{
	return reference == NULL;
}
bool _lhashMemory_BasicReferenceIsValid(lhashConstMemRef reference)
{
	return reference != NULL;
}
bool _lhashMemory_BasicReferenceIsOwner(lhashConstMemRef reference)
{
	if (reference == NULL)
		return false;

	const char *curs = (const char*) reference;

	const struct _lhashMemory_Header *header =
		(const struct _lhashMemory_Header*)
		(const void*)
		(curs - sizeof(struct _lhashMemory_Header));
	
	if (header->_validator != _LHASH_MEMORY_BASIC_HEADER_VALIDATOR)
		return false;
	else
		return lhashGetPid() == header->pid;
}
void* _lhashMemory_BasicReferenceToAddress(lhashMemRef reference)
{
	return reference;
}
const void* _lhashMemory_BasicCReferenceToCAddress(lhashConstMemRef reference)
{
	return reference;
}
lhashMemRef _lhashMemory_BasicGetNullReference( void )
{
	return NULL;
}

const struct _lhashMemory LHASH_MEMORY_BASIC = {
	.AllocateMemory = _lhashMemory_BasicAllocateMemory,
	.BorrowMemory = _lhashMemory_BasicBorrowMemory,
	.CopyMemory = _lhashMemory_BasicCopyMemory,
	.MoveMemory = _lhashMemory_BasicMoveMemory,
	.DeallocateMemory = _lhashMemory_BasicDeallocateMemory,
	.ReferenceIsNull = _lhashMemory_BasicReferenceIsNull,
	.ReferenceIsValid = _lhashMemory_BasicReferenceIsValid,
	.ReferenceIsOwner = _lhashMemory_BasicReferenceIsOwner,
	.ReferenceToAddress = _lhashMemory_BasicReferenceToAddress,
	.CReferenceToCAddress = _lhashMemory_BasicCReferenceToCAddress,
	.GetNullReference = _lhashMemory_BasicGetNullReference
};

lhashMemRef lhashMemRefFromIntegral(lhashUIntPtr_t integral)
{
	return *(void**)(void*) &integral;
};

bool lhashMemoryIsInitialized( void )
{
	return LHASH_MEMORY_INIT;
}
void lhashInitMemoryBasic( void )
{
	lhashInitMemory(&LHASH_MEMORY_BASIC);
}
void lhashInitMemory( const struct _lhashMemory *callbacks );

lhashMemRef lhashAllocateMemory(size_t block_size, lhashMemoryDestructor destructor)
{
	return LHASH_MEMORY.AllocateMemory(block_size, destructor);
}
lhashMemRef lhashBorrowMemory(lhashMemRef ref)
{
	return LHASH_MEMORY.BorrowMemory(ref);
}
lhashMemRef lhashCopyMemory(lhashMemRef from, lhashMemRef to)
{
	return LHASH_MEMORY.CopyMemory(from, to);
}
int         lhashMoveMemory(lhashMemRef from, lhashMemRef to)
{
	return LHASH_MEMORY.MoveMemory(from, to);
}
void        lhashDeallocateMemory(lhashMemRef reference)
{
	return LHASH_MEMORY.DeallocateMemory(reference);
}
bool        lhashReferenceIsNull(lhashMemRef reference)
{
	return LHASH_MEMORY.ReferenceIsNull(reference);
}
bool        lhashReferenceIsValid(lhashMemRef reference)
{
	return LHASH_MEMORY.ReferenceIsValid(reference);
}
bool        lhashReferenceIsOwner(lhashMemRef reference)
{
	return LHASH_MEMORY.ReferenceIsOwner(reference);
}
void*       lhashReferenceToAddress(lhashMemRef reference)
{
	return LHASH_MEMORY.ReferenceToAddress(reference);
}
lhashMemRef lhashGetNullReference( void )
{
	return LHASH_MEMORY.GetNullReference();
}
