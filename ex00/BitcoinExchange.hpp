#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

class BitcoinExchange
{
    private:
    	std::map<std::string, double> _bitcoinPriceMap;
    	std::map<std::string, double> _bitcoinDateAmountsMap;

    public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		std::map<std::string, double> &getPriceMap();
		std::map<std::string, double> &getDateAmountsMap();
		
		void parseExchangeRateFile();
		void parseDateValueFile(const char *inFile);
		void genOutput(std::map<std::string, double> &priceMap, std::map<std::string, double> &valueMap);

};

#endif