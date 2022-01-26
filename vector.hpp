/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:17:05 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/01/26 17:13:39 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdexcept>
#include <memory>

namespace ft
{
	template< class T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:

			//Member types
			typedef T 											value_type;
			typedef Alloc 										allocator_type;
			typedef typename allocator_type::reference 			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			//TODO iterators
			typedef size_t 										size_type;

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

			//Capacity functions
			size_type size() const {return this->_size;};
			size_type max_size() const {return this->_alloc.max_size();};
			void resize(size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::bad_alloc());
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
			void reserve (size_type n)
			{
				if (n > this->_capacity)
				{
					pointer	tmp = this->_alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
					{
						if (i < this->_capacity)
							this->_alloc.construct(tmp + i, this->_data[i]);
					}
					this->_alloc.deallocate(this->_data, this->_capacity);
					this->_data = tmp;
					this->_capacity = n;
				}
			};
			

			//Modifiers functions
			void clear()
			{
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_data + i);
				this->_size = 0;
			};

			//test
			void	add(value_type n, int index)
			{
				this->_data[index] = n;
			};

			void	print(void)
			{
				for (size_type i = 0; i < this->_size; i++)
					std::cout << this->_data[i] << std::endl;
			};

		private:

			pointer	_data;
			size_type	_size;
			size_type	_capacity;
			allocator_type	_alloc;
	};
}
