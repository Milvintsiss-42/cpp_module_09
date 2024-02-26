/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:25:31 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/26 02:45:00 by ple-stra         ###   ########.fr       */
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

	class ParsingError : public std::exception {
	private:
		size_t const _line_number;
		std::string const _description;
	public:
		ParsingError(size_t line_number, std::string const description);
		virtual ~ParsingError() throw ();
		virtual const char *what() const throw();
		size_t getLineNumber() const;
	};

	class NoDatabaseFile : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};
