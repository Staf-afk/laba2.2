#include "../include/listSequence.hpp"
#include "../include/exceptions.hpp"

template<typename T> ListSequence<T>::ListSequence() : items(new LinkedList<T>()) {}
template<typename T> ListSequence<T>::ListSequence(T* items, int count) : items(new LinkedList<T>(items, count)) {}
template<typename T> ListSequence<T>::ListSequence(const LinkedList<T>& list) : items(new LinkedList<T>(list)) {}
template<typename T> ListSequence<T>::~ListSequence() { delete items; }

template<typename T> T ListSequence<T>::GetFirst() {
    return items->GetFirst(); 
}
template<typename T> T ListSequence<T>::GetLast() { 
    return items->GetLast(); 
}
template<typename T> T ListSequence<T>::Get(int index) { 
    return items->Get(index); 
}
template<typename T> int ListSequence<T>::GetLength() { 
    return items->GetLength(); 
}

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

template<typename T>
ListSequence<T>* ListSequence<T>::Map() {
    int len = GetLength();
    if (len == 0) {
        return new ListSequence<T>();
    }
    T* newData = new T[len];
    for (int i = 0; i < len; ++i) {
        newData[i] = Get(i) + 1;
    }
    ListSequence<T>* result = new ListSequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T>
ListSequence<T>* ListSequence<T>::Where() {
    int len = GetLength();
    if (len == 0) {
        return new ListSequence<T>();
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
    ListSequence<T>* result = new ListSequence<T>(evenData, evenCount);
    delete[] evenData;
    return result;
}

template<typename T>
T ListSequence<T>::Reduce() {
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
Option<T> ListSequence<T>::Find() {
    for (int i = 0; i < GetLength(); ++i) {
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
ImmutableListSequence<T>* ImmutableListSequence<T>::InsertAt(T item, int idx) {
    auto* c = new ImmutableListSequence<T>(*this);
    c->ListSequence<T>::InsertAt(item, idx);
    return c;
}

