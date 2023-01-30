/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:20:35 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/29 01:16:54 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

static class t_nullptr
{
	public:
		template<class T>
		operator T*() const { return (0); }

		template<class C, class T>
		operator T C::*() const { return (0); }

	private:
		void operator&() const;

} u_nullptr = {};


namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		// Default Constructors
		pair() : first(), second() {}

		// Initializaion Constructor
		pair(const T1& a, const T2& b) : first(a), second(b) {}

		// Copy constructor
		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		// Assignment operator
		pair& operator= (const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}

		void swap(pair& other)
		{
			first_type tmp_first = first;
			second_type tmp_second = second;

			first = other.first;
			second = other.second;
			other.first = tmp_first;
			other.second = tmp_second;
		}
	};

	// creates a pair object of type, defined by the argument types
	template < class T1, class T2>
	inline ft::pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1, T2>(x, y)) ;
	}

	// relational operators
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first != rhs.first || lhs.second != rhs.second);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T1, class T2>
	void swap (pair<T1,T2>& x, pair<T1,T2>& y)
	{
		x.swap(y);
	}
}

#endif
