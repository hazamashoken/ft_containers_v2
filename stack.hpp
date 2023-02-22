/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:21:31 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 01:55:49 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	using namespace ft;

	template <typename _Tp, typename _Container = vector<_Tp> >
	class stack
	{
		public:
			typedef _Tp			value_type;
			typedef _Container	container_type;
			typedef typename container_type::size_type	size_type;
			typedef typename container_type::reference	reference;
			typedef typename container_type::const_reference	const_reference;

		protected:
			container_type c;

		public:
			explicit
			stack(const container_type& ctn = container_type())
				: c(ctn) {}

			bool
			empty() const
			{ return (c.empty()); }

			size_type
			size() const
			{ return (c.size()); }

			reference
			top()
			{ return (c.back()); }

			const_reference
			top() const
			{ return (c.back()); }

			void
			push(const value_type& val)
			{ c.push_back(val); }

			void
			pop()
			{ c.pop_back(); }

			void
			swap(stack& x)
			{ c.swap(x.c); }

			template <typename Tp, typename Container>
			friend inline bool
			operator==(const stack<Tp, Container>&, const stack<Tp, Container>&);

			template <typename Tp, typename Container>
			friend inline bool
			operator<(const stack<Tp, Container>&, const stack<Tp, Container>&);
	};

	template <typename _Tp, typename _Container>
	inline bool
	operator==(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (x.c == y.c); }

	template <typename _Tp, typename _Container>
	inline bool
	operator<(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (x.c < y.c); }

	template <typename _Tp, typename _Container>
	inline bool
	operator!=(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (!(x == y)); }

	template <typename _Tp, typename _Container>
	inline bool
	operator>(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (y < x); }

	template <typename _Tp, typename _Container>
	inline bool
	operator<=(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (!(y < x)); }

	template <typename _Tp, typename _Container>
	inline bool
	operator>=(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (!(x < y)); }

	template <typename _Tp, typename _Container>
	inline void
	swap(stack<_Tp, _Container>& x, stack<_Tp, _Container>& y)
	{ x.swap(y); }
}

#endif
