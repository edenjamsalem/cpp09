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

		PmergeMe();
		~PmergeMe();

		const container_t 	&getNums() const;
		void				mergeInsertSort(char **nums, int size);
	
	private:
		container_t		_initial;
		container_t		_buffer;
		container_t		_mainChain;
		container_t		_jacobsthal;
		pairs_t			_pairs;
		int				_size;
		int				_straggler;
		
		void		_parseInput(char **nums, int size);
		std::string _getContainerType();
		void		_printPairs(); // testing only

		void		_sortIntoPairs();
		void		_mergeSortPairs(pairs_t &pairs, int left, int right);
		void		_merge(pairs_t &pairs, int left, int right, int mid);
		void		_splitSortedMainChain();
		void		_binaryInsert(int value);
		void		_genJacobsthalSeq();
		void		_insertJacobsthalNums();
		void		_insertRemainingNums();
		void		_advance(typename container_t::iterator &it, int d);

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