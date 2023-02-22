/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:33:37 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 00:03:24 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "tree/Rb_tree.hpp"
# include "iterator.hpp"
# include "utils/algorithm.hpp"


namespace ft
{
	template <typename _Key, typename _Compare = std::less<_Key>,
		typename _Alloc = std::allocator<_Key> >
	class set
	{
		public:
			typedef _Key						key_type;
			typedef _Key						value_type;
			typedef _Compare					key_compare;
			typedef _Compare					value_compare;
			typedef _Alloc						allocator_type;

		private:
			typedef typename _Alloc::template rebind<value_type>::other _Key_alloc_type;

			typedef _Rb_tree<key_type, value_type, _Identity<value_type>,
					key_compare, _Key_alloc_type> _Rep_type;
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

			set() : _M_t() {}

			explicit
			set(const _Compare& __comp,
			const allocator_type& __a = allocator_type())
			: _M_t(__comp, _Key_alloc_type(__a)) { }

			template <typename _InputIterator>
			set(_InputIterator __first, _InputIterator __last)
			: _M_t()
			{ _M_t._M_insert_range_unique(__first, __last); }

			template <typename _InputIterator>
			set(_InputIterator __first, _InputIterator __last,
			const _Compare& __comp,
			const allocator_type& __a = allocator_type())
			: _M_t(__comp, _Key_alloc_type(__a))
			{ _M_t._M_insert_range_unique(__first, __last); }

			set(const set& __x)
			: _M_t(__x._M_t) { }

			~set() { }

			set&
			operator=(const set& __x)
			{
				_M_t = __x._M_t;
				return *this;
			}

			key_compare
			key_comp() const
			{ return _M_t.key_comp(); }

			value_compare
			value_comp() const
			{ return _M_t.key_comp(); }

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

			void
			swap(set& __x)
			{ _M_t.swap(__x._M_t); }

			ft::pair<iterator,bool>
			insert(const value_type& __x)
			{
				ft::pair<typename _Rep_type::iterator, bool> __p =
				_M_t._M_insert_unique(__x);
				return ft::pair<iterator, bool>(__p.first, __p.second);
			}

			iterator
			insert(const_iterator __position, const value_type& __x)
			{
				return _M_t._M_insert_unique_(__position, __x);
			}

			template <typename _InputIterator>
			void
			insert(_InputIterator __first, _InputIterator __last)
			{ _M_t._M_insert_range_unique(__first, __last); }

			void
			erase(iterator __position)
			{
				_M_t.erase(__position);
			}

			size_type
			erase(const key_type& __x)
			{ return _M_t.erase(__x); }

			void
			erase(iterator __first, iterator __last)
			{ _M_t.erase(__first, __last); }

			void
			clear()
			{ _M_t.clear(); }

			size_type
			count(const key_type& __x) const
			{ return _M_t.find(__x) == _M_t.end() ? 0 : 1; }

			iterator
			find(const key_type& __x)
			{ return _M_t.find(__x); }

			const_iterator
			find(const key_type& __x) const
			{ return _M_t.find(__x); }

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

			ft::pair<iterator,iterator>
			equal_range(const key_type& __x)
			{ return _M_t.equal_range(__x); }

			ft::pair<const_iterator,const_iterator>
			equal_range(const key_type& __x) const
			{ return _M_t.equal_range(__x); }

			template <typename _K1, typename _C1, typename _A1>
			friend bool
			operator==(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);

			template <typename _K1, typename _C1, typename _A1>
			friend bool
			operator<(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);
	}; // class set

	template <typename _Key, typename _Compare, typename _Alloc>
	inline bool
	operator==(const set<_Key, _Compare, _Alloc>& __x,
			const set<_Key, _Compare, _Alloc>& __y)
	{ return __x._M_t == __y._M_t; }

	template <typename _Key, typename _Compare, typename _Alloc>
	inline bool
	operator<(const set<_Key, _Compare, _Alloc>& __x,
			const set<_Key, _Compare, _Alloc>& __y)
	{ return __x._M_t < __y._M_t; }

	template <typename _Key, typename _Compare, typename _Alloc>
	inline bool
	operator!=(const set<_Key, _Compare, _Alloc>& __x,
			const set<_Key, _Compare, _Alloc>& __y)
	{ return !(__x == __y); }

	template <typename _Key, typename _Compare, typename _Alloc>
	inline bool
	operator>(const set<_Key, _Compare, _Alloc>& __x,
			const set<_Key, _Compare, _Alloc>& __y)
	{ return __y < __x; }

	template <typename _Key, typename _Compare, typename _Alloc>
	inline bool
	operator<=(const set<_Key, _Compare, _Alloc>& __x,
			const set<_Key, _Compare, _Alloc>& __y)
	{ return !(__y < __x); }

	template <typename _Key, typename _Compare, typename _Alloc>
	inline bool
	operator>=(const set<_Key, _Compare, _Alloc>& __x,
			const set<_Key, _Compare, _Alloc>& __y)
	{ return !(__x < __y); }

	template <typename _Key, typename _Compare, typename _Alloc>
	inline void
	swap(set<_Key, _Compare, _Alloc>& __x, set<_Key, _Compare, _Alloc>& __y)
	{ __x.swap(__y); }

} // namespace ft

#endif // SET_HPP
