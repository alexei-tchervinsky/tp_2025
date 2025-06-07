#ifndef DATASTRUCT_ITERATOR_HPP
#define DATASTRUCT_ITERATOR_HPP

#include "LineIterator.hpp"
#include "DataStruct.hpp"

class datastruct_iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = myspace::DataStruct;
    using difference_type = std::ptrdiff_t;
    using pointer = const myspace::DataStruct*;
    using reference = const myspace::DataStruct&;

    datastruct_iterator();
    explicit datastruct_iterator(line_iterator it);

    reference operator*() const;
    pointer operator->() const;

    datastruct_iterator& operator++();
    datastruct_iterator operator++(int);

    bool operator==(const datastruct_iterator& other) const;
    bool operator!=(const datastruct_iterator& other) const;

private:
    line_iterator line_it_;
    myspace::DataStruct current_ds_;

    void advance_to_valid();
};

#endif

