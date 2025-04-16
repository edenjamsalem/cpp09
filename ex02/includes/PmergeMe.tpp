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
		void mergeInsertSort();
		void sortPairs();
	
	private:
		container_t	_nums;
		pairs_t		_pairs;
		int			_straggler;

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
void PmergeMe<Container>::mergeInsertSort()
{
	sortPairs();
}

template<template<typename, typename> class Container >
void PmergeMe<Container>::sortPairs()
{
	typename PmergeMe<Container>::container_t::const_iterator it = _nums.begin();
	while (it != _nums.end())
	{
		typename PmergeMe<Container>::container_t::const_iterator next_it = it;
		++next_it;
		
		if (next_it == _nums.end()) {
			_straggler = *it;
			break ;
		}
		std::pair<int,int> pair;
		pair.first = *it;
		pair.second = *next_it;
		_pairs.push_back(pair);
		++it;
		++it;
	}
}

