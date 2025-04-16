#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <sstream>
#include <ctime>
#include <typeinfo>
#include "colours.hpp"

// UTILS
int safe_strtoi(const char* str);

template<template<typename, typename> class Container >
class PmergeMe
{
	public:
		typedef Container<int, std::allocator<int> > container_t;
		typedef Container<std::pair<int,int>, std::allocator<std::pair<int, int> > > pairs_t;

		PmergeMe(char **nums, int size);
		~PmergeMe();

		const container_t 	&getNums() const;
		void				mergeInsertSort();
	
	private:
		container_t	_nums;
		container_t	_buffer;
		pairs_t		_pairs;
		int			_size;
		int			_straggler;
		
		void		_sortIntoPairs();
		void		_mergeSortPairs(pairs_t &pairs, int left, int right);
		void		_merge(pairs_t &pairs, int left, int right, int mid);
		void		_printPairs(); // testing only
		void		_genSequences();
		std::string _getContainerType();

};

template<template<typename, typename> class Container >
std::ostream& operator<<(std::ostream &os, const PmergeMe<Container> &m)
{
	for (typename PmergeMe<Container>::container_t::const_iterator it = m.getNums().begin(); it != m.getNums().end(); it++) {
		os << *it << " ";
	}
	return os;
}

#include "../srcs/PmergeMe.tpp"