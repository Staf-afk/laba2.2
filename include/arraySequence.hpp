#pragma once
#include "sequence.hpp"
#include "dynamicArray.hpp"
#include "linkedList.hpp"

template<typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* items;
public:
    ArraySequence();
    ArraySequence(T* items, int count);
    ArraySequence(const LinkedList<T>& list);
    ArraySequence(DynamicArray<T>* arr);
    virtual ~ArraySequence();
    
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    
    ArraySequence<T>* Append(T item) override;
    ArraySequence<T>* Prepend(T item) override;
    ArraySequence<T>* InsertAt(T item, int index) override;
    ArraySequence<T>* Concat(Sequence<T>* list) override;
    
    template<typename T2> Sequence<T2>* Map(std::function<T2(T)> func);
    Sequence<T>* Where(std::function<bool(T)> predicate);
    template<typename T2> T2 Reduce(std::function<T2(T2, T)> func, T2 initial);
    Option<T> Find(std::function<bool(T)> predicate) override;
};

template<typename T> class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    MutableArraySequence(DynamicArray<T>* arr) : ArraySequence<T>(arr) {}
};

template<typename T> class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    ImmutableArraySequence(DynamicArray<T>* arr) : ArraySequence<T>(arr) {}
    
    ImmutableArraySequence<T>* Append(T item) override;
    ImmutableArraySequence<T>* Prepend(T item) override;
    ImmutableArraySequence<T>* InsertAt(T item, int index) override;
};

#include "../src/arraySequence.tpp"