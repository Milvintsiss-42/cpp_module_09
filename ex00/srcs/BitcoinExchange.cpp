/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:25:19 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 11:53:57 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::init()
{

	std::ifstream database_file("data.csv");
	if (!database_file.is_open())
		throw NoDatabaseFile();
	size_t line_number = 1;
	std::string line;
	if (!database_file.good()
		|| !std::getline(database_file, line) // we don't check anything here, get_line return a stream
		|| line != "date,exchange_rate")
		throw ParsingError(line_number, "invalid header");
	while (database_file.good())
	{
		line_number++;
		std::getline(database_file, line);
		if (line.empty())
		{
			if (database_file.good())
				throw ParsingError(line_number, "bad input => empty line");
			return;
		}

		try
		{
			std::pair<Date, double> r = parseLine(
				line,
				",",
				true,
				std::numeric_limits<int>::max());
			if (this->_exchange_rates.count(r.first) == 1)
				throw ParsingError(
					line_number,
					"date " + r.first.getDateString() + " is a duplicate");
			this->_exchange_rates.insert(r);
		}
		catch (::ParsingError &e)
		{
			throw ParsingError(line_number, e.what());
		}
	}
}

double BitcoinExchange::getNearestDateExchangeRate(Date const &date) const
{
	std::map<Date, double>::const_iterator r = this->_exchange_rates.lower_bound(date);
	if (date < r->first && r == this->_exchange_rates.begin())
		return -1;
	else if (date < r->first)
		r--;
	return r->second;
}


BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	this->_exchange_rates = rhs._exchange_rates;
	return *this;
}
