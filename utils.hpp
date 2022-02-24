/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:52:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/24 15:03:39 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# define L 0
# define R 1

namespace	ft
{
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T> 
	struct enable_if<true, T> {typedef T type;};

	template <bool integral, typename T>
	struct is_integral_type
	{
		typedef T type;
		static const bool value = integral;
	};

	template <class T> struct is_integral : public is_integral_type<false, bool> {};

    template <> struct is_integral <bool> : public is_integral_type<true, bool> {};
	template <> struct is_integral <char> : public is_integral_type<true, char> {};
	template <> struct is_integral <signed char> : public is_integral_type<true, signed char> {};
	template <> struct is_integral <short int> : public is_integral_type<true, short int> {};
	template <> struct is_integral <int> : public is_integral_type<true, int> {};
	template <> struct is_integral <long int> : public is_integral_type<true, long int> {};
	template <> struct is_integral <long long int> : public is_integral_type<true, long long int> {};
	template <> struct is_integral <unsigned char> : public is_integral_type<true, unsigned char> {};
	template <> struct is_integral <unsigned short int> : public is_integral_type<true, unsigned short int> {};
	template <> struct is_integral <unsigned int> : public is_integral_type<true, unsigned int> {};
	template <> struct is_integral <unsigned long int> : public is_integral_type<true, unsigned long int> {};

	template<class T>
	struct remove_const				{typedef T type;};
	template<class T>
	struct remove_const<const T>	{typedef T type;};

	//Pair
	template <class T1, class T2>
	struct pair
	{
		public:

			//Member types
			typedef T1	first_type;
			typedef	T2	second_type;

			//Member variables
			first_type	first;
			second_type	second;

			//Constructors
			pair() : first(first_type()), second(second_type()) {};
			template<class U, class V>
			pair (const pair<U,V>& pr)
			:
				first(pr.first),
				second(pr.second)
			{};
			pair (const first_type& a, const second_type& b) : first(a), second(b) {};

			//Operator=
			pair& operator= (const pair& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			};
	};
	//Non member functions
	//Relational operators
	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{return (lhs.first == rhs.first && lhs.second == rhs.second);};

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{return !(lhs == rhs);};

	template <class T1, class T2>
	bool operator< (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));};

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{return !(rhs < lhs);};

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{return rhs < lhs;};

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{return !(lhs < rhs);};

	//Binary function
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	//Less
	template <class T>
	struct less : binary_function <T, T, bool>
	{
		bool operator() (const T& x, const T& y) const {return x < y;};
	};

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
				// size_type	i;
				// if (this->node->left == NULL && this->node->right == NULL)
				// 	return (0);
				// if (this->node->left != NULL)
				// {
				// 	this->node = this->node->left;
				// 	i += this->size() + 1;
				// }
				// if (this->node->right != NULL)
				// {
				// 	this->node = this->node->right;
				// 	i += this->size() + 1;
				// }
				// return (i);
			};

			//Modifiers
			void	insert(const value_type& val)
			{
				if (this->node->left == NULL && this->node->right == NULL)
					new_node(val);
				else if (!this->comp(this->node->data.first, val.first))
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
