#include "../include/dynamicArray.hpp"
#include "../include/exceptions.cpp"

template<typename T> DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}

template<typename T> DynamicArray<T>::DynamicArray(size_t size) : size(size) {
    data = size > 0 ? new T[size]() : nullptr;
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& other) noexcept
    : data(other.data), size(other.size) 
{
    other.data = nullptr;
    other.size = 0;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

template<typename T> DynamicArray<T>::DynamicArray(T* items, size_t count) : size(count) {
    if (count > 0 && items == nullptr) throw NullPointerArgumentException("Items pointer cannot be null for positive count");
    data = count > 0 ? new T[count] : nullptr;
    for (size_t i = 0; i < count; ++i) data[i] = items[i];
}

template<typename T> DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : size(other.size) {
    data = size > 0 ? new T[size] : nullptr;
    for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
}

template<typename T> DynamicArray<T>::~DynamicArray() { 
    delete[] data; 
}

template<typename T> T DynamicArray<T>::Get(size_t index) const {
    if (index >= size) throw IndexOutOfRangeException();
    return data[index];
}

template<typename T> void DynamicArray<T>::Set(size_t index, T value) {
    if (index >= size) throw IndexOutOfRangeException();
    data[index] = value;
}

template<typename T> size_t DynamicArray<T>::GetSize() const { 
    return size; 
}

template<typename T> void DynamicArray<T>::Resize(size_t newSize) {
    T* newData = newSize > 0 ? new T[newSize]() : nullptr;
    size_t copyCount = (newSize < size) ? newSize : size;
    for (size_t i = 0; i < copyCount; ++i) newData[i] = data[i];
    
    delete[] data;
    data = newData;
    size = newSize;
}

template<typename T> DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = size > 0 ? new T[size] : nullptr;
        for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
    }
    return *this;
}
