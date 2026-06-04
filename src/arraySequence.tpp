#pragma once
#include <string>
#include <stdexcept>
#include "exceptions.cpp"
#include "option.hpp"

template<typename T>
ArraySequence<T>::ArraySequence() : items(new DynamicArray<T>()) {}

template<typename T>
ArraySequence<T>::ArraySequence(T* items, size_t count) {
    if (count > 0 && items == nullptr) throw NullPointerArgumentException("Items pointer cannot be null for positive count");
    this->items = new DynamicArray<T>(items, count);
}

template<typename T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list) : items(new DynamicArray<T>()) {
    size_t len = list.GetLength();
    for (size_t i = 0; i < len; ++i) {
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, list.Get(i));
    }
}

template<typename T>
ArraySequence<T>::ArraySequence(ArraySequence&& other)  
    : items(other.items) 
{
    other.items = nullptr;
}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other)
    : items(nullptr) 
{
    if (other.items != nullptr) {
        items = new DynamicArray<T>(*other.items); 
    }
}

template<typename T>
ArraySequence<T>& ArraySequence<T>::operator=(const ArraySequence<T>& other) {
    if (this != &other) {
        delete items;
        items = nullptr;
        if (other.items != nullptr) {
            items = new DynamicArray<T>(*other.items);
        }
    }
    return *this;
}

template<typename T>
ArraySequence<T>& ArraySequence<T>::operator=(ArraySequence<T>&& other)   {
    if (this != &other) {
        delete items;
        items = other.items;
        other.items = nullptr;
    }
    return *this;
}

template<typename T>
ArraySequence<T>::ArraySequence(DynamicArray<T>* arr) : items(arr) {
    if (!arr) throw NullPointerArgumentException("DynamicArray pointer cannot be null");
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
T ArraySequence<T>::Get(size_t index) {
    return items->Get(index);
}

template<typename T>
size_t ArraySequence<T>::GetLength() {
    return items->GetSize();
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    size_t size = items->GetSize();
    if (startIndex > endIndex || startIndex >= size || endIndex >= size) {
        throw IndexOutOfRangeException("Invalid subsequence range [" + std::to_string(startIndex) + ", " + std::to_string(endIndex) + "]");   
    }
    size_t len = endIndex - startIndex + 1;
    T* newData = new T[len];
    auto it = items->begin();
    for (size_t i = 0; i < startIndex; ++i) ++it;
    for (size_t i = 0; i < len; ++i) {
        newData[i] = *it;
        ++it;
    }
    
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
ArraySequence<T>* ArraySequence<T>::InsertAt(T item, size_t index) {
    size_t size = items->GetSize();
    if (index > size) throw IndexOutOfRangeException("Insert index out of bounds: " + std::to_string(index));
    items->Resize(size + 1);
    for (size_t i = size; i > index; --i) items->Set(i, items->Get(i - 1));
    items->Set(index, item);
    return this;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    if (!list) throw NullPointerArgumentException("Cannot concatenate with null sequence");
    ArraySequence<T>* res = new ArraySequence<T>(*this);
    for (size_t i = 0; i < (list->GetLength()); ++i) res->Append(list->Get(i));
    return res;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Map() {
    size_t len = GetLength();
    if (len == 0) {
        return new ArraySequence<T>();
    }
    T* newData = new T[len];
    size_t i = 0;
    for (auto& item : *this) {
        newData[i++] = item + 1;
    }
    ArraySequence<T>* result = new ArraySequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Where() {
    size_t len = GetLength();
    if (len == 0) {
        return new ArraySequence<T>();
    }
    size_t evenCount = 0;
    for (auto& item : *this) {
        if (item % 2 == 0) {
            evenCount++;
        }
    }
    T* evenData = new T[evenCount];
    size_t i = 0;
    for (auto& item : *this) {
        if (item % 2 == 0) {
            evenData[i++] = item;
        }
    }
    ArraySequence<T>* result = new ArraySequence<T>(evenData, evenCount);
    delete[] evenData;
    return result;
}

template<typename T>
T ArraySequence<T>::Reduce() {
    size_t len = GetLength();
    if (len == 0) {
        return T(0);
    }
    T sum = T(0);
    for (auto& item : *this) {
        sum = sum + item;
    }
    return sum;
}

template<typename T>
Option<T> ArraySequence<T>::Find() {
    for (auto& item : *this) {
        if (item == 3) {
            return Option<T>(item);
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
ImmutableArraySequence<T>* ImmutableArraySequence<T>::InsertAt(T item, size_t index) {
    auto* c = new ImmutableArraySequence<T>(*this);
    c->ArraySequence<T>::InsertAt(item, index);
    return c;
}

