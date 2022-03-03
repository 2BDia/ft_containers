/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:59:39 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/03 15:36:35 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "bst.hpp"
#include "map_iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			//value_compare to do
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::map_iterator<ft::pair<const Key, T> >		iterator;
			typedef ft::map_iterator<const ft::pair<const Key, T> >	const_iterator;
			//iterators and difference type
			typedef size_t											size_type;

		private:

			allocator_type		_alloc;
			key_compare			_comp;
			BST<Key, T>			_bst;

		public:

			//Constructors TODO : range and copy
			explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst()
			{};

			// Destructor
			~map() {this->_bst.delete_tree();};

			//Iterators
			iterator begin()
			{
				Node<Key, T>	*tmp = this->_bst.root;

				while (tmp->left && !(tmp->left == NULL && tmp->right == NULL))
					tmp = tmp->left;
				return (iterator(tmp));
			};
			const_iterator begin() const {return const_iterator(this->begin());};

			iterator end()
			{
				Node<Key, T>	*tmp = this->_bst.root;

				while (tmp->right && !(tmp->left == NULL && tmp->right == NULL))
					tmp = tmp->right;
				return (iterator(tmp));
			};
			const_iterator end() const {return const_iterator(this->end());};

			//Capacity
			bool empty() const {return this->_bst.empty();};

			size_type size() const {return this->_bst.size();};

			size_type max_size() const {return this->_bst.max_size();};

			// Element access
			mapped_type& operator[] (const key_type& k)
			{return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;};

			//Modifiers
			//pair<iterator,bool> to check if already existing key and if so return iterator to that node
			pair<iterator,bool> insert (const value_type& val)
			{
				pair<iterator, bool>	tmp = this->_bst.insert(val);
				this->_bst.node = this->_bst.root;
				return (tmp);
			};



			//TEST
			void	print()
			{
				std::cout << this->_bst.node->data.first << " " << this->_bst.node->data.second << std::endl;
				std::cout << this->_bst.node->left->data.first << " " << this->_bst.node->left->data.second << std::endl;
				std::cout << this->_bst.node->right->data.first << " " << this->_bst.node->right->data.second << std::endl;
				std::cout << this->_bst.node->right->right->data.first << " " << this->_bst.node->right->right->data.second << std::endl;
			}
	};
}
