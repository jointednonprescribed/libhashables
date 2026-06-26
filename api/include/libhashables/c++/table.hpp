
#ifndef _LIBHASHABLES__TABLE_HPP_
#define _LIBHASHABLES__TABLE_HPP_ 1

#ifndef _LIBHASHABLES__PACKUTILS_H_
#	include "packutils.hpp"
#endif
#ifndef _LIBHASHABLES__TABLE_H_
#	include "../table.h"
#endif
#ifndef _LIBHASHABLES__TYPES_HPP_
#	include "types.hpp"
#endif



namespace libhashables
{
	struct LHASH_API generic_table: protected lhashTable
	{
		class LHASH_API row
		{
		protected:
			generic_table *table;
			size_t         row;

		public:
			row()           noexcept;
			row(const row&) noexcept;
			row(row&&)      noexcept;
			row(generic_table *table, size_t row);

			virtual size_t Size(void);
			virtual size_t Get(size_t output_size, void *output);
			virtual size_t Get(size_t col, size_t output_size, void *output);
			virtual size_t GetWithHandler(const GTypeHandler *output);
			virtual size_t GetWithHandler(size_t col, const GTypeHandler *output);

			virtual void Set(size_t input_size, const void *output);
			virtual void Set(size_t col, size_t input_size, const void *output);
			virtual void SetWithHandler(const GTypeHandler *input);
			virtual void SetWithHandler(size_t col, const GTypeHandler *input);
		};
		class LHASH_API const_row
		{
		protected:
			const generic_table *table;
			size_t               row;

		public:
			const_row()                 noexcept;
			const_row(const const_row&) noexcept;
			const_row(const_row&&)      noexcept;
			const_row(const generic_table *table, size_t row);

			virtual size_t Size(void);
			virtual size_t Get(size_t output_size, void *output);
			virtual size_t Get(size_t col, size_t output_size, void *output);
			virtual size_t GetWithHandler(const GTypeHandler *output);
			virtual size_t GetWithHandler(size_t col, const GTypeHandler *output);
		};

		generic_table();
		generic_table(const generic_table&);
		generic_table(generic_table&&);

		typedef lhashTable&       primitive_reference_t;
		typedef const lhashTable& const_primitive_reference_t;
		typedef lhashTable        primitive_t;

		inline operator primitive_reference_t() noexcept
		{
			return generic_table::operator primitive_reference_t();
		}
		inline operator const_primitive_reference_t() noexcept
		{
			return generic_table::operator const_primitive_reference_t();
		}
		inline operator primitive_t() noexcept
		{
			return generic_table::operator primitive_t();
		}

		virtual const_row operator [](size_t i) const;
		virtual row       operator [](size_t i);
	};

	template <class ..._Cols>
	class LHASH_API table: public generic_table
	{
	public:
		template <bool _Const, class ..._Cols>
		class LHASH_API _row: public std::conditional_t<_Const, generic_table::const_row, generic_table::row>
		{
		public:
			template <size_t _Col>
			using type_in_column    = walk_pack<_Cols...>::element_by_index<const_min(_Col, sizeof...(_Cols))>;

			using parent_type       = std::conditional_t<_Const, generic_table::const_row, generic_table::row>;

			using qualified_table_t = std::conditional_t<_Const, const table<_Cols...>, table<_Cols...>>;

		protected:
			qualified_table *qual_table;

		public:
			_row()                 noexcept = default;
			_row(const const_row&) noexcept = default;
			_row(const_row&&)      noexcept = default;
			_row(qualified_table *table, size_t row):
				parent_type(table, row), qual_table(table)
			{}

			virtual size_t Size(void)
			{
				return sizeof(_Cols) + ...;
			}

			template <size_t _Col>
			virtual inline int Get(type_in_column<_Col> &output) const
			{
				constexpr size_t type_size = sizeof(decltype(output));

				return (Get(_Col, &output, type_size) != type_size);
			}

			template <size_t _Col>
			virtual std::enable_if_t<!_Const> Set(const type_in_column<_Col> &input)
			{
				constexpr size_t type_size = sizeof(decltype(output));

				return (Set(_Col, &output, type_size) != type_size);
			}
		};
		template <class ..._Cols>
		using row       = _row<false, _Cols...>;
		template <class ..._Cols>
		using const_row = _row<true, _Cols...>;

		static constexpr size_t
			nbytes       = sizeof(_Cols) + ...,
			column_count = sizeof...(_Cols);

		inline operator primitive_reference_t() noexcept
		{
			return generic_table::operator primitive_reference_t();
		}
		inline operator const_primitive_reference_t() noexcept
		{
			return generic_table::operator const_primitive_reference_t();
		}
		inline operator primitive_t() noexcept
		{
			return generic_table::operator primitive_t();
		}

		table():
			generic_table()
		{}
		table(const table<_Cols...> &cp):
			generic_table(cp)
		{}
		table(table<_Cols...> &&mv):
			generic_table(mv)
		{}

		int Drop(void)
		{
			lhashTable_Drop(this);
			this->data = lhashGetNullReference();
			this->cols = this->rows = 0;
		}

		~table()
		{
			lhashTable_Drop(this);
		}

		virtual const_row<_Cols...> operator [](size_t i) const
		{
			if (i >= rows)
				return const_row<_Cols...>();
			else
				return const_row<_Cols...>(this, i);
		}
		virtual row<_Cols...>       operator [](size_t i)
		{
			if (i >= rows)
				return row<_Cols...>();
			else
				return row<_Cols...>(this, i);
		}

		/* Push a row into the table from a type handler, chainable; return value is always self. */
		lhashTable* Push(lhashTable *self, lhashGTypeHandler *row_streamer);
		/* Push an unpadded tuple as a row into the table, nbytes is the total size (in bytes) of the
		.  tuple. */
		lhashTable* PushT(lhashTable *self, const void *tuple, size_t nbytes);

		/* Push a row into the table from a type handler at a particular index, chainable; return
		.  value is always self. */
		lhashTable* PushI(lhashTable *self, size_t at, lhashGTypeHandler *row_streamer);
		/* Push an unpadded tuple as a row into the table at a particular index, nbytes is the total
		.  size (in bytes) of the tuple. */
		lhashTable* PushTi(lhashTable *self, size_t at, const void *tuple, size_t nbytes);

		/* Copy a row from the table into a type handler, chainable; return value is always
		.  self. */
		lhashTable* Get(lhashTable *self, size_t row, lhashGTypeHandler *row_streamer);
		/* Copy a row from the table as an unpadded tuple, nbytes is the total size (in bytes) of the
		.  buffer for this tuple. */
		lhashTable* GetT(lhashTable *self, size_t row, void *buffer, size_t nbytes);

		/* Pop (copy, then remove) a row from the table into a type handler, chainable; return value
		.  is always self. */
		lhashTable* Pop(lhashTable *self, size_t row, lhashGTypeHandler *row_streamer);
		/* Pop a row from the table as an unpadded tuple, nbytes is the total size (in bytes) of the
		.  buffer for this tuple. */
		lhashTable* PopT(lhashTable *self, size_t row, void *buffer, size_t nbytes);

		/* Remove a row from the table, chainable; return value is always self. */
		lhashTable* Remove(lhashTable *self, size_t row);

		size_t      GetColumnSize(lhashTable *self, size_t col);
		size_t      GetTableWidth(lhashTable *self);
		size_t      GetTableHeight(lhashTable *self);
		size_t      GetColumnCount(lhashTable *self);
		size_t      GetCellCount(lhashTable *self);

		lhashTableColumnHeader* GetColumnHeader(lhashTable *self, size_t col);

		void*       GetRow(lhashTable *self, size_t row);

		lhashTable* GetCell(lhashTable *self, size_t col, size_t row, void *output, size_t output_size);
		lhashTable* GetCellH(lhashTable *self, size_t col, size_t row, lhashGTypeHandler *output);

		lhashTable* SetCell(lhashTable *self, size_t col, size_t row, const void *input);
		lhashTable* SetCellH(lhashTable *self, size_t col, size_t row, lhashGTypeHandler *input);
	};
}



#endif // _LIBHASHABLES__TABLE_HPP_
