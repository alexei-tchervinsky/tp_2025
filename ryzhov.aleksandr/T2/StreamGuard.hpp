#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP

#include <iostream>

namespace ryzhov {
class StreamGuard {
    public:
        // Конструкторы и деструктор
        explicit StreamGuard(std::basic_ios<char> &s);
        StreamGuard(const StreamGuard &other) = delete;
        StreamGuard(StreamGuard &&other) noexcept = delete;
        StreamGuard &operator=(const StreamGuard &other) = delete;
        StreamGuard &operator=(StreamGuard &&other) noexcept = delete;
        ~StreamGuard();

    private:
        std::basic_ios<char> &s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
};
}; // namespace ryzhov

#endif // STREAMGUARD_HPP
