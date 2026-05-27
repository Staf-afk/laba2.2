#pragma once

#include "option.hpp"
#include <functional>

template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    
    template<typename T2> Sequence<T2>* Map(std::function<T2(T)> func);
    Sequence<T>* Where(std::function<bool(T)> predicate);
    template<typename T2> T2 Reduce(std::function<T2(T2, T)> func, T2 initial);
    virtual Option<T> Find(std::function<bool(T)> predicate);
};
#include "../src/sequence.tpp"
