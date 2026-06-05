#include <iostream>
#include <string>
#include "../include/setSequence.hpp"

class SetSequenceTests {
private:
    int passed = 0;
    int failed = 0;
    
    void assertEqual(int expected, int actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  [OK] " << testName << std::endl;
            passed++;
        } else {
            std::cout << "  [FAIL] " << testName << " (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertEqual(size_t expected, size_t actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  [OK] " << testName << std::endl;
            passed++;
        } else {
            std::cout << "  [FAIL] " << testName << " (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "  [OK] " << testName << std::endl;
            passed++;
        } else {
            std::cout << "  [FAIL] " << testName << std::endl;
            failed++;
        }
    }
    
    template<typename T>
    void printSet(SetSequence<T>* set, const std::string& label) {
        std::cout << "    " << label << ": {";
        for (size_t i = 0; i < set->GetLength(); i++) {
            std::cout << set->Get(i);
            if (i < set->GetLength() - 1) std::cout << ", ";
        }
        std::cout << "} (размер: " << set->GetLength() << ")" << std::endl;
    }
    
public:
    void testConstructorAndUniqueness() {
        std::cout << "\n--- Тесты конструкторов и уникальности SetSequence ---" << std::endl;
        
        SetSequence<int> set1;
        assertEqual(0u, set1.GetLength(), "Конструктор по умолчанию - пустое множество");
        
        int itemsWithDups[] = {1, 2, 2, 3, 3, 3, 4, 5, 5};
        SetSequence<int> set2(itemsWithDups, 9);
        assertEqual(5u, set2.GetLength(), "Конструктор из массива - дубликаты удалены");
        assertEqual(1, set2.Get(0), "Элемент 1 присутствует");
        assertEqual(2, set2.Get(1), "Элемент 2 присутствует");
        assertEqual(3, set2.Get(2), "Элемент 3 присутствует");
        assertEqual(4, set2.Get(3), "Элемент 4 присутствует");
        assertEqual(5, set2.Get(4), "Элемент 5 присутствует");
        
        printSet(&set2, "Множество из массива с дубликатами");
        
        LinkedList<int> list;
        list.Append(10);
        list.Append(20);
        list.Append(20);
        list.Append(30);
        list.Append(10);
        SetSequence<int> set3(list);
        assertEqual(3u, set3.GetLength(), "Конструктор из LinkedList - дубликаты удалены");
        printSet(&set3, "Множество из LinkedList");
        
        SetSequence<int> set5(set2);
        assertEqual(5u, set5.GetLength(), "Конструктор копирования - размер скопирован");
        assertEqual(1, set5.Get(0), "Конструктор копирования - элемент 1");
        printSet(&set5, "Копия множества");
    }
    
    void testAppendUniqueness() {
        std::cout << "\n--- Тесты Append (добавление с проверкой уникальности) ---" << std::endl;
        
        SetSequence<int> set;
        SetSequence<int>* s1 = set.Append(10);
        SetSequence<int>* s2 = s1->Append(20);
        SetSequence<int>* s3 = s2->Append(30);
        
        printSet(s3, "После добавления 10, 20, 30");
        assertEqual(3u, s3->GetLength(), "3 уникальных элемента");
        assertEqual(10, s3->Get(0), "Элемент 0 = 10");
        assertEqual(20, s3->Get(1), "Элемент 1 = 20");
        assertEqual(30, s3->Get(2), "Элемент 2 = 30");
        
        SetSequence<int>* newSet = s3->Append(20);
        printSet(newSet, "После Append(20) (дубликат)");
        assertEqual(3u, newSet->GetLength(), "Дубликат не добавлен - размер не изменился");
        
        SetSequence<int>* newSet2 = s3->Append(40);
        printSet(newSet2, "После Append(40) (новый элемент)");
        assertEqual(4u, newSet2->GetLength(), "Новый элемент добавлен");
        assertEqual(40, newSet2->Get(3), "40 добавлен в конец");
        
        delete s1;
        delete s2;
        delete s3;
        delete newSet;
        delete newSet2;
    }
    
    void testMap() {
        std::cout << "\n--- Тесты Map (прибавление 1) ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        SetSequence<int> set(items, 5);
        printSet(&set, "Исходное множество");
        
        SetSequence<int>* mapped = set.Map();
        printSet(mapped, "Результат Map (+1)");
        
        assertEqual(5u, mapped->GetLength(), "Размер не изменился");
        assertEqual(2, mapped->Get(0), "1+1=2");
        assertEqual(3, mapped->Get(1), "2+1=3");
        assertEqual(4, mapped->Get(2), "3+1=4");
        assertEqual(5, mapped->Get(3), "4+1=5");
        assertEqual(6, mapped->Get(4), "5+1=6");
        
        delete mapped;
        
        SetSequence<int> emptySet;
        SetSequence<int>* mappedEmpty = emptySet.Map();
        assertEqual(0u, mappedEmpty->GetLength(), "Map пустого множества = пустое");
        delete mappedEmpty;
    }
    
    void testWhere() {
        std::cout << "\n--- Тесты Where (фильтр чётных чисел) ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        SetSequence<int> set(items, 10);
        printSet(&set, "Исходное множество");
        
        SetSequence<int>* evens = set.Where();
        printSet(evens, "Чётные числа");
        
        assertEqual(5u, evens->GetLength(), "5 чётных чисел");
        assertEqual(2, evens->Get(0), "2");
        assertEqual(4, evens->Get(1), "4");
        assertEqual(6, evens->Get(2), "6");
        assertEqual(8, evens->Get(3), "8");
        assertEqual(10, evens->Get(4), "10");
        
        delete evens;
        
        int oddsOnly[] = {1, 3, 5, 7, 9};
        SetSequence<int> oddsSet(oddsOnly, 5);
        SetSequence<int>* noEvens = oddsSet.Where();
        assertEqual(0u, noEvens->GetLength(), "Нет чётных чисел -> пустое множество");
        delete noEvens;
    }
    
    void testReduce() {
        std::cout << "\n--- Тесты Reduce (сумма элементов) ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        SetSequence<int> set(items, 5);
        printSet(&set, "Множество");
        
        int sum = set.Reduce();
        assertEqual(15, sum, "Сумма = 1+2+3+4+5 = 15");
        
        SetSequence<int> emptySet;
        int sumEmpty = emptySet.Reduce();
        assertEqual(0, sumEmpty, "Пустое множество -> сумма = 0");
        
        int singleItem[] = {42};
        SetSequence<int> singleSet(singleItem, 1);
        int sumSingle = singleSet.Reduce();
        assertEqual(42, sumSingle, "Один элемент -> сумма = 42");
    }
    
    void testFind() {
        std::cout << "\n--- Тесты Find (поиск значения 3) ---" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        SetSequence<int> set(items, 5);
        printSet(&set, "Множество");
        
        Option<int> found1 = set.Find();
        assertTrue(found1.IsNone(), "Поиск 3 - не найдено");
        
        int itemsWith3[] = {10, 20, 3, 40, 50};
        SetSequence<int> setWith3(itemsWith3, 5);
        printSet(&setWith3, "Множество с 3");
        
        Option<int> found2 = setWith3.Find();
        assertTrue(found2.IsSome(), "Поиск существующего 3");
        assertEqual(3, found2.GetValue(), "Найдено значение 3");
        
        SetSequence<int> emptySet;
        Option<int> foundEmpty = emptySet.Find();
        assertTrue(foundEmpty.IsNone(), "Пустое множество - ничего не найдено");
    }
    
    void testGetSubsequence() {
        std::cout << "\n--- Тесты GetSubsequence ---" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        SetSequence<int> set(items, 10);
        printSet(&set, "Исходное множество");
        
        SetSequence<int>* sub1 = set.GetSubsequence(2, 6);
        printSet(sub1, "Подмножество [2-6]");
        assertEqual(5u, sub1->GetLength(), "Длина = 5");
        assertEqual(30, sub1->Get(0), "Элемент на индексе 2 = 30");
        assertEqual(70, sub1->Get(4), "Элемент на индексе 6 = 70");
        delete sub1;
        
        SetSequence<int>* sub2 = set.GetSubsequence(0, 4);
        printSet(sub2, "Подмножество [0-4]");
        assertEqual(5u, sub2->GetLength(), "Длина = 5");
        assertEqual(10, sub2->GetFirst(), "Первый элемент = 10");
        assertEqual(50, sub2->GetLast(), "Последний элемент = 50");
        delete sub2;
        
        try {
            set.GetSubsequence(5, 2);
            assertTrue(false, "Неверный диапазон - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Неверный диапазон - исключение перехвачено");
        }
    }
    
    void testConcat() {
        std::cout << "\n--- Тесты Concat (объединение последовательностей с уникальностью) ---" << std::endl;
        
        int items1[] = {1, 2, 3, 4, 5};
        int items2[] = {4, 5, 6, 7, 8};
        SetSequence<int> set1(items1, 5);
        SetSequence<int> set2(items2, 5);
        
        printSet(&set1, "Множество 1");
        printSet(&set2, "Множество 2");
        
        SetSequence<int>* concatSet = set1.Concat(&set2);
        printSet(concatSet, "Concat (объединение)");
        
        assertEqual(8u, concatSet->GetLength(), "Размер = 8 (без дубликатов)");
        assertEqual(1, concatSet->Get(0), "1");
        assertEqual(2, concatSet->Get(1), "2");
        assertEqual(3, concatSet->Get(2), "3");
        assertEqual(4, concatSet->Get(3), "4");
        assertEqual(5, concatSet->Get(4), "5");
        assertEqual(6, concatSet->Get(5), "6");
        assertEqual(7, concatSet->Get(6), "7");
        assertEqual(8, concatSet->Get(7), "8");
        
        delete concatSet;
        
        SetSequence<int> emptySet;
        SetSequence<int>* concatEmpty = set1.Concat(&emptySet);
        assertEqual(5u, concatEmpty->GetLength(), "Concat с пустым = исходное");
        delete concatEmpty;
    }
    
    void testGetFirstLast() {
        std::cout << "\n--- Тесты GetFirst/GetLast ---" << std::endl;
        
        int items[] = {100, 200, 300, 400, 500};
        SetSequence<int> set(items, 5);
        printSet(&set, "Множество");
        
        assertEqual(100, set.GetFirst(), "GetFirst = 100");
        assertEqual(500, set.GetLast(), "GetLast = 500");
        
        SetSequence<int> emptySet;
        try {
            emptySet.GetFirst();
            assertTrue(false, "GetFirst на пустом множестве - должно быть исключение");
        } catch (const EmptyCollectionException&) {
            assertTrue(true, "GetFirst на пустом - исключение перехвачено");
        }
        
        try {
            emptySet.GetLast();
            assertTrue(false, "GetLast на пустом множестве - должно быть исключение");
        } catch (const EmptyCollectionException&) {
            assertTrue(true, "GetLast на пустом - исключение перехвачено");
        }
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nТЕСТЫ SET SEQUENCE (МНОЖЕСТВО)";
        std::cout << "\n========================================";
        
        testConstructorAndUniqueness();
        testAppendUniqueness();
        testMap();
        testWhere();
        testReduce();
        testFind();
        testGetSubsequence();
        testConcat();
        testGetFirstLast();
        
        std::cout << "\n--- Результат ---" << std::endl;
        std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

int main() {
    SetSequenceTests tests;
    tests.runAll();
    return 0;
}


