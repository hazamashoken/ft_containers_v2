/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:47:56 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/22 23:53:28 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <functional>

namespace ft
{
	template <typename _T1, typename _T2>
	struct pair
	{
		typedef _T1 first_type;
		typedef _T2 second_type;

		_T1 first;
		_T2 second;

		// Default Constructors
		pair() : first(), second() {}

		// Initializaion Constructor
		pair(const _T1& a, const _T2& b)
		: first(a), second(b) {}

		// Copy constructor
		template <typename _U1, typename _U2>
		pair(const pair<_U1, _U2>& pr)
		: first(pr.first), second(pr.second) {}

		/// @brief assignment operator
		/// @param pr pair to assign
		/// @return reference to this pair
		pair&
		operator= (const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}

		/// @brief swap two pair
		/// @param other pair to swap with
		void
		swap (pair& other)
		{
			first_type tmp_first = other.first;
			second_type tmp_second = other.second;

			first = other.first;
			second = other.second;
			other.first = tmp_first;
			other.second = tmp_second;
		}
	};

	/// @brief equality operator
	/// @tparam _T1 first element type
	/// @tparam _T2 second element type
	/// @param __x first pair
	/// @param __y second pair
	/// @return true if both element are equal, false otherwise
	template <typename _T1, typename _T2>
	inline bool
	operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (__x.first == __y.first && __x.second == __y.second);
	}

	/// @brief less than operator
	/// @tparam _T1 first element type
	/// @tparam _T2 second element type
	/// @param __x first pair
	/// @param __y second pair
	/// @return true if first pair both elements is less than
	/// second pair both elements, false otherwise
	template <typename _T1, typename _T2>
	inline bool
	operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (__x.first < __y.first ||
				(!(__y.first < __x.first) && __x.second < __y.second));
	}

	/// @brief greater than operator (use equality operator)
	/// @tparam _T1 first element type
	/// @tparam _T2 second element type
	/// @param __x first pair
	/// @param __y second pair
	/// @return true if first pair is not equal to second pair
	template <typename _T1, typename _T2>
	inline bool
	operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (!(__x == __y));
	}

	/// @brief greater than operator (uses less than operator)
	/// @tparam _T1 first element type
	/// @tparam _T2 second element type
	/// @param __x first pair
	/// @param __y second pair
	/// @return true if first pair is greater than second pair
	template <typename _T1, typename _T2>
	inline bool
	operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (__y < __x);
	}

	/// @brief less than or equal operator (uses less than operator)
	/// @tparam _T1 first element type
	/// @tparam _T2 second element type
	/// @param __x first pair
	/// @param __y second pair
	/// @return true if first pair is less than or equal to second pair
	template <typename _T1, typename _T2>
	inline bool
	operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (!(__y < __x));
	}

	/// @brief greater than or equal operator (uses less than operator)
	/// @tparam _T1 first element type
	/// @tparam _T2 second element type
	/// @param __x first pair
	/// @param __y second pair
	/// @return true if first pair is greater than or equal to second pair
	template <typename _T1, typename _T2>
	inline bool
	operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (!(__x < __y));
	}

	/// @brief swap content of two pairs
	/// @param __x first pair
	/// @param __y second pair
	void
	swap(pair<int, int>& __x, pair<int, int>& __y)
	{
		__x.swap(__y);
	}

	/// @brief make_pair function
	/// @tparam _T1  first element type
	/// @tparam _T2 second element type
	/// @param __x first element
	/// @param __y second element
	/// @return pair with first element __x and second element __y
	template <typename _T1, typename _T2>
	inline pair<_T1, _T2>
	make_pair(_T1 __x, _T2 __y)
	{
		return (pair<_T1, _T2>(__x, __y));
	}

}

namespace ft
{

	template <typename _Pair>
	struct _Select1st
		: public std::unary_function<_Pair, typename _Pair::first_type>
	{
		typename _Pair::first_type&
		operator()(_Pair& __x) const
		{ return __x.first; }

		const typename _Pair::first_type&
		operator()(const _Pair& __x) const
		{ return __x.first; }
	};

	template <typename _Pair>
	struct _Select2nd
		: public std::unary_function<_Pair, typename _Pair::second_type>
	{
		typename _Pair::second_type&
		operator()(_Pair& __x) const
		{ return __x.second; }

		const typename _Pair::second_type&
		operator()(const _Pair& __x) const
		{ return __x.second; }
	};

	template <typename _Tp>
	struct _Identity
		: public std::unary_function<_Tp, _Tp>
	{
		_Tp&
		operator()(_Tp& __x) const
		{ return __x; }

		const _Tp&
		operator()(const _Tp& __x) const
		{ return __x; }
	};
}

#endif
