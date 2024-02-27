/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GroupIterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:20:00 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/27 09:40:37 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template<typename Iterator>
class GroupIterator {
private:
	Iterator _it;
	size_t _size;

public:
	GroupIterator() {};
	GroupIterator(Iterator it, size_t size) : _it(it), _size(size) {};
	GroupIterator(GroupIterator<Iterator> const &src) { *this = src; };
	~GroupIterator() {}

	Iterator base() const { return this->_it; }
	size_t size() const { return this->_size; }

	GroupIterator<Iterator> &operator=(GroupIterator<Iterator> const &rhs)
	{
		this->_it = rhs._it;
		this->_size = rhs._size;
		return *this;
	}
	typename Iterator::value_type &operator*()
	{
		return *(this->_it + this->_size - 1);
	}
	GroupIterator<Iterator> operator++(int)
	{
		GroupIterator cp(*this);
		this->_it += this->_size;
		return cp;
	}
	GroupIterator<Iterator> operator--(int)
	{
		GroupIterator<Iterator> cp(*this);
		this->_it -= this->_size;
		return cp;
	}
	GroupIterator<Iterator> &operator+=(size_t increment)
	{
		this->_it += this->_size * increment;
		return *this;
	}
	GroupIterator<Iterator> &operator-=(size_t increment)
	{
		this->_it -= this->_size * increment;
		return *this;
	}
	bool operator==(GroupIterator<Iterator> const &rhs)
	{
		return this->_it == rhs._it;
	}
	bool operator!=(GroupIterator<Iterator> const &rhs)
	{
		return this->_it != rhs._it;
	}
};

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

template<typename Iterator>
void iter_swap(GroupIterator<Iterator> lhs, GroupIterator<Iterator> rhs)
{
    std::swap_ranges(lhs.base(), lhs.base() + lhs.size(), rhs.base());
}
