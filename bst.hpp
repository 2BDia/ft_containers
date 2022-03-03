/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:45:07 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/03 14:17:17 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

# define L 0
# define R 1

namespace	ft
{
	template <class T>class map_iterator;

	template < class Key, class T >
	class	Node
	{
		public:

			typedef size_t	size_type;

			Node					*parent;
			Node					*left;
			Node					*right;
			int						side;
			ft::pair<const Key, T>	data;

			Node() : parent(NULL), left(NULL), right(NULL), side(0) {};
			Node(Node *parent, bool side) : parent(parent), left(NULL), right(NULL), side(side) {};
			Node(Node *parent, bool side, const ft::pair<Key, T> val)
			: parent(parent), left(NULL), right(NULL), side(side), data(val) {};

			~Node() {};

			void	delete_tree(std::allocator<Node<Key, T> > alloc)
			{
				if (!(this->left == NULL && this->right == NULL))
				{
					if (this->left)
						this->left->delete_tree(alloc);
					if (this->right)
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
		class Alloc = std::allocator<Node<Key, T> > >
	class	BST
	{
		public:

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Alloc											allocator_type;
			typedef Node<Key, T>									node_type;
			typedef size_t											size_type;
			typedef typename ft::map_iterator<pair<const Key, T> >	iterator;

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
				this->node->side = -1;
			};

			//Destructor
			~BST() {};

		private:

			void	new_node(const value_type& val, bool side)
			{
				if (this->node->side == -1)
				{
					this->alloc.destroy(this->node);
					this->alloc.construct(this->node, node_type(NULL, 0, val));
				}
				else
				{
					node_type	*tmp;

					tmp = this->alloc.allocate(1);
					if (side == L)
					{
						this->alloc.construct(tmp, node_type(this->node, L, val));
						this->node->left = tmp;
					}
					else if (side == R)
					{
						this->alloc.construct(tmp, node_type(this->node, R, val));
						this->node->right = tmp;
					}
				}
			}

		public:

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

			ft::pair<iterator,bool>	insert(const value_type& val)
			{
				if (this->node->side == -1)
					this->new_node(val, 0);
				else if (this->comp(val.first, this->node->data.first))
				{
					if (this->node->left != NULL)
					{
						this->node = this->node->left;
						return (this->insert(val));
					}
					else
						this->new_node(val, L);
				}
				else if (this->comp(this->node->data.first, val.first))
				{
					if (this->node->right != NULL)
					{
						this->node = this->node->right;
						return (this->insert(val));
					}
					else
						this->new_node(val, R);
				}
				return (ft::pair<iterator, bool>(iterator(this->node), false));
			}

			void	delete_tree() {this->root->delete_tree(this->alloc);};
	};
}
