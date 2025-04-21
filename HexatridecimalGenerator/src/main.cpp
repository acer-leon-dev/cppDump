#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <cctype>
#include <algorithm>
#include <initializer_list>

namespace {

enum class Casing {
    LOWER,
    UPPER,
    MIXED
};

char random_number_char(int base, Casing casing) {
    static std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist{0, base - 1};

    char character;
    int ch_index = dist(gen);
    // Check if base is in decimal range [0, 9]
    if (0 <= ch_index && ch_index <= 9) {
        character = '0' + ch_index;
    // If greater than 9, number must use alphabetic characters
    } else if (10 <= ch_index && ch_index <= 35){
        character = 'a' + ch_index - 10;
        if (casing == Casing::UPPER) {
            character = std::toupper(character);
        } else if (casing == Casing::MIXED) {
            static std::uniform_int_distribution<int> binary_dist{0, 1};
            if (binary_dist(gen)) {
                character = std::toupper(character);
            }
        }
    } else {
        throw std::invalid_argument("Error: Base (= " + std::to_string(base) + ") can't be greater than 36");
    }
    
    return character;
}

std::string random_hexatridecimal_string(size_t base, size_t length, Casing casing) {
    std::string output;
    output.reserve(length);
    for (int i = 0; i < length; i++) {
        output.push_back(random_number_char(base, casing));
    }
    return output;
}

void print_usage(const std::string& program_path) {
    std::cerr << "Usage: " << std::filesystem::path(program_path).stem().string() << R"(
        [-h | --help] [(-l | --lowercase) | (-u | --uppercase) | (-m | --mixedcase)] (-b | --base) <number>) (-n | --numbers) <number>))";
}

/**
 * 
 */ 
bool s_is_int(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}

/**
 * 
 */
size_t get_option(const std::vector<std::string>& args, const std::string& option) {
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == option) {
            return i;
        }
    }

    return -1;
}

/**
 * 
 */
bool more_than_one_of(std::initializer_list<bool> list) {
    int num = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        if (*it) {
            if (num == 1) {
                return true;
            } else {
                ++num;
            }
        }
    }

    return false;
}

/**
 * 
 */
bool none_of(std::initializer_list<bool> list) {
    int num = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        if (*it) {
            return false;
        }
    }

    return true;
}

/**
 * 
 */
Casing get_casing_option(const std::vector<std::string>& arguments) {
    Casing casing;
    bool lower = get_option(arguments, "-l") != -1 || get_option(arguments, "--lowercase") != -1;
    if (lower) {
        casing = Casing::LOWER;
    }
    bool upper = get_option(arguments, "-u") != -1 || get_option(arguments, "--uppercase") != -1;
    if (upper) {
        casing = Casing::UPPER;
    }
    bool mixed = get_option(arguments, "-m") != -1 || get_option(arguments, "--mixedcase") != -1;
    if (mixed) {
        casing = Casing::MIXED;
    }

    // Check for erroneous input
    if (more_than_one_of({lower, upper, mixed})) {
        std::cerr << "Error: Cannot have multiple casing options\n";
        std::exit(1);
    }

    // Set default as LOWER
    if (none_of({lower, upper, mixed})) {
        return Casing::LOWER;
    }

    return casing;
}

/**
 * 
 */
int get_base_option(const std::vector<std::string>& arguments) {
    // Determine index of base option in argument list
    size_t index = get_option(arguments, "-b");
    if (index == -1) {
        index = get_option(arguments, "--base");
    }

    // If found, return option parameter
    if (index != -1) {
        if (arguments.size() <= index + 1) {
            std::cerr << "Fatal Error: Must specify value with \"--base\" argument.\n";
            exit(1);
        }

        const std::string& str  = arguments[index + 1];
        if (s_is_int(str)) {
            size_t x = std::stoi(str);
        } else {
            std::cerr << "Fatal Error: base must be a positive integer.\n";
            std::exit(1);
        }

        size_t x = std::stoi(str);
        if (!(1 <= x && x <= 36)) {
            std::cerr << "Fatal Error: base must be in range [1, 36].\n";
            std::exit(1);
        }

        return x;
    } else {
        // Return 10 (decimal) as default value
        return 10;
    }
}

/**
 * 
 */
int get_length_option(const std::vector<std::string>& arguments) {
    // Determine index of base option in argument list
    size_t index = get_option(arguments, "-l");
    if (index == -1) {
        index = get_option(arguments, "--length");
    }

    // If found, return option parameter
    if (index != -1) {
        if (arguments.size() <= index + 1) {
            std::cerr << "Fatal Error: Must specify value with \"--length\" argument.\n";
            exit(1);
        }

        const std::string& str = arguments.at(index + 1);

        if (s_is_int(str)) {
            size_t x = std::stoi(str);
        } else {
            std::cerr << "Fatal Error: length must be a positive integer.\n";
            std::exit(1);
        }

        size_t x = std::stoi(str);
        if (x < 0) {
            std::cerr << "Fatal Error: length must be in range [1, 36].\n";
            std::exit(1);
        }

        return x;
    } else {
        // Return 10 (decimal) as default value
        return 10;
    }
}
};

int main(int argc, char ** argv) {
    static const std::vector<std::string> ARGS = std::vector<std::string>(argv, argv + argc);    

    if (get_option(ARGS, "-h") != -1 || get_option(ARGS, "--help") != -1) {
        print_usage(ARGS[0]);
        return 0;
    }

    size_t base = get_base_option(ARGS);
    size_t length = get_length_option(ARGS);
    Casing casing = get_casing_option(ARGS);
    std::cout << random_hexatridecimal_string(base, length, casing) << '\n';
}
