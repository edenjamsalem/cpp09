#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    BitcoinExchange bitcoinExchange;
    std::string bitcoinDataFile = "data.csv";

    (void)argc;
    (void)argv;
    // if (argc != 2)
    //     throw(incorrectArgCountException())

    bitcoinExchange.parseExchangeRateFile();
    bitcoinExchange.parseDateValueFile(argv[1]);
//    bitcoinExchange.calculateExchange
    
}