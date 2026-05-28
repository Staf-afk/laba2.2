#include "../include/listSequence.hpp"
#include "../include/exceptions.cpp"

template<typename T>
ListSequence<T>::ListSequence() : items(new LinkedList<T>()) {}
template<typename T> 
ListSequence<T>::ListSequence(T* items, size_t count) : items(new LinkedList<T>(items, count)) {}
template<typename T> 
ListSequence<T>::ListSequence(const LinkedList<T>& list) : items(new LinkedList<T>(list)) {}
template<typename T>
ListSequence<T>::~ListSequence() {
    delete items;
}

template<typename T>
ListSequence<T>::ListSequence(ListSequence&& other) noexcept
    : items(other.items)
{
    other.items = nullptr;
}

template<typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& other)
    : items(nullptr) 
{
    if (other.items != nullptr) {
        items = new LinkedList<T>(*other.items);
    }
}

template<typename T>
ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T>& other) {
    if (this != &other) {
        delete items;
        items = nullptr;
        if (other.items != nullptr) {
            items = new LinkedList<T>(*other.items);
        }
    }
    return *this;
}

template<typename T>
ListSequence<T>& ListSequence<T>::operator=(ListSequence<T>&& other) noexcept {
    if (this != &other) {
        delete items;
        items = other.items;
        other.items = nullptr;
    }
    return *this;
}

template<typename T> T ListSequence<T>::GetFirst() {
    return items->GetFirst(); 
}
template<typename T> T ListSequence<T>::GetLast() { 
    return items->GetLast(); 
}
template<typename T> T ListSequence<T>::Get(size_t index) { 
    return items->Get(index); 
}
template<typename T> size_t ListSequence<T>::GetLength() { 
    return items->GetLength(); 
}

template<typename T> ListSequence<T>* ListSequence<T>::GetSubsequence(size_t s, size_t e) const {
    if (s > e || e >= items->GetLength()) throw IndexOutOfRangeException();
    return new ListSequence<T>(*items->GetSubList(s, e));
}

template<typename T> ListSequence<T>* ListSequence<T>::Append(T item) { items->Append(item); return this; }
template<typename T> ListSequence<T>* ListSequence<T>::Prepend(T item) { items->Prepend(item); return this; }
template<typename T> ListSequence<T>* ListSequence<T>::InsertAt(T item, size_t idx) { items->InsertAt(item, idx); return this; }
template<typename T> ListSequence<T>* ListSequence<T>::Concat(Sequence<T>* list) {
    if (!list) return new ListSequence<T>(*this);
    LinkedList<T>* combined = new LinkedList<T>(*items);
    for (size_t i = 0; i < static_cast<size_t>(list->GetLength()); ++i) combined->Append(list->Get(i));
    return new ListSequence<T>(*combined);
}

template<typename T>
ListSequence<T>* ListSequence<T>::Map() {
    size_t len = GetLength();
    if (len == 0) {
        return new ListSequence<T>();
    }
    T* newData = new T[len];
    for (size_t i = 0; i < len; ++i) {
        newData[i] = Get(i) + 1;
    }
    ListSequence<T>* result = new ListSequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T>
ListSequence<T>* ListSequence<T>::Where() {
    size_t len = GetLength();
    if (len == 0) {
        return new ListSequence<T>();
    }
    size_t evenCount = 0;
    for (size_t i = 0; i < len; ++i) {
        if (Get(i) % 2 == 0) {
            evenCount++;
        }
    }
    T* evenData = new T[evenCount];
    size_t index = 0;
    for (size_t i = 0; i < len; ++i) {
        if (Get(i) % 2 == 0) {
            evenData[index++] = Get(i);
        }
    }
    ListSequence<T>* result = new ListSequence<T>(evenData, evenCount);
    delete[] evenData;
    return result;
}

template<typename T>
T ListSequence<T>::Reduce() {
    size_t len = GetLength();
    if (len == 0) {
        return T(0);
    }
    T sum = T(0);
    for (size_t i = 0; i < len; ++i) {
        sum = sum + Get(i);
    }
    return sum;
}

template<typename T>
Option<T> ListSequence<T>::Find() {
    for (size_t i = 0; i < GetLength(); ++i) {
        if (Get(i) == 3) {
            return Option<T>(Get(i));
        }
    }
    return Option<T>();
}

template<typename T> 
ImmutableListSequence<T>* ImmutableListSequence<T>::Append(T item) {
    auto* c = new ImmutableListSequence<T>(*this);
    c->ListSequence<T>::Append(item);
    return c;
}

template<typename T> 
ImmutableListSequence<T>* ImmutableListSequence<T>::Prepend(T item) { 
    return InsertAt(item, 0); 
}

template<typename T> 
ImmutableListSequence<T>* ImmutableListSequence<T>::InsertAt(T item, size_t idx) {
    auto* c = new ImmutableListSequence<T>(*this);
    c->ListSequence<T>::InsertAt(item, idx);
    return c;
}

