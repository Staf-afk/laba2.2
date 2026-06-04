#pragma once
#include <iterator>

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    
public:
    class DynamicArrayIterator {
    private:
        T* current;
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        DynamicArrayIterator(T* curr = nullptr) : current(curr) {}

        DynamicArrayIterator& operator++() { ++current; return *this; }
        DynamicArrayIterator operator++(int) { DynamicArrayIterator tmp = *this; ++current; return tmp; }
        T& operator*() { return *current; }
        T* operator->() { return current; }

        bool operator==(const DynamicArrayIterator& other) const { return current == other.current; }
        bool operator!=(const DynamicArrayIterator& other) const { return !(*this == other); }
    };

    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(T* items, size_t count);
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray(DynamicArray<T>&& other);
    ~DynamicArray();
    
    T Get(size_t index) const;
    void Set(size_t index, T value);
    size_t GetSize() const;
    void Resize(size_t newSize);
    
    DynamicArray<T>& operator=(DynamicArray<T>&& other);
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    
    DynamicArrayIterator begin() { return DynamicArrayIterator(data); }
    DynamicArrayIterator end() { return DynamicArrayIterator(data + size); }
};

#include "../src/dynamicArray.tpp"