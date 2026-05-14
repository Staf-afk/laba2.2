#pragma once

template<typename T>
class Option {
private:
    T value;
    bool hasValue;
public:
    Option() : hasValue(false) {}
    Option(T val) : value(val), hasValue(true) {}
    
    bool IsSome() const { return hasValue; }
    bool IsNone() const { return !hasValue; }
    
    T GetValue() const {
        if (!hasValue) throw std::runtime_error("Option has no value");
        return value;
    }
    
    T GetValueOrDefault(T defaultValue) const {
        return hasValue ? value : defaultValue;
    }
};