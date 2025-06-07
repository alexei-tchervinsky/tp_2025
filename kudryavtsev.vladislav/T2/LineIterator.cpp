#include "LineIterator.hpp"

line_iterator::line_iterator() : stream_(nullptr) {}

line_iterator::line_iterator(std::istream& stream) : stream_(&stream) {
    ++(*this);
}

const std::string& line_iterator::operator*() const {
    return line_;
}

const std::string* line_iterator::operator->() const {
    return &line_;
}

line_iterator& line_iterator::operator++() {
    if (stream_ && !std::getline(*stream_, line_)) {
        stream_ = nullptr;
    }
    return *this;
}

line_iterator line_iterator::operator++(int) {
    line_iterator temp = *this;
    ++(*this);
    return temp;
}

bool line_iterator::operator==(const line_iterator& other) const {
    return stream_ == other.stream_;
}

bool line_iterator::operator!=(const line_iterator& other) const {
    return !(*this == other);
}

