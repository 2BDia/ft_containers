/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:17:05 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/17 18:39:49 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "../utils/iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/utils.hpp"

namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:

			//---- Member types ----//
			typedef T 											value_type;
			typedef Alloc 										allocator_type;
			typedef typename allocator_type::reference 			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::random_iterator<value_type>				iterator;
			typedef ft::random_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef size_t 										size_type;

		private:

			pointer			_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		public:

			//---- Constructors ----//

			/* Default constructor : constructs an empty constructor */
			explicit vector(const allocator_type& alloc = allocator_type())
			:
				_data(NULL),
				_size(0),
				_capacity(0),
				_alloc(alloc) 
			{};

			/* Fill constructor : constructs a container with n elements, each element is a copy of val */
			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			:
				_size(n),
				_capacity(n),
				_alloc(alloc)
			{
				this->_data = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_data + i, val);
			};

			/* Range constructor : constructs a container on the elements in the first - last range */
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				size_type	size = 0;
				for (; last != first; last--)
					size++;
				this->_size = size;
				this->_alloc = alloc;
				this->_data = this->_alloc.allocate(this->_size);
				this->_capacity = this->_size;
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(this->_data + i, *first);
					first++;
				}
			};

			/* Copy constructor : constructs a container that is a copy of another one (deep copy) */
			vector(const vector& x)
			{
				this->_data = this->_alloc.allocate(x._capacity);
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_data + i, x._data[i]);
			};

			//---- Destructor ----//
			~vector(void)
			{
				this->clear();
				this->_alloc.deallocate(this->_data, this->_capacity);
			};

			//---- Operator= ----//

			/* Copies all the elements of x into the container */
			vector& operator= (const vector& x)
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_data + i);
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_data = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_data + i, x._data[i]);
				return (*this);
			};

			//---- Iterators ----//

			/* Returns iterator to the beginning */
			iterator begin() {return iterator(this->_data);};
			const_iterator begin() const {return const_iterator(this->_data);};

			/* Returns iterator to the end */
			iterator end() {return iterator(this->_data + this->_size);};
			const_iterator end() const {return const_iterator(this->_data + this->_size);};

			/* Returns iterator to the reverse beginning */
			reverse_iterator rbegin() {return reverse_iterator(iterator(this->_data + this->_size));};
			const_reverse_iterator rbegin() const {return const_reverse_iterator(const_iterator(this->_data + this->_size));};

			/* Returns iterator to the reverse end */
			reverse_iterator rend() {return reverse_iterator(iterator(this->_data));};
			const_reverse_iterator rend() const {return const_reverse_iterator(const_iterator(this->_data));};

			//---- Capacity ----//

			/* Returns size of the container (number of elements) */
			size_type size() const {return this->_size;};

			/* Returns the maximum size of elements the vector can hold */
			size_type max_size() const {return this->_alloc.max_size();};

			/* Resizes the container so that it contains n elements, if n < size : the container is reduced
			and the extra elements are destroyed, if n > size and < capacity : new elements are inserted,
			if n > size and capacity : a reallocation happens and new elements are inserted */
			void resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					(void)val;
					for (size_type i = n; i < this->_size; i++)
						this->_alloc.destroy(this->_data + i);
					this->_size = n;
				}
				else
				{
					if (n > this->_capacity)
					{
						if (n > this->_capacity * 2)
							this->reserve(n);
						else
							this->reserve(this->_capacity * 2);
					}
					for (size_type i = this->_size; i < n; i++)
						this->_alloc.construct(this->_data + i, val);
					this->_size = n;
				}
			};

			/* Returns capacity of the container (number of elements it can hold before a reallocation needs to happen) */
			size_type capacity() const {return this->_capacity;};

			/* Return true if the container is empty, false if it isn't */
			bool empty() const {return (this->_size == 0) ? true : false;};

			/* Reallocates a larger capacity if n > capacity, else nothing happens */
			void reserve (size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error(""));
				if (n > this->_capacity)
				{
					pointer	tmp = this->_alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
					{
						if (i < this->_size)
						{
							this->_alloc.construct(tmp + i, this->_data[i]);
							this->_alloc.destroy(this->_data + i);
						}
					}
					this->_alloc.deallocate(this->_data, this->_capacity);
					this->_data = tmp;
					this->_capacity = n;
				}
			};

			//---- Element access ----//

			/* Access element at index */
			reference operator[] (size_type n) {return *(this->_data + n);};
			const_reference operator[] (size_type n) const {return *(this->_data + n);};

			/* Access element at index (but checks if n is not out of range) */
			reference at (size_type n)
			{
				if (n > this->_size)
					throw (std::out_of_range(""));
				return (this->_data[n]);
			};
			const_reference at (size_type n) const
			{
				if (n > this->_size)
					throw (std::out_of_range(""));
				return (this->_data[n]);
			};

			/* Access first element */
			reference front() {return this->_data[0];};
			const_reference front() const {return this->_data[0];};

			/* Access last element */
			reference back() {return this->_data[this->_size - 1];};
			const_reference back() const {return this->_data[this->_size - 1];};

			//---- Modifiers ----//

			//- Assign : assigns new elements to the container, replacing its old ones -//
			/* Range assign : assigns the elements present in the given range */
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				size_type	size = 0;
				for (; last != first; last--)
					size++;
				this->reserve(size);
				this->clear();
				for (size_type i = 0; i < size; i++)
				{
					this->_alloc.construct(this->_data + i, *first);
					first++;
				}
				this->_size = size;
			};
			/* Fill assign : assigns n elements of value val */
			void assign (size_type n, const value_type& val)
			{
				this->reserve(n);
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_data + i, val);
				this->_size = n;
			};

			/* Add an element to the end */
			void push_back (const value_type& val)
			{
				if (this->_capacity == 0)
					this->reserve(1);
				else if (this->_size == this->_capacity)
					this->reserve(this->_size * 2);
				this->_alloc.construct(this->_data + this->_size, val);
				this->_size++;
			};

			/* Delete the last element */
			void pop_back()
			{
				this->_alloc.destroy(this->_data + this->_size);
				this->_size--;
			};

			//- Insert : inserts new elements before the element at the specified position -//
			/* Single element insert : inserts a new element at position */
			iterator insert (iterator position, const value_type& val)
			{
				size_type	i = 0;
				for (iterator it = this->begin(); it != position; it++)
					i++;
				if (this->_size == this->_capacity)
				{
					if (this->_size == 0)
						this->reserve(1);
					else
						this->reserve(this->_size * 2);
				}
				for (size_type end = this->_size; end != i; end--)
					this->_data[end] = this->_data[end - 1];
				this->_alloc.construct(this->_data + i, val);
				this->_size++;
				return (iterator(this->_data + i));
			};
			/* Fill insert : inserts n new elements starting from position */
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type	i = 0;
				for (iterator it = this->begin(); it != position; it++)
					i++;
				if (this->_size + n > this->_capacity && this->_size + n <= this->_capacity * 2)
					this->reserve(this->_capacity * 2);
				else if (this->_size + n > this->_capacity * 2)
					this->reserve(this->_size + n);
				for (size_type end = this->_size + n; end != i; end--)
					this->_data[end] = this->_data[end - n];
				for (size_type j = 0; j < n; j++)
					this->_alloc.construct(this->_data + (i + j), val);
				this->_size += n;
			};
			/* Range insert : inserts elements that are in the given range starting from position */
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				size_type	i = 0, len = 0;
				for (InputIterator it = first; it != last; it++)
					len++;
				for (iterator it = this->begin(); it != position; it++)
					i++;
				if (this->_size + len > this->_capacity && this->_size + len <= this->_capacity * 2)
					this->reserve(this->_capacity * 2);
				else if (this->_size + len > this->_capacity * 2)
					this->reserve(this->_size + len);
				for (size_type end = this->_size + len - 1; end >= i + len; end--)
					this->_data[end] = this->_data[end - len];
				for (size_type j = 0; j < len; j++)
					this->_alloc.construct((this->_data + i) + j, *(first++));
				this->_size += len;
			};

			//- Erase : removes one or more elements from the container -//
			/* Single element erase : removes the element at position */
			iterator erase (iterator position)
			{
				size_type	i = 0;
				for (iterator it = this->begin(); it != position; it++)
					i++;
				this->_alloc.destroy(this->_data + i);
				for (size_type j = i; j < this->_size - 1; j++)
					this->_data[j] = this->_data[j + 1];
				this->_size--;
				return (iterator(this->_data + i));
			};
			/* Range erase : removes elements that are in the given range */
			iterator erase (iterator first, iterator last)
			{
				size_type	i = 0, len = 0;
				for (iterator it = first; it != last; it++)
					len++;
				for (iterator it = this->begin(); it != first; it++)
					i++;
				for (size_type j = 0; j < len; j++)
					this->_alloc.destroy(this->_data + (i + j));
				for (size_type j = i; j < this->_size - len; j++)
					this->_data[j] = this->_data[j + len];
				this->_size -= len;
				return (iterator(this->_data + i));
			};

			/* Exchanges the content of the container with the contents of x */
			void swap (vector& x)
			{
				pointer			data = x._data;
				size_type		size = x._size;
				size_type		capacity = x._capacity;
				allocator_type	alloc = x._alloc;

				x._data = this->_data;
				x._size = this->_size;
				x._capacity = this->_capacity;
				x._alloc = this->_alloc;

				this->_data = data;
				this->_size = size;
				this->_capacity = capacity;
				this->_alloc = alloc;
			};

			/* Removes all elements from the container */
			void clear()
			{
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_data + i);
				this->_size = 0;
			};

			//---- Allocator ----//
			allocator_type get_allocator() const {return this->_alloc;};
	};

	//---- Non-member function overloads ----//

	//- Relational operators -//
	/* Operator== : first compares the 2 containers' sizes, then compares each element */
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (!(lhs[i] == rhs[i]))
					return (false);
			}
			return (true);
		}
		return (false);
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (!(lhs == rhs));};

	/* Operator< : first compares each element, then compares the 2 containers' sizes */
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		for (size_t i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] < rhs[i])
				return (true);
			else if (rhs[i] < lhs[i])
				return (false);
		}
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(rhs < lhs);};

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (rhs < lhs);};

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs < rhs);};

	/* Exchanges the content of the container with the contents of x */
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);};
}
