#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

typedef std::map<std::string, double> bitcoinMap;

class BitcoinExchange
{
    private:
    	bitcoinMap _bitcoinPrice;

    public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		std::map<std::string, double> &getPriceMap();
		std::map<std::string, double> &getDateAmountsMap();
		
		void	parseExchangeRateFile();
		void	genOutputFromInfile(const char *inFile);
		bool    validDate(std::string &date);
		bool    validValue(double &price);
		double	getMultiple(std::string &date);

};

#endif