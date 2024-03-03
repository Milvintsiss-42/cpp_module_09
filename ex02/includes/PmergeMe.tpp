/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:59:41 by ple-stra          #+#    #+#             */
/*   Updated: 2024/03/03 15:27:22 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template<template<typename, typename> class Container, typename Value>
void PmergeMe::sort(FContainer &seq)
{
	sort_base<Container, Value>(
		FGroupIterator(seq.begin(), 1),
		FGroupIterator(seq.end(), 1)
	);
}

template<template<typename, typename> class Container, typename Value>
void PmergeMe::sort_base(
	FGroupIterator first,
	FGroupIterator last)
{
    static const ulint_t jacobsthal_suit[] = JACOBSTHAL_SUIT;

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

	sort_base<Container, Value>(
		FGroupIterator(first.base(), first.size() * 2),
		FGroupIterator(itend.base(), itend.size() * 2)
	);

	FGIContainer bigs;
	FGIContainer smalls;
	FGIContainer sorted;
	for (FGroupIterator it = first; it != itend; it += 2)
	{
		smalls.push_back(it);
		bigs.push_back(it + 1);
	}
	sorted.push_back(*smalls.begin());
	sorted.insert(sorted.end(), bigs.begin(), bigs.end());

	if (KDEBUG)
	{
		_dprint_FGIContainer<Container, Value>("Smalls", smalls);
		_dprint_FGIContainer<Container, Value>("Bigs", bigs);
		_dprint_FGIContainer<Container, Value>("Sorted", sorted);
	}

	bool is_first_iter = true;
	for (int k = 1; ; k++)
	{
		ulint_t magic = jacobsthal_suit[k];
		ulint_t magic_minus1 = jacobsthal_suit[k - 1];

		if (KDEBUG)
		{
			std::cout << "Magic: " << magic << std::endl;
			std::cout << "Magic_minus1: " << magic_minus1 << std::endl;
		}

		if (magic_minus1 > smalls.size() - 1)
			break;

		if (magic > smalls.size() - 1)
			magic = smalls.size() - 1;

		for (; magic > magic_minus1 || (magic == 1 && is_first_iter); magic--)
		{
			is_first_iter = false;
			typename FGIContainer::iterator to_insert = smalls.begin() + magic;
			if (KDEBUG)
			{
				std::cout << "Iter: ";
				_dprint_FGIContainer<Container, Value>("Sorted", sorted);
				std::cout << "Trying to insert: " << *(*to_insert) << std::endl;
			}
			_binary_insert<Container, Value>(sorted, to_insert);
		}
	}

	if (has_stray_element)
	{
		FGIContainer tmp;
		tmp.push_back(last - 1);
		typename FGIContainer::iterator to_insert = tmp.begin();
		_binary_insert<Container, Value>(sorted, to_insert);
	}

	if (KDEBUG)
	{
		_dprint_FGIContainer<Container, Value>("Sorted", sorted);
	}

	// Copy `sorted` in base container
	FContainer cache;
	for (typename FGIContainer::iterator it = sorted.begin(); it != sorted.end(); it++)
	{
		typename FContainer::iterator seg_begin = (*it).base();
		typename FContainer::iterator seg_end = seg_begin + (*it).size();
		for (typename FContainer::iterator seg_it = seg_begin; seg_it != seg_end; seg_it++)
		{
			cache.push_back(*seg_it);
		}
	}
	typename FContainer::iterator base_it = first.base();
	for (typename FContainer::iterator cache_it = cache.begin(); cache_it != cache.end(); cache_it++)
	{
		*base_it = *cache_it;
		base_it++;
	}

	if (KDEBUG)
	{
		_dprint_after(first, last);
		std::cout << std::endl;
	}
}

template<template<typename, typename> class Container, typename Value>
void PmergeMe::_binary_insert(
	FGIContainer &r,
	typename FGIContainer::iterator &to_insert)
{

	typename FGIContainer::iterator begin = r.begin();
	typename FGIContainer::iterator end = r.end();
	typename FGIContainer::iterator middle = begin + (end - begin) / 2;
	while (true)
	{
		if (*(*to_insert) < *(*middle))
		{
			if (middle - begin == 0)
			{
				r.insert(begin, *to_insert);
				break;
			}
			else
			{
				end = middle;
				middle = begin + (end - begin) / 2;
			}
		}
		else
		{
			if (end - middle == 1)
			{
				r.insert(end, *to_insert);
				break;
			}
			else
			{
				begin = middle + 1;
				middle = begin + (end - begin) / 2;
			}
		}
	}
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
	_dprint_pairs(first, last);
}

template<typename Iterator>
void PmergeMe::_dprint_after(
	GroupIterator<Iterator> first,
	GroupIterator<Iterator> last)
{
	std::cout << "After: ";
	_dprint_pairs(first, last);
	std::cout << "Seq: " << std::vector<int>(first.base(), last.base()) << std::endl;
}

template<typename Iterator>
void PmergeMe::_dprint_pairs(
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
		std::cout << "+stray= " << *(last - 1);
	std::cout << std::endl;
}

template<template<typename, typename> class Container, typename Value>
void PmergeMe::_dprint_FGIContainer(std::string const &name, FGIContainer &container)
{
	std::cout << name << ":";
	for (typename FGIContainer::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << " " << *(*it);
	}
	std::cout << std::endl;
}
