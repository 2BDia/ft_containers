/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:37:06 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/02 15:44:19 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	class	random_access_iterator
	{
		private :

			T	*_pointer;

		public:

			typedef typename ft::iterator<random_access_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_access_iterator, T>::value_type		value_type;
			typedef typename ft::iterator<random_access_iterator, T>::difference_type	difference_type;
			typedef typename ft::iterator<random_access_iterator, T>::pointer			pointer;
			typedef typename ft::iterator<random_access_iterator, T>::reference			reference;

			//Constructors TODO copy and copy-assign
			random_access_iterator(void) : _pointer(NULL) {};
			random_access_iterator(pointer pointer) : _pointer(pointer) {};

			//Destructor
			~random_access_iterator(void) {};

			//Operators missing a lot of them
			void operator=(random_access_iterator const &rhs) {this->_pointer = rhs._pointer;};
			reference operator*() const {return *this->_pointer;};
			random_access_iterator operator++()
			{
				this->_pointer++;
				return (*this);
			};
			random_access_iterator operator++(int)
			{
				random_access_iterator	tmp = *this;
				this->_pointer++;
				return (tmp);
			};
			random_access_iterator operator--()
			{
				this->_pointer--;
				return (*this);
			};
			random_access_iterator operator--(int)
			{
				random_access_iterator	tmp = *this;
				this->_pointer--;
				return (tmp);
			};
			bool operator!=(random_access_iterator const rhs) {return (this->_pointer != rhs._pointer);};
			bool operator==(random_access_iterator const rhs) {return (this->_pointer == rhs._pointer);};
			bool operator<(random_access_iterator const rhs) {return (this->_pointer < rhs._pointer);};
			bool operator<=(random_access_iterator const rhs) {return (this->_pointer <= rhs._pointer);};
			bool operator>(random_access_iterator const rhs) {return (this->_pointer > rhs._pointer);};
			bool operator>=(random_access_iterator const rhs) {return (this->_pointer >= rhs._pointer);};
	};

	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct reverse_iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	class	reverse_random_access_iterator
	{
		private :

			T	*_pointer;

		public:

			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::value_type		value_type;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::difference_type	difference_type;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::pointer			pointer;
			typedef typename ft::reverse_iterator<reverse_random_access_iterator, T>::reference			reference;

			//Constructors TODO copy and copy-assign
			reverse_random_access_iterator(void) : _pointer(NULL) {};
			reverse_random_access_iterator(pointer pointer) : _pointer(pointer) {};

			//Destructor
			~reverse_random_access_iterator(void) {};

			//Operators missing a lot of them
			void operator=(reverse_random_access_iterator const &rhs) {this->_pointer = rhs._pointer;};
			reference operator*() const {return *this->_pointer;};
			reverse_random_access_iterator operator++()
			{
				this->_pointer--;
				return (*this);
			};
			reverse_random_access_iterator operator++(int)
			{
				reverse_random_access_iterator	tmp = *this;
				this->_pointer--;
				return (tmp);
			};
			reverse_random_access_iterator operator--()
			{
				this->_pointer++;
				return (*this);
			};
			reverse_random_access_iterator operator--(int)
			{
				reverse_random_access_iterator	tmp = *this;
				this->_pointer++;
				return (tmp);
			};
			bool operator!=(reverse_random_access_iterator const rhs) {return (this->_pointer != rhs._pointer);};
			bool operator==(reverse_random_access_iterator const rhs) {return (this->_pointer == rhs._pointer);};
			bool operator<(reverse_random_access_iterator const rhs) {return (this->_pointer > rhs._pointer);};
			bool operator<=(reverse_random_access_iterator const rhs) {return (this->_pointer >= rhs._pointer);};
			bool operator>(reverse_random_access_iterator const rhs) {return (this->_pointer < rhs._pointer);};
			bool operator>=(reverse_random_access_iterator const rhs) {return (this->_pointer <= rhs._pointer);};
	};
}