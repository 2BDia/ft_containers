/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_map_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:23:00 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/15 19:23:00 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map_iterator.hpp"

namespace	ft
{
	template <class Iterator>
	class	reverse_map_iterator
	{
		public:

			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;

		private:

			Iterator	_it;

		public:

			//---- Constructors ----//

			/* Default constructor */
			reverse_map_iterator() : _it(NULL) {};

			/* Constructor from original iterator it */
			explicit reverse_map_iterator (iterator_type it) : _it(it) {};

			/* Constructor from reverse iterator */
			template <class Iter>
			reverse_map_iterator (const reverse_map_iterator<Iter>& rev_it) : _it(rev_it.base()) {};

			//---- Destructor ----//
			~reverse_map_iterator() {};

			//---- Operator= ----//
			reverse_map_iterator &operator=(const reverse_map_iterator& it)
			{
				this->_it = it.base();
				return (*this);
			};

			//---- Member functions ----//

			/* Returns a copy of the base iterator */
			iterator_type base() const {return this->_it;};

			/* Returns a reference to the element the pointer points to */
			value_type	&operator*() const
			{
				iterator_type	tmp = this->_it;
				return (*(--tmp));
			};

			/* Returns the lvalue of the element pointed to by the iterator */
			value_type* operator->() const {return &(operator*());};

			/* Preincrement the iterator to point to the previous element in memory */
			reverse_map_iterator	&operator++()
			{
				if (this->_it == this->_it.getLeftMost(this->_it.base()))
					this->_it = this->_it.base()->null;
				else
					this->_it--;
				return (*this);
			};
			/* Postincrement the iterator to point to the previous element in memory */
			reverse_map_iterator 	operator++(int)
			{
				reverse_map_iterator	tmp = *this;
				++(*this);
				return (tmp);
			};

			/* Preincrement the iterator to point to the next element in memory */
			reverse_map_iterator	&operator--()
			{
				if (this->_it == this->_it.base()->null)
					this->_it = this->_it.getLeftMost(this->_it.base());
				else
					this->_it++;
				return (*this);
			};
			/* Postincrement the iterator to point to the next element in memory */
			reverse_map_iterator 	operator--(int)
			{
				reverse_map_iterator	tmp = *this;
				--(*this);
				return (tmp);
			};

			//---- Relational operators ----//
			bool	operator==(reverse_map_iterator const rhs) const {return (this->_it.base() == rhs._it.base());};
			bool	operator!=(reverse_map_iterator const rhs) const {return (this->_it.base() != rhs._it.base());};
	};
}
