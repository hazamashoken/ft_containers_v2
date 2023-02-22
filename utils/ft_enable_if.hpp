/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enable_if.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:08:04 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 02:43:50 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_ENABLE_IF_HPP_
# define _FT_ENABLE_IF_HPP_

# include <typeinfo>
# include "ft_type_traits.hpp"


namespace ft
{
	template <bool, typename>
	struct __enable_if
	{ };

	template <typename _Tp>
	struct __enable_if<true, _Tp>
	{ typedef _Tp __type; };

	template <bool _Cond, typename _Iftrue, typename _Iffalse>
	struct __conditional_type
	{ typedef _Iftrue __type; };

	template <typename _Iftrue, typename _Iffalse>
	struct __conditional_type<false, _Iftrue, _Iffalse>
	{ typedef _Iffalse __type; };

	template <typename _Tp>
	struct __add_unsigned
	{
		private:
			typedef __enable_if<ft::__is_integer<_Tp>::__value, _Tp> __if_type;

		public:
			typedef typename __if_type::__type __type;
	};

	template <>
	struct __add_unsigned<char>
	{ typedef unsigned char __type; };

	template <>
	struct __add_unsigned<signed char>
	{ typedef unsigned char __type; };

	template <>
	struct __add_unsigned<short>
	{ typedef unsigned short __type; };

	template <>
	struct __add_unsigned<int>
	{ typedef unsigned int __type; };

	template <>
	struct __add_unsigned<long>
	{ typedef unsigned long __type; };

	template <>
	struct __add_unsigned<long long>
	{ typedef unsigned long long __type; };

	template <>
	struct __add_unsigned<bool>;

	template <>
	struct __add_unsigned<wchar_t>;

	template <typename _Tp>
	struct __remove_unsigned
	{
		private:
			typedef __enable_if<ft::__is_integer<_Tp>::__value, _Tp> __if_type;

		public:
			typedef typename __if_type::__type __type;
	};

	template <>
	struct __remove_unsigned<char>
	{ typedef signed char __type; };

	template <>
	struct __remove_unsigned<unsigned char>
	{ typedef signed char __type; };

	template <>
	struct __remove_unsigned<unsigned short>
	{ typedef short __type; };

	template <>
	struct __remove_unsigned<unsigned int>
	{ typedef int __type; };

	template <>
	struct __remove_unsigned<unsigned long>
	{ typedef long __type; };

	template <>
	struct __remove_unsigned<unsigned long long>
	{ typedef long long __type; };

	template <>
	struct __remove_unsigned<bool>;

	template <>
	struct __remove_unsigned<wchar_t>;

	template <typename _Type>
	inline bool
	__is_null_pointer(_Type* __ptr)
	{ return __ptr == 0; }

	template <typename _Type>
	inline bool
	__is_null_pointer(_Type)
	{ return false; }

}

#endif
