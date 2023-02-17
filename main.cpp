#include <iostream>
#include "vector.hpp"
#include <vector>

// using namespace std;
// using namespace ft;

int	main(void)
{
	{
	std::cout << "-------------------------" << std::endl;
	std::cout << "------- vector fd -------" << std::endl;
	std::cout << "-------------------------" << std::endl;
	ft::vector<int> v;

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	// std::cout << "insert 0 at begin" << std::endl;
	v.insert(v.begin(), 0);

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	// std::cout << "insert 1 at begin + 1" << std::endl;
	v.insert(v.begin() + 1, 1);

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	// std::cout << "insert 2 at begin + 1" << std::endl;
	v.insert(v.begin() + 1, 2);

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	// std::cout << "insert 3 at begin + 1" << std::endl; // bug here
	v.insert(v.begin() + 1, 3);

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	v.insert(v.begin() + 1, 4);
	v.insert(v.begin() + 1, 5);

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	v.insert(v.begin(), 6);
	v.insert(v.begin(), 7);
	v.insert(v.begin(), 8);
	v.insert(v.begin(), 9);
	v.insert(v.begin(), 10);
	v.insert(v.begin(), 11);
	v.insert(v.begin(), 12);
	v.insert(v.begin(), 13);
	v.insert(v.begin(), 14);
	v.insert(v.begin(), 15);
	v.insert(v.begin(), 16);

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	}
	std::cout << std::endl;
	{
	std::cout << "-------------------------" << std::endl;
	std::cout << "------- vector std ------" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::vector<int> v;

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	v.insert(v.begin(), 0);


	v.insert(v.begin() + 1, 1);

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;


	v.insert(v.begin() + 1, 2);

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;


	v.insert(v.begin() + 1, 3);

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	v.insert(v.begin(), 4);
	v.insert(v.begin(), 5);
	v.insert(v.begin(), 6);
	v.insert(v.begin(), 7);
	v.insert(v.begin(), 8);
	v.insert(v.begin(), 9);
	v.insert(v.begin(), 10);
	v.insert(v.begin(), 11);
	v.insert(v.begin(), 12);
	v.insert(v.begin(), 13);
	v.insert(v.begin(), 14);
	v.insert(v.begin(), 15);
	v.insert(v.begin(), 16);

	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << std::endl;

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	}
}
