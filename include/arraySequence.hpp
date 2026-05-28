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
    ArraySequence(T* items, size_t count);
    ArraySequence(const LinkedList<T>& list);
    ArraySequence(ArraySequence&& other) noexcept;
    ArraySequence(DynamicArray<T>* arr);
    virtual ~ArraySequence();
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence<T>& operator=(const ArraySequence<T>& other);
    ArraySequence<T>& operator=(ArraySequence<T>&& other) noexcept;

    T GetFirst() override;
    T GetLast() override;
    T Get(size_t index) override;
    ArraySequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    size_t GetLength() override;
    
    ArraySequence<T>* Append(T item) override;
    ArraySequence<T>* Prepend(T item) override;
    ArraySequence<T>* InsertAt(T item, size_t index) override;
    ArraySequence<T>* Concat(Sequence<T>* list) override;
    
    ArraySequence<T>* Map() override;
    ArraySequence<T>* Where() override;
    T Reduce() override;
    Option<T> Find() override;
};

template<typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, size_t count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    MutableArraySequence(DynamicArray<T>* arr) : ArraySequence<T>(arr) {}
};

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, size_t count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    ImmutableArraySequence(DynamicArray<T>* arr) : ArraySequence<T>(arr) {}
    
    ImmutableArraySequence<T>* Append(T item) override;
    ImmutableArraySequence<T>* Prepend(T item) override;
    ImmutableArraySequence<T>* InsertAt(T item, size_t index) override;
};

#include "../src/arraySequence.tpp"

