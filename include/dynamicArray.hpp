#pragma once

template<typename T>
class DynamicArray{
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
   
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
};

#include "../src/dynamicArray.tpp"

