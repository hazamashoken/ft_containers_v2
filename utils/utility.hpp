/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:47:29 by tliangso          #+#    #+#             */
/*   Updated: 2023/02/23 00:01:11 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include "pair.hpp"

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

#endif
