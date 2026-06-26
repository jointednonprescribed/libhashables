
#ifndef _LIBHASHABLES__TYPES_HPP_
#define _LIBHASHABLES__TYPES_HPP_ 1

#ifndef _LIBHASHABLES__TYPES_H_
#	include "../types.h"
#endif



namespace libhashables
{
	using 

	using GType       = lhashGType;
	using GenericType = lhashGType;

	enum _GTypes
	{
		// This is a mirror of lhashGType:
		//  1. Isolate the identifiers picked as the name of each value, delete
		//     everything else on each line using multi-select.
		//  2. Delete the first 5 characters of each name, removing the LHASH prefix
		//     and subsequent underscore character from non-underscored identifiers,
		//     and offset just so a leading underscore is left at the beginning of
		//     each name for underscored identifiers.
		// This is the naming scheme for all members of this enum to mirror lhashGType.
		TYPE_INDETERMINATE_SIZE = LHASH_TYPE_INDETERMINATE_SIZE,
		TYPE_UNKNOWN_SIZE = LHASH_TYPE_UNKNOWN_SIZE,
		TYPE_VOID = LHASH_TYPE_VOID,
		TYPE_INT = LHASH_TYPE_INT,
		TYPE_HASH = LHASH_TYPE_HASH,
		TYPE_FLOAT = LHASH_TYPE_FLOAT,
		TYPE_TIME = LHASH_TYPE_TIME,
		TYPE_STRUCT = LHASH_TYPE_STRUCT,
		TYPE_DATETIME = LHASH_TYPE_DATETIME,
		TYPE_FILEPATH = LHASH_TYPE_FILEPATH,
		_TYPE_BEG_INTEGRALS = _LHASH_TYPE_BEG_INTEGRALS,
		_TYPE_END_INTEGRALS = _LHASH_TYPE_END_INTEGRALS,
		_TYPE_BEG_PRIMITIVES = _LHASH_TYPE_BEG_PRIMITIVES,
		_TYPE_END_PRIMITIVES = _LHASH_TYPE_END_PRIMITIVES,
		_TYPE_END_BASE_TYPES = _LHASH_TYPE_END_BASE_TYPES,
		_TYPE_BASE_MASK = _LHASH_TYPE_BASE_MASK,
		_TYPE_BASE_OFFSET = _LHASH_TYPE_BASE_OFFSET,
		TYPE_LQUAL = LHASH_TYPE_LQUAL,
		TYPE_LLQUAL = LHASH_TYPE_LLQUAL,
		TYPE_LLLQUAL = LHASH_TYPE_LLLQUAL,
		TYPE_HQUAL = LHASH_TYPE_HQUAL,
		TYPE_HHQUAL = LHASH_TYPE_HHQUAL,
		_TYPE_SIZESPEC_MASK = _LHASH_TYPE_SIZESPEC_MASK,
		_TYPE_SIZESPEC_OFFSET = _LHASH_TYPE_SIZESPEC_OFFSET,
		TYPE_UNSIGNED = LHASH_TYPE_UNSIGNED,
		TYPE_PTR = LHASH_TYPE_PTR,
		TYPE_PTR_SQUARE = LHASH_TYPE_PTR_SQUARE,
		TYPE_PTR_CUBIC = LHASH_TYPE_PTR_CUBIC,
		TYPE_PTR_2 = LHASH_TYPE_PTR_2,
		TYPE_PTR_3 = LHASH_TYPE_PTR_3,
		_TYPE_PTR_MASK = _LHASH_TYPE_PTR_MASK,
		_TYPE_PTR_OFFSET = _LHASH_TYPE_PTR_OFFSET,
		TYPE_REF = LHASH_TYPE_REF,
		TYPE_CONST = LHASH_TYPE_CONST,
		TYPE_VOLATILE = LHASH_TYPE_VOLATILE,
		TYPE_NOTNULL = LHASH_TYPE_NOTNULL,
		TYPE_CV = LHASH_TYPE_CV,
		TYPE_DOUBLE = LHASH_TYPE_DOUBLE,
		TYPE_LDOUBLE = LHASH_TYPE_LDOUBLE,
		TYPE_LONG = LHASH_TYPE_LONG,
		TYPE_LLONG = LHASH_TYPE_LLONG,
		TYPE_INT128 = LHASH_TYPE_INT128,
		TYPE_ULONG = LHASH_TYPE_ULONG,
		TYPE_ULLONG = LHASH_TYPE_ULLONG,
		TYPE_UINT128 = LHASH_TYPE_UINT128,
	};

	template <size_t _C, size_t _L, class _T, class _First, class ..._Ts>
	constexpr size_t _generalize_type_index =
		(_C >= _L)?
		(-1ull) :
		(
			std::is_same_v<_T, _First>?
			_C :
			_generalize_type_index<_C + 1, _L, _T, _Ts..., void>
		);

	template <class _T>
	constexpr GType generalize_type(void)
	{
		typedef
			std::remove_const_t<
			std::remove_volatile_t<
			remove_remote_qualifiers_t<
			std::remove_const_t<
			std::remove_volatile_t<_T>>>>> base_type;

		typedef std::conditional_t<
			std::is_integral_v<_T>,
			std::make_signed_t<_T>,
			std::conditional_t<
				is_hash_type_v<_T>,
				ext_make_signed_t<_T>,
				_T
			>
		> signless_type;

		// 0:  signless
		// 1:  unsigned
		// -1: signed
		constexpr int sign =
			std::is_integral_v<_T>?
			(
				std::is_unsigned_v<_T>?
				1 : (-1)
			):
			(
				is_ext_integral_v<_T>?
				(
					ext_is_unsigned_v<_T>?
					(-1) : 1
				):
				0
			);

		constexpr size_t typei = _generalize_type_index<0, N, base_type,
			void, char, short, int, long, long long,
			lhashint128,  int128_t,  lhashint256,  int256_t,  lhashint512,  int512_t,
			lhashint1024, int1024_t, lhashint2048, int2048_t, lhashint4096, int4096_t,
			float, double, long double, lhashdatetime_t, datetime>;

		if constexpr (typei == size_t(-1ull))
			return TYPE_STRUCT;
		else switch (typei) {
			case 0:
				return TYPE_VOID;

			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				return TYPE_INT;

			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
				return TYPE_HASH;

			case 18:
			case 19:
			case 20:
				return TYPE_FLOAT;

			case 21:
			case 22:
				return TYPE_TIME;

			case 23:
			case 24:
				return TYPE_FILEPATH;
		}
	}

	typedef struct GenericCompleteType: private lhashGCompleteType
	{
		GenericCompleteType();
		GenericCompleteType(const GenericTypeHandler&);
		GenericCompleteType(GenericTypeHandler&&);

		template <class _T>
		static GenericCompleteType Get()
		{
			const GType type = generalize_type<_T>();
		}
	} GCompleteType;

	typedef struct GenericTypeHandler: private lhashGTypeHandler
	{
		GenericTypeHandler();
		GenericTypeHandler(const GenericTypeHandler&);
		GenericTypeHandler(GenericTypeHandler&&);

		GenericTypeHandler()
	} GTypeHandler;
}



#endif // _LIBHASHABLES__TYPES_HPP_
