#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <cmath>


class Complex {
private:
    double re, im;
public:
    Complex(double r = 0, double i = 0) : re(r), im(i) {}
    double real() const { return re; }
    double imag() const { return im; }
    
    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }
    
    bool operator==(const Complex& other) const {
        return re == other.re && im == other.im;
    }
    
    bool operator<(const Complex& other) const {
        if (re != other.re) return re < other.re;
        return im < other.im;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.re << (c.im >= 0 ? "+" : "") << c.im << "i";
        return os;
    }
};

template<typename T>
class FunctionWrapper {
private:
    std::function<T(T)> func;
    std::string name;
public:
    FunctionWrapper() : func(nullptr) {}
    
    FunctionWrapper(std::function<T(T)> f, const std::string& n = "func") 
        : func(f), name(n) {}
    
    T operator()(T x) const { return func(x); }
    
    bool operator==(const FunctionWrapper& other) const {
        if (!func || !other.func) return false;
        return func.target_type() == other.func.target_type();
    }
    
    bool operator<(const FunctionWrapper& other) const {
        if (!func || !other.func) return false;
        return func.target_type().name() < other.func.target_type().name();
    }
    
    std::string GetName() const { return name; }
};

inline int squareInt(int x) { return x * x; }
inline int doubleInt(int x) { return x * 2; }
inline double squareDouble(double x) { return x * x; }

class PersonID {
private:
    int series;
    int number;
public:
    PersonID(int s = 0, int n = 0) : series(s), number(n) {}
    int GetSeries() const { return series; }
    int GetNumber() const { return number; }
    
    bool operator==(const PersonID& other) const {
        return series == other.series && number == other.number;
    }
    bool operator<(const PersonID& other) const {
        if (series != other.series) return series < other.series;
        return number < other.number;
    }
};

class Person {
private:
    PersonID id;
    std::string firstName;
    std::string lastName;
public:
    Person() : id(PersonID()) {}
    Person(PersonID pid, const std::string& first, const std::string& last) 
        : id(pid), firstName(first), lastName(last) {}
    
    PersonID GetID() const { return id; }
    std::string GetFullName() const { return lastName + " " + firstName; }
    
    bool operator==(const Person& other) const { return id == other.id; }
    bool operator<(const Person& other) const { return id < other.id; }
};

typedef Person Student;
typedef Person Teacher;

template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair() : first(T1()), second(T2()) {}
    Pair(const T1& f, const T2& s) : first(f), second(s) {}
    
    T1 GetFirst() const { return first; }
    T2 GetSecond() const { return second; }
    
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    bool operator<(const Pair& other) const {
        if (first != other.first) return first < other.first;
        return second < other.second;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Pair& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
};


