/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:17:59 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 02:25:51 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	/// @brief compare two ranges lexicographically
	/// @tparam InputIterator1  first iterator type
	/// @tparam InputIterator2  second iterator type
	/// @param first1  first iterator
	/// @param last1  last iterator
	/// @param first2  second iterator
	/// @param last2  last iterator
	/// @return  true if the first range is lexicographically less than the second
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	/// @brief compare two ranges lexicographically
	/// @tparam InputIt1  first iterator type
	/// @tparam InputIt2  second iterator type
	/// @tparam Compare  comparison type
	/// @param first1  first iterator
	/// @param last1  last iterator
	/// @param first2  second iterator
	/// @param last2  last iterator
	/// @param comp  comparison function
	/// @return  true if the first range is lexicographically less than the second
	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return 	(first1 == last1) && (first2 != last2);
	}

	/// @brief check if two ranges are equal
	/// @tparam InputIterator1 first iterator type
	/// @tparam InputIterator2 second iterator type
	/// @param first1 first iterator
	/// @param last1 last iterator
	/// @param first2 second iterator
	/// @return
	template< class InputIterator1, class InputIterator2 >
	bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/// @brief check if two ranges are equal
	/// @tparam InputIt1 first iterator type
	/// @tparam InputIt2 second iterator type
	/// @tparam BinaryPredicate predicate type
	/// @param first1 first iterator
	/// @param last1 last iterator
	/// @param first2 second iterator
	/// @param p predicate
	/// @return true if the two ranges are equal
	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
	{
		while (first1 != last1)
		{
			if (!p(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}


}

#endif
