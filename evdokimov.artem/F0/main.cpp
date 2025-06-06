#include "FrequencyDictionary.hpp"
#include <iostream>
#include <sstream>
#include <string>

enum Command {
  INSERT = 1,
  REMOVE = 2,
  GET_FREQUENCY = 3,
  GET_TOP_WORDS = 4,
  PRINT_DICTIONARY = 5
};

void printMenu() {
  std::cout << "Available commands:\n"
            << "1 word_or_text - Insert word or text\n"
            << "2 word - Remove word\n"
            << "3 word - Get word frequency\n"
            << "4 N - Get top N words\n"
            << "5 - Print dictionary\n"
            << "----------------------------\n";
}

int main() {
  FrequencyDictionary dict;
  printMenu();
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      std::istringstream iss(line);
      int command_num;
      if (!(iss >> command_num)) {
        throw DictionaryError("Command must be a number");
      }

      switch (command_num) {
      case INSERT: {
        std::string input;
        std::getline(iss >> std::ws, input);
        if (input.empty()) {
          throw DictionaryError("Command 1 requires a word or text");
        }
        dict.INSERT(input);
        std::cout << "Input processed" << std::endl;
        break;
      }
      case REMOVE: {
        std::string word;
        if (!(iss >> word)) {
          throw DictionaryError("Command 2 requires a word");
        }
        dict.REMOVE(word);
        std::cout << "Word \"" << word << "\" removed" << std::endl;
        break;
      }
      case GET_FREQUENCY: {
        std::string word;
        if (!(iss >> word)) {
          throw DictionaryError("Command 3 requires a word");
        }
        int count = dict.getWordCount(word);
        std::cout << "Frequency of \"" << word << "\": " << count << std::endl;
        break;
      }
      case GET_TOP_WORDS: {
        int N;
        if (!(iss >> N)) {
          throw DictionaryError("Command 4 requires an integer N");
        }
        if (N <= 0) {
          throw DictionaryError("Number of top words must be positive");
        }
        auto top = dict.getTopWords(N);
        std::cout << "Top " << N << " words:" << std::endl;
        for (const auto &[word, count] : top) {
          std::cout << word << ": " << count << std::endl;
        }
        break;
      }
      case PRINT_DICTIONARY: {
        dict.printDictionary();
        break;
      }
      default:
        throw DictionaryError("Unknown command: " +
                              std::to_string(command_num));
      }
    } catch (const DictionaryError &e) {
      std::cout << "Error: " << e.what() << '\n';
    } catch (const std::exception &e) {
      std::cerr << "Unexpected error: " << e.what() << '\n';
    } catch (...) {
      std::cerr << "Unknown error occurred\n";
    }
  }
  return 0;
}
