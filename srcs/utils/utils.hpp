/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:52:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/18 16:13:19 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace	ft
{
	//---- Enable_if ----//
	/* enable_if is used when we want to differenciate between different function overloads,
	the is_integral struct will return false if the type isn't in the list, and enable_if will return false */

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

			//---- Member types ----//
			typedef T1	first_type;
			typedef	T2	second_type;

			//---- Member variables ----//
			first_type	first;
			second_type	second;

			//---- Constructors ----//

			/* Default constructor */
			pair() : first(first_type()), second(second_type()) {};

			/* Copy constructor */
			template<class U, class V>
			pair (const pair<U,V>& pr)
			:
				first(pr.first),
				second(pr.second)
			{};

			/* Initialization constructor */
			pair (const first_type& a, const second_type& b) : first(a), second(b) {};

			//---- Operator= ----//
			pair& operator= (const pair& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			};
	};
	//---- Non-member function overloads ----//

	//- Relational operators -//
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

	//---- Binary function ----//
	/* Base class for standard binary function objects (http://www.cplusplus.com/reference/functional/binary_function/?kw=binary_function) */
	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	//---- Less ----//
	/* Compares two arguments, returns false if x < y and true if x >= y */
	template <class T>
	struct less : binary_function <T, T, bool>
	{
		bool operator() (const T& x, const T& y) const {return x < y;};
	};

	//---- Make pair ----//
	/* Constructs a pair object with its first element set to x and its second element set to y */
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	};

	/* Empty class to identify the category of a random access iterator */
	class random_access_iterator_tag {};

	//---- Iterator ----//
	/* Base class of iterators, used for Iterator traits */
	template <class Category, class T, class Distance = ptrdiff_t,
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

	//---- Iterator traits ----//
	/*The iterator traits define the properties of iterators */
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
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
    };

	template <class T> class iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	//---- Equal ----//
	/* Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	and returns true if all of the elements in both ranges match */
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	//---- Lexicographical compare ----//
	/* Returns true if the range (first1,last1) compares lexicographically less than the range (first2,last2)
	(lexicographically means comparing sequentially the elements that have the same position in both ranges
	against each other until one element is not equivalent to the other) */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}
