#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _bitcoinPrice = other._bitcoinPrice;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::map<std::string, double> &BitcoinExchange::getPriceMap()
{
    return (_bitcoinPrice);
}

bool    BitcoinExchange::validDate(std::string &date)
{
    std::istringstream ss(date);
    std::string yearStr;
    std::string monthStr;
    std::string dayStr;

    std::getline(ss, yearStr, '-');
    std::getline(ss, monthStr, '-');
    std::getline(ss, dayStr, '-');

    int year = atoi(yearStr.c_str());
    int month = atoi(monthStr.c_str());
    int day = atoi(dayStr.c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    int maxDay;
    switch (month)
    {
        case 2: maxDay = 28;
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
                maxDay = 29;
            break;
        
        case 4: case 6: case 9: case 11: maxDay = 30;
            break;
        
        default: maxDay = 31;
            break;
    }
    return day <= maxDay;
}

bool BitcoinExchange::validValue(double &value)
{
    if (value < 0)
    {
        std::cerr << "Error: not a positive number.\n";
        return (0);
    }
    else if (value  > 1000)
    {
        std::cerr << "Error: too large a number.\n";
        return (0);
    }
    return (1);
}

double stod(std::string &str)
{
    std::istringstream iss(str);
    double value;

    if (!(iss >> value))
        value = 0.0;

    return value;
}

void BitcoinExchange::parseExchangeRateFile()
{
    std::ifstream file("data.csv");
    std::string tableHeaders;
    
    std::getline(file, tableHeaders);
    std::string line;
    while (std::getline(file, line))
    {
        std::string date, price;
        std::istringstream ss(line);

        getline(ss, date, ',');
        getline(ss, price);
        
        double value = stod(price);
        _bitcoinPrice.insert(std::pair<std::string, double>(date, value));
    }
}

double BitcoinExchange::getMultiple(std::string &date)
{
    std::map<std::string, double>::iterator it = _bitcoinPrice.upper_bound(date);

    if (it == _bitcoinPrice.begin())
        return (it->second);
    it--;
    return (it->second);
}

void BitcoinExchange::genOutputFromInfile(const char *inFile)
{
    std::ifstream file(inFile);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file.\n";
        return ;
    }

    std::string tableHeaders;
    std::getline(file, tableHeaders);

    std::string line;
    while (std::getline(file, line))
    {
        std::string date, amount;
        std::istringstream ss(line);

        getline(ss, date, '|');
        if (date.end()[-1] == ' ')
            date.erase(date.length() - 1);

        getline(ss, amount, '|');
        if (!validDate(date) || amount == "")
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue ;
        }

        double value = stod(amount);
        if (!validValue(value))
            continue ;

        std::cout << date << " => " << value <<  " = " << (value * getMultiple(date)) << std::endl;
    }
}

