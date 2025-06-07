#include "Exceptions.hpp"

namespace narumov {
    VertexDoesNotExist::VertexDoesNotExist(): _reason("Vertex does not exist") { }
    const char *VertexDoesNotExist::what() const noexcept {
        return _reason.c_str();
    }

    EdgeDoesNotExist::EdgeDoesNotExist(): _reason("Edge does not exist") { }
    const char *EdgeDoesNotExist::what() const noexcept {
        return _reason.c_str();
    }

    SelfLoopNotAllowed::SelfLoopNotAllowed(): _reason("Self-loops are not allowed") { }
    const char *SelfLoopNotAllowed::what() const noexcept {
        return _reason.c_str();
    }

    StackUnderflow::StackUnderflow(): _reason("Stack underflow") { }
    const char *StackUnderflow::what() const noexcept {
        return _reason.c_str();
    }

    IndexOutOfBoundsException::IndexOutOfBoundsException(): _reason("Index out of bounds") { }
    const char *IndexOutOfBoundsException::what() const noexcept {
        return _reason.c_str();
    }

    MemoryAllocationFailed::MemoryAllocationFailed(): _reason("Memory allocation failed") { }
    const char *MemoryAllocationFailed::what() const noexcept {
        return _reason.c_str();
    }

    FileOpenError::FileOpenError(const std::string &filename): _reason("Unable to open file " + filename) { }
    const char *FileOpenError::what() const noexcept {
        return _reason.c_str();
    }

    InvalidInput::InvalidInput(): _reason("Invalid input. Please try again") { }
    const char *InvalidInput::what() const noexcept {
        return _reason.c_str();
    }

    EmptyInput::EmptyInput(): _reason("Input cannot be empty. Please try again") { }
    const char *EmptyInput::what() const noexcept {
        return _reason.c_str();
    }
}
