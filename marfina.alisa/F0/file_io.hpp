/**
 * @file file_io.hpp
 * @brief File for input/output operations
 */

#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <string>
#include <vector>
#include <memory>

/**
 * @brief Reading file in memory
 * @param filename Name of file for reading
 * @return Pair containing the file content and its size, or empty vector if error
 */
std::vector<char> readFile(const std::string& filename);

/**
 * @brief Writing information in file
 * @param filename Name of file for writing
 * @param content Data for writing
 * @return true when all is correct, false when Error
 */
bool writeFile(const std::string& filename, const std::string& content);

/**
 * @brief Check if file size is within limits (1 MB)
 * @param filename Name of file to check
 * @return true if file size <= 1 MB, false otherwise
 */
bool isFileSizeValid(const std::string& filename);
#endif
