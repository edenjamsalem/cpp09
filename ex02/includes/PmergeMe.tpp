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

		void sort();
		void print();
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

template <typename T>
void PmergeMe<T>::sort()
{

}

template <typename T>
void PmergeMe<T>::print()
{
	for (typename T::iterator it = _nums.begin(); it != _nums.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}