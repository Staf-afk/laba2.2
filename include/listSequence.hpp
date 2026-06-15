#pragma once
#include "sequence.hpp"
#include "linkedList.hpp"

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> items;
    
public:
    ListSequence();
    ListSequence(T* items, size_t count);
    ListSequence(const LinkedList<T>& list);
    
    ListSequence(const ListSequence<T>& other);
    ListSequence(ListSequence<T>&& other);
    virtual ~ListSequence();
    
    ListSequence<T>& operator=(const ListSequence<T>& other);
    ListSequence<T>& operator=(ListSequence<T>&& other);
    
    T GetFirst() override;
    T GetLast() override;
    T Get(size_t index) override;
    ListSequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    size_t GetLength() override;
    
    ListSequence<T>* Append(T item) override;
    ListSequence<T>* Prepend(T item) override;
    ListSequence<T>* InsertAt(T item, size_t index) override;
    ListSequence<T>* Concat(Sequence<T>* list) override;
    
    ListSequence<T>* Map() override;
    ListSequence<T>* Where() override;
    T Reduce() override;
    Option<T> Find() override;

    auto begin() { return items.begin(); }
    auto end() { return items.end(); }
    auto begin() const { return items.begin(); }
    auto end() const { return items.end(); }
};

template<typename T> 
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* items, size_t count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
};

template<typename T> 
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* items, size_t count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
    
    ImmutableListSequence<T>* Append(T item) override;
    ImmutableListSequence<T>* Prepend(T item) override;
    ImmutableListSequence<T>* InsertAt(T item, size_t index) override;
};

#include "../src/listSequence.tpp"