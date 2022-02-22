/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:59:39 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/22 15:45:34 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			//value_compare to do
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			//iterators and difference type
			typedef size_t										size_type;

		private:

			allocator_type	_alloc;
			key_compare		_comp;
			Node<const Key, T>	_root;

		public:

			//Constructors
			explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_root()	
			{};

			//Destructor
			~map()
			{
				this->_alloc.destroy(this->_root.data);
				this->_root.delete_tree();
			};

			//Member functions
			//pair<iterator,bool> to check if already existing key and if so return iterator to that node
			void insert (const value_type& val)
			{
				this->_root.insert(val);
			};



			//TEST
			void	print()
			{
				std::cout << this->_root.data->first << std::endl;
				std::cout << this->_root.data->second << std::endl;
				std::cout << this->_root.right->data->first << std::endl;
				std::cout << this->_root.right->data->second << std::endl;
			}
	};
}
