/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_traits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:11:12 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 02:39:28 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_TYPE_TRAITS_HPP__
# define __FT_TYPE_TRAITS_HPP__

namespace ft
{
	struct __true_type {};
	struct __false_type {};

	template <bool>
	struct __truth_type
	{ typedef __false_type __type; };

	template <>
	struct __truth_type<true>
	{ typedef __true_type __type; };

	template <typename, typename>
	struct __are_same
	{
		enum { __value = 0 };
		typedef __false_type __type;
	};

	template <typename _Tp>
	struct __are_same<_Tp, _Tp>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <typename _Tp>
	struct __is_integer
	{
		enum { __value = 0 };
		typedef __false_type __type;
	};

	template <>
	struct __is_integer<bool>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<char>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<signed char>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned char>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<wchar_t>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<short>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned short>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<int>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned int>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<long long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <>
	struct __is_integer<unsigned long long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

}

#endif
