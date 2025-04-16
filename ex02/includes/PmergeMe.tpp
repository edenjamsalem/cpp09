#include "headers.hpp"

template<typename T>
class PmergeMe
{
	private:
		T	_nums;

	public:
		PmergeMe();
		PmergeMe(char **nums, int size);
		~PmergeMe();
};

template <typename T>
PmergeMe<T>::PmergeMe(char **nums, int size)
{
	for (int i = 0; i < size; i++) {
		_nums.push_back(safe_strtoi(nums[i]));
	}
}

template <typename T>
PmergeMe<T>::~PmergeMe() {}