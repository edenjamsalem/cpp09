#include "../includes/PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2){
		std::cout << RED << "Error: must provide at least 1 number to sort\n" << RESET;
		return (1);
	}
	try 
	{
		PmergeMe<std::vector>	mergeVec;
		PmergeMe<std::list>		mergeList;
		PmergeMe<std::deque>	mergeDeque;

		std::cout << "Before: " << mergeVec << std::endl;
		mergeVec.mergeInsertSort(argv + 1, argc - 1);
		mergeList.mergeInsertSort(argv + 1, argc - 1);
		mergeDeque.mergeInsertSort(argv + 1, argc - 1);
		std::cout << "After: " << mergeVec << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return (-1);
	}
}