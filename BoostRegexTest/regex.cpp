#include "pch.hpp"

struct Token;
using string_const_iterator = std::string::const_iterator;
// using optional_token = std::optional<Token>;
using optional_token = std::optional<std::string>;

bool isbadwhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}

std::optional<std::string> match_regex_continuously(const std::string& pattern, string_const_iterator begin, string_const_iterator end) {
    boost::smatch match;
    boost::regex regex{pattern};
    boost::regex_search(begin, end, match, regex, boost::match_continuous);
    if (!match[0].str().empty()) {
        return match[0].str();
    } else {
        return {};
    }
}

string_const_iterator get_string_iterator_from_distance_with_cap(const std::string& s, int distance) {
    auto it = s.begin();
    std::advance(it, distance);
    return it;
}

class Lexer
{
public:
    Lexer(std::string source) : source{source} {}
    std::vector<std::string> Tokenize();
private:
    std::string source;
    optional_token HandleComment(std::size_t begin, std::size_t end = std::string::npos);
    optional_token HandleNewline(std::size_t begin, std::size_t end = std::string::npos);
    optional_token HandleOperator(std::size_t begin, std::size_t end = std::string::npos);
    optional_token HandleNormalFunction(std::size_t begin, std::size_t end = std::string::npos);
    optional_token HandleLogarithmicFunction(std::size_t begin, std::size_t end = std::string::npos);
    optional_token HandleVariable(std::size_t begin, std::size_t end = std::string::npos);
    optional_token HandleNumber(std::size_t begin, std::size_t end = std::string::npos);
};

optional_token Lexer::HandleComment(std::size_t begin, std::size_t end) {
    static const std::string pattern = 
        R"((\/\/[^\n\r]*\n))";
    return match_regex_continuously(pattern, source.begin() + begin, source.end());
}

optional_token Lexer::HandleNewline(std::size_t begin, std::size_t end) {
    static const std::string pattern = R"(\n)";
    return match_regex_continuously(pattern, source.begin() + begin, source.end());
}

optional_token Lexer::HandleOperator(std::size_t begin, std::size_t end) {
    static const std::string pattern = 
        R"(\(|)" 
        R"(\)|)" 
        R"(\||)" 
        R"(=|)" 
        R"(\+|)" 
        R"(\-|)" 
        R"(\*|)" 
        R"(\/|)" 
        R"(\^|)" 
        R"(\!|)" 
        R"(mod)";
    return match_regex_continuously(pattern, source.begin() + begin, source.end());
}

optional_token Lexer::HandleNormalFunction(std::size_t begin, std::size_t end) {
    static const std::string pattern = R"(sin|cos|tan|ln|floor|ceil|)";
    return match_regex_continuously(pattern, source.begin() + begin, source.end()); 
}
optional_token Lexer::HandleLogarithmicFunction(std::size_t begin, std::size_t end) {
    static const std::string pattern = R"((log\d*\.?\d*))";
    return match_regex_continuously(pattern, source.begin() + begin, source.end()); 
}

optional_token Lexer::HandleVariable(std::size_t begin, std::size_t end) {
    static const std::string pattern = R"(([[:alpha:]](_\d)?)|)";
    return match_regex_continuously(pattern, source.begin() + begin, source.end());
}

optional_token Lexer::HandleNumber(std::size_t begin, std::size_t end) {
    static const std::string pattern = R"(\d*\.?\d+|\d+\.?\d*)";
    return match_regex_continuously(pattern, source.begin() + begin, source.end());
}

std::vector<std::string> Lexer::Tokenize() {
    std::vector<std::string> tokens;
    for (std::size_t i = 0; i < source.length();) {
        // Skip whitespace
        while (isbadwhitespace(source.at(i))) {
            i++;
            if (i >= source.length()) {
                return tokens;
            }
        }

        optional_token opt_token;
        if      (opt_token = HandleComment(i)) {}
        else if (opt_token = HandleNewline(i)) {}
        else if (opt_token = HandleOperator(i)) {}
        else if (opt_token = HandleNormalFunction(i)) {}
        else if (opt_token = HandleLogarithmicFunction(i)) {}
        else if (opt_token = HandleVariable(i)) {}
        else if (opt_token = HandleNumber(i)) {}
        else {
            std::cerr << std::format("Error: Invalid token \"{}\"\n", *opt_token);
        }

        i += opt_token->length();
        
        // if (opt_token->type & token_any) {
            tokens.push_back(*opt_token);
        // }
    }

    return tokens;
}

void test(const std::string& str) {
    Lexer lexer{str};
    auto tokens = lexer.Tokenize();
    
    std::string output;
    for (int i = 0; i < tokens.size(); i++) {
        output += "'" + tokens.at(i) + "' ";
    }
    output += '\n';
    std::cout << output;
}

int main() {

    // test(R"(\w*)", "             Armadillo BearCat Bear      Dog  Bear            Elephant");
    test("// ex1.brose\n");
    test("a = 2^3 - floor(3.50)\n");
    test("b = 0.333 * a(5 - 1.2)\n");
    test("c = 4 / 3 + .5x\n");
    test("d = c mod 4 - 2\n");
    test("y = d ^ ( 1/3 ) * b");
    test("// ex2.brose\n");
    test("f = log10(x^2)\n");
    test("p = (3.14159)^2\n");
    test("m = fp\n");
    test("c = 54.23/11.96\n");
    test("y = m + -x / 10 * c)");
    test("// ex3.brose\n");
    test("A = ceil(.5*x) * 0.2\n");
    test("a = x * (1 / 3)\n");
    test("B = sin(A * 66.666)\n");
    test("b = aB\n");
    test("y = b ");
}