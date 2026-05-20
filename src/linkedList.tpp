#include "../include/linkedList.hpp"
#include "../include/exceptions.hpp"

template<typename T> LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}
template<typename T> LinkedList<T>::LinkedList(T* items, int count) : head(nullptr), tail(nullptr), length(0) {
    for (int i = 0; i < count; ++i) Append(items[i]);
}
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), length(0) {
    Node<T>* curr = other.head;
    while (curr) { Append(curr->data); curr = curr->next; }
}
template<typename T> LinkedList<T>::~LinkedList() {
    Node<T>* curr = head;
    while (curr) { Node<T>* next = curr->next; delete curr; curr = next; }
}

template<typename T> T LinkedList<T>::GetFirst() const {
    if (!head) throw EmptyCollectionException();
    return head->data;
}
template<typename T> T LinkedList<T>::GetLast() const {
    if (!tail) throw EmptyCollectionException();
    return tail->data;
}
template<typename T> T LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length) throw IndexOutOfRangeException();
    Node<T>* curr = head;
    for (int i = 0; i < index; ++i) curr = curr->next;
    return curr->data;
}
template<typename T> int LinkedList<T>::GetLength() const { return length; }

template<typename T> LinkedList<T>* LinkedList<T>::GetSubList(int start, int end) const {
    if (start < 0 || end >= length || start > end) throw IndexOutOfRangeException();
    LinkedList<T>* res = new LinkedList<T>();
    Node<T>* curr = head;
    for (int i = 0; i < start; ++i) curr = curr->next;
    for (int i = start; i <= end; ++i) { res->Append(curr->data); curr = curr->next; }
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
template<typename T> void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > length) throw IndexOutOfRangeException();
    if (index == 0) { Prepend(item); return; }
    if (index == length) { Append(item); return; }
    Node<T>* curr = head;
    for (int i = 0; i < index - 1; ++i) curr = curr->next;
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
