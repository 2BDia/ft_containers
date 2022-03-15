/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:59:39 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/15 20:31:23 by rvan-aud         ###   ########.fr       */
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
#include "reverse_map_iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef Compare																key_compare;
			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}

				public:

					bool operator() (const value_type& x, const value_type& y) const
						{return (comp(x.first, y.first));}
			};
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef ft::map_iterator<ft::pair<const Key, T> >							iterator;
			typedef ft::map_iterator<const ft::pair<const Key, T> >						const_iterator;
			typedef ft::reverse_map_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_map_iterator<const_iterator>							const_reverse_iterator;
			typedef typename ft::map_iterator<ft::pair<const Key, T> >::difference_type	difference_type;
			typedef size_t																size_type;

		private:

			allocator_type		_alloc;
			key_compare			_comp;
			BST<Key, T>			_bst;

		public:

			explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst()
			{};

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst()
			{
				this->insert(first, last);
			};

			map (const map& x)
			{
				*this = x;
			};

			//Destructor
			~map() {this->_bst.delete_tree();};

			//Operator=
			map& operator= (const map& x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			};

			//Iterators
			iterator begin()
			{
				Node<Key, T>	*tmp = this->_bst.root;

				if (tmp == tmp->null)
					return (iterator(tmp));
				while (tmp->left != tmp->null && !(tmp->left == tmp->null && tmp->right == tmp->null))
					tmp = tmp->left;
				return (iterator(tmp));
			};
			const_iterator begin() const
			{
				Node<Key, T>	*tmp = this->_bst.root;

				if (tmp == tmp->null)
					return (const_iterator(tmp));
				while (tmp->left != tmp->null && !(tmp->left == tmp->null && tmp->right == tmp->null))
					tmp = tmp->left;
				return const_iterator(tmp);
			};

			iterator end()
			{
				Node<Key, T>	*tmp = this->_bst.root;

				if (tmp == tmp->null)
					return (iterator(tmp));
				while (tmp->right != tmp->null && !(tmp->left == tmp->null && tmp->right == tmp->null))
					tmp = tmp->right;
				return (iterator(tmp->right));
			};
			const_iterator end() const
			{
				Node<Key, T>	*tmp = this->_bst.root;

				if (tmp == tmp->null)
					return (const_iterator(tmp));
				while (tmp->right != tmp->null && !(tmp->left == tmp->null && tmp->right == tmp->null))
					tmp = tmp->right;
				return (const_iterator(tmp->right));
			};

			reverse_iterator rbegin()
			{
				Node<Key, T>	*tmp = this->_bst.root;

				if (tmp == tmp->null)
					return (reverse_iterator(tmp));
				while (tmp->right != tmp->null && !(tmp->left == tmp->null && tmp->right == tmp->null))
					tmp = tmp->right;
				return (reverse_iterator(tmp));
			};
			const_reverse_iterator rbegin() const
			{
				Node<Key, T>	*tmp = this->_bst.root;

				if (tmp == tmp->null)
					return (const_reverse_iterator(tmp));
				while (tmp->right != tmp->null && !(tmp->left == tmp->null && tmp->right == tmp->null))
					tmp = tmp->right;
				return (const_reverse_iterator(tmp));
			};

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
			iterator insert (iterator position, const value_type& val)
			{
				static_cast<void>(position);
				iterator	tmp = this->_bst.insert(val);
				this->_bst.node = this->_bst.root;
				return (tmp);
			};
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->_bst.insert(*first);
					this->_bst.node = this->_bst.root;
					first++;
				}
			};

			void erase (iterator position)
			{
				this->_bst.erase(position);
			};
			size_type erase (const key_type& k)
			{
				iterator	first = this->begin();
				iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first == k)
					{
						this->_bst.erase(first);
						return (1);
					}
				}
				return (0);
			};
			void erase (iterator first, iterator last)
			{
				for (; first != last; first++)
					this->_bst.erase(first);
			};

			void swap (map& x)
			{
				map	tmp = x;
				x = *this;
				*this = tmp;
			};

			void clear()
			{
				while (this->_bst.root != this->_bst.null)
					this->erase(this->_bst.root->data.first);
			};

			//Observers
			key_compare key_comp() const
			{
				return (this->_comp);
			};

			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			};

			//Operations
			iterator find (const key_type& k)
			{
				iterator	first = this->begin();
				iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first == k)
						break ;
				}
				return (first);
			};
			const_iterator find (const key_type& k) const
			{
				const_iterator	first = this->begin();
				const_iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first == k)
						break ;
				}
				return (first);
			};

			size_type count (const key_type& k) const
			{
				const_iterator	first = this->begin();
				const_iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first == k)
						return (1);
				}
				return (0);
			};

			iterator lower_bound (const key_type& k)
			{
				iterator	first = this->begin();
				iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first >= k)
						break ;
				}
				return (first);
			};
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator	first = this->begin();
				const_iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first >= k)
						break ;
				}
				return (first);
			};

			iterator upper_bound (const key_type& k)
			{
				iterator	first = this->begin();
				iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first > k)
						break ;
				}
				return (first);
			};
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator	first = this->begin();
				const_iterator	last = this->end();
				for (; first != last; first++)
				{
					if ((*first.base()).data.first > k)
						break ;
				}
				return (first);
			};

			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			};

			//Allocator
			allocator_type get_allocator() const {return (this->_alloc);};
	};
}
