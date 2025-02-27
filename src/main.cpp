#include <random>
#include <cctype>
#include "common.hpp"
#include <iterator>
#include <iostream>
#include <stdexcept>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    using diff_t = typename std::iterator_traits<Iter>::difference_type;
    std::uniform_int_distribution<diff_t> dist(0, std::distance(start, end) - 1);
    std::advance(start, dist(g));
    return start;
}
template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::minstd_rand gen(get_global_random_device()());
    return select_randomly(start, end, gen);
}

std::string process_alpha_char(char c) {
    std::string output = "";
    if (isupper(c)) {
        std::string lookup_str(1, c);
        auto it = main_dict.find(lookup_str);
        if (it != main_dict.end()) {
            output += *select_randomly(it->second.begin(), it->second.end());
        } else {
            std::cerr << "Error: Key not found in main_dict: " << lookup_str << std::endl;
        }
    }
    else if (islower(c)) {
        output.push_back(c);
    }
    return output;
}

int main() {
    order_states states;
    for (int i = 0; i < WORDS_AMOUNT; i++) {
        std::string output_str;
        for (char c : order) {
            std::vector<std::string> local_selection;
            if (states.bracket_open == true) {
                /*
                 not implemented yet, but unlike for parenthesis, the phoneme classes within 
                 brackets HAVE to be included in the final root word
                */
            }
            else if (states.parenthesis_open == true) {
                /*
                 WIP, but unlike for brackets, the phoneme classes within 
                 parenthesis have a 50/50 chance to be included in the final root word
                */
                std::minstd_rand gen(get_global_random_device()());
                std::uniform_int_distribution<int> dist(0, 1);
                if (dist(gen) == 1) {
                    output_str += process_alpha_char(c);
                }
            }
            else if (isalpha(c)) {
                output_str += process_alpha_char(c);
            }
            else if (c == '(') {
                states.parenthesis_open = true;
            }
            else if (c == ')') {
                states.parenthesis_open = false;
            }
            else if (c == '[') {
                states.bracket_open = true;
            }
            else if (c == ']') {
                states.bracket_open = false;
            }
        }
        std::cout << output_str << "\n";
    }
}