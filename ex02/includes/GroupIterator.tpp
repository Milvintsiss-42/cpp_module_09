/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GroupIterator.tpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:08:35 by ple-stra          #+#    #+#             */
/*   Updated: 2024/03/03 15:21:44 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


template<typename Iterator>
GroupIterator<Iterator>::GroupIterator() {};

template<typename Iterator>
GroupIterator<Iterator>::GroupIterator(Iterator it, size_t size)
	: _it(it), _size(size) {};

template<typename Iterator>
GroupIterator<Iterator>::GroupIterator(GroupIterator<Iterator> const &src)
{
	*this = src;
};

template<typename Iterator>
GroupIterator<Iterator>::~GroupIterator() {}

template<typename Iterator>
Iterator GroupIterator<Iterator>::base() const
{
	return this->_it;
}

template<typename Iterator>
size_t GroupIterator<Iterator>::size() const
{
	return this->_size;
}

template<typename Iterator>
GroupIterator<Iterator> &GroupIterator<Iterator>::operator=(GroupIterator<Iterator> const &rhs)
{
	this->_it = rhs._it;
	this->_size = rhs._size;
	return *this;
}

template<typename Iterator>
typename Iterator::value_type &GroupIterator<Iterator>::operator*()
{
	return *(this->_it + this->_size - 1);
}
template<typename Iterator>
typename Iterator::value_type GroupIterator<Iterator>::operator*() const
{
	return *(this->_it + this->_size - 1);
}
template<typename Iterator>
GroupIterator<Iterator> GroupIterator<Iterator>::operator++(int)
{
	GroupIterator cp(*this);
	this->_it += this->_size;
	return cp;
}
template<typename Iterator>
GroupIterator<Iterator> GroupIterator<Iterator>::operator--(int)
{
	GroupIterator<Iterator> cp(*this);
	this->_it -= this->_size;
	return cp;
}
template<typename Iterator>
GroupIterator<Iterator> &GroupIterator<Iterator>::operator+=(size_t increment)
{
	this->_it += this->_size * increment;
	return *this;
}
template<typename Iterator>
GroupIterator<Iterator> &GroupIterator<Iterator>::operator-=(size_t increment)
{
	this->_it -= this->_size * increment;
	return *this;
}
template<typename Iterator>
bool GroupIterator<Iterator>::operator==(GroupIterator<Iterator> const &rhs)
{
	return this->_it == rhs._it;
}
template<typename Iterator>
bool GroupIterator<Iterator>::operator!=(GroupIterator<Iterator> const &rhs)
{
	return this->_it != rhs._it;
}


template<typename Iterator>
GroupIterator<Iterator> operator+(
	GroupIterator<Iterator> it,
	size_t increment)
{
    return it += increment;
}
template<typename Iterator>
GroupIterator<Iterator> operator-(
	GroupIterator<Iterator> it,
	size_t increment)
{
    return it -= increment;
}
template<typename Iterator>
size_t operator-(
	GroupIterator<Iterator> const &lhs,
	GroupIterator<Iterator> const &rhs)
{
    return (lhs.base() - rhs.base()) / lhs.size();
}
template<typename T, typename Iterator>
bool operator<(
	T const &lhs,
	GroupIterator<Iterator> const &rhs)
{
    return lhs < *rhs;
}

template<typename Iterator>
void iter_swap(GroupIterator<Iterator> lhs, GroupIterator<Iterator> rhs)
{
    std::swap_ranges(lhs.base(), lhs.base() + lhs.size(), rhs.base());
}
