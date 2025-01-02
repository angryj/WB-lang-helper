#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#define WORDS_AMOUNT 100
#define FILTER_DUPLICATES

struct order_states {
    bool parenthesis_open = false;
    bool bracket_open = false;
};

// default values
std::unordered_map<std::string, std::vector<std::string>> main_dict = {
    {"C", {"p", "t", "k", "s", "m", "n"}}, // consonants, specifically stops
    {"V", {"a", "i", "u"}}, // vowels
    {"N", {"m", "n"}} // consonants, specifically nasals
};

std::string order = "CV(CV)(N)"; // default value