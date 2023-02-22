/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:52:36 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 00:02:52 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "tree/Rb_tree.hpp"
# include "utils/algorithm.hpp"

namespace ft
{
	template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
		typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
	class map
	{
		public:
			typedef _Key						key_type;
			typedef _Tp							mapped_type;
			typedef ft::pair<const _Key, _Tp>	value_type;
			typedef _Compare					key_compare;
			typedef _Alloc						allocator_type;

		public:
			class value_compare
			: public std::binary_function<value_type, value_type, bool>
			{
				friend class ft::map<_Key, _Tp, _Compare, _Alloc>;
				protected:
					_Compare comp;
					value_compare(_Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const
					{ return comp(x.first, y.first); }
			};

		private:
			typedef typename _Alloc::template rebind<value_type>::other _Pair_alloc_type;

			typedef _Rb_tree<key_type, value_type, _Select1st<value_type>,
					key_compare, _Pair_alloc_type> _Rep_type;

			_Rep_type _M_t;

		public:
			typedef typename _Alloc::pointer					pointer;
			typedef typename _Alloc::const_pointer				const_pointer;
			typedef typename _Alloc::reference					reference;
			typedef typename _Alloc::const_reference			const_reference;

			typedef typename _Rep_type::iterator				iterator;
			typedef typename _Rep_type::const_iterator			const_iterator;
			typedef typename _Rep_type::reverse_iterator		reverse_iterator;
			typedef typename _Rep_type::const_reverse_iterator	const_reverse_iterator;
			typedef typename _Rep_type::size_type				size_type;
			typedef typename _Rep_type::difference_type			difference_type;

			map() : _M_t() { }

			explicit
			map(const _Compare& __comp,
			const allocator_type& __a = allocator_type())
			: _M_t(__comp, _Pair_alloc_type(__a)) { }

			map(const map& __x)
			: _M_t(__x._M_t) { }

			template <typename _InputIterator>
			map(_InputIterator __first, _InputIterator __last)
			: _M_t()
			{ _M_t._M_insert_range_unique(__first, __last); }

			template <typename _InputIterator>
			map(_InputIterator __first, _InputIterator __last,
			const _Compare& __comp,
			const allocator_type& __a = allocator_type())
			: _M_t(__comp, _Pair_alloc_type(__a))
			{ _M_t._M_insert_range_unique(__first, __last); }

			~map()
			{
				_M_t.clear();
			}

			map&
			operator=(const map& __x)
			{
				_M_t = __x._M_t;
				return *this;
			}

			allocator_type
			get_allocator() const
			{ return allocator_type(_M_t.get_allocator()); }

			iterator
			begin()
			{ return _M_t.begin(); }

			const_iterator
			begin() const
			{ return _M_t.begin(); }

			iterator
			end()
			{ return _M_t.end(); }

			const_iterator
			end() const
			{ return _M_t.end(); }

			reverse_iterator
			rbegin()
			{ return _M_t.rbegin(); }

			const_reverse_iterator
			rbegin() const
			{ return _M_t.rbegin(); }

			reverse_iterator
			rend()
			{ return _M_t.rend(); }

			const_reverse_iterator
			rend() const
			{ return _M_t.rend(); }

			bool
			empty() const
			{ return _M_t.empty(); }

			size_type
			size() const
			{ return _M_t.size(); }

			size_type
			max_size() const
			{ return _M_t.max_size(); }

			mapped_type&
			operator[](const key_type& __k)
			{
				iterator __i = lower_bound(__k);
				if (__i == end() || key_comp()(__k, (*__i).first))
					__i = insert(__i, value_type(__k, mapped_type()));
				return (*__i).second;
			}

			mapped_type&
			at(const key_type& __k)
			{
				iterator __i = lower_bound(__k);
				if (__i == end() || key_comp()(__k, (*__i).first))
					throw std::out_of_range("map::at");
				return (*__i).second;
			}

			const mapped_type&
			at(const key_type& __k) const
			{
				const_iterator __i = lower_bound(__k);
				if (__i == end() || key_comp()(__k, (*__i).first))
					throw std::out_of_range("map::at");
				return (*__i).second;
			}

			ft::pair<iterator, bool>
			insert(const value_type& __x)
			{ return _M_t._M_insert_unique(__x); }

			iterator
			insert(iterator __position, const value_type& __x)
			{ return _M_t._M_insert_unique_(__position, __x); }

			template <typename _InputIterator>
			void
			insert(_InputIterator __first, _InputIterator __last)
			{ _M_t._M_insert_range_unique(__first, __last); }

			void
			erase(iterator __position)
			{ _M_t.erase(__position); }

			size_type
			erase(const key_type& __x)
			{ return _M_t.erase(__x); }

			void
			erase(iterator __first, iterator __last)
			{ _M_t.erase(__first, __last); }

			void
			swap(map& __x)
			{ _M_t.swap(__x._M_t); }

			void
			clear()
			{ _M_t.clear(); }

			key_compare
			key_comp() const
			{ return _M_t.key_comp(); }

			value_compare
			value_comp() const
			{ return value_compare(_M_t.key_comp()); }

			iterator
			find(const key_type& __x)
			{ return _M_t.find(__x); }

			const_iterator
			find(const key_type& __x) const
			{ return _M_t.find(__x); }

			size_type
			count(const key_type& __x) const
			{ return _M_t.find(__x) == _M_t.end() ? 0 : 1; }

			iterator
			lower_bound(const key_type& __x)
			{ return _M_t.lower_bound(__x); }

			const_iterator
			lower_bound(const key_type& __x) const
			{ return _M_t.lower_bound(__x); }

			iterator
			upper_bound(const key_type& __x)
			{ return _M_t.upper_bound(__x); }

			const_iterator
			upper_bound(const key_type& __x) const
			{ return _M_t.upper_bound(__x); }

			ft::pair<iterator, iterator>
			equal_range(const key_type& __x)
			{ return _M_t.equal_range(__x); }

			ft::pair<const_iterator, const_iterator>
			equal_range(const key_type& __x) const
			{ return _M_t.equal_range(__x); }

			template <typename _K1, typename _T1, typename _C1, typename _A1>
			friend bool
			operator==(const map<_K1, _T1, _C1, _A1>&,
			const map<_K1, _T1, _C1, _A1>&);

			template <typename _K1, typename _T1, typename _C1, typename _A1>
			friend bool
			operator<(const map<_K1, _T1, _C1, _A1>&,
			const map<_K1, _T1, _C1, _A1>&);
	}; // class map

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline bool
	operator==(const map<_Key, _Tp, _Compare, _Alloc>& __x,
	const map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ return __x._M_t == __y._M_t; }

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline bool
	operator<(const map<_Key, _Tp, _Compare, _Alloc>& __x,
	const map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ return __x._M_t < __y._M_t; }

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline bool
	operator!=(const map<_Key, _Tp, _Compare, _Alloc>& __x,
	const map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ return !(__x == __y); }

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline bool
	operator>(const map<_Key, _Tp, _Compare, _Alloc>& __x,
	const map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ return __y < __x; }

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline bool
	operator<=(const map<_Key, _Tp, _Compare, _Alloc>& __x,
	const map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ return !(__y < __x); }

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline bool
	operator>=(const map<_Key, _Tp, _Compare, _Alloc>& __x,
	const map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ return !(__x < __y); }

	template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	inline void
	swap(map<_Key, _Tp, _Compare, _Alloc>& __x,
	map<_Key, _Tp, _Compare, _Alloc>& __y)
	{ __x.swap(__y); }
} // namespace ft

#endif // MAP_HPP
