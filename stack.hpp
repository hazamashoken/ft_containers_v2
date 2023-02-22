/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:21:31 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/21 12:32:42 by tliangso         ###   ########.fr       */
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
			container_type _c;

		public:
			explicit
			stack(const container_type& ctn = container_type())
				: _c(ctn) {}

			bool
			empty() const
			{ return (_c.empty()); }

			size_type
			size() const
			{ return (_c.size()); }

			reference
			top()
			{ return (_c.back()); }

			const_reference
			top() const
			{ return (_c.back()); }

			void
			push(const value_type& val)
			{ _c.push_back(val); }

			void
			pop()
			{ _c.pop_back(); }

			void
			swap(stack& x)
			{ _c.swap(x._c); }

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
	{ return (x._c == y._c); }

	template <typename _Tp, typename _Container>
	inline bool
	operator<(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{ return (x._c < y._c); }

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
