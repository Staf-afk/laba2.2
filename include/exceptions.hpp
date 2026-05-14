#pragma once
#include <exception>
#include <string>

class IndexOutOfRangeException : public std::exception {
private:
    std::string message;
public:
    IndexOutOfRangeException(const std::string& msg = "Index out of range") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EmptyCollectionException : public std::exception {
private:
    std::string message;
public:
    EmptyCollectionException(const std::string& msg = "Collection is empty") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};