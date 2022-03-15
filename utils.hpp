/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:52:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/15 18:58:55 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

	//Make pair
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	};

	class random_access_iterator_tag {};

	//Iterator
	template <class Category, class T, class Distance = __gnu_cxx::ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:

			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
	};

	//Iterator traits
	template <class Iterator> class iterator_traits
	{
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T> class iterator_traits<T*>
	{
			typedef __gnu_cxx::ptrdiff_t			difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;
    };

	template <class T> class iterator_traits<const T*>
	{
		typedef __gnu_cxx::ptrdiff_t			difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};
}
