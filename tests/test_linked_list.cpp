#include <iostream>
#include <string>
#include "../include/linkedList.hpp"

class LinkedListTests {
private:
    int passed = 0;
    int failed = 0;
    
    template<typename T>
    void assertEqual(T expected, T actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  ? " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } else {
            std::cout << "  ? " << testName << " - НЕ ПРОЙДЕН (Ожидалось: " << expected 
                      << ", Получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertEqual(size_t expected, size_t actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  ? " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } else {
            std::cout << "  ? " << testName << " - НЕ ПРОЙДЕН (Ожидалось: " << expected 
                      << ", Получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "  ? " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } else {
            std::cout << "  ? " << testName << " - НЕ ПРОЙДЕН" << std::endl;
            failed++;
        }
    }
    
    void printList(LinkedList<int>* list, const std::string& label) {
        std::cout << "    " << label << ": [";
        for (size_t i = 0; i < static_cast<size_t>(list->GetLength()); i++) {
            std::cout << list->Get(i);
            if (i < list->GetLength() - 1) std::cout << " ? ";
        }
        std::cout << "] (длина: " << list->GetLength() << ")" << std::endl;
    }
    
public:
    void testConstructor() {
        std::cout << "\n--- Тесты конструкторов LinkedList ---" << std::endl;
        
        LinkedList<int> list1;
        assertEqual(static_cast<size_t>(0), list1.GetLength(), "Конструктор по умолчанию - длина");
        std::cout << "    Создан пустой список" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        LinkedList<int> list2(items, 5);
        assertEqual(static_cast<size_t>(5), list2.GetLength(), "Конструктор из массива - длина");
        assertEqual(10, list2.GetFirst(), "Конструктор из массива - первый элемент");
        assertEqual(50, list2.GetLast(), "Конструктор из массива - последний элемент");
        
        std::cout << "    Входные данные: [10, 20, 30, 40, 50]" << std::endl;
        printList(&list2, "Созданный список");
        
        LinkedList<int> list3(list2);
        assertEqual(static_cast<size_t>(5), list3.GetLength(), "Конструктор копирования - длина");
        assertEqual(10, list3.GetFirst(), "Конструктор копирования - первый элемент");
    }
    
    void testAppendPrepend() {
        std::cout << "\n--- Тесты Append/Prepend LinkedList ---" << std::endl;
        
        LinkedList<int> list;
        
        list.Append(10);
        assertEqual(static_cast<size_t>(1), list.GetLength(), "Append первого элемента - длина");
        assertEqual(10, list.GetFirst(), "Append первого элемента - значение");
        assertEqual(10, list.GetLast(), "Append первого элемента - последний");
        printList(&list, "После Append(10)");
        
        list.Append(20);
        assertEqual(static_cast<size_t>(2), list.GetLength(), "Append второго элемента - длина");
        assertEqual(10, list.GetFirst(), "Append второго элемента - первый не изменился");
        assertEqual(20, list.GetLast(), "Append второго элемента - последний обновлен");
        printList(&list, "После Append(20)");
        
        list.Prepend(5);
        assertEqual(static_cast<size_t>(3), list.GetLength(), "Prepend элемента - длина");
        assertEqual(5, list.GetFirst(), "Prepend элемента - новый первый");
        assertEqual(10, list.Get(1), "Prepend элемента - элементы сдвинуты");
        assertEqual(20, list.GetLast(), "Prepend элемента - последний не изменился");
        printList(&list, "После Prepend(5)");
        
        std::cout << "    Ожидаемый результат: [5 ? 10 ? 20]" << std::endl;
    }
    
    void testInsertAt() {
        std::cout << "\n--- Тесты InsertAt LinkedList ---" << std::endl;
        
        LinkedList<int> list;
        for (int i = 1; i <= 5; i++) list.Append(i * 10);
        printList(&list, "Исходный список");
        std::cout << "    Ожидаемый результат: [10 ? 20 ? 30 ? 40 ? 50]" << std::endl;
        
        list.InsertAt(99, 0);
        assertEqual(static_cast<size_t>(6), list.GetLength(), "Вставка в начало - длина");
        assertEqual(99, list.GetFirst(), "Вставка в начало - значение");
        printList(&list, "После InsertAt(99, 0)");
        
        list.InsertAt(88, list.GetLength());
        assertEqual(static_cast<size_t>(7), list.GetLength(), "Вставка в конец - длина");
        assertEqual(88, list.GetLast(), "Вставка в конец - значение");
        printList(&list, "После InsertAt(88, в конец)");
        
        list.InsertAt(77, 3);
        assertEqual(static_cast<size_t>(8), list.GetLength(), "Вставка в середину - длина");
        assertEqual(77, list.Get(3), "Вставка в середину - значение на индексе 3");
        printList(&list, "После InsertAt(77, 3)");
        
        try {
            list.InsertAt(5, 100);
            assertTrue(false, "Вставка за пределами - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Вставка за пределами - исключение перехвачено");
            std::cout << "    Ожидалось исключение IndexOutOfRangeException - получено" << std::endl;
        }
    }
    
    void testGetFirstLast() {
        std::cout << "\n--- Тесты GetFirst/GetLast LinkedList ---" << std::endl;
        
        LinkedList<int> empty;
        try {
            empty.GetFirst();
            assertTrue(false, "GetFirst на пустом списке - должно быть исключение");
        } catch (const EmptyCollectionException&) {
            assertTrue(true, "GetFirst на пустом списке - исключение перехвачено");
        }
        
        try {
            empty.GetLast();
            assertTrue(false, "GetLast на пустом списке - должно быть исключение");
        } catch (const EmptyCollectionException&) {
            assertTrue(true, "GetLast на пустом списке - исключение перехвачено");
        }
        
        LinkedList<int> list;
        list.Append(42);
        assertEqual(42, list.GetFirst(), "GetFirst с одним элементом");
        assertEqual(42, list.GetLast(), "GetLast с одним элементом");
        
        list.Append(100);
        assertEqual(42, list.GetFirst(), "GetFirst после Append");
        assertEqual(100, list.GetLast(), "GetLast после Append");
        
        std::cout << "    Список: [42 ? 100], GetFirst() = 42, GetLast() = 100" << std::endl;
    }
    
    void testGetSubList() {
        std::cout << "\n--- Тесты GetSubList LinkedList ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        LinkedList<int> list(items, 10);
        printList(&list, "Исходный список");
        
        LinkedList<int>* sublist1 = list.GetSubList(0, 4);
        assertEqual(static_cast<size_t>(5), sublist1->GetLength(), "Подсписок [0-4] - длина");
        assertEqual(1, sublist1->GetFirst(), "Подсписок [0-4] - первый элемент");
        assertEqual(5, sublist1->GetLast(), "Подсписок [0-4] - последний элемент");
        printList(sublist1, "Подсписок [0-4]");
        std::cout << "    Ожидаемый результат: [1 ? 2 ? 3 ? 4 ? 5]" << std::endl;
        delete sublist1;
        
        LinkedList<int>* sublist2 = list.GetSubList(5, 9);
        assertEqual(static_cast<size_t>(5), sublist2->GetLength(), "Подсписок [5-9] - длина");
        assertEqual(6, sublist2->GetFirst(), "Подсписок [5-9] - первый элемент");
        assertEqual(10, sublist2->GetLast(), "Подсписок [5-9] - последний элемент");
        printList(sublist2, "Подсписок [5-9]");
        std::cout << "    Ожидаемый результат: [6 ? 7 ? 8 ? 9 ? 10]" << std::endl;
        delete sublist2;
        
        LinkedList<int>* sublist3 = list.GetSubList(3, 6);
        assertEqual(static_cast<size_t>(4), sublist3->GetLength(), "Подсписок [3-6] - длина");
        assertEqual(4, sublist3->GetFirst(), "Подсписок [3-6] - первый элемент");
        assertEqual(7, sublist3->GetLast(), "Подсписок [3-6] - последний элемент");
        printList(sublist3, "Подсписок [3-6]");
        std::cout << "    Ожидаемый результат: [4 ? 5 ? 6 ? 7]" << std::endl;
        delete sublist3;
        
        try {
            list.GetSubList(5, 3);
            assertTrue(false, "GetSubList с неверным диапазоном - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "GetSubList с неверным диапазоном - исключение перехвачено");
        }
    }
    
    void testConcat() {
        std::cout << "\n--- Тесты Concat LinkedList ---" << std::endl;
        
        int items1[] = {1, 2, 3};
        int items2[] = {4, 5, 6};
        LinkedList<int> list1(items1, 3);
        LinkedList<int> list2(items2, 3);
        
        printList(&list1, "Список 1");
        printList(&list2, "Список 2");
        
        LinkedList<int>* combined = list1.Concat(&list2);
        assertEqual(static_cast<size_t>(6), combined->GetLength(), "Concat - правильная длина");
        assertEqual(1, combined->GetFirst(), "Concat - первый элемент из списка 1");
        assertEqual(6, combined->GetLast(), "Concat - последний элемент из списка 2");
        
        printList(combined, "Конкатенированный список");
        std::cout << "    Ожидаемый результат: [1 ? 2 ? 3 ? 4 ? 5 ? 6]" << std::endl;
        delete combined;
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nЗАПУСК ТЕСТОВ LINKED LIST";
        std::cout << "\n========================================";
        
        testConstructor();
        testAppendPrepend();
        testInsertAt();
        testGetFirstLast();
        testGetSubList();
        testConcat();
        
        std::cout << "\n--- Итог ---" << std::endl;
        std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

int main() {
    LinkedListTests tests;
    tests.runAll();
    return 0;
}