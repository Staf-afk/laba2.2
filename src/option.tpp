#include "../include/option.hpp"

template<typename T>
Option<T>::Option() : value(nullptr), hasValue(false) {}

template<typename T>
Option<T>::Option(T val) : hasValue(true) {
    value = new T(val);
}

template<typename T>
Option<T>::Option(const Option<T>& other) : hasValue(other.hasValue) {
    if (hasValue) {
        value = new T(*other.value);
    } else {
        value = nullptr;
    }
}

template<typename T>
Option<T>::~Option() {
    delete value;
}

template<typename T>
bool Option<T>::IsSome() const {
    return hasValue;
}

template<typename T>
bool Option<T>::IsNone() const {
    return !hasValue;
}

template<typename T>
T Option<T>::GetValue() const {
    if (!hasValue) {
        throw std::runtime_error("Option has no value");
    }
    return *value;
}

template<typename T>
T Option<T>::GetValueOrDefault(T defaultValue) const {
    if (!hasValue) {
        return defaultValue;
    }
    return *value;
}

template<typename T>
Option<T>& Option<T>::operator=(const Option<T>& other) {
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

template<typename T>
Some<T>::Some(T val) : Option<T>(val) {}

template<typename T>
None<T>::None() : Option<T>() {}