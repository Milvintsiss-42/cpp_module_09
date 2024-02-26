/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:36:12 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/26 01:03:47 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
	{
		std::cerr << "Usage: ./RPN \"RPN expression\"" << std::endl;
		return -1;
	}

	RPN rpn_processor;
	try
	{
		rpn_processor.evaluateExpression(argv[1]);
		if (rpn_processor.getSize() == 1)
			std::cout << rpn_processor.getTop() << std::endl;
		else
		{
			std::cerr << "Error: expression does not end to a result."
				<< std::endl;
			return -1;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}
