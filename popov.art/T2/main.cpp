#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <chrono>
#include <thread>
#include <atomic>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
static bool hasVisibleChars(const std::string& s) {
    return std::any_of(s.begin(), s.end(), [](unsigned char c) {
        return !std::isspace(c);
    });
}
void setNonBlockingInput() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::vector<DataStruct> records;
    std::size_t nonEmptyLines = 0;
    std::atomic<bool> inputEnded{false};
    setNonBlockingInput();
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::thread inputThread([&]() {
        std::string line;
        char ch;
        auto lastInputTime = std::chrono::steady_clock::now();
        while (!inputEnded) {
            if (read(STDIN_FILENO, &ch, 1) > 0) {
                if (ch == '\n') {
                    if (!line.empty()) {
                        if (hasVisibleChars(line)) {
                            nonEmptyLines++;
                            std::istringstream iss(line);
                            DataStruct ds;
                            if (iss >> ds) {
                                records.push_back(ds);
                            }
                        }
                        line.clear();
                    }
                } else {
                    line += ch;
                }
                lastInputTime = std::chrono::steady_clock::now();
            }
            else if (std::chrono::steady_clock::now() - lastInputTime > std::chrono::seconds(3)) {
                if (!line.empty() && hasVisibleChars(line)) {
                    nonEmptyLines++;
                    std::istringstream iss(line);
                    DataStruct ds;
                    if (iss >> ds) {
                        records.push_back(ds);
                    }
                }
                inputEnded = true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    inputThread.join();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    if (records.empty()) {
        std::cout << (nonEmptyLines == 0 ? 
            "Looks like there is no supported record. Cannot determine input. Test skipped\n" :
            "At least one supported record type\n");
        return 0;
    }
    std::sort(records.begin(), records.end());
    std::copy(records.begin(), records.end(),
             std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}
