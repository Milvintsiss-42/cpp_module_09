/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:36:12 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/28 19:32:12 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include "common.hpp"
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	int rvalue = 0;

	if (argc < 2)
	{
		std::cout << "Usage: ./PmergeMe [positive integer sequence]" << std::endl;
		return -1;
	}
	std::vector<int> vseq;
	std::deque<int> dseq;
	if (!parseSequence(vseq, argv + 1, argc -1))
		return -1;
	std::copy(vseq.begin(), vseq.end(), std::back_inserter(dseq));

	std::cout << "Before:	" << vseq << std::endl;

	struct timeval vec_start_time, vec_end_time, deq_start_time, deq_end_time;
    gettimeofday(&vec_start_time, NULL);
	if (KDEBUG)
		std::cerr << "Vector" << std::endl;
	PmergeMe::sort(vseq);
    gettimeofday(&vec_end_time, NULL);
    gettimeofday(&deq_start_time, NULL);
	if (KDEBUG)
		std::cerr << "Deque" << std::endl;
	PmergeMe::sort(dseq);
    gettimeofday(&deq_end_time, NULL);

	std::cout << "After:	" << vseq << std::endl;

	printProcessTime("vector", vseq.size(),
		getProcessTimeInMicro(vec_start_time, vec_end_time));
	printProcessTime("deque", dseq.size(),
		getProcessTimeInMicro(deq_start_time, deq_end_time));

	if (!areContainersEqual(vseq, dseq))
	{
		std::cout << "Containers are not equal !" << std::endl;
		rvalue = -1;
	}
	if (!is_sorted(vseq))
	{
		std::cout << "Vector is not sorted!" << std::endl;
		rvalue = -1;
	}
	if (!is_sorted(dseq))
	{
		std::cout << "Deque is not sorted!" << std::endl;
		rvalue = -1;
	}
	return rvalue;
}
