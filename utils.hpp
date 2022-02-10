/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:52:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/10 12:05:43 by rvan-aud         ###   ########.fr       */
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
}
