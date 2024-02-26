/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:19:07 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/26 02:49:36 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>

class RPN {
private:
	std::stack<int> _exec_stack;

	void _execOperation(char c);
	void _getOperands(int &a, int &b);
	void _sum();
	void _substract();
	void _multiply();
	void _divide();
public:
	RPN();
	RPN(RPN const &src);
	~RPN();

	std::stack<int>::size_type getSize() const;
	int getTop() const;

	void evaluateExpression(std::string const &expr);

	RPN &operator=(RPN const &rhs);

	class InvalidRPNExpression : public std::exception {
	public:
		virtual const char *what() const throw();
	};
	class Overflow : public std::exception {
	public:
		virtual const char *what() const throw();
	};
	class DivisionByZero : public std::exception {
	public:
		virtual const char *what() const throw();
	};
	class TopOnEmptyStack : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};
