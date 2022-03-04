/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:40:51 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/04 16:59:19 by rvan-aud         ###   ########.fr       */
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
				node_type	*tmp = n;
				
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->left != tmp->null)
					tmp = tmp->left;
				return (tmp);
			}

			node_type	*getRightMost(node_type *n)
			{
				node_type	*tmp = n;
				
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->right != tmp->null)
					tmp = tmp->right;
				return (tmp);
			}

			bool	isNull(node_type *n)
			{
				if (n == n->null)
					return (1);
				return (0);
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

				// if we're at the last node + 1, return same iterator
				if (n == n->null)
				{
					this->_nPointer = n;
					return (*this);
				}
				// if we're at the last node, go to last node + 1
				else if (n == getRightMost(n))
					n = n->right;
				// - if node has a right subtree, go to leftmost node of that subtree
				else if (!isNull(n->right))
				{
					n = n->right;
					while (!isNull(n->left))
						n = n->left;
				}
				// - if it doesn't, traverse up the tree :
				// if you make a right turn, parent is next
				else if (n->side == L && !isNull(n->parent))
				{
					n = n->parent;
				}
				// if you make a left turn, keep on traversing up the tree until a right turn or root
				else if (n->side == R && !isNull(n->parent))
				{
					while (n->side == R && !isNull(n->parent))
						n = n->parent;
					if (n->side == L && !isNull(n->parent))
						n = n->parent;
				}
				else
				{
					n = n->right;
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

			// works the same as ++ but left is right and vice versa
			map_iterator &	operator--()
			{
				node_type	*n = this->_nPointer;

				if (n == getLeftMost(n))
				{
					this->_nPointer = n;
					return (*this);
				}
				else if (n == n->null)
					n = getRightMost(n);
				else if (!isNull(n->left))
				{
					n = n->left;
					while (!isNull(n->right))
						n = n->right;
				}
				else if (n->side == R && !isNull(n->parent))
					n = n->parent;
				else if (n->side == L && !isNull(n->parent))
				{
					while (n->side == L && !isNull(n->parent))
						n = n->parent;
					if (n->side == R && !isNull(n->parent))
						n = n->parent;
				}
				this->_nPointer = n;
				return (*this);
			}
			map_iterator 	operator--(int)
			{
				map_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}

			bool	operator==(map_iterator const rhs) const {return (this->_nPointer == rhs._nPointer);};
			bool	operator!=(map_iterator const rhs) const {return (this->_nPointer != rhs._nPointer);};
	};
}
