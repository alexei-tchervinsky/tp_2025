#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace narumov {
    class VertexDoesNotExist: public std::exception {
    public:
        VertexDoesNotExist();
        const char *what() const noexcept;
    private:
        std::string _reason;
    };

    class EdgeDoesNotExist: public std::exception {
    public:
        EdgeDoesNotExist();
        const char *what() const noexcept;
    private:
        std::string _reason;
    };

    class SelfLoopNotAllowed: public std::exception {
    public:
        SelfLoopNotAllowed();
        const char *what() const noexcept;
    private:
        std::string _reason;
    };

    class StackUnderflow: public std::exception {
    public:
        StackUnderflow();
        const char *what() const noexcept;
    private:
        const std::string _reason;
    };

    class IndexOutOfBoundsException: public std::exception {
    public:
        IndexOutOfBoundsException();
        const char *what() const noexcept;
    private:
        const std::string _reason;
    };

    class MemoryAllocationFailed: public std::exception {
    public:
        MemoryAllocationFailed();
        const char *what() const noexcept;
    private:
        const std::string _reason;
    };

    class FileOpenError: public std::exception {
    public:
        FileOpenError(const std::string &);
        const char *what() const noexcept;
    private:
        std::string _reason;
    };

    class InvalidInput: public std::exception {
    public:
        InvalidInput();
        const char *what() const noexcept;
    private:
        std::string _reason;
    };

    class EmptyInput: public std::exception {
    public:
        EmptyInput();
        const char *what() const noexcept;
    private:
        std::string _reason;
    };
}

#endif
