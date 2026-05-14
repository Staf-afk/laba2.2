#include "../include/dynamicArray.hpp"
#include "../include/exceptions.hpp"

template<typename T> DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}
template<typename T> DynamicArray<T>::DynamicArray(int size) : size(size), capacity(size) {
    data = size > 0 ? new T[size]() : nullptr;
}
template<typename T> DynamicArray<T>::DynamicArray(T* items, int count) : size(count), capacity(count) {
    data = count > 0 ? new T[count] : nullptr;
    for (int i = 0; i < count; ++i) data[i] = items[i];
}
template<typename T> DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : size(other.size), capacity(other.capacity) {
    data = capacity > 0 ? new T[capacity] : nullptr;
    for (int i = 0; i < size; ++i) data[i] = other.data[i];
}
template<typename T> DynamicArray<T>::~DynamicArray() { delete[] data; }

template<typename T> T DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= size) throw IndexOutOfRangeException();
    return data[index];
}
template<typename T> void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= size) throw IndexOutOfRangeException();
    data[index] = value;
}
template<typename T> int DynamicArray<T>::GetSize() const { return size; }

template<typename T> void DynamicArray<T>::Resize(int newSize) {
    if (newSize < 0) throw IndexOutOfRangeException("New size cannot be negative");
    T* newData = newSize > 0 ? new T[newSize]() : nullptr;
    int copyCount = (newSize < size) ? newSize : size;
    for (int i = 0; i < copyCount; ++i) newData[i] = data[i];
    delete[] data;
    data = newData;
    size = newSize;
    capacity = newSize;
}

template<typename T> IEnumerator<T>* DynamicArray<T>::GetEnumerator() { return nullptr; } // Заглушка