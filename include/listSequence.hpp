#pragma once
#include "sequence.hpp"
#include "linkedList.hpp"

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* items;
public:
    ListSequence();
    ListSequence(T* items, int count);
    ListSequence(const LinkedList<T>& list);
    virtual ~ListSequence();
    
    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    
    ListSequence<T>* Append(T item) override;
    ListSequence<T>* Prepend(T item) override;
    ListSequence<T>* InsertAt(T item, int index) override;
    ListSequence<T>* Concat(Sequence<T>* list) override;
    
    ListSequence<T>* Map();
    ListSequence<T>* Where();
    T Reduce();
    Option<T> Find(std::function<bool(T)> predicate) override;
};

template<typename T> class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
};

template<typename T> class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
    
    ImmutableListSequence<T>* Append(T item) override;
    ImmutableListSequence<T>* Prepend(T item) override;
    ImmutableListSequence<T>* InsertAt(T item, int index) override;
};

#include "../src/listSequence.tpp"
