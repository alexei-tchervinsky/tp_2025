#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
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

class datastruct_iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = nspace::DataStruct;
    using difference_type = std::ptrdiff_t;
    using pointer = const nspace::DataStruct*;
    using reference = const nspace::DataStruct&;

    datastruct_iterator() : line_it_() {}
    datastruct_iterator(line_iterator it) : line_it_(it) { advance_to_valid(); }

    const nspace::DataStruct& operator*() const { return current_ds_; }
    const nspace::DataStruct* operator->() const { return &current_ds_; }

    datastruct_iterator& operator++() {
        ++line_it_;
        advance_to_valid();
        return *this;
    }

    datastruct_iterator operator++(int) {
        datastruct_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const datastruct_iterator& other) const {
        return line_it_ == other.line_it_;
    }

    bool operator!=(const datastruct_iterator& other) const {
        return !(*this == other);
    }

private:
    line_iterator line_it_;
    nspace::DataStruct current_ds_;

    void advance_to_valid() {
        while (line_it_ != line_iterator()) {
            if (!line_it_->empty()) {
                std::istringstream iss(*line_it_);
                if (iss >> current_ds_) {
                    return;
                }
            }
            ++line_it_;
        }
    }
};

int main() {
    std::vector<nspace::DataStruct> ds;


    std::copy(datastruct_iterator(line_iterator(std::cin)),
              datastruct_iterator(),
              std::back_inserter(ds));

    std::sort(ds.begin(), ds.end(), nspace::compare);

    std::copy(ds.begin(), ds.end(),
              std::ostream_iterator<nspace::DataStruct>(std::cout, "\n"));

    return 0;
}
