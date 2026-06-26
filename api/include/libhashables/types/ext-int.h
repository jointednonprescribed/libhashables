
#ifndef _LIBHASHABLES__types_EXT_INT_H_
#define _LIBHASHABLES__types_EXT_INT_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



#include "int128.h"
#include "int256.h"
#include "int512.h"
#include "int1024.h"
#include "int2048.h"
#include "int4096.h"

#ifdef __cplusplus
namespace libhashables
{
	template <class _T>
	struct is_ext_integral
	{
		static constexpr bool value =
			std::is_same_v<_T, lhashint128>  || std::is_same_v<_T, uint128>
			std::is_same_v<_T, lhashint256>  || std::is_same_v<_T, uint256>
			std::is_same_v<_T, lhashint512>  || std::is_same_v<_T, uint512>
			std::is_same_v<_T, lhashint1024> || std::is_same_v<_T, uint1024>
			std::is_same_v<_T, lhashint2048> || std::is_same_v<_T, uint2048>
			std::is_same_v<_T, lhashint4096> || std::is_same_v<_T, uint4096>;
	};

	template <class _T>
	static constexpr bool is_ext_integral_v = is_ext_integral<_T>::value;

	template <class _T>
	struct ext_is_signed
	{
		static constexpr bool value =
			std::is_same_v<_T, lhashint128>  ||
			std::is_same_v<_T, lhashint256>  ||
			std::is_same_v<_T, lhashint512>  ||
			std::is_same_v<_T, lhashint1024> ||
			std::is_same_v<_T, lhashint2048> ||
			std::is_same_v<_T, lhashint4096> ||
			std::is_same_v<_T, int128>       ||
			std::is_same_v<_T, int256>       ||
			std::is_same_v<_T, int512>       ||
			std::is_same_v<_T, int1024>      ||
			std::is_same_v<_T, int2048>      ||
			std::is_same_v<_T, int4096>;
	};

	template <class _T>
	static constexpr bool ext_is_signed_v = ext_is_signed<_T>::value;

	template <class _T>
	struct ext_is_unsigned
	{
		static constexpr bool value =
			std::is_same_v<_T, lhashuint128>  ||
			std::is_same_v<_T, lhashuint256>  ||
			std::is_same_v<_T, lhashuint512>  ||
			std::is_same_v<_T, lhashuint1024> ||
			std::is_same_v<_T, lhashuint2048> ||
			std::is_same_v<_T, lhashuint4096> ||
			std::is_same_v<_T, uint128>       ||
			std::is_same_v<_T, uint256>       ||
			std::is_same_v<_T, uint512>       ||
			std::is_same_v<_T, uint1024>      ||
			std::is_same_v<_T, uint2048>      ||
			std::is_same_v<_T, uint4096>;
	};

	template <class _T>
	static constexpr bool ext_is_unsigned_v = ext_is_unsigned<_T>::value;

	template <class _T>
	struct ext_make_signed
	{
		typedef
			std::conditional_t<std::is_same_v<_T, lhashuint128>,  lhashint128,
			std::conditional_t<std::is_same_v<_T, lhashuint256>,  lhashint256,
			std::conditional_t<std::is_same_v<_T, lhashuint512>,  lhashint512,
			std::conditional_t<std::is_same_v<_T, lhashuint1024>, lhashint1024,
			std::conditional_t<std::is_same_v<_T, lhashuint2048>, lhashint2048,
			std::conditional_t<std::is_same_v<_T, lhashuint4096>, lhashint4096,
			std::conditional_t<std::is_same_v<_T, uint128>,       int128,
			std::conditional_t<std::is_same_v<_T, uint256>,       int256,
			std::conditional_t<std::is_same_v<_T, uint512>,       int512,
			std::conditional_t<std::is_same_v<_T, uint1024>,      int1024,
			std::conditional_t<std::is_same_v<_T, uint2048>,      int2048,
			std::conditional_t<std::is_same_v<_T, uint4096>,      int4096,
			std::conditional_t<std::is_ext_integral_v<_T>, _T, void>>>>>>>>>>>>
		type;
	};

	template <class _T>
	using ext_make_signed_t = ext_make_signed<_T>::type;

	template <class _T>
	struct ext_make_unsigned
	{
		typedef
			std::conditional_t<std::is_same_v<_T, lhashint128>,  lhashuint128,
			std::conditional_t<std::is_same_v<_T, lhashint256>,  lhashuint256,
			std::conditional_t<std::is_same_v<_T, lhashint512>,  lhashuint512,
			std::conditional_t<std::is_same_v<_T, lhashint1024>, lhashuint1024,
			std::conditional_t<std::is_same_v<_T, lhashint2048>, lhashuint2048,
			std::conditional_t<std::is_same_v<_T, lhashint4096>, lhashuint4096,
			std::conditional_t<std::is_same_v<_T, int128>,       uint128,
			std::conditional_t<std::is_same_v<_T, int256>,       uint256,
			std::conditional_t<std::is_same_v<_T, int512>,       uint512,
			std::conditional_t<std::is_same_v<_T, int1024>,      uint1024,
			std::conditional_t<std::is_same_v<_T, int2048>,      uint2048,
			std::conditional_t<std::is_same_v<_T, int4096>,      uint4096,
			std::conditional_t<std::is_ext_integral_v<_T>, _T, void>>>>>>>>>>>>
		type;
	};

	template <class _T>
	using ext_make_unsigned_t = ext_make_unsigned<_T>::type;
}
#endif



#endif // _LIBHASHABLES__types_EXT_INT_H_
