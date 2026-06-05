#pragma once
#include "../include/setSequence.hpp"
#include "../include/exceptions.cpp"
#include <set>

template<typename T>
void SetSequence<T>::ensureUnique() {
    if (!data) return;
    
    std::set<T> uniqueSet;
    
    for (size_t i = 0; i < data->GetLength(); ++i) {
        uniqueSet.insert(data->Get(i));
    }
    
    Sequence<T>* newSeq = new ArraySequence<T>();
    for (const T& val : uniqueSet) {
        newSeq->Append(val);
    }
    
    delete data;
    data = newSeq;
}

template<typename T>
SetSequence<T>::SetSequence() : data(new ArraySequence<T>()) {}

template<typename T>
SetSequence<T>::SetSequence(T* items, size_t count) {
    data = new ArraySequence<T>(items, count);
    ensureUnique();
}

template<typename T>
SetSequence<T>::SetSequence(const LinkedList<T>& list) {
    data = new ArraySequence<T>(list);
    ensureUnique();
}

template<typename T>
SetSequence<T>::SetSequence(const DynamicArray<T>& arr) {
    data = new ArraySequence<T>();
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        data->Append(arr.Get(i));
    }
    ensureUnique();
}

template<typename T>
SetSequence<T>::SetSequence(const ArraySequence<T>& seq) {
    data = new ArraySequence<T>();
    for (size_t i = 0; i < seq.GetLength(); ++i) {
        data->Append(seq.Get(i));
    }
    ensureUnique();
}

template<typename T>
SetSequence<T>::SetSequence(const ListSequence<T>& seq) {
    data = new ArraySequence<T>();
    for (size_t i = 0; i < seq.GetLength(); ++i) {
        data->Append(seq.Get(i));
    }
    ensureUnique();
}

template<typename T>
SetSequence<T>::SetSequence(SetSequence<T>& other) { 
    data = new ArraySequence<T>();
    for (size_t i = 0; i < other.GetLength(); ++i) {
        data->Append(other.Get(i));
    }
}

template<typename T>
SetSequence<T>::~SetSequence() {
    delete data;
}

template<typename T>
SetSequence<T>& SetSequence<T>::operator=(const SetSequence<T>& other) {
    if (this != &other) {
        delete data;
        data = new ArraySequence<T>();
        for (size_t i = 0; i < other.GetLength(); ++i) {
            data->Append(other.Get(i));
        }
    }
    return *this;
}

template<typename T>
T SetSequence<T>::GetFirst() {
    if (!data || data->GetLength() == 0) throw EmptyCollectionException();
    return data->GetFirst();
}

template<typename T>
T SetSequence<T>::GetLast() {
    if (!data || data->GetLength() == 0) throw EmptyCollectionException();
    return data->GetLast();
}

template<typename T>
T SetSequence<T>::Get(size_t index) {
    if (!data) throw IndexOutOfRangeException();
    return data->Get(index);
}

template<typename T>
SetSequence<T>* SetSequence<T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    if (!data) throw IndexOutOfRangeException();
    Sequence<T>* sub = data->GetSubsequence(startIndex, endIndex);
    SetSequence<T>* result = new SetSequence<T>();
    delete result->data;
    result->data = sub;
    result->ensureUnique();
    return result;
}

template<typename T>
size_t SetSequence<T>::GetLength() {
    return data ? data->GetLength() : 0;
}

template<typename T>
SetSequence<T>* SetSequence<T>::Append(T item) {
    SetSequence<T>* result = new SetSequence<T>(*this);
    result->data->Append(item);
    result->ensureUnique();
    return result;
}

template<typename T>
SetSequence<T>* SetSequence<T>::Prepend(T item) {
    return Append(item);
}

template<typename T>
SetSequence<T>* SetSequence<T>::InsertAt(T item, size_t index) {
    (void)index;
    return Append(item);
}

template<typename T>
SetSequence<T>* SetSequence<T>::Concat(Sequence<T>* list) {
    if (!list) return new SetSequence<T>(*this);
    SetSequence<T>* result = new SetSequence<T>(*this);
    for (size_t i = 0; i < list->GetLength(); ++i) {
        result->data->Append(list->Get(i));
    }
    result->ensureUnique();
    return result;
}

template<typename T>
SetSequence<T>* SetSequence<T>::Map() {
    SetSequence<T>* result = new SetSequence<T>();
    for (size_t i = 0; i < GetLength(); ++i) {
        T newVal = Get(i) + 1;
        SetSequence<T>* temp = result->Append(newVal);
        delete result;
        result = temp;
    }
    return result;
}

template<typename T>
SetSequence<T>* SetSequence<T>::Where() {
    SetSequence<T>* result = new SetSequence<T>();
    for (size_t i = 0; i < GetLength(); ++i) {
        T val = Get(i);
        if (val % 2 == 0) {
            SetSequence<T>* temp = result->Append(val);
            delete result;
            result = temp;
        }
    }
    return result;
}

template<typename T>
T SetSequence<T>::Reduce() {
    if (GetLength() == 0) return T(0);
    T sum = T(0);
    for (size_t i = 0; i < GetLength(); ++i) {
        sum = sum + Get(i);
    }
    return sum;
}

template<typename T>
Option<T> SetSequence<T>::Find() {
    for (size_t i = 0; i < GetLength(); ++i) {
        if (Get(i) == 3) {
            return Option<T>(Get(i));
        }
    }
    return Option<T>();
}

