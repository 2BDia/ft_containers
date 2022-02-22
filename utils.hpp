/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:52:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/22 15:46:12 by rvan-aud         ###   ########.fr       */
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

	template < class Key, class T, class Compare = ft::less<Key> >
	class	Node
	{
		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef std::allocator<Node>					allocator_type;
			typedef std::allocator<ft::pair<const Key, T> >		pair_allocator_type;

			Node					*parent;
			Node					*left;
			Node					*right;
			bool					side;
			ft::pair<const Key, T>		*data;
			Compare					comp;
			allocator_type			alloc;
			pair_allocator_type		pair_alloc;

			//Constructors
			Node(void) : parent(NULL), left(NULL), right(NULL), side(0) {};
			Node(Node *parent, bool side) : parent(parent), left(NULL), right(NULL), side(side) {};

			//Destructor
			~Node()
			{
				if (this->data)
				{
					this->pair_alloc.destroy(this->data);
					if (this->parent == NULL)
						this->pair_alloc.deallocate(this->data, 1);
				}
			}

			//Functions

			void	create_node(const value_type& val)
			{
				this->left = this->alloc.allocate(1);
				this->alloc.construct(this->left, Node(this, L));
				this->right = this->alloc.allocate(1);
				this->alloc.construct(this->right, Node(this, R));
				this->data = this->pair_alloc.allocate(1);
				this->pair_alloc.construct(this->data, value_type(val));
			}
			
			void	insert(const value_type& val)
			{
				if (this->left == NULL && this->right == NULL)
					create_node(val);
				else if (!this->comp(this->data->first, val.first))
					this->left->insert(val);
				else if (this->comp(this->data->first, val.first))
					this->right->insert(val);
				// else
				// 	key already exists
			}

			void	delete_tree()
			{
				if (!(this->left == NULL && this->right == NULL))
				{
					this->left->delete_tree();
					this->right->delete_tree();
				}
				if (this->parent != NULL) //root is not malloced therefore no need to free it
					this->alloc.deallocate(this, 1);
			}

	};
}
