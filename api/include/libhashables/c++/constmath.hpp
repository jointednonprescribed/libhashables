
#ifndef _LIBHASHABLES__CONSTMATH_HPP_
#define _LIBHASHABLES__CONSTMATH_HPP_ 1



namespace libhashables
{
	template <class _T>
	constexpr _T const_min(_T a, _T b)
	{
		static_assert(std::is_floating_point_v<_T> || std::is_integral_v<_T>,
			"Cannot find the minimum between two non-arithmetic types.");
		
		return (a < b)? a : b;
	}
	template <class _T>
	constexpr _T const_max(_T a, _T b)
	{
		static_assert(std::is_floating_point_v<_T> || std::is_integral_v<_T>,
			"Cannot find the minimum between two non-arithmetic types.");
		
		return (a > b)? a : b;
	}
}



#endif // _LIBHASHABLES__CONSTMATH_HPP_
