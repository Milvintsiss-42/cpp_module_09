/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:18:51 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/27 11:46:33 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include "GroupIterator.hpp"
#include "common.hpp"

class PmergeMe {
private:
	template<typename Iterator>
	static void _dprint_before(
		GroupIterator<Iterator> first,
		GroupIterator<Iterator> last);
	template<typename Iterator>
	static void _dprint_after(
		GroupIterator<Iterator> first,
		GroupIterator<Iterator> last);
	template<typename Iterator>
	static void _dprint_elements(
		GroupIterator<Iterator> first,
		GroupIterator<Iterator> last);
public:
	PmergeMe();
	PmergeMe(PmergeMe const &src);
	~PmergeMe();

	template<typename Iterator>
	static void base_sort(
		GroupIterator<Iterator> first,
		GroupIterator<Iterator> last);

	template<typename Container>
	static void sort(Container &seq);

	PmergeMe &operator=(PmergeMe const &rhs);
};

template<typename Container>
void PmergeMe::sort(Container &seq)
{
	base_sort(
		GroupIterator<typename Container::iterator>(seq.begin(), 1),
		GroupIterator<typename Container::iterator>(seq.end(), 1)
	);
}

template<typename Iterator>
void PmergeMe::base_sort(
	GroupIterator<Iterator> first,
	GroupIterator<Iterator> last)
{
	size_t size = last - first;
	bool has_stray_element = size % 2;
	if (size < 2)
		return;
	if (KDEBUG)
		_dprint_before(first, last);

	GroupIterator<Iterator> it = first;
	GroupIterator<Iterator> itend = it + size;
	if (has_stray_element)
		itend--;
	for (; it != itend; it += 2)
	{
		if (*it > *(it + 1))
			iter_swap(it, it + 1);
	}
	if (KDEBUG)
		_dprint_after(first, last);
	base_sort(
		GroupIterator<Iterator>(first.base(), first.size() * 2),
		GroupIterator<Iterator>(last.base(), last.size() * 2)
	);
}

template<typename Iterator>
void PmergeMe::_dprint_before(
	GroupIterator<Iterator> first,
	GroupIterator<Iterator> last)
{
	size_t size = last - first;
	std::cout << std::endl << "Size: " << size << std::endl;
	std::cout << "Pairs count: " << size / 2 << std::endl;
	std::cout << "Has stray element: " << (size % 2 ? "Yes" : "No") << std::endl;
	std::cout << "Before: ";
	_dprint_elements(first, last);
}

template<typename Iterator>
void PmergeMe::_dprint_after(
	GroupIterator<Iterator> first,
	GroupIterator<Iterator> last)
{
	std::cout << "After: ";
	_dprint_elements(first, last);
	std::cout << "Seq: " << std::vector<int>(first.base(), last.base()) << std::endl;
}

template<typename Iterator>
void PmergeMe::_dprint_elements(
	GroupIterator<Iterator> first,
	GroupIterator<Iterator> last)
{
	size_t size = last - first;
	bool has_stray_element = size % 2;

	GroupIterator<Iterator> it = first;
	GroupIterator<Iterator> itend = it + size;
	if (has_stray_element)
		itend--;
	for (; it != itend; it += 2)
	{
		std::cout << "[" << *it << " " << *(it + 1) << "] - ";
	}
	if (has_stray_element)
		std::cout << "+stray= " << std::vector<int>(first.base() + first.size() * 2 * (size / 2), last.base());
	std::cout << std::endl;
}
