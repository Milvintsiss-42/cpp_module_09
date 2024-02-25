/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:25:31 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 20:49:31 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <string>
#include <map>
#include "Date.hpp"
#include "common.hpp"

class BitcoinExchange {
private:
	std::map<Date, float> _exchange_rates;
public:
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &src);
	~BitcoinExchange();

	void init();
	float getNearestDateExchangeRate(Date const &date) const;

	BitcoinExchange &operator=(BitcoinExchange const &rhs);

	class ParsingError : virtual public std::exception {
	private:
		size_t const _line_number;
		std::string const _description;
	public:
		ParsingError(size_t line_number, std::string const description)
			: _line_number(line_number), _description(description) {}
		virtual ~ParsingError() throw () {}
		virtual const char *what() const throw()
		{
			return this->_description.c_str();
		}
		size_t getLineNumber() const { return this->_line_number; }
	};

	class NoDatabaseFile : public std::exception {
	public:
		virtual const char *what() const throw()
		{
			return ("Unable to open 'data.csv' file, verify that the file is at the root of the directory and accessible.");
		}
	};
};
