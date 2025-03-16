#include <iostream>
#include "binary/binary.hpp"

int main(int argc, char** argv)
{
	// Test examples
	int example_cases [] = {1, 2, 3, 5, 7, 9, 14, 26, 37, 52, 84, 101, 196, 255, 9999999};

	for (int& num : example_cases) {
		int n_10 = num;
		std::string n_2 = uint_to_binary(n_10);
		std::cout << n_10 << " as binary: " << n_2 << std::endl;
	}

	return 0;
}