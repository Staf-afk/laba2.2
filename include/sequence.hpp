#pragma once

#include "option.hpp"
#include <functional>

template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(size_t index) = 0;
    virtual Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const = 0;
    virtual size_t GetLength() = 0;
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, size_t index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    
    virtual Sequence<T>* Map() = 0;
    virtual Sequence<T>* Where() = 0;
    virtual T Reduce() = 0;
    virtual Option<T> Find() = 0;
};
