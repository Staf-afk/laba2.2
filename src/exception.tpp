#include "../include/exceptions.hpp"

IndexOutOfRangeException::IndexOutOfRangeException(const std::string& msg) : message(msg) {}

const char* IndexOutOfRangeException::what() const noexcept {
    return message.c_str();
}

EmptyCollectionException::EmptyCollectionException(const std::string& msg) : message(msg) {}

const char* EmptyCollectionException::what() const noexcept {
    return message.c_str();
}