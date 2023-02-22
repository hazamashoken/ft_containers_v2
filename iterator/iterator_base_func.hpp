/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_base_func.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:36:34 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/22 23:17:10 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_BASE_FUNC_HPP__
# define __ITERATOR_BASE_FUNC_HPP__

#include "iterator_base_types.hpp"

namespace ft
{
	template <typename _InputIterator>
	inline
	typename iterator_traits<_InputIterator>::difference_type
	__distance(_InputIterator __first, _InputIterator __last,
		std::input_iterator_tag)
	{
		typename iterator_traits<_InputIterator>::difference_type __n = 0;
		while (__first != __last)
		{
			++__first;
			++__n;
		}
		return __n;
	}

	template <typename _RandomAccessIterator>
	inline
	typename iterator_traits<_RandomAccessIterator>::difference_type
	__distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
		std::random_access_iterator_tag)
	{
		return __last - __first;
	}

	template <typename _InputIterator>
	inline
	typename iterator_traits<_InputIterator>::difference_type
	distance(_InputIterator __first, _InputIterator __last)
	{
		return ft::__distance(__first, __last,
			ft::__iterator_category(__first));
	}

	template <typename _InputIterator, typename _Distance>
	inline
	void
	__advance(_InputIterator& __i, _Distance __n, std::input_iterator_tag)
	{
		while (__n--)
			++__i;
	}

	template <typename _BidirectionalIterator, typename _Distance>
	inline
	void
	__advance(_BidirectionalIterator& __i, _Distance __n,
		std::bidirectional_iterator_tag)
	{
		if (__n >= 0)
			while (__n--)
				++__i;
		else
			while (__n++)
				--__i;
	}

	template <typename _RandomAccessIterator, typename _Distance>
	inline
	void
	__advance(_RandomAccessIterator& __i, _Distance __n,
		std::random_access_iterator_tag)
	{
		__i += __n;
	}

	template <typename _InputIterator, typename _Distance>
	inline
	void
	advance(_InputIterator& __i, _Distance __n)
	{
		ft::__advance(__i, __n, ft::__iterator_category(__i));
	}
}

#endif
