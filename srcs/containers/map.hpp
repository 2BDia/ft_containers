/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:59:39 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/21 17:56:34 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "../utils/iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/utils.hpp"
#include "../utils/bst.hpp"
#include "../utils/map_iterator.hpp"
#include "../utils/reverse_map_iterator.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:

			//---- Member types ----//
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef Compare																key_compare;
			/* Value_compare : nested function class to compare elements */
			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {};

				public:

					bool operator() (const value_type& x, const value_type& y) const
					{return (comp(x.first, y.first));};
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

		public:

			allocator_type				_alloc;
			key_compare					_comp;
			BST<Key, T, key_compare>	_bst;

		public:

			//---- Constructors ----//

			/* Default constructor : constructs an empty container */
			explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst(comp, alloc, 0)
			{};

			/* Range constructor : constructs a container with the elements in the first - last range */
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst(comp, alloc, 0)
			{
				this->insert(first, last);
			};

			/* Copy constructor : constructs a container that is a copy of x (deep copy) */
			map (const map& x)
			{
				*this = x;
			};

			//---- Destructor ----//
			~map()
			{
				this->clear();
				this->_bst.delete_null();
			};

			//---- Operator= ----//

			/* Copies all the elements of x into the container */
			map& operator= (const map& x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			};

			//---- Iterators ----//

			/* Returns iterator to the beginning (leftmost element in the tree) */
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

			/* Returns iterator to the end (null element to the right of the rightmost element in the tree) */
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

			/* Returns iterator to the reverse beginning (rightmost element in the tree) */
			reverse_iterator rbegin() {return (reverse_iterator(this->end()));};
			const_reverse_iterator rbegin() const {return (const_reverse_iterator(this->end()));};

			/* Returns iterator to the reverse end (null element to the left of the leftmost element in the tree) */
			reverse_iterator rend() {return (reverse_iterator(this->begin()));};
			const_reverse_iterator rend() const {return (const_reverse_iterator(this->begin()));};

			//---- Capacity ----//

			/* Return true if the container is empty, false if it isn't */
			bool empty() const {return this->_bst.empty();};

			/* Returns size of the container (number of elements) */
			size_type size() const {return this->_bst.size();};

			/* Returns the maximum size of elements the map can hold */
			size_type max_size() const {return this->_bst.max_size();};

			//---- Element access ----//

			/* Access element whose key is k */
			mapped_type& operator[] (const key_type& k)
			{
				iterator tmp = this->find(k);

				if (tmp == this->end())
					this->insert(ft::make_pair(k, mapped_type()));
				tmp = this->find(k);
				return ((*tmp).second);
			};

			//---- Modifiers ----//

			//- Insert : inserts new elements -//
			/* Single element insert : inserts a new element */
			pair<iterator,bool> insert (const value_type& val)
			{
				pair<iterator, bool>	tmp = this->_bst.insert(val);
				return (tmp);
			};
			/* Hint insert : inserts a new element */
			iterator insert (iterator position, const value_type& val)
			{
				static_cast<void>(position);
				pair<iterator, bool>	tmp = this->_bst.insert(val);
				return (tmp.first);
			};
			/* Range insert : inserts elements that are in the given range */
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					std::cout << first->first << std::endl;
					this->_bst.insert(*first);
					first++;
				}
			};

			//- Erase : removes elements -//
			/* Position erase : erase an element at position */
			void erase (iterator position) {this->_bst.erase(position);};
			/* Key erase : erase an element whose key is k */
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
			/* Range erase : erase elements in the given range */
			void erase (iterator first, iterator last)
			{
				iterator	tmp;

				while (first != this->_bst.null && first != last)
				{
					tmp = first;
					if (++tmp == this->_bst.null)
					{
						this->_bst.erase(first);
						break ;
					}
					else
					{
						this->_bst.erase(first);
						first++;
					}
				}
			};

			/* Exchanges the content of the container with the contents of x */
			void swap (map& x) {this->_bst.swap(x._bst);};

			/* Removes all elements from the container */
			void clear()
			{
				while (this->_bst.root != this->_bst.null)
					this->erase(this->_bst.root->data.first);
			};

			//---- Observers ----//

			/* Returns the key comparison object */
			key_compare key_comp() const {return (this->_comp);};

			/* Returns the value comparison object */
			value_compare value_comp() const {return (value_compare(key_compare()));};

			//---- Operations ----//

			/* Returns iterator to element whose key is k */
			iterator find (const key_type& k) {return (this->_bst.find(k));};
			const_iterator find (const key_type& k) const {return (this->_bst.find(k));};

			/* Counts number of elements who have the k key (can only be one in map since each key is unique) */
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

			/* Returns iterator to the first element whose key is equivalent or bigger than k (goes after k) */
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

			/* Returns iterator to the first element whose key is strictly bigger than k (goes after k) */
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

			/* Returns a range that includes elements which have a key equivalent to k, that range can only be
			of 1 at most in map since each key is unique*/
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			};

			//---- Allocator ----//
			allocator_type get_allocator() const {return (this->_alloc);};
	};

	//---- Non-member function overloads ----//

	//- Relational operators -//
	/* Operator== : compares if each element is equivalent */
	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return (true);
		return (false);
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs)
	{return (!(lhs == rhs));};

	/* Operator< : compares if each element of lhs is smaller than that of rhs */
	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return (true);
		return (false);
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs)
	{return !(rhs < lhs);};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs)
	{return (rhs < lhs);};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs)
	{return !(lhs < rhs);};
}
