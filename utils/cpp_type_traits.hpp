/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_type_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:11:12 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 01:02:36 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_CPP_TYPE_TRAITS_HPP__
# define __FT_CPP_TYPE_TRAITS_HPP__

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

	// template <class _Sp, class _Tp>
	// struct __traitor
	// {
	// 	enum { __value = bool(_Sp::__value) || bool(_Tp::__value) };
	// 	typedef typename __truth_type<__value>::__type __type;
	// };

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

	// template <typename _Tp>
	// struct __is_void
	// {
	// 	enum { __value = 0 };
	// 	typedef __false_type __type;
	// };

	// template <>
	// struct __is_void<void>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

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

	// template <typename _Tp>
	// struct __is_floating
	// {
	// 	enum { __value = 0 };
	// 	typedef __false_type __type;
	// };

	// template <>
	// struct __is_floating<float>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <>
	// struct __is_floating<double>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <>
	// struct __is_floating<long double>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <typename _Tp>
	// struct __is_pointer
	// {
	// 	enum { __value = 0 };
	// 	typedef __false_type __type;
	// };

	// template <typename _Tp>
	// struct __is_pointer<_Tp*>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <typename _Tp>
	// struct __is_arithmetic
	// : public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >
	// { };

	// template <typename _Tp>
	// struct __is_scalar
	// : public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >
	// { };

	// template <typename _Tp>
	// struct __is_char
	// {
	// 	enum { __value = 0 };
	// 	typedef __false_type __type;
	// };

	// template <>
	// struct __is_char<char>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <typename _Tp>
	// struct __is_byte
	// {
	// 	enum { __value = 0 };
	// 	typedef __false_type __type;
	// };

	// template <>
	// struct __is_byte<char>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <>
	// struct __is_byte<signed char>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

	// template <>
	// struct __is_byte<unsigned char>
	// {
	// 	enum { __value = 1 };
	// 	typedef __true_type __type;
	// };

}

#endif
