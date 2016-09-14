#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <iostream>

#include "file_io.hpp"


int main(int argc, char **argv)
{
	// Getting the absolute name of our file
	// Try to launch this tutorial from various directories.
	std::string fullname;
	getFullNameOfFile("asset/example.txt", argv[0], fullname);
	
	// Open the file as an ifstream, as read only
	// File<> is possible, ifstream is the default template argument.
	// This constructor may throw an exception if fullname is unreachable
	File<std::ifstream> file(fullname);
	
	// Store the int line into a vector
	std::vector<int> integers;
	while(integers.empty())
	{
		// skip lines which doesn't contain ints
		integers = file.readFromLine<int>();
	}
	std::cout << "There is the ints : " << integers.size() << std::endl;
	for (int i : integers)
		std::cout << " " << i;
	std::cout << std::endl << std::endl;
	
	
	std::list<float> floats;
	while (floats.empty())
	{
		// store into a list this time
		floats = file.readFromLine<float, std::list>();
	}
	std::cout << "There is the floats : " << floats.size() << std::endl;
	for (float i : floats)
		std::cout << " " << i;
	std::cout << std::endl;
	
	// Destructor of File will close it for you
	return EXIT_SUCCESS;
}
