/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:35:11 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 00:59:06 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ITERATOR_HPP_
# define _ITERATOR_HPP_

# include <iostream>

# include "../type_traits.hpp"
# include "iterator_base.hpp"

namespace ft
{
	using ft::iterator_traits;
	using ft::iterator;

	template <typename Iterator>
	class base_iterator
	{
		protected:
			Iterator								_ptr;
			typedef iterator_traits<Iterator>	traits_type;

		public:
			typedef Iterator									iterator_type;
			typedef typename traits_type::iterator_category		iterator_category;
			typedef typename traits_type::value_type			value_type;
			typedef typename traits_type::difference_type		difference_type;
			typedef typename traits_type::pointer				pointer;
			typedef typename traits_type::reference				reference;

			base_iterator() : _ptr(Iterator()) {}
			explicit base_iterator(Iterator it) : _ptr(it) {}
			template <class Iter>
			base_iterator(const base_iterator<Iter>& base_it) : _ptr(base_it.base()) {}
			virtual ~base_iterator() {}

			base_iterator& operator=(const base_iterator& base_it)
			{
				_ptr = base_it._ptr;
				return *this;
			}

			base_iterator& operator=(const pointer& ptr)
			{
				_ptr = ptr;
				return *this;
			}

			const iterator_type&	base() const { return _ptr; }

			reference		operator*() const { return *_ptr; }
			pointer			operator->() const { return _ptr; }

			base_iterator&	operator++()
			{
				++_ptr;
				return *this;
			}

			base_iterator	operator++(int)
			{
				base_iterator tmp = *this;
				++_ptr;
				return tmp;
			}

			base_iterator&	operator--()
			{
				--_ptr;
				return *this;
			}

			base_iterator	operator--(int)
			{
				base_iterator tmp = *this;
				--_ptr;
				return tmp;
			}

			base_iterator	operator+(difference_type n) const
			{
				base_iterator tmp = *this;
				return tmp += n;
			}

			base_iterator	operator-(difference_type n) const
			{
				base_iterator tmp = *this;
				return tmp -= n;
			}

			base_iterator&	operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			}

			base_iterator&	operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			}

			reference		operator[](difference_type n) const { return *(*this + n); }
	};

	template <typename Iterator>
	inline bool operator==(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator==(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator>
	inline bool operator!=(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator!=(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iterator>
	inline bool operator<(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator<(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator>
	inline bool operator<=(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator<=(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iterator>
	inline bool operator>(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator>(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator>
	inline bool operator>=(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator>=(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator>
	inline typename base_iterator<Iterator>::difference_type operator-(const base_iterator<Iterator>& lhs, const base_iterator<Iterator>& rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline typename base_iterator<Iterator_L>::difference_type operator-(const base_iterator<Iterator_L>& lhs, const base_iterator<Iterator_R>& rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename Iterator>
	inline base_iterator<Iterator> operator+(typename base_iterator<Iterator>::difference_type n, const base_iterator<Iterator>& rhs)
	{
		return base_iterator<Iterator>(rhs.base() + n);
	}

	template <typename Iterator>
	class reverse_iterator
	: public iterator<
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator									_ptr;
			typedef iterator_traits<Iterator>			traits_type;

		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;

			reverse_iterator() : _ptr() {}
			explicit reverse_iterator(iterator_type it) : _ptr(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base()) {}
			~reverse_iterator() {}

			reverse_iterator& operator=(const reverse_iterator& rev_it)
			{
				_ptr = rev_it.base();
				return *this;
			}

			iterator_type	base() const { return _ptr; }

			reference		operator*() const
			{
				iterator_type tmp = _ptr;
				return *--tmp;
			}

			pointer			operator->() const {
				iterator_type tmp = _ptr;
				--tmp;
				return _get_pointer(tmp);
			}

		private:
			template <typename Iter>
			static Iter*	_get_pointer(Iter* it)
			{
				return it;
			}

			template <typename Iter>
			static pointer		_get_pointer(Iter it)
			{
				return it.operator->();
			}

		public:
			reverse_iterator&	operator++()
			{
				--_ptr;
				return *this;
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator tmp = *this;
				--_ptr;
				return tmp;
			}

			reverse_iterator&	operator--()
			{
				++_ptr;
				return *this;
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator tmp = *this;
				++_ptr;
				return tmp;
			}

			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(_ptr - n);
			}

			reverse_iterator&	operator+=(difference_type n)
			{
				_ptr -= n;
				return *this;
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return reverse_iterator(_ptr + n);
			}

			reverse_iterator&	operator-=(difference_type n)
			{
				_ptr += n;
				return *this;
			}

			reference			operator[](difference_type n) const
			{
				return *(*this + n);
			}
	};

	template <typename Iterator>
	inline bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator==(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator>
	inline bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator!=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iterator>
	inline bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator<(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator>
	inline bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator<=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator>
	inline bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator>(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator>
	inline bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline bool operator>=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <typename Iterator_L, typename Iterator_R>
	inline typename reverse_iterator<Iterator_L>::difference_type operator-(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <typename Iterator>
	inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

}

#endif
