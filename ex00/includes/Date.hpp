/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 04:26:18 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 04:47:21 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <ctime>

class Date {
private:
	std::string _date_string;
	time_t _timestamp;
public:
	Date();
	Date(std::string const &date_string);
	Date(Date const &src);
	~Date();

	std::string getDateString() const;
	time_t getTimestamp() const;

	Date &operator=(Date const &rhs);
	bool operator<=(Date const &rhs) const;
	bool operator>=(Date const &rhs) const;
	bool operator<(Date const &rhs) const;
	bool operator>(Date const &rhs) const;
	bool operator==(Date const &rhs) const;
	bool operator!=(Date const &rhs) const;
};

std::ostream & operator<<(std::ostream & o, Date const & rhs);
