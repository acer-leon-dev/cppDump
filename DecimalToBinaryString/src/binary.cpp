#include "binary/binary.hpp"
#include <cmath>

std::string uint_to_binary(unsigned int decimal) {
	int number_binary_power = 0;
	std::string binary_characters = "";
	while (!(std::pow(2, number_binary_power) > decimal)) {
		number_binary_power++;
	}

	int count = 0;
	for (int exponent = number_binary_power; exponent >= 0; exponent--) {
		int value = std::pow(2, exponent);
		if (count + value > decimal) {
			if (count != 0) {
				binary_characters += ('0');
			}
		} else {
			count += value;
			binary_characters += ('1');
		}
	}

	return binary_characters;
}
