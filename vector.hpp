/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:17:05 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/07 10:45:46 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"
#include "utils.hpp"

namespace	ft
{
	template< class T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:

			//Member types
			typedef T 														value_type;
			typedef Alloc 													allocator_type;
			typedef typename allocator_type::reference 						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer 						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_random_access_iterator<value_type>			reverse_iterator;
			typedef ft::reverse_random_access_iterator<const value_type>	const_reverse_iterator;
			typedef size_t 													size_type;

		private:

			pointer			_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		public :

			//Constructors : TODO range and operator=
			explicit vector(const allocator_type& alloc = allocator_type())
			:
				_data(NULL),
				_size(0),
				_capacity(0),
				_alloc(alloc) 
			{};

			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
			:
				_size(n),
				_capacity(n),
				_alloc(alloc)
			{
				this->_data = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_data[i] = val;
			};

			vector(const vector& x)
			{
				this->_data = this->_alloc.allocate(x._capacity);
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_data + i, x._data[i]);
			};

			//Detructor
			~vector(void)
			{
				this->clear();
				this->_alloc.deallocate(this->_data, this->_capacity);
			};

			//Iterators functions
			iterator begin() {return this->_data;};
			const_iterator begin() const {return this->_data;};

			iterator end() {return this->_data + this->_size;};
			const_iterator end() const {return this->_data + this->_size;};

			reverse_iterator rbegin() {return this->_data + (this->_size - 1);};
			const_reverse_iterator rbegin() const {return this->_data + (this->_size - 1);};

			reverse_iterator rend() {return this->_data - 1;};
			const_reverse_iterator rend() const {return this->_data - 1;};

			//Capacity functions
			size_type size() const {return this->_size;};

			size_type max_size() const {return this->_alloc.max_size();};

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

			size_type capacity() const {return this->_capacity;};

			bool empty() const {return (this->_size == 0) ? true : false;};

			void reserve (size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error(""));
				if (n > this->_capacity)
				{
					pointer	tmp = this->_alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
					{
						if (i < this->_capacity)
							this->_alloc.construct(tmp + i, this->_data[i]);
						this->_alloc.destroy(this->_data + i);
					}
					this->_alloc.deallocate(this->_data, this->_capacity);
					this->_data = tmp;
					this->_capacity = n;
				}
			};

			//Element access
			reference operator[] (size_type n) {return *(this->_data + n);};
			const_reference operator[] (size_type n) const {return *(this->_data + n);};

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

			reference front() {return this->_data[0];};
			const_reference front() const {return this->_data[0];};

			reference back() {return this->_data[this->_size - 1];};
			const_reference back() const {return this->_data[this->_size - 1];};

			//Modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr) //not compatible with list iterators (no last - first possible)
			{
				this->reserve(last - first);
				this->clear();
				size_type	size = last - first;
				for (size_type i = 0; i < size; i++)
				{
					this->_alloc.construct(this->_data + i, *first);
					first++;
				}
				this->_size = size;
			};
			void assign (size_type n, const value_type& val)
			{
				this->reserve(n);
				this->clear();
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_data + i, val);
				this->_size = n;
			};

			void push_back (const value_type& val)
			{
				if (this->_size == this->_capacity)
					this->reserve(this->_size + 1);
				this->_alloc.construct(this->_data + this->_size, val);
				this->_size++;
			};

			void pop_back()
			{
				this->_alloc.destroy(this->_data + this->_size);
				this->_size--;
			};

			void clear()
			{
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_data + i);
				this->_size = 0;
			};
	};
}
