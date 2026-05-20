#include "../include/arraySequence.hpp"
#include "../include/exceptions.hpp"

template<typename T> ArraySequence<T>::ArraySequence() : items(new DynamicArray<T>()) {}
template<typename T> ArraySequence<T>::ArraySequence(T* items, int count) : items(new DynamicArray<T>(items, count)) {}
template<typename T> ArraySequence<T>::ArraySequence(const LinkedList<T>& list) : items(new DynamicArray<T>()) {
    for (int i = 0; i < list.GetLength(); ++i) {
        items->Resize(items->GetSize() + 1);
        items->Set(items->GetSize() - 1, list.Get(i));
    }
}
template<typename T> ArraySequence<T>::ArraySequence(DynamicArray<T>* arr) : items(arr) {}
template<typename T> ArraySequence<T>::~ArraySequence() { delete items; }

template<typename T> T ArraySequence<T>::GetFirst() const {
    if (items->GetSize() == 0) throw EmptyCollectionException();
    return items->Get(0);
}
template<typename T> T ArraySequence<T>::GetLast() const {
    if (items->GetSize() == 0) throw EmptyCollectionException();
    return items->Get(items->GetSize() - 1);
}
template<typename T> T ArraySequence<T>::Get(int index) const { return items->Get(index); }
template<typename T> int ArraySequence<T>::GetLength() const { return items->GetSize(); }

template<typename T> ArraySequence<T>* ArraySequence<T>::GetSubsequence(int s, int e) const {
    if (s < 0 || e >= items->GetSize() || s > e) throw IndexOutOfRangeException();
    int len = e - s + 1;
    T* newData = new T[len];
    for (int i = 0; i < len; ++i) newData[i] = items->Get(s + i);
    ArraySequence<T>* result = new ArraySequence<T>(newData, len);
    delete[] newData;
    return result;
}

template<typename T> ArraySequence<T>* ArraySequence<T>::Append(T item) {
    items->Resize(items->GetSize() + 1);
    items->Set(items->GetSize() - 1, item);
    return this;
}
template<typename T> ArraySequence<T>* ArraySequence<T>::Prepend(T item) { return InsertAt(item, 0); }
template<typename T> ArraySequence<T>* ArraySequence<T>::InsertAt(T item, int idx) {
    if (idx < 0 || idx > items->GetSize()) throw IndexOutOfRangeException();
    items->Resize(items->GetSize() + 1);
    for (int i = items->GetSize() - 1; i > idx; --i) items->Set(i, items->Get(i - 1));
    items->Set(idx, item);
    return this;
}
template<typename T> ArraySequence<T>* ArraySequence<T>::Concat(Sequence<T>* list) {
    if (!list) return new ArraySequence<T>(*this);
    ArraySequence<T>* res = new ArraySequence<T>(*this);
    for (int i = 0; i < list->GetLength(); ++i) res->Append(list->Get(i));
    return res;
}

template<typename T> template<typename T2>
Sequence<T2>* ArraySequence<T>::Map(std::function<T2(T)> func) {
    T2* data = new T2[GetLength()];
    for (int i = 0; i < GetLength(); ++i) data[i] = func(Get(i));
    Sequence<T2>* result = new ArraySequence<T2>(data, GetLength());
    delete[] data;
    return result;
}

template<typename T>
Sequence<T>* ArraySequence<T>::Where(std::function<bool(T)> pred) {
    DynamicArray<T>* filtered = new DynamicArray<T>();
    for (int i = 0; i < GetLength(); ++i) {
        if (pred(Get(i))) {
            filtered->Resize(filtered->GetSize() + 1);
            filtered->Set(filtered->GetSize() - 1, Get(i));
        }
    }
    return new ArraySequence<T>(filtered);
}

template<typename T> template<typename T2>
T2 ArraySequence<T>::Reduce(std::function<T2(T2, T)> func, T2 initial) {
    T2 res = initial;
    for (int i = 0; i < GetLength(); ++i) res = func(res, Get(i));
    return res;
}

template<typename T> 
Option<T> ArraySequence<T>::Find(std::function<bool(T)> pred) {
    for (int i = 0; i < GetLength(); ++i) {
        if (pred(Get(i))) return Option<T>(Get(i));
    }
    return Option<T>();
}

// Immutable overrides
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
ImmutableArraySequence<T>* ImmutableArraySequence<T>::InsertAt(T item, int idx) {
    auto* c = new ImmutableArraySequence<T>(*this);
    c->ArraySequence<T>::InsertAt(item, idx);
    return c;
}