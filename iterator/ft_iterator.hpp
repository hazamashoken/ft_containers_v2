/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:41:38 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 02:03:01 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_ITERATOR_HPP__
# define __FT_ITERATOR_HPP__

# include "../type_traits.hpp"
# include "iterator_base_func.hpp"
# include "iterator_base_types.hpp"

namespace ft
{
	template <typename _Iterator>
	class reverse_iterator
	: public ft::iterator<typename iterator_traits<_Iterator>::iterator_category,
			typename iterator_traits<_Iterator>::value_type,
			typename iterator_traits<_Iterator>::difference_type,
			typename iterator_traits<_Iterator>::pointer,
			typename iterator_traits<_Iterator>::reference>
	{
		protected:
			_Iterator									current;

			typedef ft::iterator_traits<_Iterator>		__traits_type;

		public:
			typedef _Iterator								iterator_type;
			typedef typename __traits_type::difference_type	difference_type;
			typedef typename __traits_type::pointer			pointer;
			typedef typename __traits_type::reference		reference;

			reverse_iterator() : current() {}

			explicit
			reverse_iterator(iterator_type __x) : current(__x) {}

			reverse_iterator(const reverse_iterator& __x)
			: current(__x.current) {}

			template <typename _Iter>
			reverse_iterator(const reverse_iterator<_Iter>& __x)
			: current(__x.base()) {}

			iterator_type
			base() const
			{ return current; }

			reference
			operator*() const
			{
				_Iterator __tmp = current;
				return *--__tmp;
			}

			pointer
			operator->() const
			{
				_Iterator __tmp = current;
				--__tmp;
				return _S_to_pointer(__tmp);
			}

			reverse_iterator&
			operator++()
			{
				--current;
				return *this;
			}

			reverse_iterator
			operator++(int)
			{
				reverse_iterator __tmp = *this;
				--current;
				return __tmp;
			}

			reverse_iterator&
			operator--()
			{
				++current;
				return *this;
			}

			reverse_iterator
			operator--(int)
			{
				reverse_iterator __tmp = *this;
				++current;
				return __tmp;
			}

			reverse_iterator
			operator+(difference_type __n) const
			{ return reverse_iterator(current - __n); }

			reverse_iterator&
			operator+=(difference_type __n)
			{
				current -= __n;
				return *this;
			}

			reverse_iterator
			operator-(difference_type __n) const
			{ return reverse_iterator(current + __n); }

			reverse_iterator&
			operator-=(difference_type __n)
			{
				current += __n;
				return *this;
			}

			reference
			operator[](difference_type __n) const
			{ return *(*this + __n); }

		private:
			template <typename _Tp>
			static _Tp*
			_S_to_pointer(_Tp* __p)
			{ return __p; }

			template <typename _Tp>
			static pointer
			_S_to_pointer(_Tp __it)
			{ return __it.operator->(); }

	};

	template <typename _Iterator>
	inline bool
	operator==(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return __x.base() == __y.base(); }

	template <typename _Iterator>
	inline bool
	operator<(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return __y.base() < __x.base(); }

	template <typename _Iterator>
	inline bool
	operator!=(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return !(__x == __y); }

	template <typename _Iterator>
	inline bool
	operator>(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return __y < __x; }

	template <typename _Iterator>
	inline bool
	operator<=(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return !(__y < __x); }

	template <typename _Iterator>
	inline bool
	operator>=(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return !(__x < __y); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool
	operator==(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return __x.base() == __y.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool
	operator<(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return __y.base() < __x.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool
	operator!=(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return !(__x == __y); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool
	operator>(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return __y < __x; }

	template <typename _IteratorL, typename _IteratorR>
	inline bool
	operator<=(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return !(__y < __x); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool
	operator>=(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return !(__x < __y); }

	template <typename _Iterator>
	inline typename reverse_iterator<_Iterator>::difference_type
	operator-(const reverse_iterator<_Iterator>& __x,
			const reverse_iterator<_Iterator>& __y)
	{ return __y.base() - __x.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline typename reverse_iterator<_IteratorL>::difference_type
	operator-(const reverse_iterator<_IteratorL>& __x,
			const reverse_iterator<_IteratorR>& __y)
	{ return __y.base() - __x.base(); }

	template <typename _Iterator>
	inline reverse_iterator<_Iterator>
	operator+(typename reverse_iterator<_Iterator>::difference_type __n,
			const reverse_iterator<_Iterator>& __x)
	{ return reverse_iterator<_Iterator>(__x.base() - __n); }
}

namespace ft
{
	using ft::iterator_traits;
	using ft::iterator;

	template <typename _Iterator, typename _Container>
	class base_iterator
	{
		protected:
			_Iterator _M_current;

			typedef iterator_traits<_Iterator>		__traits_type;

		public:
			typedef _Iterator									iterator_type;
			typedef typename __traits_type::iterator_category	iterator_category;
			typedef typename __traits_type::value_type			value_type;
			typedef typename __traits_type::difference_type		difference_type;
			typedef typename __traits_type::reference			reference;
			typedef typename __traits_type::pointer				pointer;

			base_iterator()
			: _M_current(_Iterator()) { }

			explicit
			base_iterator(const _Iterator& __i)
			: _M_current(__i) { }

			template <typename _Iter>
			base_iterator(const base_iterator<_Iter,
					typename ft::__enable_if<
					(ft::__are_same<_Iter, typename _Container::pointer>::__value),
					_Container>::__type>& __i)
			: _M_current(__i.base()) { }

			reference
			operator*() const
			{ return *_M_current; }

			pointer
			operator->() const
			{ return _M_current; }

			base_iterator&
			operator++()
			{
				++_M_current;
				return *this;
			}

			base_iterator
			operator++(int)
			{ return base_iterator(_M_current++); }

			base_iterator&
			operator--()
			{
				--_M_current;
				return *this;
			}

			base_iterator
			operator--(int)
			{ return base_iterator(_M_current--); }

			reference
			operator[](difference_type __n) const
			{ return _M_current[__n]; }

			base_iterator&
			operator+=(difference_type __n)
			{ _M_current += __n; return *this; }

			base_iterator
			operator+(difference_type __n) const
			{ return base_iterator(_M_current + __n); }

			base_iterator&
			operator-=(difference_type __n)
			{ _M_current -= __n; return *this; }

			base_iterator
			operator-(difference_type __n) const
			{ return base_iterator(_M_current - __n); }

			const _Iterator&
			base() const
			{ return _M_current; }
	};

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
	operator==(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() == __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline bool
	operator==(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() == __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
	operator!=(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() != __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline bool
	operator!=(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() != __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
	operator<(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() < __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline bool
	operator<(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() < __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
	operator>(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() > __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline bool
	operator>(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() > __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
	operator<=(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() <= __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline bool
	operator<=(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() <= __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool
	operator>=(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() >= __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline bool
	operator>=(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() >= __rhs.base(); }

	template <typename _IteratorL, typename _IteratorR, typename _Container>
	inline typename base_iterator<_IteratorL, _Container>::difference_type
	operator-(const base_iterator<_IteratorL, _Container>& __lhs,
			const base_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() - __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline typename base_iterator<_Iterator, _Container>::difference_type
	operator-(const base_iterator<_Iterator, _Container>& __lhs,
			const base_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() - __rhs.base(); }

	template <typename _Iterator, typename _Container>
	inline base_iterator<_Iterator, _Container>
	operator+(typename base_iterator<_Iterator, _Container>::difference_type __n,
			const base_iterator<_Iterator, _Container>& __i)
	{ return base_iterator<_Iterator, _Container>(__i.base() + __n); }

}

#endif
