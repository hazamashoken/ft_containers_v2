/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:25:17 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 02:41:31 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <limits>
# include "utils/ft_type_traits.hpp"

namespace ft
{
	/// @brief enable_if type match
	/// @tparam T type
	/// @tparam B boolean
	template <bool B, class T = void>
	struct enable_if {};

	/// @brief enable_if type match
	/// @tparam T type to match
	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	template <typename T>
	struct is_integral
	{
		static const bool value = std::numeric_limits<T>::is_integer;
	};

}

#endif
