#pragma once
#include "../includes/PmergeMe.hpp"

/* *** CONSTRUCTORS & DESTURCTORS *** */

template<template<typename, typename> class Container >
PmergeMe<Container>::PmergeMe() {}

template<template<typename, typename> class Container >
PmergeMe<Container>::~PmergeMe() {}

/* *** GETTERS & SETTERS *** */

template<template<typename, typename> class Container >
const typename PmergeMe<Container>::container_t &PmergeMe<Container>::getSorted() const {
	return (_mainChain);
}

template<template<typename, typename> class Container >
const typename PmergeMe<Container>::container_t &PmergeMe<Container>::getInitial() const {
	return (_initial);
}

template<template<typename, typename> class Container >
std::string PmergeMe<Container>::getContainerElems(const container_t &c) 
{
	std::stringstream ss;
	typename container_t::const_iterator it = c.begin();
	while (it != c.end()) {
		ss << *it << " ";
		++it;
	}
	return (ss.str());
}

template<template<typename, typename> class Container >
std::string PmergeMe<Container>::getContainerType()
{
	std::string typeData = typeid(container_t).name();	
	if (typeData.find("vector") != std::string::npos)
		return ("std::vector");
	else if (typeData.find("list") != std::string::npos)
		return ("std::list");
	else if (typeData.find("deque") != std::string::npos)
		return ("std::deque");
	return ("unknown container");
}

/* *** MISC FNS *** */

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
void PmergeMe<Container>::printTimeTaken() 
{
	std::cout << "Time to process a range of " << CYAN << _size << RESET << " elements with " << CYAN << getContainerType() << RESET << ": " << YELLOW << _timeTaken << " us\n" << RESET;
} 

template<template<typename, typename> class Container >
void	PmergeMe<Container>::_parseInput(char **nums, int size)
{
	for (int i = 0; i < size; i++) {
		_initial.push_back(safe_strtoi(nums[i]));
	}
	_size = size;
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::_advance(typename PmergeMe<Container>::container_t::iterator &it, int d)
{
	while (it != _mainChain.end() && d-- > 0)
		it++;
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
	_splitSortedMainChain();
	_genJacobsthalSeq();
	_insertJacobsthalNums();
	_insertRemainingNums();
	
	std::clock_t end = std::clock();
	_timeTaken = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::_sortIntoPairs()
{
	_straggler = -1;
	typename container_t::iterator it = _initial.begin();
	while (it != _initial.end())
	{
		typename container_t::iterator next_it = it;
		next_it++;
		if (next_it == _initial.end()) {
			_straggler = *it;
			break ;
		}
		std::pair<int,int> pair;
		pair.first = *it;
		it++;
		pair.second = *it;
		it++;

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
void PmergeMe<Container>::_splitSortedMainChain()
{
	for (typename pairs_t::iterator it = _pairs.begin(); it != _pairs.end(); ++it) {
		_mainChain.push_back(it->first);
		_buffer.push_back(it->second);
	}
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::_binaryInsert(int value)
{
    size_t left = 0;
    size_t right = _mainChain.size();

    while (left < right)
	{
        size_t mid = left + (right - left) / 2;
		typename container_t::iterator it = _mainChain.begin();
		for (size_t i = 0; i < mid; i++)
			it++;

        if (it != _mainChain.end() && *it < value)
            left = mid + 1;
        else
            right = mid;
    }
	typename container_t::iterator insert_it = _mainChain.begin();
	for (size_t i = 0; i < left; i++)
		insert_it++;

    _mainChain.insert(insert_it, value);
}

template<template<typename, typename> class Container >
void	PmergeMe<Container>::_genJacobsthalSeq()
{
	size_t size = _buffer.size();
	size_t j0, j1, j2;

	if (size > 0)
		_jacobsthal.push_back(0);
	if (size > 1)
		_jacobsthal.push_back(1);
	if (size < 3)
		return ;

	j0 = 1;	
	j1 = 1;	
	j2 = j1 + (2 * j0);	
	while (j2 < size) {
		_jacobsthal.push_back(j2);
		j0 = j1;
		j1 = j2;
		j2 = j1 + (2 * j0);	
	}
}

template<template<typename, typename> class Container >
void	PmergeMe<Container>::_insertJacobsthalNums()
{
	for (typename container_t::iterator jacob_it = _jacobsthal.begin(); jacob_it != _jacobsthal.end(); ++jacob_it)
	{
		typename container_t::iterator buffer_it = _buffer.begin();
		int step = (*jacob_it > 0) ? *jacob_it - 1 : 0;
		_advance(buffer_it, step);
		if (buffer_it == _buffer.end())
			break ;
		_binaryInsert(*buffer_it);
		_buffer.erase(buffer_it);
	}
}

template<template<typename, typename> class Container >
void	PmergeMe<Container>::_insertRemainingNums()
{
	typename container_t::iterator buffer_it = _buffer.begin();
	while (buffer_it != _buffer.end()) {
		_binaryInsert(*buffer_it);
		buffer_it = _buffer.erase(buffer_it);
	}
	if (_straggler != -1)
		_binaryInsert(_straggler);
}