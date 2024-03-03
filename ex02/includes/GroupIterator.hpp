/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GroupIterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:20:00 by ple-stra          #+#    #+#             */
/*   Updated: 2024/03/03 15:16:02 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template<typename Iterator>
class GroupIterator {
private:
	Iterator _it;
	size_t _size;

public:
	GroupIterator();
	GroupIterator(Iterator it, size_t size);
	GroupIterator(GroupIterator<Iterator> const &src);
	~GroupIterator();

	Iterator base() const;
	size_t size() const;

	GroupIterator<Iterator> &operator=(GroupIterator<Iterator> const &rhs);
	typename Iterator::value_type &operator*();
	typename Iterator::value_type operator*() const;
	GroupIterator<Iterator> operator++(int);
	GroupIterator<Iterator> operator--(int);
	GroupIterator<Iterator> &operator+=(size_t increment);
	GroupIterator<Iterator> &operator-=(size_t increment);
	bool operator==(GroupIterator<Iterator> const &rhs);
	bool operator!=(GroupIterator<Iterator> const &rhs);
};

template<typename Iterator>
GroupIterator<Iterator> operator+(
	GroupIterator<Iterator> it,
	size_t increment);
template<typename Iterator>
GroupIterator<Iterator> operator-(
	GroupIterator<Iterator> it,
	size_t increment);
template<typename Iterator>
size_t operator-(
	GroupIterator<Iterator> const &lhs,
	GroupIterator<Iterator> const &rhs);
template<typename T, typename Iterator>
bool operator<(
	T const &lhs,
	GroupIterator<Iterator> const &rhs);

template<typename Iterator>
void iter_swap(GroupIterator<Iterator> lhs, GroupIterator<Iterator> rhs);

#include "GroupIterator.tpp"
