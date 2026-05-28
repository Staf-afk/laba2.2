#pragma once

template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t length;
public:
    LinkedList();
    LinkedList(T* items, size_t count);
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();
    LinkedList(LinkedList<T>&& other) noexcept;
    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
    
    T GetFirst() const;
    T GetLast() const;
    T Get(size_t index) const;
    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) const;
    size_t GetLength() const;
    
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, size_t index);
    LinkedList<T>* Concat(LinkedList<T>* list);
};
#include "../src/linkedList.tpp"

