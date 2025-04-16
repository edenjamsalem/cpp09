#include "../includes/PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2){
		std::cout << RED << "Error: must provide at least 1 number to sort\n" << RESET;
		return (1);
	}
	try 
	{
		PmergeMe<std::vector> mergeVec(argv + 1, argc - 1);
		PmergeMe<std::list> mergeList(argv + 1, argc - 1);
		PmergeMe<std::deque> mergeDeque(argv + 1, argc - 1);

		std::cout << "Before: " << mergeVec << std::endl;
		mergeVec.mergeInsertSort();
		mergeList.mergeInsertSort();
		mergeDeque.mergeInsertSort();
		std::cout << "After: " << mergeVec << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what();
		return (-1);
	}
}