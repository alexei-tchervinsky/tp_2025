#ifndef __STRUCT_HPP__
#define __STRUCT_HPP__

#include <iostream>

struct Edge
{
    std::size_t value_;
    std::size_t first_parent_;
    std::size_t second_parent_;

    Edge() :
        value_(0),
        first_parent_(0),
        second_parent_(0)
    {}

    Edge(std::size_t value, std::size_t first_parent, std::size_t second_parent) :
        value_(value),
        first_parent_(first_parent),
        second_parent_(second_parent)
    {}

    friend std::ostream& operator<<(std::ostream& out, const Edge src)
    {
        out
            << "Edge:\n"
            << "\tvalue: " << src.value_ << std::endl
            << "\tfirst vertex: " << src.first_parent_ << std::endl
            << "\tsecond vertex: " << src.second_parent_;

        return out;
    }

    bool operator<(const Edge& other) const
    {
        return value_ < other.value_;
    }

    bool operator>(const Edge& other) const
    {
        return value_ > other.value_;
    }

    bool operator<=(const Edge& other) const
    {
        return value_ <= other.value_;
    }

    bool operator>=(const Edge& other) const
    {
        return value_ >= other.value_;
    }
};

#endif // !__STRUCT_HPP

