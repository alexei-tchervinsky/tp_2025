#include "DataStruct.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

class line_iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type        = std::string;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const std::string*;
    using reference         = const std::string&;

    line_iterator() : s_(nullptr) {}
    line_iterator(std::istream& s) : s_(&s) { ++*this; }

    reference operator*() const { return line_; }
    pointer   operator->() const { return &line_; }

    line_iterator& operator++() {
        if (s_ && !std::getline(*s_, line_)) s_ = nullptr;
        return *this;
    }

    bool operator==(const line_iterator& o) const { return s_ == o.s_; }
    bool operator!=(const line_iterator& o) const { return s_ != o.s_; }

private:
    std::istream* s_;
    std::string   line_;
};

class datastruct_iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type        = nspace::DataStruct;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    datastruct_iterator() = default;
    datastruct_iterator(line_iterator it) : it_(it) { advance(); }

    reference operator*() const { return ds_; }
    pointer   operator->() const { return &ds_; }

    datastruct_iterator& operator++() { ++it_; advance(); return *this; }
    bool operator==(const datastruct_iterator& o) const { return it_ == o.it_; }
    bool operator!=(const datastruct_iterator& o) const { return it_ != o.it_; }

private:
    line_iterator      it_;
    nspace::DataStruct ds_;

    void advance() {
        while (it_ != line_iterator()) {
            if (!it_->empty()) {
                std::istringstream iss(*it_);
                if (iss >> ds_) return;
            }
            ++it_;
        }
    }
};

int main() {
    std::vector<nspace::DataStruct> vec;
    std::copy(
        datastruct_iterator(line_iterator(std::cin)),
        datastruct_iterator(),
        std::back_inserter(vec)
    );
    std::sort(vec.begin(), vec.end(), nspace::compare);
    std::copy(
        vec.begin(),
        vec.end(),
        std::ostream_iterator<nspace::DataStruct>(std::cout, "\n")
    );
    return 0;
}
