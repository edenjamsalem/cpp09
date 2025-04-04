#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Incorrect number of arguments: expected 2\n";
        return  (-1);
    }
    
    RPN rpn;
    std::string equation(av[1]);
    rpn.calculate(equation);
}
