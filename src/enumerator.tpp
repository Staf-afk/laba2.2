#pragma once

#include "../include/enumerator.hpp"

template <typename T>
ArrayEnumerator<T>::ArrayEnumerator(T* arr, int sz, bool takeOwnership) 
    : data(arr), size(sz), position(-1), ownsData(takeOwnership) {}

template <typename T>
ArrayEnumerator<T>::~ArrayEnumerator() {
    if (ownsData) {
        delete[] data;
    }
}

template <typename T>
bool ArrayEnumerator<T>::MoveNext() {
    if (position + 1 < size) {
        position++;
        return true;
    }
    return false;
}

template <typename T>
T ArrayEnumerator<T>::GetCurrent() {
    return data[position];
}

template <typename T>
void ArrayEnumerator<T>::Reset() {
    position = -1;
}

template <typename T>
ListEnumerator<T>::ListEnumerator(Node<T>* head) : start(head), current(head), first(true) {}

template <typename T>
bool ListEnumerator<T>::MoveNext() {
    if (first) {
        first = false;
        return current != nullptr;
    }
    if (current != nullptr) {
        current = current->next;
        return current != nullptr;
    }
    return false;
}

template <typename T>
T ListEnumerator<T>::GetCurrent() {
    return current->data;
}

template <typename T>
void ListEnumerator<T>::Reset() {
    current = start;
    first = true;
}