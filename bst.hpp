/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:45:07 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/08 16:43:41 by rvan-aud         ###   ########.fr       */
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
			Node					*null;
			int						side;
			ft::pair<const Key, T>	data;

			//Constructors
			Node() : parent(NULL), left(NULL), right(NULL), side(0) {};
			Node(Node *parent, int side) : parent(parent), left(NULL), right(NULL), side(side) {};
			Node(Node *parent, int side, const ft::pair<Key, T> val, Node *null)
			: parent(parent), left(null), right(null), null(null), side(side), data(val) {};
			Node(int side, const ft::pair<Key, T> val)
			: parent(NULL), left(NULL), right(NULL), side(side), data(val) {};

			//Destructor
			~Node() {};

			void	delete_tree(std::allocator<Node<Key, T> > alloc)
			{
				if (!(this->left == this->null && this->right == this->null))
				{
					if (this->left != this->null)
						this->left->delete_tree(alloc);
					if (this->right != this->null)
						this->right->delete_tree(alloc);
				}
				if (this->parent == NULL)
				{
					alloc.destroy(null);
					alloc.deallocate(null, 1);
				}
				alloc.destroy(this);
				alloc.deallocate(this, 1);
			}

			size_type	size() const
			{
				if (this == this->null || (this->left == NULL && this->right == NULL))
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
			node_type		*null;
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
				this->null = this->alloc.allocate(1);
				this->alloc.construct(this->null, node_type(-1, value_type()));
				this->null->null = this->null; //need pointer on null in the node as well for iterators
				this->null->parent = this->root;
			};

			//Destructor
			~BST() {};

		private:

			void	new_node(const value_type& val, bool side)
			{
				if (this->node->side == -1)
				{
					this->alloc.destroy(this->node);
					this->alloc.construct(this->node, node_type(NULL, 0, val, this->null));
				}
				else
				{
					node_type	*tmp;

					tmp = this->alloc.allocate(1);
					if (side == L)
					{
						this->alloc.construct(tmp, node_type(this->node, L, val, this->null));
						this->node->left = tmp;
					}
					else if (side == R)
					{
						this->alloc.construct(tmp, node_type(this->node, R, val, this->null));
						this->node->right = tmp;
					}
				}
			};

		public:

			//Capacity
			bool	empty() const
			{
				if (this->root->left == NULL && this->root->right == NULL)
					return (true);
				return (false);
			};

			size_type	size() const
			{
				if (this->empty() == 1)
					return (0);
				return (this->root->size());
			};

			size_type	max_size() const
			{
				return (this->alloc.max_size());
			};

			//Modifiers
			ft::pair<iterator,bool>	insert(const value_type& val)
			{
				if (this->node->side == -1)
					this->new_node(val, 0);
				else if (this->comp(val.first, this->node->data.first))
				{
					if (this->node->left != this->null)
					{
						this->node = this->node->left;
						return (this->insert(val));
					}
					else
						this->new_node(val, L);
				}
				else if (this->comp(this->node->data.first, val.first))
				{
					if (this->node->right != this->null)
					{
						this->node = this->node->right;
						return (this->insert(val));
					}
					else
						this->new_node(val, R);
				}
				return (ft::pair<iterator, bool>(iterator(this->node), false));
			};

			// https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/#:~:text=1)%20Node%20to%20be%20deleted,Simply%20remove%20from%20the%20tree.&text=3)%20Node%20to%20be%20deleted,predecessor%20can%20also%20be%20used.
			void	erase(iterator position)
			{
				node_type	*tmp = position.getNPointer();
				if (position.isNull(tmp->left) && position.isNull(tmp->right)) //if node is a leaf
				{
					node_type	*parent = tmp->parent;
					int			side = tmp->side;

					this->alloc.destroy(tmp);
					this->alloc.deallocate(tmp, 1);
					if (side == L)
						parent->left = this->null;
					else if (side == R)
						parent->right = this->null;
				}
				else if ((!position.isNull(tmp->left) && position.isNull(tmp->right))
					|| (position.isNull(tmp->left) && !position.isNull(tmp->right))) //if node has one child
				{
					node_type	*parent = tmp->parent;
					int			side = tmp->side;
					node_type	*save;

					if (!position.isNull(tmp->left) && position.isNull(tmp->right)) //only left child
						save = tmp->left;
					else //only right child
						save = tmp->right;
					this->alloc.destroy(tmp);
					this->alloc.deallocate(tmp, 1);
					save->parent = parent;
					save->side = side;
					if (side == L)
						parent->left = save;
					else if (side == R)
						parent->right = save;
					save->side = side;
				}
				else //if node has two children
				{
					node_type	*save = (++position).getNPointer();
					node_type	*s_parent = save->parent;
					node_type	*s_left = save->left;
					node_type	*s_right = save->right;
					int			s_side = save->side;
					node_type	*parent = tmp->parent;
					node_type	*left = tmp->left;
					node_type	*right = tmp->right;
					int			side = tmp->side;

					this->alloc.destroy(tmp);
					this->alloc.deallocate(tmp, 1);
					save->parent = parent;
					save->left = left;
					save->right = right;
					save->side = side;
					//placed save in tmp's spot

					if (s_left == this->null && s_right == this->null) //if save is a leaf
					{
						if (s_side == L)
							s_parent->left = this->null;
						else if (s_side == R)
							s_parent->right = this->null;
					}
					else if (s_left != this->null && s_right == this->null) //if save only has a left child
					{
						if (s_side == L) //save used to be left
						{
							s_parent->left = s_left;
							s_left->parent = s_parent;
						}
						else if (s_side == R) //save used to be right
						{
							s_parent->right = s_left;
							s_left->parent = s_parent;
							s_left->side = R;
						}
					}
					else if (s_left == this->null && s_right != this->null) //if save only has a right child
					{
						if (s_side == L) //save used to be left
						{
							s_parent->left = s_right;
							s_right->parent = s_parent;
							s_right->side = L;
						}
						else if (s_side == R) //save used to be right
						{
							s_parent->right = s_right;
							s_right->parent = s_parent;
						}
					}
				}
			};

			void	delete_tree() {this->root->delete_tree(this->alloc);};
	};
}
