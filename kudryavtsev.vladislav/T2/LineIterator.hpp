#ifndef LINE_ITERATOR_HPP
#define LINE_ITERATOR_HPP

#include <iostream>
#include <string>
#include <iterator>

class line_iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = const std::string*;
    using reference = const std::string&;

    line_iterator();
    explicit line_iterator(std::istream& stream);

    reference operator*() const;
    pointer operator->() const;

    line_iterator& operator++();
    line_iterator operator++(int);

    bool operator==(const line_iterator& other) const;
    bool operator!=(const line_iterator& other) const;

private:
    std::istream* stream_;
    std::string line_;
};

#endif

