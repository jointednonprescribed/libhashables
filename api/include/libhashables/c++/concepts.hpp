
#ifndef _LIBHASHABLES__CONCEPTS_HPP_
#define _LIBHASHABLES__CONCEPTS_HPP_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#	include "../includes.h"
#endif



namespace libhashables
{
	template <class _T>
	struct remove_remote_qualifiers
	{
		typedef
			std::conditional_t<
				std::is_pointer_v<_T>,
					remove_remote_qualifiers<std::remove_pointer_t<_T>>,
			std::conditional_t<
				std::is_reference_v<_T>,
					remove_remote_qualifiers<std::remove_reference_t<_T>>,
			std::conditional_t<
				std::is_array_v<_T>,
					remove_remote_qualifiers<std::remove_all_extents_t<_T>>,
					_T
			>>> type;
	};

	template <class _T>
	using remove_remote_qualifiers_t = typename remove_remote_qualifiers<_T>::type;
}



#endif // _LIBHASHABLES__CONCEPTS_HPP_
