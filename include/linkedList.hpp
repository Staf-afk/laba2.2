#pragma once
#include <iterator>

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t length;
    
public:
    class LinkedListIterator {
    private:
        Node* current;
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        LinkedListIterator(Node* node = nullptr) : current(node) {}

        LinkedListIterator& operator++() { if (current) current = current->next; return *this; }
        LinkedListIterator operator++(int) { LinkedListIterator tmp = *this; ++(*this); return tmp; }
        T& operator*() { return current->data; }
        T* operator->() { return &(current->data); }

        bool operator==(const LinkedListIterator& other) const { return current == other.current; }
        bool operator!=(const LinkedListIterator& other) const { return !(*this == other); }
    };

    LinkedList();
    LinkedList(T* items, size_t count);
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();
    LinkedList(LinkedList<T>&& other);
    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T>&& other);
    
    T GetFirst() const;
    T GetLast() const;
    T Get(size_t index) const;
    LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) const;
    size_t GetLength() const;
    
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, size_t index);
    LinkedList<T>* Concat(LinkedList<T>* list);
    
    LinkedListIterator begin() { return LinkedListIterator(head); }
    LinkedListIterator end() { return LinkedListIterator(nullptr); }
};

#include "../src/linkedList.tpp"