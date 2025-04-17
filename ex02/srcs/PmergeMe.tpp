#pragma once
#include "../includes/PmergeMe.hpp"

/* *** CONSTRUCTORS & DESTURCTORS *** */
template<template<typename, typename> class Container >
PmergeMe<Container>::PmergeMe()
{

}

template<template<typename, typename> class Container >
PmergeMe<Container>::~PmergeMe() {}

/* *** GETTERS & SETTERS *** */

template<template<typename, typename> class Container >
const typename PmergeMe<Container>::container_t &PmergeMe<Container>::getNums() const {
	return (_nums);
}

/* *** MISC FNS *** */

template<template<typename, typename> class Container >
std::string PmergeMe<Container>::_getContainerType()
{
	std::string typeData = typeid(container_t).name();	
	if (typeData == "St6vectorIiSaIiEE")
		return ("std::vector");
	else if (typeData == "NSt7__cxx114listIiSaIiEEE")
		return ("std::list");
	else if (typeData == "St5dequeIiSaIiEE")
		return ("std::deque");
	return ("unknown container");
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::_printPairs() 
{
	std::cout << "Pairs: ";

	typename pairs_t::iterator it = _pairs.begin();
	while (it != _pairs.end()) {
		std::cout << it->first << "," << it->second << "  ";
		++it;
	}
	std::cout << std::endl;
}

template<template<typename, typename> class Container >
void	PmergeMe<Container>::_parseInput(char **nums, int size)
{
	for (int i = 0; i < size; i++) {
		_nums.push_back(safe_strtoi(nums[i]));
	}
	_size = size;
}

/* *** MERGE INSERTION SORT FNS *** */

template<template<typename, typename> class Container >
void PmergeMe<Container>::mergeInsertSort(char **nums, int size)
{
	std::clock_t start = std::clock();

	_parseInput(nums, size);
	_sortIntoPairs();
	_mergeSortPairs(_pairs, 0, _pairs.size() - 1);
//	_printPairs(); // testing only
	_genSequences();
	
	std::clock_t end = std::clock();
	double time_taken = end - start * 1000000.0 / CLOCKS_PER_SEC;
	std::cout << YELLOW << "Time taken to process a range of " << _size; 
	std::cout << " elements with " << _getContainerType() << " : ";
	std::cout << std::fixed << time_taken << " us" << RESET << std::endl;
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::_sortIntoPairs()
{
	typename container_t::iterator it = _nums.begin();
	while (_nums.size() > 0)
	{
		if (_nums.size() == 1) {
			_straggler = *it;
			_nums.erase(it);
			break ;
		}
		std::pair<int,int> pair;
		pair.first = *it;
		it = _nums.erase(it);

		pair.second = *it;
		it = _nums.erase(it);

		if (pair.first < pair.second)
			std::swap(pair.first, pair.second);
		_pairs.push_back(pair);
	}
}

template<template<typename, typename> class Container>
void PmergeMe<Container>::_mergeSortPairs(pairs_t &pairs, int left, int right)
{
    if (left < right)
	{
        int mid = left + (right - left) / 2;
        _mergeSortPairs(pairs, left, mid);
        _mergeSortPairs(pairs, mid + 1, right);
        _merge(pairs, left, right, mid);
    }
}

template<template<typename, typename> class Container>
void PmergeMe<Container>::_merge(pairs_t &pairs, int left, int right, int mid)
{
    pairs_t tmpLeft;
    pairs_t tmpRight;
    
    // Copy data to temporary containers
    typename pairs_t::iterator it = pairs.begin();
    for (int i = 0; i < left; i++) {
        ++it;
    }
    for (int i = left; i <= mid; i++) {
        tmpLeft.push_back(*it);
        ++it;
    }
    for (int i = mid + 1; i <= right; i++) {
        tmpRight.push_back(*it);
        ++it;
    }
    
    // Merge the temporary containers back
    typename pairs_t::iterator leftIt = tmpLeft.begin();
    typename pairs_t::iterator rightIt = tmpRight.begin();
    it = pairs.begin();
    
    // Manually advance to the left position
    for (int i = 0; i < left; i++) {
        ++it;
    }
    
    // Compare and merge
    while (leftIt != tmpLeft.end() && rightIt != tmpRight.end())
	{
        if (leftIt->first <= rightIt->first) {
            *it = *leftIt;
            ++leftIt;
        }
		else {
            *it = *rightIt;
            ++rightIt;
        }
        ++it;
    }
    
    // Copy remaining elements from temp containers
    while (leftIt != tmpLeft.end()) {
        *it = *leftIt;
        ++leftIt;
        ++it;
    }
    while (rightIt != tmpRight.end()) {
        *it = *rightIt;
        ++rightIt;
        ++it;
    }
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::_genSequences()
{
	for (typename pairs_t::iterator it = _pairs.begin(); it != _pairs.end(); ++it) {
		_nums.push_back(it->first);
		_buffer.push_back(it->second);
	}
}