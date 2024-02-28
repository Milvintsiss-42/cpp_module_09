/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:46:43 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/28 19:31:48 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"

static bool is_positive_int(std::string const &int_string)
{
	if (int_string.empty())
		return false;
    std::string::const_iterator it = int_string.begin();
	if (*it == '+')
		it++;
    while (it != int_string.end() && std::isdigit(*it))
		++it;
    return (it == int_string.end());
}

bool parseSequence(std::vector<int> &rseq, char **unparsed_seq, int elements_count)
{
	while (elements_count--)
	{
		if (!is_positive_int(*unparsed_seq))
		{
			std::cout << "Error: invalid value \"" << *unparsed_seq << "\"" << std::endl;
			return false;
		}
		int i;
		std::istringstream ss(*unparsed_seq);
		ss >> i;
		if (ss.fail())
		{
			std::cout << "Error: unable to parse value \"" << *unparsed_seq << "\" (maybe overflow ?)." << std::endl;
			return false;
		}
		rseq.push_back(i);
		unparsed_seq++;
	}
	return true;
}

std::ostream &operator<<(std::ostream & o, std::vector<int> const & rhs)
{
	std::vector<int>::const_iterator it = rhs.begin();
	while (it != rhs.end())
	{
		o << *it;
		if (it + 1 != rhs.end())
			o << ' ';
		it++;
	}
	return o;
}

std::ostream &operator<<(std::ostream & o, std::deque<int> const & rhs)
{
	std::deque<int>::const_iterator it = rhs.begin();
	while (it != rhs.end())
	{
		o << *it;
		if (it + 1 != rhs.end())
			o << ' ';
		it++;
	}
	return o;
}

long getProcessTimeInMicro(struct timeval start_time, struct timeval end_time)
{
	long diff, seconds, useconds;

    seconds = end_time.tv_sec - start_time.tv_sec;
    useconds = end_time.tv_usec - start_time.tv_usec;
    diff = ((seconds) * 1000  * 1000 + useconds);

    return diff;
}

void printProcessTime(std::string const &container_name, size_t size, long process_time)
{
	std::cout << "Time to process a range of " << size
		<< " elements with std::" << container_name << " : " << process_time
		<< " us." << std::endl;
}

bool areContainersEqual(std::vector<int> const &vec, std::deque<int> const &deq)
{
	if (vec.size() != deq.size())
		return false;
	std::vector<int>::const_iterator vit = vec.begin();
	std::deque<int>::const_iterator dit = deq.begin();
	while (vit != vec.end())
	{
		if (*vit != *dit)
			return false;
		vit++;
		dit++;
	}
	return true;
}
