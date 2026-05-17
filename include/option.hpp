#pragma once
#include <stdexcept>

template<typename T>
class Option {
private:
    T* value;
    bool hasValue;
    
public:
    Option() : value(nullptr), hasValue(false) {}
    
    Option(T val) : hasValue(true) {
        value = new T(val);
    }
    
    Option(const Option<T>& other) : hasValue(other.hasValue) {
        if (hasValue) {
            value = new T(*other.value);
        } else {
            value = nullptr;
        }
    }
    
    ~Option() {
        delete value;
    }
    
    bool IsSome() const {
        return hasValue;
    }
    
    bool IsNone() const {
        return !hasValue;
    }
    
    T GetValue() const {
        if (!hasValue) {
            throw std::runtime_error("Option has no value");
        }
        return *value;
    }
    
    T GetValueOrDefault(T defaultValue) const {
        if (!hasValue) {
            return defaultValue;
        }
        return *value;
    }
    
    Option<T>& operator=(const Option<T>& other) {
        if (this != &other) {
            delete value;
            hasValue = other.hasValue;
            if (hasValue) {
                value = new T(*other.value);
            } else {
                value = nullptr;
            }
        }
        return *this;
    }
};

template<typename T>
class Some : public Option<T> {
public:
    Some(T val) : Option<T>(val) {}
};

template<typename T>
class None : public Option<T> {
public:
    None() : Option<T>() {}
};