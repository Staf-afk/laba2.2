#pragma once
#include "sequence.hpp"
#include "dynamicArray.hpp"
#include "arraySequence.hpp"
#include "linkedList.hpp"
#include "listSequence.hpp"
#include <functional>

template<typename T>
class SetSequence : public Sequence<T> {
private:
    Sequence<T>* data;
    void ensureUnique();

public:
    SetSequence();
    SetSequence(T* items, size_t count);
    SetSequence(const LinkedList<T>& list);
    SetSequence(const DynamicArray<T>& arr);
    SetSequence(const ArraySequence<T>& seq);
    SetSequence(const ListSequence<T>& seq);
    SetSequence(SetSequence<T>& other);
    ~SetSequence();

    SetSequence<T>& operator=(const SetSequence<T>& other);

    T GetFirst() override;
    T GetLast() override;
    T Get(size_t index) override;
    SetSequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    size_t GetLength() override;

    SetSequence<T>* Append(T item) override;
    SetSequence<T>* Prepend(T item) override;
    SetSequence<T>* InsertAt(T item, size_t index) override;
    SetSequence<T>* Concat(Sequence<T>* list) override;

    SetSequence<T>* Map(std::function<T(T)> func);
    SetSequence<T>* Map() override;
    SetSequence<T>* Where(std::function<bool(T)> predicate);
    SetSequence<T>* Where() override;
    T Reduce(std::function<T(T, T)> func, T initial);
    T Reduce() override;
    Option<T> Find(std::function<bool(T)> predicate);
    Option<T> Find() override;

    typename DynamicArray<T>::DynamicArrayIterator begin() {
        if (auto* arrSeq = dynamic_cast<ArraySequence<T>*>(data)) {
            return arrSeq->begin();
        }
        static DynamicArray<T> dummy;
        return dummy.begin();
    }
    typename DynamicArray<T>::DynamicArrayIterator end() {
        if (auto* arrSeq = dynamic_cast<ArraySequence<T>*>(data)) {
            return arrSeq->end();
        }
        static DynamicArray<T> dummy;
        return dummy.end();
    }
};

#include "../src/setSequence.tpp"


