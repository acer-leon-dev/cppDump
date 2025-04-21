#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <cctype>

namespace {

enum class Casing {
    LOWER,
    UPPER,
    MIXED
};

char random_number_char(int base, Casing casing) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> dist{0, base};

    char character;
    int ch_index = dist(gen);
    if (0 <= ch_index && ch_index <= 9) {
        character = '0' + ch_index;
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
    std::cerr << "Usage: " << std::filesystem::path(program_path).stem().string() << " [-u | --upper] <n>\n";
}

bool is_int(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}

};

int main(int argc, char ** argv) {
    std::vector<std::string> args = std::vector<std::string>(argv, argv + argc);
    
    size_t base = 0;
    size_t length = 0;
    Casing casing;

    for (int i = 1; i < argc; i++) {
        std::string this_arg = args[i];

        if (this_arg == "-h" || this_arg == "--help") {
            print_usage(args[0]);
        }

        else if (this_arg == "-l" || this_arg == "--lower") {
            casing = Casing::LOWER;
        }

        else if (this_arg == "-u" || this_arg == "--upper") {
            casing = Casing::UPPER;
        }

        else if (this_arg == "-m" || this_arg == "--mixed") {
            casing = Casing::MIXED;
        }

        else if (this_arg == "-b" || this_arg == "--base") {
            const std::string& s_base  = args[i + 1];

            if (!is_int(s_base)) {
                std::cerr << "Fatal Error: base must be an int.\n";
                std::exit(1);
            }
            
            size_t i_base = std::stoi(s_base);

            if (i_base < 1 || i_base > 36) {
                std::cerr << "Fatal Error: base must be in range [1, 36].\n";
                std::exit(1);
            }
        }

        else if (this_arg == "-n" || this_arg == "--numbers") {
            const std::string& s_length = args[i + 1];
            
            if (!is_int(s_length)) {
                std::cerr << "Fatal Error: length must be an int.\n";
                std::exit(1);
            }

            size_t i_length = std::stoi(s_length);
            
            if (i_length < 0) {
                std::cerr << "Fatal Error: length must be positive.\n";
                std::exit(1);
            }
        }
    }
    
    std::cout << random_hexatridecimal_string(base, length, casing) << '\n';
    
    return EXIT_SUCCESS;
}