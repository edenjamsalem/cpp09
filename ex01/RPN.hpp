#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>

class RPN
{
	private:
		std::stack<unsigned int> _stack;	

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		void	add(std::string &nbr);
		void	applyOp(std::string &op);
		void	calculate(std::string &equation);

		class invalidNumber : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class invalidOperator : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class invalidNotation: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class zeroDivision: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

};

#endif
