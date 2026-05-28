#include "../include/linkedList.hpp"
#include "../include/exceptions.cpp"

template<typename T> LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}
template<typename T> LinkedList<T>::LinkedList(T* items, size_t count) : head(nullptr), tail(nullptr), length(0) {
    for (size_t i = 0; i < count; ++i) Append(items[i]);
}
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), length(0) {
    Node<T>* curr = other.head;
    while (curr) { Append(curr->data); curr = curr->next; }
}
template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
    : head(other.head), tail(other.tail), length(other.length) 
{
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
        Node<T>* currentOther = other.head;
        while (currentOther) {
            Node<T>* newNode = new Node<T>(currentOther->data);
            if (!head) head = tail = newNode;
            else { tail->next = newNode; tail = newNode; }
            length++;
            currentOther = currentOther->next;
        }
    }
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this != &other) {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = other.head;
        tail = other.tail;
        length = other.length;
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }
    return *this;
}

template<typename T> T LinkedList<T>::GetFirst() const {
    if (!head) throw EmptyCollectionException();
    return head->data;
}
template<typename T> T LinkedList<T>::GetLast() const {
    if (!tail) throw EmptyCollectionException();
    return tail->data;
}
template<typename T> T LinkedList<T>::Get(size_t index) const {
    if (index >= length) throw IndexOutOfRangeException();
    Node<T>* curr = head;
    for (size_t i = 0; i < index; ++i) curr = curr->next;
    return curr->data;
}
template<typename T> size_t LinkedList<T>::GetLength() const { return length; }

template<typename T> LinkedList<T>* LinkedList<T>::GetSubList(size_t start, size_t end) const {
    if (start > end || end >= length) throw IndexOutOfRangeException();
    LinkedList<T>* res = new LinkedList<T>();
    Node<T>* curr = head;
    for (size_t i = 0; i < start; ++i) curr = curr->next;
    for (size_t i = start; i <= end; ++i) { res->Append(curr->data); curr = curr->next; }
    return res;
}

template<typename T> void LinkedList<T>::Append(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (!tail) head = tail = newNode;
    else { tail->next = newNode; tail = newNode; }
    length++;
}
template<typename T> void LinkedList<T>::Prepend(T item) {
    Node<T>* newNode = new Node<T>(item);
    if (!head) head = tail = newNode;
    else { newNode->next = head; head = newNode; }
    length++;
}
template<typename T> void LinkedList<T>::InsertAt(T item, size_t index) {
    if (index > length) throw IndexOutOfRangeException();
    if (index == 0) { Prepend(item); return; }
    if (index == length) { Append(item); return; }
    Node<T>* curr = head;
    for (size_t i = 0; i < index - 1; ++i) curr = curr->next;
    Node<T>* newNode = new Node<T>(item);
    newNode->next = curr->next;
    curr->next = newNode;
    length++;
}
template<typename T> LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
    if (!list) return new LinkedList<T>(*this);
    LinkedList<T>* res = new LinkedList<T>(*this);
    Node<T>* curr = list->head;
    while (curr) { res->Append(curr->data); curr = curr->next; }
    return res;
}
