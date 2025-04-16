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

		const T 	&getNums() const;
		void sort();
};

template <typename T>
std::ostream& operator<<(std::ostream &os, const PmergeMe<T> &m)
{
	for (typename T::const_iterator it = m.getNums().begin(); it != m.getNums().end(); it++) {
		os << *it << " ";
	}
	return os;
}

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
const T &PmergeMe<T>::getNums() const {
	return (_nums);
}

template <typename T>
void PmergeMe<T>::sort()
{

}
