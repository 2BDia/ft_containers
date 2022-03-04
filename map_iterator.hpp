/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:40:51 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/03 17:36:06 by rvan-aud         ###   ########.fr       */
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

			node_type	*getLeftMost(node_type *n)
			{
				while (n->left)
					n = n->left;
				return (n);
			}

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

			//Member functions
			value_type	&operator*() const {return this->_nPointer->data;};

			T* operator->() const {return &this->_nPointer->data;};

			// https://stackoverflow.com/questions/2942517/how-do-i-iterate-over-binary-tree
			map_iterator	&operator++() //might have to point on end after last
			{
				node_type	*n = this->_nPointer;

				// - if node has a right subtree, go to leftmost node of that subtree
				if (n->right)
				{
					n = n->right;
					while (n->left)
						n = n->left;
				}
				// - if it doesn't, traverse up the tree :
				// if you make a right turn, parent is next
				else if (n->side == L && n->parent)
					n = n->parent;
				// if you make a left turn, keep on traversing up the tree until a right turn or root
				else if (n->side == R && n->parent)
				{
					while (n->side == R && n->parent)
						n = n->parent;
					if (n->side == L && n->parent)
						n = n->parent;
				}
				this->_nPointer = n;
				return (*this);
			}
			map_iterator 	operator++(int)
			{
				map_iterator	tmp = *this;
				++(*this);
				return (tmp);
			}

			// map_iterator &	operator--()
			// {
			// 	node_type	*n = this->_nPointer;

			// 	if (n->left)
			// 	{
			// 		n = n->left;
			// 		while (n->right)
			// 			n = n->right;
			// 	}
			// 	else if (n->side == R && n->parent)
			// 		n = n->parent;
			// 	else if (n->side == L && n->parent)
			// 	{
			// 		while (n->side == L && n->parent)
			// 			n = n->parent;
			// 		if (n->side == R && n->parent)
			// 			n = n->parent;
			// 	}
			// 	this->_nPointer = n;
			// 	return (*this);
			// }
	};
}
