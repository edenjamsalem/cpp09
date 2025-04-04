#include "./RPN.hpp"
#include "sstream"
#include <cstdlib>

RPN::RPN() {}

// RPN::RPN(const RPN& other)
// {
	
// }

// RPN& RPN::operator=(const RPN& other)
// {
// 	if (this != &other)
// 	{
		
// 	}
// 	return *this;
// }

RPN::~RPN() {}

bool isoperator(std::string &op)
{
    return (op == "+" || op == "-" || op == "*" || op == "/");
}

void RPN::add(int nbr)
{
	if (nbr < 0 || nbr > 9)
		throw invalidNumber();

	_stack.push(nbr);
}

void RPN::applyOp(std::string &op)
{
	if (!isoperator(op))
		throw invalidOperator();
	if (_stack.size() < 2)
		throw invalidNotation();
	
	unsigned int a = _stack.top();
	_stack.pop();
	unsigned int b = _stack.top();
	_stack.pop();
	if (op == "+")
		_stack.push(a + b);
	else if (op == "-")
		_stack.push(b - a);
	else if (op == "*")
		_stack.push(a * b);
	else if (op == "/")
	{
		if (a == 0)
			throw zeroDivision();
		_stack.push(b / a);
	}
}

void	RPN::calculate(std::string &equation)
{
	std::stringstream ss(equation);
	std::string elem;
	try
	{
		while (ss >> elem) 
		{
			if (isdigit(elem[0]))
				add(atoi(&elem[0]));
			else
				applyOp(elem);
		}
		if (_stack.size() != 1)
			throw invalidNotation();
		std::cout << _stack.top() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

const char *RPN::invalidNumber::what() const throw()
{
	return ("Invalid number: Must be in range 0-9.");
}

const char *RPN::invalidOperator::what() const throw()
{
	return ("Invalid operator: Must be '+, -, *, /' only.");
}

const char *RPN::invalidNotation::what() const throw()
{
	return ("Invalid RPN.");
}

const char *RPN::zeroDivision::what() const throw()
{
	return ("Division by zero error.");
}
