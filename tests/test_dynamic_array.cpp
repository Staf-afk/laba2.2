#include <iostream>
#include <string>
#include "../include/dynamicArray.hpp"

class DynamicArrayTests {
private:
    int passed = 0;
    int failed = 0;
    
    void assertEqual(int expected, int actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  ? " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } 
        else {
            std::cout << "  ? " << testName << " - НЕ ПРОЙДЕН (Ожидалось: " << expected 
                      << ", Получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertEqual(size_t expected, size_t actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  ? " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } 
        else {
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
    
    void printArray(DynamicArray<int>& arr, const std::string& label) {
        std::cout << "    " << label << ": [";
        for (size_t i = 0; i < static_cast<size_t>(arr.GetSize()); i++) {
            std::cout << arr.Get(i);
            if (i < arr.GetSize() - 1) std::cout << ", ";
        }
        std::cout << "] (размер: " << arr.GetSize() << ")" << std::endl;
    }
    
public:
    void testConstructor() {
        std::cout << "\n--- Тесты конструкторов DynamicArray ---" << std::endl;
        
        DynamicArray<int> arr1;
        assertEqual(static_cast<size_t>(0), arr1.GetSize(), "Конструктор по умолчанию - размер");
        
        DynamicArray<int> arr2(5);
        assertEqual(static_cast<size_t>(5), arr2.GetSize(), "Конструктор с размером - размер");
        
        int items[] = {1, 2, 3, 4, 5};
        DynamicArray<int> arr3(items, 5);
        assertEqual(static_cast<size_t>(5), arr3.GetSize(), "Конструктор из массива - размер");
        assertEqual(1, arr3.Get(0), "Конструктор из массива - элемент 0");
        assertEqual(3, arr3.Get(2), "Конструктор из массива - элемент 2");
        assertEqual(5, arr3.Get(4), "Конструктор из массива - элемент 4");
        
        std::cout << "    Входные данные: [1, 2, 3, 4, 5]" << std::endl;
        printArray(arr3, "Созданный массив");
        
        DynamicArray<int> arr4(arr3);
        assertEqual(static_cast<size_t>(5), arr4.GetSize(), "Конструктор копирования - размер");
        assertEqual(1, arr4.Get(0), "Конструктор копирования - элемент 0");
    }
    
    void testGetSet() {
        std::cout << "\n--- Тесты Get/Set DynamicArray ---" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        DynamicArray<int> arr(items, 5);
        
        std::cout << "    Исходный массив: [10, 20, 30, 40, 50]" << std::endl;
        
        assertEqual(10, arr.Get(0), "Get(0) начальное значение");
        assertEqual(30, arr.Get(2), "Get(2) начальное значение");
        assertEqual(50, arr.Get(4), "Get(4) начальное значение");
        
        arr.Set(1, 99);
        assertEqual(99, arr.Get(1), "Set(1, 99) - новое значение");
        std::cout << "    После Set(1, 99): [10, 99, 30, 40, 50]" << std::endl;
        
        arr.Set(3, 100);
        assertEqual(100, arr.Get(3), "Set(3, 100) - новое значение");
        
        try {
            arr.Get(10);
            assertTrue(false, "Get за пределами - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Get за пределами - исключение перехвачено");
            std::cout << "    Ожидалось исключение IndexOutOfRangeException - получено" << std::endl;
        }
        
        try {
            arr.Set(10, 5);
            assertTrue(false, "Set за пределами - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Set за пределами - исключение перехвачено");
        }
    }
    
    void testResize() {
        std::cout << "\n--- Тесты Resize DynamicArray ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        DynamicArray<int> arr(items, 5);
        
        std::cout << "    Исходный массив: [1, 2, 3, 4, 5]" << std::endl;
        
        arr.Resize(8);
        assertEqual(static_cast<size_t>(8), arr.GetSize(), "Увеличение размера до 8 - новый размер");
        assertEqual(1, arr.Get(0), "Увеличение размера - элементы сохранены");
        assertEqual(5, arr.Get(4), "Увеличение размера - последний элемент сохранен");
        assertEqual(0, arr.Get(7), "Увеличение размера - новые элементы обнулены");
        std::cout << "    После Resize(8): [1, 2, 3, 4, 5, 0, 0, 0]" << std::endl;
        
        arr.Resize(3);
        assertEqual(static_cast<size_t>(3), arr.GetSize(), "Уменьшение размера до 3 - новый размер");
        assertEqual(1, arr.Get(0), "Уменьшение размера - первые элементы сохранены");
        assertEqual(3, arr.Get(2), "Уменьшение размера - обрезано корректно");
        std::cout << "    После Resize(3): [1, 2, 3]" << std::endl;
        
        try {
            arr.Resize(static_cast<size_t>(-1));
            assertTrue(false, "Resize с отрицательным размером - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Resize с отрицательным размером - исключение перехвачено");
        }
    }
    
    void testEdgeCases() {
        std::cout << "\n--- Тесты граничных случаев DynamicArray ---" << std::endl;
        
        DynamicArray<int> empty;
        assertEqual(static_cast<size_t>(0), empty.GetSize(), "Пустой массив - размер");
        std::cout << "    Пустой массив создан успешно" << std::endl;
        
        DynamicArray<int> single(1);
        single.Set(0, 42);
        assertEqual(42, single.Get(0), "Массив из одного элемента - установка и получение");
        std::cout << "    Массив из одного элемента: [42]" << std::endl;
        
        int items[] = {7};
        DynamicArray<int> singleFromArray(items, 1);
        assertEqual(7, singleFromArray.Get(0), "Массив из одного элемента из массива");
        
        DynamicArray<int> zeroSize(0);
        assertEqual(static_cast<size_t>(0), zeroSize.GetSize(), "Массив нулевого размера");
    }
    
    void testAssignment() {
        std::cout << "\n--- Тесты оператора присваивания DynamicArray ---" << std::endl;
        
        int items[] = {10, 20, 30};
        DynamicArray<int> arr1(items, 3);
        DynamicArray<int> arr2;
        
        std::cout << "    arr1: [10, 20, 30]" << std::endl;
        std::cout << "    arr2: []" << std::endl;
        
        arr2 = arr1;
        assertEqual(static_cast<size_t>(3), arr2.GetSize(), "Присваивание - размер скопирован");
        assertEqual(10, arr2.Get(0), "Присваивание - элемент 0 скопирован");
        assertEqual(30, arr2.Get(2), "Присваивание - элемент 2 скопирован");
        
        std::cout << "    После arr2 = arr1: arr2 = [10, 20, 30]" << std::endl;
        
        arr2.Set(1, 99);
        assertEqual(20, arr1.Get(1), "Присваивание - глубокая копия (оригинал не изменился)");
        std::cout << "    arr2 изменен, arr1 остался неизменным - глубокая копия" << std::endl;
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nЗАПУСК ТЕСТОВ DYNAMIC ARRAY";
        std::cout << "\n========================================";
        
        testConstructor();
        testGetSet();
        testResize();
        testEdgeCases();
        testAssignment();
        
        std::cout << "\n--- Итог ---" << std::endl;
        std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

int main() {
    DynamicArrayTests tests;
    tests.runAll();
    return 0;
}