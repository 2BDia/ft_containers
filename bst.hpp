/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:45:07 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/11 14:23:56 by rvan-aud         ###   ########.fr       */
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

			void	delete_tree(std::allocator<Node<Key, T> > alloc, bool mod)
			{
				if (this == this->null)
				{
					if (!mod)
					{	
						alloc.destroy(this);
						alloc.deallocate(this, 1);
					}
					return ;
				}
				if (!(this->left == this->null && this->right == this->null))
				{
					if (this->left != this->null)
						this->left->delete_tree(alloc, 0);
					if (this->right != this->null)
						this->right->delete_tree(alloc, 0);
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
				this->null = this->alloc.allocate(1);
				this->alloc.construct(this->null, node_type(-1, value_type()));
				this->null->null = this->null; //need pointer on null in the node as well for iterators
				this->root = this->null;
				this->node = this->null;
			};

			//Destructor
			~BST() {};

		private:

			void	new_node(const value_type& val, bool side)
			{
				if (this->node->side == -1)
				{
					this->node = this->alloc.allocate(1);
					this->alloc.construct(this->node, node_type(NULL, 0, val, this->null));
					this->root = this->node;
					this->null->parent = this->root;
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

			//https://www.youtube.com/watch?v=DkOswl0k7s4
			//https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/#:~:text=1)%20Node%20to%20be%20deleted,Simply%20remove%20from%20the%20tree.&text=3)%20Node%20to%20be%20deleted,predecessor%20can%20also%20be%20used.
			//If leaf : delete node and parent’s left or right child to null
			//If one child : parent of node points to child, child points to parent and delete node
			//If 2 children : get min in right subtree (last left), assign that min to node, parent of node points to min,
			//min points to old left and right child, min points to old parent, old min parent points to null and delete node
			void	erase(iterator position)
			{
				node_type	*old = position.getNPointer();

				if (old->left == this->null && old->right == this->null) //if node is a leaf
				{
					if (old == this->root)
					{
						this->root = this->null;
						this->node = this->null;
						if (old->side == L)
							old->left = old->parent;
					}
					else
					{
						if (old->side == L)
							old->parent->left = this->null;
						else if (old->side == R)
							old->parent->right = this->null;
					}
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				else if (old->left != this->null && old->right == this->null) //if node has a left child
				{
					if (old == this->root)
					{
						this->root = old->left;
						this->node = old->left;
					}
					else
					{
						if (old->side == L)
							old->parent->left = old->left;
						else if (old->side == R)
							old->parent->right = old->left;
					}
					old->left->parent = old->parent;
					old->left->side = old->side;
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				else if (old->left == this->null && old->right != this->null) //if node has a right child
				{
					if (old == this->root)
					{
						this->root = old->right;
						this->node = old->right;
					}
					else
					{
						if (old->side == L)
							old->parent->left = old->right;
						else if (old->side == R)
							old->parent->right = old->right;
					}
					old->right->parent = old->parent;
					old->right->side = old->side;
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
				else //if node has 2 children
				{
					node_type	*tmp = old->right;

					while (tmp->left != this->null) //get minimum in right subtree
						tmp = tmp->left;
					tmp->left = old->left;
					tmp->left->parent = tmp;
					if (tmp->right != this->null)
					{
						tmp->right->parent = tmp->parent;
						tmp->right->side = tmp->side;
						if (tmp->side == L)
							tmp->parent->left = tmp->right;
						else if (tmp->side == R)
							tmp->parent->right = tmp->right;
					}
					else if (tmp->side == L)
						tmp->parent->left = this->null;
					else if (tmp->side == R)
						tmp->parent->right = this->null;
					tmp->right = old->right;
					tmp->right->parent = tmp;
					tmp->parent = old->parent;
					tmp->side = old->side;
					if (old == this->root)
					{
						this->root = tmp;
						this->node = tmp;
					}
					else
					{
						if (old->side == L)
							old->parent->left = tmp;
						else if (old->side == R)
							old->parent->right = tmp;
					}
					this->alloc.destroy(old);
					this->alloc.deallocate(old, 1);
				}
			}

			void	delete_tree(bool mod)
			{
				this->root->delete_tree(this->alloc, mod);
				if (mod)
				{
					this->root = this->null;
					this->node = this->null;
				}
			};
	};
}
