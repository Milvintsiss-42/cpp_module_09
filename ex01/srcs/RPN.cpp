/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:18:52 by ple-stra          #+#    #+#             */
/*   Updated: 2024/02/26 02:47:30 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(RPN const &src)
{
	*this = src;
}

RPN::~RPN()
{

}

void RPN::evaluateExpression(std::string const &expr)
{
	std::string::const_iterator it = expr.begin();
	while (it != expr.end())
	{
		if (*it == ' ')
		{
			if (it == expr.begin() || it + 1 == expr.end()
				|| *(it - 1) == ' ' || *(it + 1) == ' ')
				throw RPN::InvalidRPNExpression();
		}
		else if (std::isdigit(*it))
		{
			if (it + 1 != expr.end() && *(it + 1) != ' ')
				throw RPN::InvalidRPNExpression();
			this->_exec_stack.push(*it - '0');
		}
		else
			_execOperation(*it);
		it++;
	}
}
#include <iostream>
void RPN::_execOperation(char c)
{
	switch (c)
	{
		case '+':
			_sum();
			break;
		case '-':
			_substract();
			break;
		case '*':
			_multiply();
			break;
		case '/':
			_divide();
			break;
		default:
			throw RPN::InvalidRPNExpression();
	}
}

void RPN::_getOperands(int &a, int &b)
{
	if (this->_exec_stack.size() < 2)
		throw RPN::InvalidRPNExpression();
	b = this->_exec_stack.top();
	this->_exec_stack.pop();
	a = this->_exec_stack.top();
	this->_exec_stack.pop();
}

void RPN::_sum()
{
	int a, b, r;
	_getOperands(a, b);
	r = a + b;
	if ((a > 0 && b > 0 && r < 0)
		|| (a < 0 && b < 0 && r > 0))
		throw Overflow();
	this->_exec_stack.push(r);
}

void RPN::_substract()
{
	int a, b, r;
	_getOperands(a, b);
	r = a - b;
	if ((a > 0 && b < 0 && r < 0)
		|| (a < 0 && b > 0 && r > 0))
		throw Overflow();
	this->_exec_stack.push(r);
}

void RPN::_multiply()
{
	int a, b, r;
	_getOperands(a, b);
	r = a * b;
	if (b != 0 && a != r / b)
		throw RPN::Overflow();
	this->_exec_stack.push(r);
}

void RPN::_divide()
{
	int a, b, r;
	_getOperands(a, b);
	if (b == 0)
		throw RPN::DivisionByZero();
	r = a / b;
	this->_exec_stack.push(r);
}


std::stack<int>::size_type RPN::getSize() const
{
	return this->_exec_stack.size();
}

int RPN::getTop() const
{
	if (this->_exec_stack.empty())
		throw RPN::TopOnEmptyStack();
	return this->_exec_stack.top();
}


RPN &RPN::operator=(RPN const &rhs)
{
	this->_exec_stack = rhs._exec_stack;
	return *this;
}

const char *RPN::InvalidRPNExpression::what() const throw()
{
	return ("InvalidRPNExpression");
}
const char *RPN::Overflow::what() const throw()
{
	return ("Overflow");
}
const char *RPN::DivisionByZero::what() const throw()
{
	return ("DivisionByZero");
}
const char *RPN::TopOnEmptyStack::what() const throw()
{
	return ("TopOnEmptyStack");
}
