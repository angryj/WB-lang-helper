#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#define WORDS_AMOUNT 100
#define FILTER_DUPLICATES

std::unordered_map<std::string, std::vector<std::string>> main_dict;
std::string order = "CV(C)";