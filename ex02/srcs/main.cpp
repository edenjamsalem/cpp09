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

		mergeVec.mergeInsertSort(argv + 1, argc - 1);
		mergeList.mergeInsertSort(argv + 1, argc - 1);
		mergeDeque.mergeInsertSort(argv + 1, argc - 1);

		std::cout << "Before: " << BLUE << mergeVec.getContainerElems(mergeVec.getInitial()) << RESET << std::endl;
		std::cout << "After: " << GREEN << mergeVec.getContainerElems(mergeVec.getSorted()) << RESET << std::endl;
		mergeVec.printTimeTaken();
		mergeList.printTimeTaken();
		mergeDeque.printTimeTaken();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (-1);
	}
}