/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:53:14 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/16 08:55:08 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace	ft
{
	template <class Iterator>
	class	reverse_iterator
	{
		public:

			//Member types
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;

		private :

			Iterator	_it;

		public:

			//Constructors
			reverse_iterator() : _it(NULL) {};
			explicit reverse_iterator (iterator_type it) : _it(it) {};
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {};

			//Destructor
			~reverse_iterator() {};

			//Operator=
			reverse_iterator &operator=(const reverse_iterator& it)
			{
				this->_it = it.base();
				return (*this);
			}

			//Member functions
			iterator_type base() const {return this->_it;};

			reference operator*() const {return *(this->_it - 1);};

			reverse_iterator operator+ (difference_type n) const {return reverse_iterator(this->_it - n);};
			reverse_iterator operator- (difference_type n) const {return reverse_iterator(this->_it + n);};

			reverse_iterator& operator++()
			{
				this->_it--;
				return (*this);
			};
			reverse_iterator  operator++(int)
			{
				reverse_iterator	tmp = *this;
				this->_it--;
				return (tmp);
			};

			reverse_iterator& operator--()
			{
				this->_it++;
				return (*this);
			};
			reverse_iterator  operator--(int)
			{
				reverse_iterator	tmp = *this;
				this->_it++;
				return (tmp);
			};

			reverse_iterator& operator+= (difference_type n)
			{
				this->_it -= n;
				return (*this);
			};
			reverse_iterator& operator-= (difference_type n)
			{
				this->_it += n;
				return (*this);
			};

			pointer operator->() const {return &(operator*());};
			reference operator[] (difference_type n) const {return *(operator+(n));};
	};

	//Non-member function overloads

	//Relational operators
	template <class Iterator>
	bool operator== (const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	};
	template<typename T_L, typename T_R>
	bool operator==(const ft::reverse_iterator<T_L> lhs,
		const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() == rhs.base());
	};

	template <class Iterator>
	bool operator!= (const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	};
	template<typename T_L, typename T_R>
	bool operator!=(const ft::reverse_iterator<T_L> lhs,
		const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() != rhs.base());
	};

	template <class Iterator>
	bool operator<  (const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	};
	template<typename T_L, typename T_R>
	bool operator<(const ft::reverse_iterator<T_L> lhs,
		const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() > rhs.base());
	};

	template <class Iterator>
	bool operator<= (const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	};
	template<typename T_L, typename T_R>
	bool operator<=(const ft::reverse_iterator<T_L> lhs,
		const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() >= rhs.base());
	};

	template <class Iterator>
	bool operator>  (const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	};
	template<typename T_L, typename T_R>
	bool operator>(const ft::reverse_iterator<T_L> lhs,
		const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() < rhs.base());
	};

	template <class Iterator>
	bool operator>= (const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	};
	template<typename T_L, typename T_R>
	bool operator>=(const ft::reverse_iterator<T_L> lhs,
		const ft::reverse_iterator<T_R> rhs)
	{
		return (lhs.base() <= rhs.base());
	};

	//Operators + and -
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	};

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator- (
		const ft::reverse_iterator<Iterator>& lhs,
		const ft::reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	};
	template <class Iterator_L, class Iterator_R>
	typename ft::reverse_iterator<Iterator_L>::difference_type operator- (
		const ft::reverse_iterator<Iterator_L>& lhs,
		const ft::reverse_iterator<Iterator_R>& rhs)
	{
		return (rhs.base() - lhs.base());
	};
}
