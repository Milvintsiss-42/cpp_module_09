/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:36:12 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/25 11:54:39 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include "common.hpp"

int parsing_error(std::string const &description)
{
	std::cerr << "Error: " << description << "." << std::endl;
	return -1;
}

int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
	{
		std::cerr << "Usage: ./btc input_file" << std::endl;
		return -1;
	}
	BitcoinExchange exchangeDatabase;
	try
	{
		exchangeDatabase.init();
	}
	catch (BitcoinExchange::NoDatabaseFile &e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	catch (BitcoinExchange::ParsingError &e)
	{
		std::cerr << "Database parsing error at line " << e.getLineNumber()
			<< ": " << e.what() << "." << std::endl;
		return -1;
	}

	std::ifstream input_file(argv[1]);
	if (!input_file.is_open())
	{
		parsing_error("could not open file");
		return 2;
	}

	std::string line;
	if (!input_file.good()
		|| !std::getline(input_file, line) // we don't check anything here, get_line return a stream
		|| line != "date | value")
		return parsing_error("invalid header");
	while (input_file.good())
	{
		std::getline(input_file, line);
		if (line.empty())
		{
			if (input_file.good())
				parsing_error("bad input => empty line");
			continue;
		}

		try
		{
			std::pair<Date, double> r = parseLine(line, " | ", false, 1000);
			double exchangeRate =
				exchangeDatabase.getNearestDateExchangeRate(r.first);
			if (exchangeRate >= 0)
				std::cout << r.first << " => " << r.second << " = "
					<< r.second * exchangeRate << std::endl;
			else
				std::cout << "Error: " << r.first << " => This date is not in database and there is no antecedent date in the database." << std::endl;
		}
		catch (ParsingError &e)
		{
			parsing_error(e.what());
			continue;
		}
	}
	return 0;
}
