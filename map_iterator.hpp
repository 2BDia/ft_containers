/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:40:51 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/01 12:59:54 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#include "bst.hpp"

namespace	ft
{
	template <class T>
	class	map_iterator
	{
		public:

			typedef Node<typename remove_const<typename T::first_type>::type, typename T::second_type>	node_type;
			typedef T	value_type;

		private:

			node_type	*_nPointer;

		public:

			//Constructors
			map_iterator() : _nPointer(NULL) {};
			map_iterator(const map_iterator &src) : _nPointer(src._nPointer) {};
			map_iterator(node_type *x) : _nPointer(x) {};

			//Destructor
			~map_iterator() {};

			//Operator=
			map_iterator	&operator=(const map_iterator &rhs)
			{
				this->_nPointer = rhs._nPointer;
				return (*this);
			}

			value_type	&operator*() const {return this->_nPointer->data;};

			T* operator->() const
			{ return (&this->_nPointer->data); };
	};
}
