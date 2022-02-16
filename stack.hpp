/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:37:41 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/16 09:28:46 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace	ft
{
	template < class T, class Container = ft::vector<T> >
	class	stack
	{
		public:

			//Member types
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:

			container_type	c;

		public:

			//Constructor
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {};

			//Member functions
			bool empty() const {return c.empty();};

			size_type size() const {return c.size();};

			value_type& top() {return c.back();};
			const value_type& top() const {return c.back();};

			void push (const value_type& val) {c.push_back(val);};

			void pop() {c.pop_back();};
	};
}
