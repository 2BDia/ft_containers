/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:06:31 by rvan-aud          #+#    #+#             */
/*   Updated: 2022/02/02 18:29:34 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <vector>

#include "vector.hpp"

int	main()
{
	{		
		/*********************************/
		/*              FT               */
		/*********************************/
		std::cout << "*** FT ***" << std::endl;
		ft::vector<int>	mine(10);
		for (size_t i = 0; i < mine.size(); i++)
			mine[i] = i;
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;

		std::cout << std::endl << "- Iterators -" << std::endl;
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
		ft::vector<int>::iterator	one = mine.begin();
		ft::vector<int>::iterator	two = mine.begin();
		two++;
		if (one != two)
			std::cout << "!= ok" << std::endl;
		two--;
		if (one == two)
			std::cout << "== ok" << std::endl;
		two++;
		if (one < two)
			std::cout << "< ok" << std::endl;
		if (one <= two)
		{
			one++;
			if (one <= two)
				std::cout << "<= ok" << std::endl;
		}
		one++;
		if (one > two)
			std::cout << "> ok" << std::endl;
		if (one >= two)
		{
			one--;
			if (one >= two)
				std::cout << ">= ok" << std::endl;
		}

		std::cout << std::endl << "- Reverse iterators -" << std::endl;
		ft::vector<int>::reverse_iterator	rit = mine.rbegin();
		std::cout << "rbegin = " << *rit << std::endl;
		rit = mine.rend();
		std::cout << "rend = " << *rit << std::endl;
		rit = mine.rbegin();
		std::cout << "++rbegin = " << *(++rit) << std::endl;
		std::cout << "rit++ = " << *(rit++) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
		std::cout << "--rit = " << *(--rit) << std::endl;
		std::cout << "rit-- = " << *(rit--) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
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

		std::cout << std::endl << "- Modifiers -" << std::endl;
		mine.assign(10, 42);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "size = " << mine.size() << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
		
	}
	{
		/*********************************/
		/*              STD              */
		/*********************************/
		std::cout << std::endl << "-------------------------------------------------------" << std::endl;
		std::cout << std::endl << "*** STD ***" << std::endl;
		std::vector<int> real(10);

		for (size_t i = 0; i < real.size(); i++)
			real[i] = i;
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;

		std::cout << std::endl << "- Iterators -" << std::endl;
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
		std::vector<int>::iterator	one = real.begin();
		std::vector<int>::iterator	two = real.begin();
		two++;
		if (one != two)
			std::cout << "!= ok" << std::endl;
		two--;
		if (one == two)
			std::cout << "== ok" << std::endl;
		two++;
		if (one < two)
			std::cout << "< ok" << std::endl;
		if (one <= two)
		{
			one++;
			if (one <= two)
				std::cout << "<= ok" << std::endl;
		}
		one++;
		if (one > two)
			std::cout << "> ok" << std::endl;
		if (one >= two)
		{
			one--;
			if (one >= two)
				std::cout << ">= ok" << std::endl;
		}

		std::cout << std::endl << "- Reverse iterators -" << std::endl;
		std::vector<int>::reverse_iterator	rit = real.rbegin();
		std::cout << "rbegin = " << *rit << std::endl;
		rit = real.rend();
		std::cout << "rend = " << *rit << std::endl;
		rit = real.rbegin();
		std::cout << "++rbegin = " << *(++rit) << std::endl;
		std::cout << "rit++ = " << *(rit++) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
		std::cout << "--rit = " << *(--rit) << std::endl;
		std::cout << "rit-- = " << *(rit--) << std::endl;
		std::cout << "rit now = " << *rit << std::endl;
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

		std::cout << std::endl << "- Modifiers -" << std::endl;
		real.assign(10, 42);
		for (size_t i = 0; i < real.size(); i++)
			std::cout << real[i] << std::endl;
		std::cout << "size = " << real.size() << std::endl;
		std::cout << "capacity = " << real.capacity() << std::endl;
	}
	{
		std::cout << std::endl << "*** TEST ***" << std::endl;
		std::vector<int> test(10);
		ft::vector<int>	mine(10);
		std::vector<int> sec(10);
		ft::vector<int> thi(10);

		for (size_t i = 0; i < sec.size(); i++)
			sec[i] = i;
		std::vector<int>::iterator	it = sec.begin();
		for (size_t i = 0; i < thi.size(); i++)
			thi[i] = i;
		ft::vector<int>::iterator	mit = thi.begin();
		ft::vector<int>::iterator	mite = thi.begin();
		mite++;
		mite++;
		mite++;
		mite++;
		mite++;

		test.assign(it, it + 5);
		for (size_t i = 0; i < test.size(); i++)
			std::cout << test[i] << std::endl;
		std::cout << "capacity = " << test.capacity() << std::endl;
		mine.assign(mit, mite);
		for (size_t i = 0; i < mine.size(); i++)
			std::cout << mine[i] << std::endl;
		std::cout << "capacity = " << mine.capacity() << std::endl;
	}
	// system("leaks containers");
}
