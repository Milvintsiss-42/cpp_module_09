/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 04:34:41 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 11:54:27 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"

static int countDigits(std::string::const_iterator start, std::string::const_iterator end);
static bool isDateFormatValid(std::string const &datetimeString);
static bool isDateValid(std::string const &datetimeString, struct tm date);
static time_t parseDate(std::string const &datetimeString);

Date::Date() : _date_string("invalid"), _timestamp(-1)
{
}

Date::Date(std::string const &date_string) : _date_string(date_string)
{
	this->_timestamp = parseDate(date_string);
	if (this->_timestamp < 0)
		this->_date_string = "invalid";
}

Date::Date(Date const &src)
{
	*this = src;
}

Date::~Date()
{
}


std::string Date::getDateString() const
{
	return this->_date_string;
}

time_t Date::getTimestamp() const
{
	return this->_timestamp;
}


Date &Date::operator=(Date const &rhs)
{
	this->_date_string = rhs._date_string;
	this->_timestamp = rhs._timestamp;
	return *this;
}

bool Date::operator<=(Date const &rhs) const
{
	return this->_timestamp <= rhs._timestamp;
}

bool Date::operator>=(Date const &rhs) const
{
	return this->_timestamp >= rhs._timestamp;
}

bool Date::operator<(Date const &rhs) const
{
	return this->_timestamp < rhs._timestamp;
}

bool Date::operator>(Date const &rhs) const
{
	return this->_timestamp > rhs._timestamp;
}

bool Date::operator==(Date const &rhs) const
{
	return this->_timestamp == rhs._timestamp;
}

bool Date::operator!=(Date const &rhs) const
{
	return this->_timestamp != rhs._timestamp;
}

std::ostream & operator<<(std::ostream & o, Date const & rhs)
{
	o << rhs.getDateString();
	return o;
}

static int countDigits(std::string::const_iterator start, std::string::const_iterator end)
{
	return std::count_if<std::string::const_iterator, int(*)(int)>(start, end, std::isdigit);
}

static bool isDateFormatValid(std::string const &datetimeString)
{
	if (datetimeString.length() != 10)
		return false;

	std::string::const_iterator begin(datetimeString.begin());
	if (countDigits(begin, begin + 4) != 4
		|| datetimeString[4] != '-'
		|| countDigits(begin + 5, begin + 7) != 2
		|| datetimeString[7] != '-'
		|| countDigits(begin + 8, begin + 10) != 2)
		return false;
	return true;
}

static bool isDateValid(std::string const &datetimeString, struct tm date)
{
	int y, m, d = 0;
	char delimiter;
	std::istringstream(datetimeString)
		>> y >> delimiter >> m >> delimiter >> d;
	return (y == date.tm_year + 1900
		&& m == date.tm_mon + 1
		&& d == date.tm_mday);
}

static time_t parseDate(std::string const &datetimeString)
{
	if (!isDateFormatValid(datetimeString))
		return -1;
    struct tm tmStruct = {};
    strptime(datetimeString.c_str(), "%Y-%m-%d", &tmStruct);
	time_t timestamp = mktime(&tmStruct); // also normalize tmStruct
	if (!isDateValid(datetimeString, tmStruct))
		return -1;
    return timestamp;
}
