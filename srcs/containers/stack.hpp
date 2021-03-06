/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:37:41 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/17 18:42:38 by rvan-aud         ###   ########.fr       */
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

			//---- Member types ----//
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:

			container_type	c;

		public:

			//---- Constructor ----//
			explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {};

			//---- Member functions ----//

			/* Return true if the container is empty, false if it isn't */
			bool empty() const {return c.empty();};

			/* Returns size of the container (number of elements) */
			size_type size() const {return c.size();};

			/* Access top element */
			value_type& top() {return c.back();};
			const value_type& top() const {return c.back();};

			/* Inserts new element at the top of the container */
			void push (const value_type& val) {c.push_back(val);};

			/* Removes the element at the top of the container */
			void pop() {c.pop_back();};

		private:

			/* Prototype declarations for non-member relational operators that need
			to access the protected container */
			template <class TM, class ContainerM>
			friend bool operator== (const stack<TM,ContainerM>& lhs, const stack<TM,ContainerM>& rhs);
			template <class TM, class ContainerM>
			friend bool operator!= (const stack<TM,ContainerM>& lhs, const stack<TM,ContainerM>& rhs);
			template <class TM, class ContainerM>
			friend bool operator<  (const stack<TM,ContainerM>& lhs, const stack<TM,ContainerM>& rhs);
			template <class TM, class ContainerM>
			friend bool operator<= (const stack<TM,ContainerM>& lhs, const stack<TM,ContainerM>& rhs);
			template <class TM, class ContainerM>
			friend bool operator>  (const stack<TM,ContainerM>& lhs, const stack<TM,ContainerM>& rhs);
			template <class TM, class ContainerM>
			friend bool operator>= (const stack<TM,ContainerM>& lhs, const stack<TM,ContainerM>& rhs);
	};

	//---- Non-member function overloads ----//

	//- Relational operators (use the underlying container's operators) -//
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{return (lhs.c == rhs.c);};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{return (lhs.c != rhs.c);};

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{return (lhs.c < rhs.c);};

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{return (lhs.c <= rhs.c);};

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{return (lhs.c > rhs.c);};

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{return (lhs.c >= rhs.c);};
}
