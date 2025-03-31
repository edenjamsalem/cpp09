#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    BitcoinExchange bitcoinExchange;

    if (argc != 2)
    {
        std::cerr << "Error: could not open file.\n";
        return (1);
    }
    bitcoinExchange.parseExchangeRateFile();
    bitcoinExchange.genOutputFromInfile(argv[1]);
}