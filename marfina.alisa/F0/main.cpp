/**
 * @file main.cpp
 * @brief The main module of program
 */

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "common.hpp"
#include "shannon_fano.hpp"
#include "file_io.hpp"

namespace
{
    /**
     * @brief Output construction for usage
     * @param programName Name of our working file
     */
    void printUsage(const char* programName)
    {
        std::cout << "Usage: " << programName << " <input_file> <encoded_file> <decoded_file>\n";
        std::cout << "Example: " << programName << " input.txt encoded.bin decoded.txt\n";
    }

    /**
     * @brief Output message when we face with Error
     * @param message Text of our Error
     */
    void printError(const std::string& message)
    {
        std::cerr << "Error:\n" << message << "\n";
    }

    void printWarning(const std::string& message)
    {
        std::cerr << "Warning:\n" << message << "\n";
    }

    void printStatistics(int originalSize, int encodedSize)
    {
        const double compressionRatio = 100.0 * (1.0 - static_cast<double>(encodedSize) / (originalSize * 8));

        std::cout << "\nCompression Statistics:\n";
        std::cout << "Original size: " << originalSize << " bytes (" << (originalSize * 8) << " bits)\n";
        std::cout << "Encoded size: " << encodedSize << " bits\n";
        std::cout << "Compression ratio: " << compressionRatio << "%\n";
        std::cout << "Bits per symbol (original): 8\n";
        std::cout << "Bits per symbol (encoded): " << (static_cast<double>(encodedSize) / originalSize) << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printUsage(argv[0]);
        std::cerr << "Error: Incorrect number of arguments\n";
        return 1;
    }

    for (int i = 1; i < 4; ++i)
    {
        if (!argv[i] || !*argv[i])
        {
            printError("Invalid filename argument");
            return 1;
        }
    }

    const std::string inputFilename = argv[1];
    const std::string encodedFilename = argv[2];
    const std::string decodedFilename = argv[3];

    std::vector<char> text = readFile(inputFilename);
    if (text.empty())
    {
        printError("Failed to read input file");
        return 1;
    }

    std::cout << "Processing file: " << inputFilename << " (" << text.size() << " bytes)\n";

    SymbolTable table = createSymbolTable(text);
    if (table.symbols.empty())
    {
        printError("Failed to create symbol table");
        return 1;
    }

    if (!writeFrequencyTable(table, "table.txt"))
    {
        printWarning("Failed to write frequency table");
    }
    else
    {
        std::cout << "Frequency table written to: table.txt\n";
    }

    std::string encodedText = encodeText(text, table);
    printStatistics(text.size(), encodedText.size());

    if (!writeFile(encodedFilename, encodedText))
    {
        printError("Failed to write encoded file");
        return 1;
    }

    std::cout << "Encoded data written to: " << encodedFilename << "\n";

    std::string decodedText = decodeText(encodedText, table);
    if (decodedText.empty())
    {
        printError("Failed to decode text");
        return 1;
    }

    if (!writeFile(decodedFilename, decodedText))
    {
        printError("Failed to write decoded file");
    }
    else
    {
        std::cout << "Decoded data written to: " << decodedFilename << "\n";
    }

    // Проверка совпадения оригинального и декодированного текста
    if (text.size() == decodedText.size() &&
        std::equal(text.begin(), text.end(), decodedText.begin()))
    {
        std::cout << "\nVerification: Original and decoded texts match.\n";
    }
    else
    {
        printWarning("Original and decoded texts differ!");
    }

    return 0;
}
