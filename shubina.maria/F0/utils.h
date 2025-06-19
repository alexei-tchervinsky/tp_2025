#pragma once

#include <string>
#include <algorithm>
#include <cctype>

inline bool isBlank(const std::string& str) {
    return str.empty() || std::all_of(str.begin(), str.end(), ::isspace);
}

