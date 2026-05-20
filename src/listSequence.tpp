#include "../include/listSequence.hpp"
#include "../include/exceptions.hpp"

template<typename T> ListSequence<T>::ListSequence() : items(new LinkedList<T>()) {}
template<typename T> ListSequence<T>::ListSequence(T* items, int count) : items(new LinkedList<T>(items, count)) {}
template<typename T> ListSequence<T>::ListSequence(const LinkedList<T>& list) : items(new LinkedList<T>(list)) {}
template<typename T> ListSequence<T>::~ListSequence() { delete items; }

template<typename T> T ListSequence<T>::GetFirst() const { return items->GetFirst(); }
template<typename T> T ListSequence<T>::GetLast() const { return items->GetLast(); }
template<typename T> T ListSequence<T>::Get(int index) const { return items->Get(index); }
template<typename T> int ListSequence<T>::GetLength() const { return items->GetLength(); }

template<typename T> ListSequence<T>* ListSequence<T>::GetSubsequence(int s, int e) const {
    if (s < 0 || e >= items->GetLength() || s > e) throw IndexOutOfRangeException();
    return new ListSequence<T>(*items->GetSubList(s, e));
}

template<typename T> ListSequence<T>* ListSequence<T>::Append(T item) { items->Append(item); return this; }
template<typename T> ListSequence<T>* ListSequence<T>::Prepend(T item) { items->Prepend(item); return this; }
template<typename T> ListSequence<T>* ListSequence<T>::InsertAt(T item, int idx) { items->InsertAt(item, idx); return this; }
template<typename T> ListSequence<T>* ListSequence<T>::Concat(Sequence<T>* list) {
    if (!list) return new ListSequence<T>(*this);
    LinkedList<T>* combined = new LinkedList<T>(*items);
    for (int i = 0; i < list->GetLength(); ++i) combined->Append(list->Get(i));
    return new ListSequence<T>(*combined);
}

template<typename T> template<typename T2>
Sequence<T2>* ListSequence<T>::Map(std::function<T2(T)> func) {
    T2* data = new T2[GetLength()];
    for (int i = 0; i < GetLength(); ++i) data[i] = func(Get(i));
    Sequence<T2>* result = new ListSequence<T2>(data, GetLength());
    delete[] data;
    return result;
}

template<typename T>
Sequence<T>* ListSequence<T>::Where(std::function<bool(T)> pred) {
    LinkedList<T>* filtered = new LinkedList<T>();
    for (int i = 0; i < GetLength(); ++i) if (pred(Get(i))) filtered->Append(Get(i));
    return new ListSequence<T>(*filtered);
}

template<typename T> template<typename T2>
T2 ListSequence<T>::Reduce(std::function<T2(T2, T)> func, T2 initial) {
    T2 res = initial;
    for (int i = 0; i < GetLength(); ++i) res = func(res, Get(i));
    return res;
}

template<typename T> 
Option<T> ListSequence<T>::Find(std::function<bool(T)> pred) {
    for (int i = 0; i < GetLength(); ++i) {
        if (pred(Get(i))) return Option<T>(Get(i));
    }
    return Option<T>();
}

// Immutable 
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
ImmutableListSequence<T>* ImmutableListSequence<T>::InsertAt(T item, int idx) {
    auto* c = new ImmutableListSequence<T>(*this);
    c->ListSequence<T>::InsertAt(item, idx);
    return c;
}