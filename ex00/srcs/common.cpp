/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:25:10 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 20:49:31 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"

static bool is_float(std::string const literal);

std::pair<Date, float> parseLine(
	std::string const &line,
	std::string const &delimiter,
	bool do_accept_0,
	float max_value)
{
		size_t delimiter_pos = line.find(delimiter);
		if (delimiter_pos == std::string::npos)
			throw ParsingError("bad input => \"" + line + "\"");

		std::string date_string = line.substr(0, delimiter_pos);
		Date date(date_string);
		if (date.getTimestamp() < 0)
			throw ParsingError("bad input => " + date_string + " => date format or value invalid");

		std::string float_string = line.substr(delimiter_pos + delimiter.length());
		if (!is_float(float_string))
			throw ParsingError("bad input => " + float_string + " => invalid value");
		float value;
		std::istringstream(float_string) >> value;
		if (value < 0)
			throw ParsingError("not a positive number");
		if (value == 0 && !do_accept_0)
			throw ParsingError("0 is not a valid value");
		if (value >= max_value)
			throw ParsingError("too large a number");

		return std::pair<Date, float>(date, value);
}

static bool is_float(std::string const literal)
{
	std::string s(literal);
	int dot_count = 0;

	std::string::const_iterator it = s.begin();
	if (*it == '-')
		it++;
    while (it != s.end())
	{
		if (*it == '.' && it != s.begin())
			dot_count++;
		else if (!std::isdigit(*it))
			return false;
		++it;
	}
	if (dot_count > 1 || *(s.end() - 1) == '.')
		return false;
    return true;
}
