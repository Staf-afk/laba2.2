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

class InvalidArgumentException : public std::exception {
private:
    std::string message;
public:
    InvalidArgumentException(const std::string& msg = "Invalid argument passed") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class NullPointerArgumentException : public std::exception {
private:
    std::string message;
public:
    NullPointerArgumentException(const std::string& msg = "Null pointer argument") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EmptyFunctionException : public std::exception {
private:
    std::string message;
public:
    EmptyFunctionException(const std::string& msg = "Empty or null function provided") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class SizeMismatchException : public std::exception {
private:
    std::string message;
public:
    SizeMismatchException(const std::string& msg = "Size mismatch between sequences") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

