/**
 * @file file_io.cpp
 * @brief Realisation for input/output
 */

#include "file_io.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

constexpr size_t MAX_FILE_SIZE = 1024 * 1024; // 1 MB

bool isFileSizeValid(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }
    std::streamsize size = file.tellg();
    return size > 0 && static_cast<size_t>(size) <= MAX_FILE_SIZE;
}

std::vector<char> readFile(const std::string& filename)
{
    if (!isFileSizeValid(filename))
    {
        std::cerr << "File size exceeds 1 MB limit or is empty: " << filename << "\n";
        return {};
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << "\n";
        return {};
    }

    std::streamsize size = file.tellg();
    if (size <= 0)
    {
        std::cerr << "Empty file or error getting file size\n";
        return {};
    }

    std::vector<char> buffer(size + 1);
    file.seekg(0, std::ios::beg);
    if (!file.read(buffer.data(), size))
    {
        std::cerr << "Error reading file content\n";
        return {};
    }

    buffer[size] = '\0';
    return buffer;
}

bool writeFile(const std::string& filename, const std::string& content)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file for writing\n";
        return false;
    }

    file << content;
    return file.good();
}
