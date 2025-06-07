#include "interface.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        interactiveMode();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}