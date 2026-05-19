#pragma once
#include "enumerator.hpp"

template<typename T>
class DynamicArray : public IEnumerable<T> {
private:
    T* data;
    int size;
public:
    DynamicArray();
    DynamicArray(int size);
    DynamicArray(T* items, int count);
    DynamicArray(const DynamicArray<T>& other);
    ~DynamicArray();
    
    T Get(int index) const;
    void Set(int index, T value);
    int GetSize() const;
    void Resize(int newSize);
    IEnumerator<T>* GetEnumerator() override;
    
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
};

#include "../src/dynamicArray.tpp"