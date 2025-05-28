/**
 * @file shannon_fano.hpp
 * @brief File for Shannon-Fano Algorithm
 */

#ifndef SHANNON_FANO_HPP
#define SHANNON_FANO_HPP

#include "common.hpp"

/**
 * @brief Builds tree of Shannon-Fano
 * @param symbols Array of symbols
 */
void buildShannonFanoTree(std::vector<SymbolInfo>& symbols);

/**
 * @brief Makes table of symbols from text
 * @param text Input-text
 * @return Full symbol-table
 */
SymbolTable createSymbolTable(const std::vector<char>& text);

/**
 * @brief Codes text with Shannon-Fano Algorithm
 * @param text Input-text
 * @param table Table of symbols
 * @return Coded string
 */
std::string encodeText(const std::vector<char>& text, const SymbolTable& table);

/**
 * @brief Decodes text with Shannon-Fano Algorithm
 * @param encodedText Coded string
 * @param table Table of symbols
 * @return Decoded text
 */
std::string decodeText(const std::string& encodedText, const SymbolTable& table);

/**
 * @brief Writes frequency table to file
 * @param table Symbol table
 * @param filename Output filename
 * @return true if successful, false otherwise
 */
bool writeFrequencyTable(const SymbolTable& table, const std::string& filename);

#endif
