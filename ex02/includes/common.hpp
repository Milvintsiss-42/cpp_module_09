/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:44:49 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/28 08:27:44 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <sys/time.h>

#ifndef KDEBUG
# define KDEBUG 0
#endif

bool parseSequence(std::vector<int> &rseq, char **unparsed_seq, int elements_count);

std::ostream &operator<<(std::ostream & o, std::vector<int> const & rhs);
std::ostream &operator<<(std::ostream & o, std::deque<int> const & rhs);

long getProcessTimeInMicro(struct timeval start_time, struct timeval end_time);
void printProcessTime(std::string const &container_name, size_t size, long process_time);

bool areContainersEqual(std::vector<int> const &vec, std::deque<int> const &deq);

template<typename Container>
bool is_sorted(Container const &container)
{
	Container newContainer(container);

	sort(newContainer.begin(), newContainer.end());
	return container == newContainer;
}
