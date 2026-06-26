
#ifndef _LIBHASHABLES__PACKUTILS_HPP_
#define _LIBHASHABLES__PACKUTILS_HPP_ 1



namespace libhashables
{
	template <class ..._Pack>
	struct walk_pack
	{
		template <size_t _I, size_t _L, class _First, class ..._Rest>
		typedef std::conditional_t<
			_I == 0,
			_First,
			std::conditional_t<
				sizeof...(_Rest) == 0 || _I >= _L,
				void,
				_element_by_index<_I - 1, _L, _Rest..., void>
			>
		> _element_by_index;

		template <size_t _I>
		typedef _element_by_index<_I, sizeof...(_Pack), _Pack..., void> element_by_index;
	};
}



#endif // _LIBHASHABLES__PACKUTILS_HPP_
