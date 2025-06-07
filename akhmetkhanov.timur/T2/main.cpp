#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <sstream>

class line_iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = const std::string*;
    using reference = const std::string&;

    line_iterator() : stream_(nullptr) {}
    line_iterator(std::istream& stream) : stream_(&stream) { ++(*this); }

    const std::string& operator*() const { return line_; }
    const std::string* operator->() const { return &line_; }

    line_iterator& operator++() {
        if (stream_ && !std::getline(*stream_, line_)) {
            stream_ = nullptr;
        }
        return *this;
    }

    line_iterator operator++(int) {
        line_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const line_iterator& other) const {
        return stream_ == other.stream_;
    }

    bool operator!=(const line_iterator& other) const {
        return !(*this == other);
    }

private:
    std::istream* stream_;
    std::string line_;
};

int main() {
    std::vector<std::string> lines{
        line_iterator(std::cin),
        line_iterator()
    };

    std::vector<nspace::DataStruct> ds = std::accumulate(
        lines.begin(), lines.end(),
        std::vector<nspace::DataStruct>{},
        [](std::vector<nspace::DataStruct> acc, const std::string& line) {
            if (line.empty()) {
                return acc;
            }

            std::istringstream iss(line);
            nspace::DataStruct temp;

            if (iss >> temp) {
                acc.push_back(temp);
            }
            return acc;
        }
    );

    std::sort(ds.begin(), ds.end(), nspace::compare);

    std::copy(ds.begin(), ds.end(),
              std::ostream_iterator<nspace::DataStruct>(std::cout, "\n"));

    return 0;
}
