/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:06:31 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/03/22 15:58:41 by rvan-aud         ###   ########.fr       */
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

int	main()
{
	/*********************************/
	/*              STD              */
	/*********************************/
	std::cout << std::endl << "-------------------------------------------------------" << std::endl;
	std::cout << std::endl << "*** STD ***" << std::endl;
	std::cout << std::endl << "--- Vector ---" << std::endl;
	{
		std::cout << std::endl << "- Constructors -" << std::endl;
		std::vector<int>	zero;
		std::vector<int>	one(10);
		std::vector<int>	two(10, 81);
		std::vector<int>	three(two.begin(), two.begin() + 6);
		std::vector<int>	four(three);

		std::cout << "default :" << std::endl;
		for (size_t i = 0; i < 5; i++)
			zero.push_back(i);
		for (size_t i = 0; i < zero.size(); i++)
			std::cout << zero[i] << std::endl;
		std::cout << "size = " << zero.size() << std::endl;
		std::cout << "capacity = " << zero.capacity() << std::endl;

		std::cout << std::endl << "fill 1 :" << std::endl;
		for (size_t i = 0; i < one.size(); i++)
			one[i] = i;
		for (size_t i = 0; i < one.size(); i++)
			std::cout << one[i] << std::endl;
		std::cout << "size = " << one.size() << std::endl;
		std::cout << "capacity = " << one.capacity() << std::endl;

		std::cout << std::endl << "fill 2 :" << std::endl;
		for (size_t i = 0; i < two.size(); i++)
			std::cout << two[i] << std::endl;
			std::cout << "size = " << two.size() << std::endl;
		std::cout << "capacity = " << two.capacity() << std::endl;

		std::cout << std::endl << "range :" << std::endl;
		for (size_t i = 0; i < three.size(); i++)
			std::cout << three[i] << std::endl;
		std::cout << "size = " << three.size() << std::endl;
		std::cout << "capacity = " << three.capacity() << std::endl;

		std::cout << std::endl << "copy :" << std::endl;
		for (size_t i = 0; i < four.size(); i++)
			std::cout << four[i] << std::endl;
		std::cout << "size = " << four.size() << std::endl;
		std::cout << "capacity = " << four.capacity() << std::endl;
	}
	{
		std::cout << std::endl << "- Iterators -" << std::endl;
		std::vector<int> real(10);

		for (size_t i = 0; i < real.size(); i++)
			real[i] = i;
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;

		std::vector<int>::iterator	it = real.begin();
		std::cout << "begin = " << *it << std::endl;
		it = real.end();
		it--;
		std::cout << "end = " << *it << std::endl;
		it = real.begin();
		std::cout << "++begin = " << *(++it) << std::endl;
		std::cout << "it++ = " << *(it++) << std::endl;
		std::cout << "it now = " << *it << std::endl;
		std::cout << "--it = " << *(--it) << std::endl;
		std::cout << "it-- = " << *(it--) << std::endl;
		std::cout << "it now = " << *it << std::endl;
		it = it + 5;
		std::cout << "it + 5 = " << *it << std::endl;
		it = it - 3;
		std::cout << "it - 3 = " << *it << std::endl;
		it += 6;
		std::cout << "it += 6 = " << *it << std::endl;
		it -= 2;
		std::cout << "it -= 2 = " << *it << std::endl;
		it = real.begin();
		std::cout << "it[5] = " << it[5] << std::endl;
		std::vector<int>::iterator	ione = real.begin();
		std::vector<int>::iterator	itwo = real.begin();
		itwo++;
		if (ione != itwo)
			std::cout << "!= ok" << std::endl;
		itwo--;
		if (ione == itwo)
			std::cout << "== ok" << std::endl;
		itwo++;
		if (ione < itwo)
			std::cout << "< ok" << std::endl;
		if (ione <= itwo)
		{
			ione++;
			if (ione <= itwo)
				std::cout << "<= ok" << std::endl;
		}
		ione++;
		if (ione > itwo)
			std::cout << "> ok" << std::endl;
		if (ione >= itwo)
		{
			ione--;
			if (ione >= itwo)
				std::cout << ">= ok" << std::endl;
		}

		std::cout << std::endl << "- Reverse iterators -" << std::endl;
		std::vector<int>::reverse_iterator	rit = real.rbegin();
		std::cout << "rbegin = " << *rit << std::endl;
		rit = real.rend();
		std::cout << "rend = " << *(rit - 1) << std::endl;
		rit = real.rbegin();
		std::cout << "++rbegin = " << *(++rit) << std::endl;
		std::cout << "rit++ = " << *(rit++) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
		std::cout << "--rit = " << *(--rit) << std::endl;
		std::cout << "rit-- = " << *(rit--) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
		rit = rit + 5;
		std::cout << "rit + 5 = " << *rit << std::endl;
		rit = rit - 3;
		std::cout << "rit - 3 = " << *rit << std::endl;
		rit += 6;
		std::cout << "rit += 6 = " << *rit << std::endl;
		rit -= 2;
		std::cout << "rit -= 2 = " << *rit << std::endl;
		rit = real.rbegin();
		std::cout << "rit[5] = " << rit[5] << std::endl;
		std::vector<int>::reverse_iterator	rone = real.rbegin();
		std::vector<int>::reverse_iterator	rtwo = real.rbegin();
		rone++;
		if (rone != rtwo)
			std::cout << "!= ok" << std::endl;
		rone--;
		if (rone == rtwo)
			std::cout << "== ok" << std::endl;
		rtwo++;
		if (rone < rtwo)
			std::cout << "< ok" << std::endl;
		if (rone <= rtwo)
		{
			rone++;
			if (rone <= rtwo)
				std::cout << "<= ok" << std::endl;
		}
		rone++;
		if (rone > rtwo)
			std::cout << "> ok" << std::endl;
		if (rone >= rtwo)
		{
			rtwo++;
			if (rone >= rtwo)
				std::cout << ">= ok" << std::endl;
		}

		std::cout << std::endl << "- Size -" << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "max_size = " << real.max_size() << std::endl;

		std::cout << std::endl << "- Element access -" << std::endl;
		std::cout << "at(5) = " << real.at(5) << std::endl;
		std::cout << "front = " << real.front() << std::endl;
		std::cout << "back = " << real.back() << std::endl;

		std::cout << std::endl << "- Resize -" << std::endl;
		real.resize(5);
		real.resize(8, 100);
		real.resize(12);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;
		real.reserve(25);
		std::cout << "capacity = " << real.capacity() << std::endl;

		std::cout << std::endl << "- Empty and clear -" << std::endl;
		std::cout << "empty? : " << (real.empty() ? "yes" : "no") << std::endl;
		real.clear();
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "empty? : " << (real.empty() ? "yes" : "no") << std::endl;
	}
	{
		std::cout << std::endl << "- Modifiers -" << std::endl;
		std::vector<int>	real(10);
		std::cout << "assign" << std::endl;
		real.assign(11, 42);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;
		std::vector<int>	test1(15);
		for (size_t i = 0; i < test1.size(); i++)
			test1[i] = i;
		real.assign(test1.begin(), test1.begin() + 10);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;

		std::cout << std::endl << "push_back" << std::endl;
		real.push_back(42);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;

		std::cout << std::endl << "pop_back" << std::endl;
		real.pop_back();
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;

		std::cout << std::endl << "insert" << std::endl;
		std::vector<int>::iterator it = real.insert(real.begin() + 5, 81);
		std::cout << "pos = " << *it << std::endl;
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;
		std::cout << std::endl << "insert fill" << std::endl;
		real.insert(real.begin() + 5, 4, 92);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;
		std::cout << std::endl << "insert range" << std::endl;
		std::vector<int>	test2(10);
		for (size_t i = 0; i < test2.size(); i++)
			test2[i] = i * 10;
		real.insert(real.begin() + 6, test2.begin() + 1, test2.end() - 1);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;

		std::cout << std::endl << "erase" << std::endl;
		it = real.erase(real.begin() + 2);
		std::cout << "pos = " << *it << std::endl;
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;
		std::cout << std::endl << "erase range" << std::endl;
		it = real.erase(real.begin() + 5, real.begin() + 13);
		std::cout << "pos = " << *it << std::endl;
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;

		std::cout << std::endl << "swap" << std::endl;
		std::vector<int>	one(5, 100);
		std::vector<int>	two(3, 200);
		std::cout << "one :";
		for (size_t i = 0; i < one.size(); i++)
			std::cout << ' ' << one[i];
		std::cout << std::endl << "two :";
		for (size_t i = 0; i < two.size(); i++)
			std::cout << ' ' << two[i];
		one.swap(two);
		std::cout << std::endl << "one :";
		for (size_t i = 0; i < one.size(); i++)
			std::cout << ' ' << one[i];
		std::cout << std::endl << "two :";
		for (size_t i = 0; i < two.size(); i++)
			std::cout << ' ' << two[i];
	}
	{
		std::cout << std::endl << " --- Stack ---" << std::endl;

		std::cout << std::endl << "Member functions" << std::endl;
		std::stack<int>	real;
		for (size_t i = 0; i < 5; i++)
			real.push(i);
		std::cout << "size = " << real.size() << std::endl;
		while (!real.empty())
		{
			std::cout << ' ' << real.top();
			real.pop();
		}
		std::cout << std::endl;
		std::cout << "size = " << real.size() << std::endl;

		std::cout << std::endl << "Relational operators" << std::endl;
		std::stack<int>	one;
		for (size_t i = 0; i < 5; i++)
			one.push(i);
		std::stack<int>	two;
		for (size_t i = 0; i < 5; i++)
			two.push(i);
		if (one == two)
			std::cout << "== ok" << std::endl;
		one.push(6);
		if (one != two)
			std::cout << "=! ok" << std::endl;
		if (one > two)
			std::cout << "> ok" << std::endl;
		if (one >= two)
		{
			one.pop();
			if (one >= two)
				std::cout << ">= ok" << std::endl;
		}
		if (one <= two)
		{
			one.pop();
			if (one <= two)
				std::cout << "<= ok" << std::endl;
		}
		one.pop();
		if (one < two)
			std::cout << "< ok" << std::endl;
	}
	{
		std::cout << std::endl << std::endl << "--- Map ---" << std::endl;
		std::cout << std::endl << "- Constructors -" << std::endl;

		std::cout << "default :" << std::endl;
		std::map<int, int>	zero;
		zero.insert(std::pair<int, int>(2, 28));
		zero.insert(std::pair<int, int>(1, 40));
		zero.insert(std::pair<int, int>(3,96));
		zero.insert(std::pair<int, int>(4, 100));
		for (std::map<int, int>::iterator it = zero.begin(); it != zero.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << zero.size() << std::endl;

		std::cout << std::endl << "range :" << std::endl;
		std::map<int, int>::iterator	iter = zero.end();
		iter--;
		iter--;
		std::map<int, int>	one(zero.begin(), iter);
		for (std::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << one.size() << std::endl;

		std::cout << std::endl << "copy :" << std::endl;
		std::map<int, int>	two(one);
		for (std::map<int, int>::iterator it = two.begin(); it != two.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << two.size() << std::endl;

		std::cout << std::endl << "operator= :" << std::endl;
		std::map<int, int>	three;
		three = two;
		for (std::map<int, int>::iterator it = three.begin(); it != three.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << three.size() << std::endl;
	}
	{
		std::cout << std::endl << "- Iterators -" << std::endl;
		std::map<int, int> real;
		real.insert(std::pair<int, int>(2, 2));
		real.insert(std::pair<int, int>(3, 3));
		real.insert(std::pair<int, int>(1, 1));
		real.insert(std::pair<int, int>(6, 6));
		real.insert(std::pair<int, int>(4, 4));
		real.insert(std::pair<int, int>(7, 7));
		real.insert(std::pair<int, int>(10, 10));
		real.insert(std::pair<int, int>(14, 14));
		real.insert(std::pair<int, int>(13, 13));
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;

		std::cout << std::endl << "- Reverse iterators -" << std::endl;
		for (std::map<int, int>::reverse_iterator rit = real.rbegin(); rit != real.rend(); rit++)
			std::cout << rit->first << " " << rit->second << std::endl;
	}
	{
		std::cout << std::endl << "- Relational operators -" << std::endl;
		std::map<int, int>	one;
		one.insert(std::pair<int, int>(2, 2));
		one.insert(std::pair<int, int>(3, 3));
		one.insert(std::pair<int, int>(1, 1));
		one.insert(std::pair<int, int>(6, 6));
		one.insert(std::pair<int, int>(4, 4));
		std::map<int, int>	two;
		two.insert(std::pair<int, int>(2, 2));
		two.insert(std::pair<int, int>(3, 3));
		two.insert(std::pair<int, int>(1, 1));
		two.insert(std::pair<int, int>(6, 6));
		two.insert(std::pair<int, int>(4, 4));
		if (one == two)
			std::cout << "== ok" << std::endl;
		two.erase(2);
		if (one != two)
			std::cout << "!= ok" << std::endl;
		two.insert(std::pair<int, int>(0, 0));
		if (two < one)
			std::cout << "< ok" << std::endl;
		if (two <= one)
		{
			two.erase(0);
			one.erase(2);
			if (one <= two)
				std::cout << "<= ok" << std::endl;
		}
		one.insert(std::pair<int, int>(9, 9));
		two.insert(std::pair<int, int>(8, 8));
		if (one > two)
			std::cout << "> ok" << std::endl;
		one.erase(9);
		two.erase(8);
		if (one >= two)
		{
			two.erase(1);
			two.insert(std::pair<int, int>(0, 0));
			if (one >= two)
				std::cout << ">= ok" << std::endl;
		}
	}
	{
		std::cout << std::endl << "- Capacity -" << std::endl;
		std::map<int, int> real;
		std::cout << "max_size = " << real.max_size() << std::endl;
		std::cout << "empty? " << (real.empty() ? "yes" : "no") << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		real.insert(std::pair<int, int>(2, 28));
		real.insert(std::pair<int, int>(1, 40));
		real.insert(std::pair<int, int>(3, 96));
		real.insert(std::pair<int, int>(4, 100));
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "empty? " << (real.empty() ? "yes" : "no") << std::endl;
		std::cout << "size = " << real.size() << std::endl;
	}
	{
		std::cout << std::endl << "- Insert and erase -" << std::endl;
		std::map<int, int>	real;
		real.insert(std::pair<int, int>(50, 5));
		real.insert(std::pair<int, int>(30, 3));
		real.insert(std::pair<int, int>(40, 4));
		real.insert(std::pair<int, int>(20, 2));
		real.insert(std::pair<int, int>(70, 7));
		real.insert(std::pair<int, int>(60, 6));
		real.insert(std::pair<int, int>(100, 10));
		real.insert(std::pair<int, int>(90, 9));
		real.insert(std::pair<int, int>(95, 9));
		real.insert(std::pair<int, int>(110, 11));
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		real.erase(50);
		std::cout << "erase 50" << std::endl;
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		real.erase(100);
		std::cout << "erase 100" << std::endl;
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;

		std::cout << std::endl << "- Clear -" << std::endl;
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		real.clear();
		std::cout << "clear" << std::endl << "map = *empty*" << std::endl; 
		for (std::map<int, int>::iterator it = real.begin(); it != real.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}
	{
		std::cout << std::endl << "- Swap -" << std::endl;
		std::map<int, int>	one;
		one.insert(std::pair<int, int>(50, 5));
		one.insert(std::pair<int, int>(30, 3));
		one.insert(std::pair<int, int>(40, 4));
		one.insert(std::pair<int, int>(20, 2));
		std::map<int, int>	two;
		two.insert(std::pair<int, int>(5, 5));
		two.insert(std::pair<int, int>(3, 3));
		std::cout << "one = " << std::endl;
		for (std::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		std::cout << "two = " << std::endl;
		for (std::map<int, int>::iterator it = two.begin(); it != two.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl << "swap" << std::endl;
		one.swap(two);
		std::cout << "one = " << std::endl;
		for (std::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		std::cout << "two = " << std::endl;
		for (std::map<int, int>::iterator it = two.begin(); it != two.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}
	{
		std::cout << std::endl << "- Find, count, bound functions (operations) -" << std::endl;
		std::map<int, int>	real;
		real.insert(std::pair<int, int>(50, 5));
		real.insert(std::pair<int, int>(30, 3));
		real.insert(std::pair<int, int>(40, 4));
		real.insert(std::pair<int, int>(20, 2));
		std::map<int, int>::iterator	it;
		it = real.find(30);
		std::cout << "find 30 = " << it->first << " " << it->second << std::endl;
		std::cout << "count 30 = " << real.count(30) << std::endl;
		it = real.lower_bound(30);
		std::cout << "lower_bound 30 = " << it->first << " " << it->second << std::endl;
		it = real.upper_bound(30);
		std::cout << "upper_bound 30 = " << it->first << " " << it->second << std::endl;
		std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator>	mpair = real.equal_range(45);
		std::cout << "equal_range 45, lower = " << mpair.first->first << " " << mpair.first->second << std::endl;
		std::cout << "equal_range 45, upper = " << mpair.second->first << " " << mpair.second->second << std::endl;
	}
}

#else

int	main()
{
	/*********************************/
	/*              FT               */
	/*********************************/
	std::cout << "*** FT ***" << std::endl;
	std::cout << std::endl << "--- Vector ---" << std::endl;
	{
		std::cout << std::endl << "- Constructors -" << std::endl;
		ft::vector<int>	zero;
		ft::vector<int>	one(10);
		ft::vector<int>	two(10, 81);
		ft::vector<int>	three(two.begin(), two.begin() + 6);
		ft::vector<int>	four(three);

		std::cout << "default :" << std::endl;
		for (size_t i = 0; i < 5; i++)
			zero.push_back(i);
		for (size_t i = 0; i < zero.size(); i++)
			std::cout << zero[i] << std::endl;
		std::cout << "size = " << zero.size() << std::endl;
		std::cout << "capacity = " << zero.capacity() << std::endl;

		std::cout << std::endl << "fill 1 :" << std::endl;
		for (size_t i = 0; i < one.size(); i++)
			one[i] = i;
		for (size_t i = 0; i < one.size(); i++)
			std::cout << one[i] << std::endl;
		std::cout << "size = " << one.size() << std::endl;
		std::cout << "capacity = " << one.capacity() << std::endl;

		std::cout << std::endl << "fill 2 :" << std::endl;
		for (size_t i = 0; i < two.size(); i++)
			std::cout << two[i] << std::endl;
			std::cout << "size = " << two.size() << std::endl;
		std::cout << "capacity = " << two.capacity() << std::endl;

		std::cout << std::endl << "range :" << std::endl;
		for (size_t i = 0; i < three.size(); i++)
			std::cout << three[i] << std::endl;
		std::cout << "size = " << three.size() << std::endl;
		std::cout << "capacity = " << three.capacity() << std::endl;

		std::cout << std::endl << "copy :" << std::endl;
		for (size_t i = 0; i < four.size(); i++)
			std::cout << four[i] << std::endl;
		std::cout << "size = " << four.size() << std::endl;
		std::cout << "capacity = " << four.capacity() << std::endl;
	}
	{
		std::cout << std::endl << "- Iterators -" << std::endl;
		ft::vector<int>	mine(10);
		for (size_t i = 0; i < mine.size(); i++)
			mine[i] = i;
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;

		ft::vector<int>::iterator	it = mine.begin();
		std::cout << "begin = " << *it << std::endl;
		it = mine.end();
		it--;
		std::cout << "end = " << *it << std::endl;
		it = mine.begin();
		std::cout << "++begin = " << *(++it) << std::endl;
		std::cout << "it++ = " << *(it++) << std::endl;
		std::cout << "it now = " << *it << std::endl;
		std::cout << "--it = " << *(--it) << std::endl;
		std::cout << "it-- = " << *(it--) << std::endl;
		std::cout << "it now = " << *it << std::endl;
		it = it + 5;
		std::cout << "it + 5 = " << *it << std::endl;
		it = it - 3;
		std::cout << "it - 3 = " << *it << std::endl;
		it += 6;
		std::cout << "it += 6 = " << *it << std::endl;
		it -= 2;
		std::cout << "it -= 2 = " << *it << std::endl;
		it = mine.begin();
		std::cout << "it[5] = " << it[5] << std::endl;
		ft::vector<int>::iterator	ione = mine.begin();
		ft::vector<int>::iterator	itwo = mine.begin();
		itwo++;
		if (ione != itwo)
			std::cout << "!= ok" << std::endl;
		itwo--;
		if (ione == itwo)
			std::cout << "== ok" << std::endl;
		itwo++;
		if (ione < itwo)
			std::cout << "< ok" << std::endl;
		if (ione <= itwo)
		{
			ione++;
			if (ione <= itwo)
				std::cout << "<= ok" << std::endl;
		}
		ione++;
		if (ione > itwo)
			std::cout << "> ok" << std::endl;
		if (ione >= itwo)
		{
			ione--;
			if (ione >= itwo)
				std::cout << ">= ok" << std::endl;
		}

		std::cout << std::endl << "- Reverse iterators -" << std::endl;
		ft::vector<int>::reverse_iterator	rit = mine.rbegin();
		std::cout << "rbegin = " << *rit << std::endl;
		rit = mine.rend();
		std::cout << "rend = " << *(rit - 1) << std::endl;
		rit = mine.rbegin();
		std::cout << "++rbegin = " << *(++rit) << std::endl;
		std::cout << "rit++ = " << *(rit++) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
		std::cout << "--rit = " << *(--rit) << std::endl;
		std::cout << "rit-- = " << *(rit--) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
		rit = rit + 5;
		std::cout << "rit + 5 = " << *rit << std::endl;
		rit = rit - 3;
		std::cout << "rit - 3 = " << *rit << std::endl;
		rit += 6;
		std::cout << "rit += 6 = " << *rit << std::endl;
		rit -= 2;
		std::cout << "rit -= 2 = " << *rit << std::endl;
		rit = mine.rbegin();
		std::cout << "rit[5] = " << rit[5] << std::endl;
		ft::vector<int>::reverse_iterator	rone = mine.rbegin();
		ft::vector<int>::reverse_iterator	rtwo = mine.rbegin();
		rone++;
		if (rone != rtwo)
			std::cout << "!= ok" << std::endl;
		rone--;
		if (rone == rtwo)
			std::cout << "== ok" << std::endl;
		rtwo++;
		if (rone < rtwo)
			std::cout << "< ok" << std::endl;
		if (rone <= rtwo)
		{
			rone++;
			if (rone <= rtwo)
				std::cout << "<= ok" << std::endl;
		}
		rone++;
		if (rone > rtwo)
			std::cout << "> ok" << std::endl;
		if (rone >= rtwo)
		{
			rtwo++;
			if (rone >= rtwo)
				std::cout << ">= ok" << std::endl;
		}
		
		std::cout << std::endl << "- Size -" << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "max_size = " << mine.max_size() << std::endl;

		std::cout << std::endl << "- Element access -" << std::endl;
		std::cout << "at(5) = " << mine.at(5) << std::endl;
		std::cout << "front = " << mine.front() << std::endl;
		std::cout << "back = " << mine.back() << std::endl;

		std::cout << std::endl << "- Resize -" << std::endl;
		mine.resize(5);
		mine.resize(8, 100);
		mine.resize(12);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
		mine.reserve(25);
		std::cout << "capacity = " << mine.capacity() << std::endl;

		std::cout << std::endl << "- Empty and clear -" << std::endl;
		std::cout << "empty? : " << (mine.empty() ? "yes" : "no") << std::endl;
		mine.clear();
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "empty? : " << (mine.empty() ? "yes" : "no") << std::endl;
	}
	{
		std::cout << std::endl << "- Modifiers -" << std::endl;
		ft::vector<int>	mine(10);
		std::cout << "assign" << std::endl;
		mine.assign(11, 42);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
		ft::vector<int>	test1(15);
		for (size_t i = 0; i < test1.size(); i++)
			test1[i] = i;
		mine.assign(test1.begin(), test1.begin() + 10);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;

		std::cout << std::endl << "push_back" << std::endl;
		mine.push_back(42);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;

		std::cout << std::endl << "pop_back" << std::endl;
		mine.pop_back();
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;

		std::cout << std::endl << "insert" << std::endl;
		ft::vector<int>::iterator it = mine.insert(mine.begin() + 5, 81);
		std::cout << "pos = " << *it << std::endl;
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
		std::cout << std::endl << "insert fill" << std::endl;
		mine.insert(mine.begin() + 5, 4, 92);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
		std::cout << std::endl << "insert range" << std::endl;
		ft::vector<int>	test2(10);
		for (size_t i = 0; i < test2.size(); i++)
			test2[i] = i * 10;
		mine.insert(mine.begin() + 6, test2.begin() + 1, test2.end() - 1);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;

		std::cout << std::endl << "erase" << std::endl;
		it = mine.erase(mine.begin() + 2);
		std::cout << "pos = " << *it << std::endl;
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
		std::cout << std::endl << "erase range" << std::endl;
		it = mine.erase(mine.begin() + 5, mine.begin() + 13);
		std::cout << "pos = " << *it << std::endl;
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;

		std::cout << std::endl << "swap" << std::endl;
		ft::vector<int>	one(5, 100);
		ft::vector<int>	two(3, 200);
		std::cout << "one :";
		for (size_t i = 0; i < one.size(); i++)
			std::cout << ' ' << one[i];
		std::cout << std::endl << "two :";
		for (size_t i = 0; i < two.size(); i++)
			std::cout << ' ' << two[i];
		one.swap(two);
		std::cout << std::endl << "one :";
		for (size_t i = 0; i < one.size(); i++)
			std::cout << ' ' << one[i];
		std::cout << std::endl << "two :";
		for (size_t i = 0; i < two.size(); i++)
			std::cout << ' ' << two[i];
	}
	{
		std::cout << std::endl << " --- Stack ---" << std::endl;

		std::cout << std::endl << "Member functions" << std::endl;
		ft::stack<int>	mine;
		for (size_t i = 0; i < 5; i++)
			mine.push(i);
		std::cout << "size = " << mine.size() << std::endl;
		while (!mine.empty())
		{
			std::cout << ' ' << mine.top();
			mine.pop();
		}
		std::cout << std::endl;
		std::cout << "size = " << mine.size() << std::endl;

		std::cout << std::endl << "Relational operators" << std::endl;
		ft::stack<int>	one;
		for (size_t i = 0; i < 5; i++)
			one.push(i);
		ft::stack<int>	two;
		for (size_t i = 0; i < 5; i++)
			two.push(i);
		if (one == two)
			std::cout << "== ok" << std::endl;
		one.push(6);
		if (one != two)
			std::cout << "=! ok" << std::endl;
		if (one > two)
			std::cout << "> ok" << std::endl;
		if (one >= two)
		{
			one.pop();
			if (one >= two)
				std::cout << ">= ok" << std::endl;
		}
		if (one <= two)
		{
			one.pop();
			if (one <= two)
				std::cout << "<= ok" << std::endl;
		}
		one.pop();
		if (one < two)
			std::cout << "< ok" << std::endl;
	}
	{
		std::cout << std::endl << std::endl << "--- Map ---" << std::endl;
		std::cout << std::endl << "- Constructors -" << std::endl;

		std::cout << "default :" << std::endl;
		ft::map<int, int>	zero;
		zero.insert(ft::pair<int, int>(2, 28));
		zero.insert(ft::pair<int, int>(1, 40));
		zero.insert(ft::pair<int, int>(3,96));
		zero.insert(ft::pair<int, int>(4, 100));
		for (ft::map<int, int>::iterator it = zero.begin(); it != zero.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << zero.size() << std::endl;

		std::cout << std::endl << "range :" << std::endl;
		ft::map<int, int>::iterator	iter = zero.end();
		iter--;
		iter--;
		ft::map<int, int>	one(zero.begin(), iter);
		for (ft::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << one.size() << std::endl;

		std::cout << std::endl << "copy :" << std::endl;
		ft::map<int, int>	two(one);
		for (ft::map<int, int>::iterator it = two.begin(); it != two.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << two.size() << std::endl;

		std::cout << std::endl << "operator= :" << std::endl;
		ft::map<int, int>	three;
		three = two;
		for (ft::map<int, int>::iterator it = three.begin(); it != three.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "size = " << three.size() << std::endl;
	}
	{
		std::cout << std::endl << "- Iterators -" << std::endl;
		ft::map<int, int> mine;
		mine.insert(ft::pair<int, int>(2, 2));
		mine.insert(ft::pair<int, int>(3, 3));
		mine.insert(ft::pair<int, int>(1, 1));
		mine.insert(ft::pair<int, int>(6, 6));
		mine.insert(ft::pair<int, int>(4, 4));
		mine.insert(ft::pair<int, int>(7, 7));
		mine.insert(ft::pair<int, int>(10, 10));
		mine.insert(ft::pair<int, int>(14, 14));
		mine.insert(ft::pair<int, int>(13, 13));
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;

		std::cout << std::endl << "- Reverse iterators -" << std::endl;
		for (ft::map<int, int>::reverse_iterator rit = mine.rbegin(); rit != mine.rend(); rit++)
			std::cout << rit->first << " " << rit->second << std::endl;
	}
	{
		std::cout << std::endl << "- Relational operators -" << std::endl;
		ft::map<int, int>	one;
		one.insert(ft::pair<int, int>(2, 2));
		one.insert(ft::pair<int, int>(3, 3));
		one.insert(ft::pair<int, int>(1, 1));
		one.insert(ft::pair<int, int>(6, 6));
		one.insert(ft::pair<int, int>(4, 4));
		ft::map<int, int>	two;
		two.insert(ft::pair<int, int>(2, 2));
		two.insert(ft::pair<int, int>(3, 3));
		two.insert(ft::pair<int, int>(1, 1));
		two.insert(ft::pair<int, int>(6, 6));
		two.insert(ft::pair<int, int>(4, 4));
		if (one == two)
			std::cout << "== ok" << std::endl;
		two.erase(2);
		if (one != two)
			std::cout << "!= ok" << std::endl;
		two.insert(ft::pair<int, int>(0, 0));
		if (two < one)
			std::cout << "< ok" << std::endl;
		if (two <= one)
		{
			two.erase(0);
			one.erase(2);
			if (one <= two)
				std::cout << "<= ok" << std::endl;
		}
		one.insert(ft::pair<int, int>(9, 9));
		two.insert(ft::pair<int, int>(8, 8));
		if (one > two)
			std::cout << "> ok" << std::endl;
		one.erase(9);
		two.erase(8);
		if (one >= two)
		{
			two.erase(1);
			two.insert(ft::pair<int, int>(0, 0));
			if (one >= two)
				std::cout << ">= ok" << std::endl;
		}
	}
	{
		std::cout << std::endl << "- Capacity -" << std::endl;
		ft::map<int, int> mine;
		std::cout << "max_size = " << mine.max_size() << std::endl;
		std::cout << "empty? " << (mine.empty() ? "yes" : "no") << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		mine.insert(ft::pair<int, int>(2, 28));
		mine.insert(ft::pair<int, int>(1, 40));
		mine.insert(ft::pair<int, int>(3, 96));
		mine.insert(ft::pair<int, int>(4, 100));
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << "empty? " << (mine.empty() ? "yes" : "no") << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
	}
	{
		std::cout << std::endl << "- Insert and erase -" << std::endl;
		ft::map<int, int>	mine;
		mine.insert(ft::pair<int, int>(50, 5));
		mine.insert(ft::pair<int, int>(30, 3));
		mine.insert(ft::pair<int, int>(40, 4));
		mine.insert(ft::pair<int, int>(20, 2));
		mine.insert(ft::pair<int, int>(70, 7));
		mine.insert(ft::pair<int, int>(60, 6));
		mine.insert(ft::pair<int, int>(100, 10));
		mine.insert(ft::pair<int, int>(90, 9));
		mine.insert(ft::pair<int, int>(95, 9));
		mine.insert(ft::pair<int, int>(110, 11));
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		mine.erase(50);
		std::cout << "erase 50" << std::endl;
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		mine.erase(100);
		std::cout << "erase 100" << std::endl;
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;

		std::cout << std::endl << "- Clear -" << std::endl;
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		mine.clear();
		std::cout << "clear" << std::endl << "map = *empty*" << std::endl; 
		for (ft::map<int, int>::iterator it = mine.begin(); it != mine.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}
	{
		std::cout << std::endl << "- Swap -" << std::endl;
		ft::map<int, int>	one;
		one.insert(ft::pair<int, int>(50, 5));
		one.insert(ft::pair<int, int>(30, 3));
		one.insert(ft::pair<int, int>(40, 4));
		one.insert(ft::pair<int, int>(20, 2));
		ft::map<int, int>	two;
		two.insert(ft::pair<int, int>(5, 5));
		two.insert(ft::pair<int, int>(3, 3));
		std::cout << "one = " << std::endl;
		for (ft::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		std::cout << "two = " << std::endl;
		for (ft::map<int, int>::iterator it = two.begin(); it != two.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl << "swap" << std::endl;
		one.swap(two);
		std::cout << "one = " << std::endl;
		for (ft::map<int, int>::iterator it = one.begin(); it != one.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
		std::cout << std::endl;
		std::cout << "two = " << std::endl;
		for (ft::map<int, int>::iterator it = two.begin(); it != two.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}
	{
		std::cout << std::endl << "- Find, count, bound functions (operations) -" << std::endl;
		ft::map<int, int>	mine;
		mine.insert(ft::pair<int, int>(50, 5));
		mine.insert(ft::pair<int, int>(30, 3));
		mine.insert(ft::pair<int, int>(40, 4));
		mine.insert(ft::pair<int, int>(20, 2));
		ft::map<int, int>::iterator	it;
		it = mine.find(30);
		std::cout << "find 30 = " << it->first << " " << it->second << std::endl;
		std::cout << "count 30 = " << mine.count(30) << std::endl;
		it = mine.lower_bound(30);
		std::cout << "lower_bound 30 = " << it->first << " " << it->second << std::endl;
		it = mine.upper_bound(30);
		std::cout << "upper_bound 30 = " << it->first << " " << it->second << std::endl;
		ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	mpair = mine.equal_range(45);
		std::cout << "equal_range 45, lower = " << mpair.first->first << " " << mpair.first->second << std::endl;
		std::cout << "equal_range 45, upper = " << mpair.second->first << " " << mpair.second->second << std::endl;
	}
}

#endif
