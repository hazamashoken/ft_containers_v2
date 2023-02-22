/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:54:12 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/22 23:01:04 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	template <bool _BoolType>
	struct __equal
	{
		template <typename _II1, typename _II2>
		static bool
		equal(_II1 __first1, _II1 __last1, _II2 __first2)
		{
			for (; __first1 != __last1; ++__first1, (void) ++__first2)
				if (!(*__first1 == *__first2))
					return (false);
			return (true);
		}
	};

	template <>
	struct __equal<true>
	{
		template <typename _Tp>
		static bool
		equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
		{
			const size_t __len = __last1 - __first1;
			return !__builtin_memcmp(__first1, __first2, sizeof(_Tp) * __len);
		}
	};

}

#endif
