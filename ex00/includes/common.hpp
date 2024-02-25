/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:25:00 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 20:49:31 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <limits>
#include "Date.hpp"

std::pair<Date, float> parseLine(
	std::string const &line,
	std::string const &delimiter,
	bool do_accept_0,
	float max_value);

class ParsingError : virtual public std::exception {
private:
	std::string const _description;
public:
	ParsingError(std::string const description) : _description(description) {}
	virtual ~ParsingError() throw () {}
	virtual const char *what() const throw()
	{
		return this->_description.c_str();
	}
};
