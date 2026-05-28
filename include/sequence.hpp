#pragma once

#include "option.hpp"
#include <functional>

template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() = 0;
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    
    virtual Sequence<T>* Map() = 0;
    virtual Sequence<T>* Where() = 0;
    virtual T Reduce() = 0;
    virtual Option<T> Find() = 0;
};
