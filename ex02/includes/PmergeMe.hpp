/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:18:51 by ple-stra          #+#    #+#             */
/*   Updated: 2024/03/03 15:27:22 by ple-stra         ###   ########.fr       */
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

#define JACOBSTHAL_SUIT { \
 1u, 1u, 3u, 5u, 11u, 21u, 43u, 85u, 171u, 341u, 683u, 1365u, 2731u, 5461u, \
 10923u, 21845u, 43691u, 87381u, 174763u, 349525u, 699051u, 1398101u, \
 2796203u, 5592405u, 11184811u, 22369621u, 44739243u, 89478485u, \
 178956971u, 357913941u, 715827883u, 1431655765u, 2863311531u, \
 5726623061u, 11453246123u}

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
	static void _dprint_pairs(
		GroupIterator<Iterator> first,
		GroupIterator<Iterator> last);
	template<template<typename, typename> class Container, typename Value>
	static void _dprint_FGIContainer(std::string const &name, FGIContainer &container);
	template<template<typename, typename> class Container, typename Value>
	static void _binary_insert(
		FGIContainer &r,
		typename FGIContainer::iterator &to_insert);

public:
	PmergeMe();
	PmergeMe(PmergeMe const &src);
	~PmergeMe();

	template<template<typename, typename> class Container, typename Value>
	static void sort(FContainer &seq);

	template<template<typename, typename> class Container, typename Value>
	static void sort_base(
		FGroupIterator first,
		FGroupIterator last);

	PmergeMe &operator=(PmergeMe const &rhs);
};

#include "PmergeMe.tpp"
