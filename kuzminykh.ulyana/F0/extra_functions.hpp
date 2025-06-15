#pragma once
#include "HashTable.hpp"
#include <string>

std::string checkWord(const std::string& symb);
bool fillTable(HashTable& table, const std::string& filename);
