/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:37:06 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/17 21:12:52 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>

#include "utils.hpp"

namespace	ft
{
	template <class T>
	class	reverse_random_iterator;

	template <class T>
	class	random_iterator
	{
		public:

			//---- Member types ----//
			typedef typename ft::iterator<random_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_iterator, T>::value_type			value_type;
			typedef typename ft::iterator<random_iterator, T>::difference_type		difference_type;
			typedef typename ft::iterator<random_iterator, T>::pointer				pointer;
			typedef typename ft::iterator<random_iterator, T>::reference			reference;

		private:

			T	*_pointer;

		public:

			//---- Constructors ----//

			/* Default constructor */
			random_iterator(void) : _pointer(NULL) {};

			/* Constructor from pointer */
			random_iterator(pointer pointer) : _pointer(pointer) {};

			/* Copy constructor */
			random_iterator(const random_iterator<typename remove_const<T>::type>& it) : _pointer(it.base()) {};

			/* Constructor from reverse iterator */
			random_iterator(const reverse_random_iterator<typename remove_const<T>::type> & rit) : _pointer(rit.base()) {};

			//---- Constructor ----//
			~random_iterator(void) {};

			//---- Operator= ----//
			random_iterator<T> &operator=(const random_iterator<typename remove_const<T>::type>& it)
			{
				this->_pointer = it.base();
				return (*this);
			}

			//---- Member functions ----//

			/* Returns a pointer to the element the pointer points to */
			pointer base() const {return this->_pointer;};

			/* Returns a reference to the element the pointer points to */
			reference operator*() const {return *this->_pointer;};

			/* Returns the lvalue of the element pointed to by the iterator */
			pointer operator->() const {return &(operator*());};

			/* Returns a reference to the element with the n index */
			reference operator[](difference_type n) const {return *(operator+(n));};

			/* Returns iterator pointing to element + n */
			random_iterator	operator+(difference_type n) const {return this->_pointer + n;};
			/* Returns iterator pointing to element - n */
			random_iterator	operator-(difference_type n) const {return this->_pointer - n;};

			/* Preincrement the iterator to point to the next element in memory */
			random_iterator& operator++()
			{
				this->_pointer++;
				return (*this);
			};
			/* Postincrement the iterator to point to the next element in memory */
			random_iterator operator++(int)
			{
				random_iterator	tmp = *this;
				this->_pointer++;
				return (tmp);
			};

			/* Preincrement the iterator to point to the previous element in memory */
			random_iterator& operator--()
			{
				this->_pointer--;
				return (*this);
			};
			/* Postincrement the iterator to point to the previous element in memory */
			random_iterator operator--(int)
			{
				random_iterator	tmp = *this;
				this->_pointer--;
				return (tmp);
			};

			/* Increments iterator by n and returns it */
			random_iterator& operator+=(difference_type n)
			{
				this->_pointer += n;
				return (*this);
			};
			/* Decrements iterator by n and returns it */
			random_iterator& operator-=(difference_type n)
			{
				this->_pointer -= n;
				return (*this);
			};

			//---- Relational operators prototypes ----//
			bool operator!=(random_iterator const rhs) {return (this->_pointer != rhs._pointer);};
			bool operator==(random_iterator const rhs) {return (this->_pointer == rhs._pointer);};
			bool operator<(random_iterator const rhs) {return (this->_pointer < rhs._pointer);};
			bool operator<=(random_iterator const rhs) {return (this->_pointer <= rhs._pointer);};
			bool operator>(random_iterator const rhs) {return (this->_pointer > rhs._pointer);};
			bool operator>=(random_iterator const rhs) {return (this->_pointer >= rhs._pointer);};
	};

	//---- Non-member function overloads ----//
	//(all the template<typename T_L, typename T_R> functions are to compare iterator with const_iterator)

	//---- Relational operators ----//
	template <class Iterator>
	bool operator== (const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() == rhs.base());};
	template<typename T_L, typename T_R>
	bool operator==(const ft::random_iterator<T_L> lhs,
		const ft::random_iterator<T_R> rhs)
	{return (lhs.base() == rhs.base());};

	template <class Iterator>
	bool operator!= (const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() != rhs.base());};
	template<typename T_L, typename T_R>
	bool operator!=(const ft::random_iterator<T_L> lhs,
		const ft::random_iterator<T_R> rhs)
	{return (lhs.base() != rhs.base());};

	template <class Iterator>
	bool operator<  (const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() < rhs.base());};
	template<typename T_L, typename T_R>
	bool operator<(const ft::random_iterator<T_L> lhs,
		const ft::random_iterator<T_R> rhs)
	{return (lhs.base() < rhs.base());};

	template <class Iterator>
	bool operator<= (const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() <= rhs.base());};
	template<typename T_L, typename T_R>
	bool operator<=(const ft::random_iterator<T_L> lhs,
		const ft::random_iterator<T_R> rhs)
	{return (lhs.base() <= rhs.base());};

	template <class Iterator>
	bool operator>  (const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() > rhs.base());};
	template<typename T_L, typename T_R>
	bool operator>(const ft::random_iterator<T_L> lhs,
		const ft::random_iterator<T_R> rhs)
	{return (lhs.base() > rhs.base());};

	template <class Iterator>
	bool operator>= (const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() >= rhs.base());};
	template<typename T_L, typename T_R>
	bool operator>=(const ft::random_iterator<T_L> lhs,
		const ft::random_iterator<T_R> rhs)
	{return (lhs.base() >= rhs.base());};

	//---- Operators + and - ----//
	template <class Iterator>
	ft::random_iterator<Iterator> operator+ (
		typename ft::random_iterator<Iterator>::difference_type n,
		const ft::random_iterator<Iterator>& it)
	{return (it + n);};

	template <class Iterator>
	typename ft::random_iterator<Iterator>::difference_type operator- (
		const ft::random_iterator<Iterator>& lhs,
		const ft::random_iterator<Iterator>& rhs)
	{return (lhs.base() - rhs.base());};
	template <class Iterator_L, class Iterator_R>
	typename ft::random_iterator<Iterator_L>::difference_type operator- (
		const ft::random_iterator<Iterator_L>& lhs,
		const ft::random_iterator<Iterator_R>& rhs)
	{return (lhs.base() - rhs.base());};
}
