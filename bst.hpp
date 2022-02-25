/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:45:07 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/25 10:47:56 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

# define L 0
# define R 1

namespace	ft
{
	template < class Key, class T >
	class	Node
	{
		public:

			typedef size_t	size_type;

			Node				*parent;
			Node				*left;
			Node				*right;
			bool				side;
			ft::pair<Key, T>	data;

			Node() : parent(NULL), left(NULL), right(NULL), side(0) {};
			Node(Node *parent, bool side) : parent(parent), left(NULL), right(NULL), side(side) {};
			Node(Node *parent, bool side, const ft::pair<const Key, T> val)
			: parent(parent), left(NULL), right(NULL), side(side), data(val) {};

			~Node() {};

			void	delete_tree(std::allocator<Node<const Key, T> > alloc)
			{
				if (!(this->left == NULL && this->right == NULL))
				{
					this->left->delete_tree(alloc);
					this->right->delete_tree(alloc);
				}
				alloc.destroy(this);
				alloc.deallocate(this, 1);
			}

			size_type	size() const
			{
				if (this->left == NULL && this->right == NULL)
					return (0); 
				return(this->left->size() + this->right->size() + 1);
			}
	};

	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = std::allocator<Node<const Key, T> > >
	class	BST
	{
		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef Compare									key_compare;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef Alloc									allocator_type;
			typedef Node<Key, T>							node_type;
			typedef size_t									size_type;

			node_type		*node;
			node_type		*root;
			allocator_type	alloc;
			Compare			comp;

			//Constructor
			BST(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				alloc(alloc),
				comp(comp)
			{
				this->node = this->alloc.allocate(1);
				this->alloc.construct(this->node, node_type());
				this->root = this->node;
			};

			//Destructor
			~BST()
			{};

			void	new_node(const value_type& val)
			{
				node_type	*tmp_parent = this->node->parent;
				bool		side = this->node->side;

				this->alloc.destroy(this->node);
				this->alloc.construct(this->node, node_type(tmp_parent, side, val));
				this->node->left = this->alloc.allocate(1);
				this->alloc.construct(this->node->left, node_type(this->node, L));
				this->node->right = this->alloc.allocate(1);
				this->alloc.construct(this->node->right, node_type(this->node, R));
			}

			//Capacity
			bool	empty() const
			{
				if (this->root->left == NULL && this->root->right == NULL)
					return (true);
				return (false);
			}

			size_type	size() const
			{
				return (this->root->size());
			};

			size_type	max_size() const
			{
				return (this->alloc.max_size());
			}

			//Modifiers
			void	insert(const value_type& val)
			{
				if (this->node->left == NULL && this->node->right == NULL)
					new_node(val);
				else if (this->comp(val.first, this->node->data.first))
				{
					this->node = this->node->left;
					this->insert(val);
				}
				else if (this->comp(this->node->data.first, val.first))
				{
					this->node = this->node->right;
					this->insert(val);
				}
				this->node = this->root;
				// else
				// 	key already exists
			}

			void	delete_tree() {this->root->delete_tree(this->alloc);};
	};
}