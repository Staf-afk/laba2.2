#pragma once
#include <exception>
#include <string>
#include <sstream>

class IndexOutOfRangeException : public std::exception {
private:
    std::string message;
public:
    IndexOutOfRangeException() : message("Индекс выходит за пределы диапазона") {}
    
    IndexOutOfRangeException(const char* method, const char* param, size_t size, size_t index) {
        std::ostringstream oss;
        oss << "Ошибка в методе " << method << ": параметр " << param << " = " << index 
            << " (размер = " << size << ")";
        message = oss.str();
    }
    
    IndexOutOfRangeException(const char* method, size_t size, size_t index) {
        std::ostringstream oss;
        oss << "Ошибка в методе " << method << ": индекс = " << index 
            << " (размер = " << size << ")";
        message = oss.str();
    }
    
    IndexOutOfRangeException(const char* msg) : message(msg) {}
    
    const char* what() const noexcept override { 
        return message.c_str(); 
    }
};

class EmptyCollectionException : public std::exception {
private:
    std::string message;
public:
    EmptyCollectionException() : message("Коллекция пуста") {}
    
    EmptyCollectionException(const char* method) {
        std::ostringstream oss;
        oss << "Ошибка в методе " << method << ": коллекция пуста";
        message = oss.str();
    }
    
    const char* what() const noexcept override { 
        return message.c_str(); 
    }
};

class InvalidArgumentException : public std::exception {
private:
    std::string message;
public:
    InvalidArgumentException() : message("Передан неверный аргумент") {}
    
    InvalidArgumentException(const char* method, const char* reason) {
        std::ostringstream oss;
        oss << "Ошибка в методе " << method << ": " << reason;
        message = oss.str();
    }
    
    const char* what() const noexcept override { 
        return message.c_str(); 
    }
};

class NullPointerArgumentException : public std::exception {
private:
    std::string message;
public:
    NullPointerArgumentException() : message("Передан нулевой указатель") {}
    
    NullPointerArgumentException(const char* method, const char* param) {
        std::ostringstream oss;
        oss << "Ошибка в методе " << method << ": параметр " << param << " является нулевым указателем";
        message = oss.str();
    }
    
    const char* what() const noexcept override { 
        return message.c_str(); 
    }
};

class SizeMismatchException : public std::exception {
private:
    std::string message;
public:
    SizeMismatchException() : message("Размеры последовательностей не совпадают") {}
    
    SizeMismatchException(const char* method, size_t size1, size_t size2) {
        std::ostringstream oss;
        oss << "Ошибка в методе " << method << ": размеры " << size1 << " и " << size2 << " не совпадают";
        message = oss.str();
    }
    
    const char* what() const noexcept override { 
        return message.c_str(); 
    }
};