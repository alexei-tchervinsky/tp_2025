#include "DataStructIterator.hpp"
#include <sstream>

datastruct_iterator::datastruct_iterator() : line_it_() {}

datastruct_iterator::datastruct_iterator(line_iterator it) : line_it_(it) {
    advance_to_valid();
}

const myspace::DataStruct& datastruct_iterator::operator*() const {
    return current_ds_;
}

const myspace::DataStruct* datastruct_iterator::operator->() const {
    return &current_ds_;
}

datastruct_iterator& datastruct_iterator::operator++() {
    ++line_it_;
    advance_to_valid();
    return *this;
}

datastruct_iterator datastruct_iterator::operator++(int) {
    datastruct_iterator temp = *this;
    ++(*this);
    return temp;
}

bool datastruct_iterator::operator==(const datastruct_iterator& other) const {
    return line_it_ == other.line_it_;
}

bool datastruct_iterator::operator!=(const datastruct_iterator& other) const {
    return !(*this == other);
}

void datastruct_iterator::advance_to_valid() {
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

