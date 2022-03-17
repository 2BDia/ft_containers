/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_time.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:12:09 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/17 17:37:42 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <stack>
#include <map>

#include "srcs/containers/vector.hpp"
#include "srcs/containers/stack.hpp"
#include "srcs/containers/map.hpp"
#include "srcs/utils/utils.hpp"

#if STL

int main()
{
	std::map<int, int>	one;
	int r = 0;
	for (int i = 0; i < 10000; i++)
	{
		r = rand() % 100000;
		one.insert(std::pair<int, int>(r, r * 10));
	}
	for (std::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	for (int i = 0; i < 100; i++)
	{
		r = rand() % 100000;
		one.erase(r);
	}
	for (std::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	std::map<int, int>	two;
	for (int i = 0; i < 10000; i++)
	{
		r = rand() % 10000;
		one.insert(std::pair<int, int>(r, r));
	}
	one.swap(two);
}

#else

int main()
{
	ft::map<int, int>	one;
	int r = 0;
	for (int i = 0; i < 10000; i++)
	{
		r = rand() % 100000;
		one.insert(ft::pair<int, int>(r, r * 10));
	}
	for (ft::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	for (int i = 0; i < 500; i++)
	{
		r = rand() % 100000;
		one.erase(r);
	}
	for (ft::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	ft::map<int, int>	two;
	for (int i = 0; i < 10000; i++)
	{
		r = rand() % 10000;
		one.insert(ft::pair<int, int>(r, r));
	}
	one.swap(two);
}

#endif
