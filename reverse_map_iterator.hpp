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

			//Constructors
			reverse_map_iterator() : _it(NULL) {};
			explicit reverse_map_iterator (iterator_type it) : _it(it) {};
			template <class Iter>
			reverse_map_iterator (const reverse_map_iterator<Iter>& rev_it) : _it(rev_it.getNPointer()) {};

			//Destructor
			~reverse_map_iterator() {};

			//Operator=
			reverse_map_iterator &operator=(const reverse_map_iterator& it)
			{
				this->_it = it.base();
				return (*this);
			};

			//Member functions
			value_type	&operator*() const {return this->_it.base()->data;};

			value_type* operator->() const {return &this->_it.base()->data;};

			reverse_map_iterator	&operator++()
			{
				this->_it--;
				return (*this);
			};

			iterator_type base() const {return this->_it;};
	};
}
