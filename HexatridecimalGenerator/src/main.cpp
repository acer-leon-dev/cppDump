#include <filesystem>
#include <iostream>
#include <random>
#include <string>

namespace
{

char random_hexatridecimal_char(bool upper = false)
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<char> uniform_dist{'0', 'z' + 1};

    int alpha_diff = (upper) ? 35 : 0; 
    int ch;
    do {
        ch = uniform_dist(gen);
    } while (!('a' - alpha_diff <= ch && ch <= 'z' - alpha_diff) && !('0' <= ch && ch <= '9'));

    return ch;
}

std::string random_hexatridecimal_string(unsigned int digits, bool upper = false)
{
    std::string output;
    output.reserve(digits);
    
    for (int i = 0; i < digits; i++) {
        output.push_back(random_hexatridecimal_char(upper));
    }
    
    return output;
}

bool has_option(const std::vector<std::string>& args, const std::string&str)
{
    return *std::find(args.begin(), args.end(), str) == str;
}

std::string find_argument(const std::vector<std::string>& args, unsigned int n)
{
    unsigned int count = 0;
    for (int i = 0; i < args.size(); i++)
    {   
        std::string str = args[i];
        if (str[0] != '-') {
            if (count == n) {
                return str;
            }
            else
            {
                count++;
            }
        }
    }

    return "";
}

std::vector<std::string> get_args(int argc, char ** argv)
{
    std::vector<std::string> args;
    args.reserve(argc); 
    for (int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    return args;
}

void print_usage(const std::vector<std::string>& args)
{
    std::cerr << "Usage: " << std::filesystem::path(args[0]).stem().string() << " [-u | --upper] <n>\n";
}

bool string_is_integer(std::string str) {
    for (char c : str)
    {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}

void assert(const std::vector<std::string>& args, bool b) {
    if (b) {
        print_usage(args);
        std::exit(EXIT_FAILURE);
    }
}

};

int main(int argc, char ** argv)
{
    std::vector<std::string> args = get_args(argc, argv);

    assert(args, argc < 2 || has_option(args, "-h") || has_option(args, "--help"));

    std::string str_n = find_argument(args, 1);
    assert(args, str_n.empty() || !string_is_integer(str_n));
    
    bool upper = has_option(args, "-u") || has_option(args, "--upper");
    std::cout << random_hexatridecimal_string(std::stoi(str_n), upper) << '\n';
    
    return EXIT_SUCCESS;
}