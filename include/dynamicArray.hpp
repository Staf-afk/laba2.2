#pragma once

template<typename T>
class DynamicArray{
private:
    T* data;
    size_t size;
public:
    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(T* items, size_t count);
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray(DynamicArray<T>&& other) noexcept;
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept;
    ~DynamicArray();
    
    T Get(size_t index) const;
    void Set(size_t index, T value);
    size_t GetSize() const;
    void Resize(size_t newSize);
   
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
};

#include "../src/dynamicArray.tpp"

