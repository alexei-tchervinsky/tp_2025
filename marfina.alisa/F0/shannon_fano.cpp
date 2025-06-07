/**
 * @file shannon_fano.cpp
 * @brief Realisation of Shannon-Fano Algorithm
 */

#include "shannon_fano.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

namespace
{
    /**
     * @brief Sorts symbols by frequency (from the highest to lowest)
     * @param symbols Array of symbols for sorting
     */
    void sortSymbolsByFrequency(std::vector<SymbolInfo>& symbols)
    {
        std::sort(symbols.begin(), symbols.end(),
                  [](const SymbolInfo& a, const SymbolInfo& b) {
                      return a.frequency > b.frequency;
                  });
    }

    /**
     * @brief Calculate the sum frequency for symbols
     * @param symbols Array of symbols
     * @param start Start-index for range
     * @param end End-index for range
     * @return Sum frequency of symbols in range
     */
    int calculateTotalFrequency(const std::vector<SymbolInfo>& symbols, int start, int end)
    {
        int total = 0;
        for (int i = start; i <= end; ++i)
        {
            total += symbols[i].frequency;
        }
        return total;
    }

    /**
     * @brief Finds an optimal dot for split for building tree
     * @param symbols Array of symbols
     * @param start Start-index for range
     * @param end End-index for range
     * @return Index of splitting
     */
    int findSplitIndex(const std::vector<SymbolInfo>& symbols, int start, int end)
    {
        int total = calculateTotalFrequency(symbols, start, end);
        int half = total / 2;
        int sum = 0;
        int split = start;

        while (split <= end)
        {
            sum += symbols[split].frequency;
            if (sum >= half)
            {
                int diff1 = std::abs(sum - half);
                int diff2 = std::abs((sum - symbols[split].frequency) - half);
                if (diff2 < diff1 && split > start)
                {
                    --split;
                }
                return split;
            }
            ++split;
        }
        return end;
    }

    /**
     * @brief Recursively nominate code with symbols
     * @param symbols Array of symbols
     * @param start Start-index for range
     * @param end End-index for range
     * @param code Buffer for collecting code
     */
    void assignCodes(std::vector<SymbolInfo>& symbols, int start, int end, std::string code)
    {
        if (start > end) return;
        if (start == end)
        {
            symbols[start].code = code;
            return;
        }

        int split = findSplitIndex(symbols, start, end);
        assignCodes(symbols, start, split, code + "0");
        assignCodes(symbols, split + 1, end, code + "1");
    }
}

void buildShannonFanoTree(std::vector<SymbolInfo>& symbols)
{
    assignCodes(symbols, 0, symbols.size() - 1, "");
}

SymbolTable createSymbolTable(const std::vector<char>& text)
{
    if (text.empty())
    {
        std::cerr << "Invalid input for symbol table creation\n";
        return {};
    }

    int freq[256] = {0};
    for (char c : text)
    {
        freq[static_cast<unsigned char>(c)]++;
    }

    SymbolTable table;
    for (int i = 0; i < 256; ++i)
    {
        if (freq[i] > 0)
        {
            table.symbols.push_back({static_cast<char>(i), freq[i], ""});
        }
    }

    sortSymbolsByFrequency(table.symbols);
    buildShannonFanoTree(table.symbols);
    return table;
}

std::string encodeText(const std::vector<char>& text, const SymbolTable& table)
{
    std::string encodedText;
    for (char c : text)
    {
        for (const auto& symbol : table.symbols)
        {
            if (symbol.symbol == c)
            {
                encodedText += symbol.code;
                break;
            }
        }
    }
    return encodedText;
}

std::string decodeText(const std::string& encodedText, const SymbolTable& table)
{
    std::string decodedText;
    std::string currentCode;
    for (char c : encodedText)
    {
        currentCode += c;
        for (const auto& symbol : table.symbols)
        {
            if (symbol.code == currentCode)
            {
                decodedText += symbol.symbol;
                currentCode.clear();
                break;
            }
        }
    }
    return decodedText;
}

bool writeFrequencyTable(const SymbolTable& table, const std::string& filename)
{
    if (filename.empty())
    {
        std::cerr << "Invalid parameters for writeFrequencyTable\n";
        return false;
    }

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file for writing frequency table\n";
        return false;
    }

    file << "Symbol | Frequency | Code\n";
    file << "------------------------\n";

    for (const auto& symbol : table.symbols)
    {
        file << "'" << symbol.symbol << "'   | "
             << symbol.frequency << "        | "
             << symbol.code << "\n";
    }

    return file.good();
}
