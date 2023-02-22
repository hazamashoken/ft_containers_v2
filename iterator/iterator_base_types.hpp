/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_base_types.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:23:55 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/22 23:16:31 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_BASE_TYPES_HPP__
# define __ITERATOR_BASE_TYPES_HPP__

# include <cstddef>

namespace ft
{
	template < typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
		typename _Pointer = _Tp*, typename _Reference = _Tp& >
	struct iterator
	{
		/// @brief One of the @link iterator_tags tag types@endlink.
		typedef _Category	iterator_category;
		/// @brief The type "pointed to" by the iterator.
		typedef _Tp			value_type;
		/// @brief Distance between iterators is represented as this type.
		typedef _Distance	difference_type;
		/// @brief This type represents a pointer-to-value_type.
		typedef _Pointer	pointer;
		/// @brief This type represents a reference-to-value_type.
		typedef _Reference	reference;
	};

	template <typename _Iterator>
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category	iterator_category;
		typedef typename _Iterator::value_type			value_type;
		typedef typename _Iterator::difference_type		difference_type;
		typedef typename _Iterator::pointer				pointer;
		typedef typename _Iterator::reference			reference;
	};

	template <typename _Tp>
	struct iterator_traits<_Tp*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef _Tp							value_type;
		typedef ptrdiff_t					difference_type;
		typedef _Tp*						pointer;
		typedef _Tp&						reference;
	};

	template <typename _Tp>
	struct iterator_traits<const _Tp*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef _Tp							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const _Tp*					pointer;
		typedef const _Tp&					reference;
	};

	template <typename _Iter>
	inline
	typename iterator_traits<_Iter>::iterator_category
	__iterator_category(const _Iter&)
	{
		return typename iterator_traits<_Iter>::iterator_category();
	}

	template <typename _Iterator, bool _HasBase>
	struct _Iter_base
	{
		typedef _Iterator iterator_type;
		static iterator_type _S_base(_Iterator __it)
		{ return __it; }

	};

	template <typename _Iterator>
	struct _Iter_base<_Iterator, true>
	{
		typedef typename _Iterator::iterator_type iterator_type;
		static iterator_type _S_base(_Iterator __it)
		{ return __it.base(); }
	};
}

#endif
