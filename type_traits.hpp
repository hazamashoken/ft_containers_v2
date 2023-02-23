/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:25:17 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 19:49:18 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <limits>
# include <typeinfo>
# include <algorithm>

namespace ft
{
	/// @brief enable_if type match
	/// @tparam T type
	/// @tparam B boolean
	template <bool, typename T = void>
	struct enable_if
	{};

	/// @brief enable_if type match
	/// @tparam T type to match
	template <typename T>
	struct enable_if<true, T>
	{ typedef T type; };

	template <typename T>
	struct is_integral
	{
		static const bool value = std::numeric_limits<T>::is_integer;
	};

	template <typename, typename>
	struct are_same
	{
		enum { value = 0 };
	};

	template <typename _Tp>
	struct are_same<_Tp, _Tp>
	{
		enum { value = 1 };
	};

}

#endif
