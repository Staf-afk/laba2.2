#pragma once
#include <string>
#include <stdexcept>
#include "exceptions.hpp"
#include "option.hpp"

template<typename T>
ArraySequence<T>::ArraySequence() : items(new DynamicArray<T>()) {}

template<typename T>
ArraySequence<T>::ArraySequence(T* items, int count) {
    if (count < 0) throw IndexOutOfRangeException("Count cannot be negative");
    if (count > 0 && items == nullptr) throw IndexOutOfRangeException("Items pointer cannot be null for positive count");
    this->items = new DynamicArray<T>(items, count);
}

template<typename T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list) : items(new DynamicArray<T>()) {
    int len = list.GetLength();
    if (len < 0) throw IndexOutOfRangeException("Invalid list length");
    for (int i = 0; i < len; ++i) {
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, list.Get(i));
    }
}

template<typename T>
ArraySequence<T>::ArraySequence(DynamicArray<T>* arr) : items(arr) {
    if (!arr) throw IndexOutOfRangeException("DynamicArray pointer cannot be null");
}

template<typename T>
ArraySequence<T>::~ArraySequence() {
    delete items;
}

template<typename T>
T ArraySequence<T>::GetFirst() {
    if (items->GetSize() == 0) throw EmptyCollectionException();
    return items->Get(0);
}

template<typename T>
T ArraySequence<T>::GetLast() {
    if (items->GetSize() == 0) throw EmptyCollectionException();
    return items->Get(items->GetSize() - 1);
}

template<typename T>
T ArraySequence<T>::Get(int index) {
    return items->Get(index);
}

template<typename T>
int ArraySequence<T>::GetLength() {
    return items->GetSize();
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    int size = items->GetSize();
    if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex > endIndex) {
        throw IndexOutOfRangeException("Invalid subsequence range [" + std::to_string(startIndex) + ", " + std::to_string(endIndex) + "]");
    }
    int len = endIndex - startIndex + 1;
    T* newData = new T[len];
    for (int i = 0; i < len; ++i) newData[i] = items->Get(startIndex + i);
    ArraySequence<T>* result = new ArraySequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Append(T item) {
    items->Resize(items->GetSize() + 1);
    items->Set(items->GetSize() - 1, item);
    return this;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Prepend(T item) {
    return InsertAt(item, 0);
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::InsertAt(T item, int index) {
    int size = items->GetSize();
    if (index < 0 || index > size) throw IndexOutOfRangeException("Insert index out of bounds: " + std::to_string(index));
    items->Resize(size + 1);
    for (int i = size; i > index; --i) items->Set(i, items->Get(i - 1));
    items->Set(index, item);
    return this;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    if (!list) throw IndexOutOfRangeException("Cannot concatenate with null sequence");
    ArraySequence<T>* res = new ArraySequence<T>(*this);
    for (int i = 0; i < list->GetLength(); ++i) res->Append(list->Get(i));
    return res;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Map() {
    int len = GetLength();
    if (len == 0) {
        return new ArraySequence<T>();
    }
    T* newData = new T[len];
    for (int i = 0; i < len; ++i) {
        newData[i] = Get(i) + 1;
    }
    ArraySequence<T>* result = new ArraySequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Where() {
    int len = GetLength();
    if (len == 0) {
        return new ArraySequence<T>();
    }
    int evenCount = 0;
    for (int i = 0; i < len; ++i) {
        if (Get(i) % 2 == 0) {
            evenCount++;
        }
    }
    T* evenData = new T[evenCount];
    int index = 0;
    for (int i = 0; i < len; ++i) {
        if (Get(i) % 2 == 0) {
            evenData[index++] = Get(i);
        }
    }
    ArraySequence<T>* result = new ArraySequence<T>(evenData, evenCount);
    delete[] evenData;
    return result;
}

template<typename T>
T ArraySequence<T>::Reduce() {
    int len = GetLength();
    if (len == 0) {
        return T(0);
    }
    T sum = T(0);
    for (int i = 0; i < len; ++i) {
        sum = sum + Get(i);
    }
    return sum;
}

template<typename T>
Option<T> ArraySequence<T>::Find() {
    for (int i = 0; i < GetLength(); ++i) {
        if (Get(i) == 3) {  
            return Option<T>(Get(i));
        }
    }
    return Option<T>();
}


template<typename T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::Append(T item) {
    auto* c = new ImmutableArraySequence<T>(*this);
    c->ArraySequence<T>::Append(item);
    return c;
}

template<typename T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::Prepend(T item) {
    return InsertAt(item, 0);
}

template<typename T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::InsertAt(T item, int index) {
    auto* c = new ImmutableArraySequence<T>(*this);
    c->ArraySequence<T>::InsertAt(item, index);
    return c;
}

