#pragma once
#include <string>
#include <stdexcept>
#include "../include/exceptions.cpp"
#include "../include/option.hpp"

template<typename T>
ArraySequence<T>::ArraySequence() : items() {}

template<typename T>
ArraySequence<T>::ArraySequence(T* itemsArr, size_t count) {
    if (count > 0 && itemsArr == nullptr) 
        throw NullPointerArgumentException("ArraySequence", "itemsArr");
    items = DynamicArray<T>(itemsArr, count);
}

template<typename T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list) : items() {
    size_t len = list.GetLength();
    items.Resize(len);
    for (size_t i = 0; i < len; ++i) {
        items.Set(i, list.Get(i));
    }
}

template<typename T>
ArraySequence<T>::ArraySequence(DynamicArray<T>&& arr) : items(std::move(arr)) {}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) : items(other.items) {}

template<typename T>
ArraySequence<T>::ArraySequence(ArraySequence<T>&& other) : items(std::move(other.items)) {}

template<typename T>
ArraySequence<T>::~ArraySequence() {}

template<typename T>
ArraySequence<T>& ArraySequence<T>::operator=(const ArraySequence<T>& other) {
    if (this != &other) {
        items = other.items;
    }
    return *this;
}

template<typename T>
ArraySequence<T>& ArraySequence<T>::operator=(ArraySequence<T>&& other) {
    if (this != &other) {
        items = std::move(other.items);
    }
    return *this;
}

template<typename T>
T ArraySequence<T>::GetFirst() {
    if (items.GetSize() == 0) throw EmptyCollectionException("GetFirst");
    return items.Get(0);
}

template<typename T>
T ArraySequence<T>::GetLast() {
    if (items.GetSize() == 0) throw EmptyCollectionException("GetLast");
    return items.Get(items.GetSize() - 1);
}

template<typename T>
T ArraySequence<T>::Get(size_t index) {
    return items.Get(index);
}

template<typename T>
size_t ArraySequence<T>::GetLength() {
    return items.GetSize();
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    size_t size = items.GetSize();
    if (startIndex > endIndex) {
        throw InvalidArgumentException("GetSubsequence", "начальный индекс больше конечного");
    }
    if (startIndex >= size) {
        throw IndexOutOfRangeException("GetSubsequence", size, startIndex);
    }
    if (endIndex >= size) {
        throw IndexOutOfRangeException("GetSubsequence", size, endIndex);
    }
    
    size_t len = endIndex - startIndex + 1;
    T* newData = new T[len];
    
    for (size_t i = 0; i < len; ++i) {
        newData[i] = items.Get(startIndex + i);
    }
    
    ArraySequence<T>* result = new ArraySequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Append(T item) {
    items.Resize(items.GetSize() + 1);
    items.Set(items.GetSize() - 1, item);
    return this;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Prepend(T item) {
    return InsertAt(item, 0);
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::InsertAt(T item, size_t index) {
    size_t size = items.GetSize();
    if (index > size) {
        throw IndexOutOfRangeException("InsertAt", size, index);
    }
    items.Resize(size + 1);
    for (size_t i = size; i > index; --i) {
        items.Set(i, items.Get(i - 1));
    }
    items.Set(index, item);
    return this;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    if (!list) throw NullPointerArgumentException("Concat", "list");
    ArraySequence<T>* res = new ArraySequence<T>(*this);
    for (size_t i = 0; i < list->GetLength(); ++i) res->Append(list->Get(i));
    return res;
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Map() {
    throw std::runtime_error("Map требует параметр-функцию. Используйте Map(std::function<T(T)> func)");
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::Where() {
    throw std::runtime_error("Where требует параметр-предикат. Используйте Where(std::function<bool(T)> pred)");
}

template<typename T>
T ArraySequence<T>::Reduce() {
    throw std::runtime_error("Reduce требует параметр-функцию. Используйте Reduce(std::function<T(T,T)> func, T initial)");
}

template<typename T>
Option<T> ArraySequence<T>::Find() {
    throw std::runtime_error("Find требует параметр-предикат. Используйте Find(std::function<bool(T)> pred)");
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

