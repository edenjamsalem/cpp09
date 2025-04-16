#include "headers.hpp"

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
		pairs_t		_pairs;
		int			_straggler;
		
		void	sortIntoPairs();
		void	mergeSortPairs(pairs_t &pairs, int left, int right);
		void	merge(pairs_t &pairs, int left, int right, int mid);
		void	clearNums();
		void	printPairs();

};

template<template<typename, typename> class Container >
std::ostream& operator<<(std::ostream &os, const PmergeMe<Container> &m)
{
	for (typename PmergeMe<Container>::container_t::const_iterator it = m.getNums().begin(); it != m.getNums().end(); it++) {
		os << *it << " ";
	}
	return os;
}

template<template<typename, typename> class Container >
PmergeMe<Container>::PmergeMe(char **nums, int size)
{
	for (int i = 0; i < size; i++) {
		_nums.push_back(safe_strtoi(nums[i]));
	}
}

template<template<typename, typename> class Container >
PmergeMe<Container>::~PmergeMe() {}

template<template<typename, typename> class Container >
const typename PmergeMe<Container>::container_t &PmergeMe<Container>::getNums() const {
	return (_nums);
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::printPairs() 
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
void PmergeMe<Container>::clearNums() 
{
	typename container_t::iterator it = _nums.begin();
	while (it != _nums.end()) {
		it = _nums.erase(it);
	}
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::mergeInsertSort()
{
	sortIntoPairs();
	mergeSortPairs(_pairs, 0, _pairs.size() - 1);
	printPairs();
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::sortIntoPairs()
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
void PmergeMe<Container>::mergeSortPairs(pairs_t &pairs, int left, int right)
{
    if (left < right)
	{
        int mid = left + (right - left) / 2;
        mergeSortPairs(pairs, left, mid);
        mergeSortPairs(pairs, mid + 1, right);
        merge(pairs, left, right, mid);
    }
}

template<template<typename, typename> class Container>
void PmergeMe<Container>::merge(pairs_t &pairs, int left, int right, int mid)
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