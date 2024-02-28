/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:18:51 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/28 04:57:16 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include "GroupIterator.hpp"
#include "common.hpp"

#define FContainer Container<Value, std::allocator<Value> >
#define FGroupIterator GroupIterator<typename FContainer::iterator>
#define FGIContainer Container<FGroupIterator, std::allocator<FGroupIterator > >
#define FGIContIterContainer Container<typename FGIContainer::iterator, std::allocator<typename FGIContainer::iterator > >

typedef long unsigned int ulint_t;

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

	template<template<typename, typename> class Container, typename Value>
	static void base_sort(
		FGroupIterator first,
		FGroupIterator last);


	template<template<typename, typename> class Container, typename Value>
	static void sort(FContainer &seq);

	PmergeMe &operator=(PmergeMe const &rhs);
};

template<template<typename, typename> class Container, typename Value>
void PmergeMe::sort(FContainer &seq)
{
	base_sort<Container, Value>(
		FGroupIterator(seq.begin(), 1),
		FGroupIterator(seq.end(), 1)
	);
}

template<template<typename, typename> class Container, typename Value>
void PmergeMe::base_sort(
	FGroupIterator first,
	FGroupIterator last)
{
	// Cache all the differences between a Jacobsthal number and its
    // predecessor that fit in 64 bits, starting with the difference
    // between the Jacobsthal numbers 4 and 3 (the previous ones are
    // unneeded)
    static const ulint_t jacobsthal_diff[] = {
        2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
        2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
        1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
        178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
        11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
        366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
        11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
        375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
        6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
        96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
        1537228672809129216u, 3074457345618258432u, 6148914691236516864u
    };

	size_t size = last - first;
	bool has_stray_element = size % 2;
	if (size < 2)
		return;
	if (KDEBUG)
		_dprint_before(first, last);

	FGroupIterator itend = first + size;
	if (has_stray_element)
		itend--;
	for (FGroupIterator it = first; it != itend; it += 2)
	{
		if (*it > *(it + 1))
			iter_swap(it, it + 1);
	}
	if (KDEBUG)
		_dprint_after(first, last);

	base_sort<Container, Value>(
		FGroupIterator(first.base(), first.size() * 2),
		FGroupIterator(last.base(), last.size() * 2)
	);

    ////////////////////////////////////////////////////////////
    // Separate main chain and pend elements

    // The first pend element is always part of the main chain,
    // so we can safely initialize the list with the first two
    // elements of the sequence
	FGIContainer chain;
	chain.push_back(first);
	chain.push_back(first + 1);

    // Upper bounds for the insertion of pend elements
	FGIContIterContainer pend;

	// We insert all highest values in the main chain
	for (FGroupIterator it = first + 2; it != itend; it += 2)
	{
		typename FGIContainer::iterator tmp = chain.insert(chain.end(), it + 1);
		pend.push_back(tmp);
	}

    // Add the last element to pend if it exists; when it
    // exists, it always has to be inserted in the full chain,
    // so giving it chain.end() as end insertion point is ok
	if (has_stray_element)
		pend.push_back(chain.end());

    ////////////////////////////////////////////////////////////
    // Binary insertion into the main chain
	FGroupIterator current_it = first + 2;
	typename FGIContIterContainer::iterator current_pend = pend.begin();

	for (int k = 0; ; ++k)
	{
        // Should be safe: in this code, (pend.end() - current_pend) should always return
        // a positive number, so there is no risk of comparing funny values

		// Find next index
		ulint_t dist = jacobsthal_diff[k];
		if (dist > static_cast<ulint_t>(pend.end() - current_pend))
			break;

		FGroupIterator it = current_it + dist * 2;
		typename FGIContIterContainer::iterator pe = current_pend + dist;

		do
		{
			--pe;
			it -= 2;

			typename FGIContainer::iterator insertion_point
				= std::upper_bound(chain.begin(), *pe, *it);
			chain.insert(insertion_point, it);
		} while (pe != current_pend);

		current_it += dist * 2;
		current_pend += dist;
	}

    // If there are pend elements left, insert them into
    // the main chain, the order of insertion does not
    // matter so forward traversal is ok
	while (current_pend != pend.end())
	{
		typename FGIContainer::iterator insertion_point
			= std::upper_bound(chain.begin(), *current_pend, *current_it);
		chain.insert(insertion_point, current_it);
		current_it += 2;
		current_pend++;
	}


    ////////////////////////////////////////////////////////////
    // Move values in order to a cache then back to origin
	FContainer cache;
	for (typename FGIContainer::iterator it = chain.begin(); it != chain.end(); it++)
	{
		typename FContainer::iterator begin = (*it).base();
		typename FContainer::iterator end = begin + (*it).size();
		while (begin != end)
		{
			cache.push_back(*begin);
			begin++;
		}
	}
	typename FContainer::iterator it_main = first.base();
	for (typename FContainer::iterator it = cache.begin(); it != cache.end(); it++)
	{
		*it_main = *it;
		it_main++;
	}
	if (KDEBUG)
		_dprint_after(first, last);
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

	GroupIterator<Iterator> itend = first + size;
	if (has_stray_element)
		itend--;
	for (GroupIterator<Iterator> it = first; it != itend; it += 2)
	{
		std::cout << "[" << *it << " " << *(it + 1) << "] - ";
	}
	if (has_stray_element)
		std::cout << "+stray= " << std::vector<int>(first.base() + first.size() * 2 * (size / 2), last.base());
	std::cout << std::endl;
}
