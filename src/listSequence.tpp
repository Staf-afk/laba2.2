#include "../include/listSequence.hpp"
#include "../include/exceptions.cpp"

template<typename T>
ListSequence<T>::ListSequence() : items() {}

template<typename T> 
ListSequence<T>::ListSequence(T* itemsArr, size_t count) : items(itemsArr, count) {}

template<typename T> 
ListSequence<T>::ListSequence(const LinkedList<T>& list) : items(list) {}

template<typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) : items(other.items) {}

template<typename T>
ListSequence<T>::ListSequence(ListSequence<T>&& other) : items(std::move(other.items)) {}

template<typename T>
ListSequence<T>::~ListSequence() {}

template<typename T>
ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T>& other) {
    if (this != &other) {
        items = other.items;
    }
    return *this;
}

template<typename T>
ListSequence<T>& ListSequence<T>::operator=(ListSequence<T>&& other) {
    if (this != &other) {
        items = std::move(other.items);
    }
    return *this;
}

template<typename T> 
T ListSequence<T>::GetFirst() { 
    return items.GetFirst(); 
}

template<typename T> 
T ListSequence<T>::GetLast() { 
    return items.GetLast(); 
}

template<typename T> 
T ListSequence<T>::Get(size_t index) { 
    return items.Get(index); 
}

template<typename T> 
size_t ListSequence<T>::GetLength() { 
    return items.GetLength(); 
}

template<typename T> 
ListSequence<T>* ListSequence<T>::GetSubsequence(size_t start, size_t end) const {
    if (start > end || end >= items.GetLength()) throw IndexOutOfRangeException();
    LinkedList<T>* sublist = items.GetSubList(start, end);
    ListSequence<T>* result = new ListSequence<T>(*sublist);
    delete sublist;
    return result;
}

template<typename T> 
ListSequence<T>* ListSequence<T>::Append(T item) { 
    items.Append(item); 
    return this; 
}

template<typename T> 
ListSequence<T>* ListSequence<T>::Prepend(T item) { 
    items.Prepend(item); 
    return this; 
}

template<typename T> 
ListSequence<T>* ListSequence<T>::InsertAt(T item, size_t index) { 
    items.InsertAt(item, index); 
    return this; 
}

template<typename T> 
ListSequence<T>* ListSequence<T>::Concat(Sequence<T>* list) {
    if (!list) return new ListSequence<T>(*this);
    ListSequence<T>* result = new ListSequence<T>(*this);
    for (size_t i = 0; i < list->GetLength(); ++i) {
        result->Append(list->Get(i));
    }
    return result;
}

template<typename T>
ListSequence<T>* ListSequence<T>::Map() {
    throw std::runtime_error("Map requires a function parameter. Use Map(std::function<T(T)> func) instead.");
    return this;
}

template<typename T>
ListSequence<T>* ListSequence<T>::Where() {
    throw std::runtime_error("Where requires a predicate parameter. Use Where(std::function<bool(T)> pred) instead.");
    return this;
}

template<typename T>
T ListSequence<T>::Reduce() {
    throw std::runtime_error("Reduce requires a function parameter. Use Reduce(std::function<T(T,T)> func, T initial) instead.");
    return T();
}

template<typename T>
Option<T> ListSequence<T>::Find() {
    throw std::runtime_error("Find requires a predicate parameter. Use Find(std::function<bool(T)> pred) instead.");
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
ImmutableListSequence<T>* ImmutableListSequence<T>::InsertAt(T item, size_t index) {
    auto* c = new ImmutableListSequence<T>(*this);
    c->ListSequence<T>::InsertAt(item, index);
    return c;
}

