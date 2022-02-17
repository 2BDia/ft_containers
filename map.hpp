/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:59:39 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/17 15:22:55 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace	ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
		class Alloc = allocator< ft::pair<const Key,T>> >
	class map
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<key_type, mapped_type>				value_type;
			typedef Compare										key_compare;
			//value_compare to do
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			//iterators and difference type
			typedef size_t										size_type;

		private:

			allocator_type	_alloc;
			Node			_root;
			key_compare		_comp;
	};
}
