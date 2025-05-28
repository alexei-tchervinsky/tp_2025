/**
 * @file common.hpp
 * @brief definition of structures for Shannon-Fano Algorithm
 */

#ifndef SHANNON_FANO_COMMON_HPP
#define SHANNON_FANO_COMMON_HPP

#include <string>
#include <vector>

/**
 * @brief Structure with symbol's information
 */
struct SymbolInfo
{
    char symbol;         ///< Symbol
    int frequency;       ///< How many times we can find symbol
    std::string code;    ///< Symbol in code-version
};

/**
 * @brief Structure with table of symbols
 */
struct SymbolTable
{
    std::vector<SymbolInfo> symbols; ///< Array of symbols
};

#endif
