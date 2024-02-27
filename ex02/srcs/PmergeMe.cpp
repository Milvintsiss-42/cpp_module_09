/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:18:34 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/27 13:38:11 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	(void)rhs;
	return *this;
}

// static std::vector<int>::iterator getA(std::vector<int>::iterator it, int step)
// {
// 	return it + (step - 1) / 2;
// }

// static std::vector<int>::iterator getB(std::vector<int>::iterator it, int step)
// {
// 	return it + step - 1;
// }

// static void print_elements(
// 	std::vector<int> &seq,
// 	int step,
// 	size_t pairs_count,
// 	bool has_stray_element)
// {
// 	std::vector<int>::iterator it = seq.begin();
// 	std::vector<int>::iterator itend = it + step * pairs_count;
// 	for (; it != itend; it += step)
// 	{
// 		std::cout << "[" << *getA(it, step) << " " << *getB(it, step) << "] - ";
// 	}
// 	if (has_stray_element)
// 		std::cout << "+stray= " << std::vector<int>(seq.begin() + step * pairs_count, seq.end());
// 	std::cout << std::endl;
// }

// static void print_before(
// 	std::vector<int> &seq,
// 	int step,
// 	size_t pairs_count,
// 	bool has_stray_element)
// {
// 	std::cout << std::endl << "Pairs count: " << pairs_count << std::endl;
// 	std::cout << "Has stray element: " << (has_stray_element ? "Yes" : "No") << std::endl;
// 	std::cout << "Before: ";
// 	print_elements(seq, step, pairs_count, has_stray_element);
// }

// static void print_after(
// 	std::vector<int> &seq,
// 	int step,
// 	size_t pairs_count,
// 	bool has_stray_element)
// {
// 	std::cout << "After: ";
// 	print_elements(seq, step, pairs_count, has_stray_element);
// 	std::cout << "Seq: " << seq << std::endl;
// }


// static void base_sort(
// 	std::vector<int> &seq,
// 	int step)
// {
// 	size_t pairs_count = seq.size() / step;
// 	bool has_stray_element = seq.size() % step;
// 	if (KDEBUG)
// 		print_before(seq, step, pairs_count, has_stray_element);
// 	if (pairs_count < 1)
// 		return;

// 	std::vector<int>::iterator it = seq.begin();
// 	std::vector<int>::iterator itend = it + step * pairs_count;
// 	for (; it != itend; it += step)
// 	{
// 		if (*getA(it, step) > *getB(it, step))
// 			std::swap_ranges(it, getA(it, step) + 1, getA(it, step) + 1);
// 	}
// 	if (KDEBUG)
// 		print_after(seq, step, pairs_count, has_stray_element);
// 	base_sort(seq, step * 2);
// }

// void PmergeMe::sort(std::vector<int> &seq)
// {
// 	base_sort(seq, 2);
// }
