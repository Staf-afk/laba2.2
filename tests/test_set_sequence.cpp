#include <iostream>
#include <string>
#include "../include/setSequence.hpp"
#include "../include/setTypes.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

class SetSequenceTests {
private:
    int passed = 0;
    int failed = 0;
    
    template<typename T>
    void assertEqual(T expected, T actual, const std::string& testName) {
        if (expected == actual) {
            std::cout <<GREEN << "  [PASS] " << RESET << testName << std::endl;
            passed++;
        } else {
            std::cout << RED << "  [FAIL] " << RESET << testName << " (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertEqual(size_t expected, size_t actual, const std::string& testName) {
        if (expected == actual) {
            std::cout <<GREEN << "  [PASS] " << RESET << testName << std::endl;
            passed++;
        } else {
            std::cout << RED << "  [FAIL] " << RESET << testName << " (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout <<GREEN << "  [PASS] " << RESET << testName << std::endl;
            passed++;
        } else {
            std::cout << RED << "  [FAIL] " << RESET << testName << std::endl;
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
    
    void printPersonSet(SetSequence<Person>* set, const std::string& label) {
        std::cout << "    " << label << ": {";
        for (size_t i = 0; i < set->GetLength(); i++) {
            std::cout << set->Get(i).GetFullName();
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
        std::cout << "\n--- Тесты Map ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        SetSequence<int> set(items, 5);
        printSet(&set, "Исходное множество");
        
        auto* mapped = set.Map([](int x) { return x + 1; });
        printSet(mapped, "Результат Map (+1)");
        
        assertEqual(5u, mapped->GetLength(), "Размер не изменился");
        assertEqual(2, mapped->Get(0), "1+1=2");
        assertEqual(6, mapped->Get(4), "5+1=6");
        
        delete mapped;
    }
    
    void testWhere() {
        std::cout << "\n--- Тесты Where ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        SetSequence<int> set(items, 10);
        printSet(&set, "Исходное множество");
        
        auto* evens = set.Where([](int x) { return x % 2 == 0; });
        printSet(evens, "Чётные числа");
        
        assertEqual(5u, evens->GetLength(), "5 чётных чисел");
        
        delete evens;
    }
    
    void testReduce() {
        std::cout << "\n--- Тесты Reduce ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        SetSequence<int> set(items, 5);
        printSet(&set, "Множество");
        
        int sum = set.Reduce([](int a, int b) { return a + b; }, 0);
        assertEqual(15, sum, "Сумма = 15");
        
        int product = set.Reduce([](int a, int b) { return a * b; }, 1);
        assertEqual(120, product, "Произведение = 120");
    }
    
    void testFind() {
        std::cout << "\n--- Тесты Find ---" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        SetSequence<int> set(items, 5);
        printSet(&set, "Множество");
        
        auto found1 = set.Find([](int x) { return x == 3; });
        assertTrue(found1.IsNone(), "Поиск 3 - не найдено");
        
        int itemsWith3[] = {10, 20, 3, 40, 50};
        SetSequence<int> setWith3(itemsWith3, 5);
        
        auto found2 = setWith3.Find([](int x) { return x == 3; });
        assertTrue(found2.IsSome(), "Поиск существующего 3");
        assertEqual(3, found2.GetValue(), "Найдено значение 3");
        
        SetSequence<int> emptySet;
        auto foundEmpty = emptySet.Find([](int x) { return x == 3; });
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
    
    void testIntSet() {
        std::cout << "\n--- Тесты SetSequence<int> ---" << std::endl;
        
        int items[] = {1, 2, 2, 3, 3, 3, 4, 5, 5};
        SetSequence<int> set(items, 9);
        assertEqual(5u, set.GetLength(), "int - конструктор с дубликатами");
        
        auto* newSet = set.Append(6);
        assertEqual(6u, newSet->GetLength(), "int - Append нового элемента");
        
        auto* dupSet = newSet->Append(3);
        assertEqual(6u, dupSet->GetLength(), "int - Append дубликата");
        
        int sum = dupSet->Reduce([](int a, int b) { return a + b; }, 0);
        assertEqual(21, sum, "int - сумма элементов");
        
        delete newSet;
        delete dupSet;
    }
    
    void testDoubleSet() {
        std::cout << "\n--- Тесты SetSequence<double> ---" << std::endl;
        
        double items[] = {1.1, 2.2, 2.2, 3.3, 4.4, 4.4, 5.5};
        SetSequence<double> set(items, 7);
        assertEqual(5u, set.GetLength(), "double - конструктор с дубликатами");
        
        auto* newSet = set.Append(6.6);
        assertEqual(6u, newSet->GetLength(), "double - Append нового элемента");
        
        auto* dupSet = newSet->Append(3.3);
        assertEqual(6u, dupSet->GetLength(), "double - Append дубликата");
        
        double sum = dupSet->Reduce([](double a, double b) { return a + b; }, 0.0);
        assertEqual(23.1, sum, "double - сумма элементов");
        
        delete newSet;
        delete dupSet;
    }
    
    void testComplexSet() {
        std::cout << "\n--- Тесты SetSequence<Complex> ---" << std::endl;
        
        Complex items[] = {
            Complex(1, 1), Complex(2, 2), Complex(2, 2),
            Complex(3, 3), Complex(1, 1), Complex(4, 4)
        };
        SetSequence<Complex> set(items, 6);
        assertEqual(4u, set.GetLength(), "Complex - конструктор с дубликатами");
        
        auto* newSet = set.Append(Complex(5, 5));
        assertEqual(5u, newSet->GetLength(), "Complex - Append нового элемента");
        
        auto* dupSet = newSet->Append(Complex(2, 2));
        assertEqual(5u, dupSet->GetLength(), "Complex - Append дубликата");
        
        delete newSet;
        delete dupSet;
    }
    
    void testStringSet() {
        std::cout << "\n--- Тесты SetSequence<std::string> ---" << std::endl;
        
        std::string items[] = {"apple", "banana", "apple", "cherry", "banana", "date"};
        SetSequence<std::string> set(items, 6);
        assertEqual(4u, set.GetLength(), "string - конструктор с дубликатами");
        
        auto* newSet = set.Append("elderberry");
        assertEqual(5u, newSet->GetLength(), "string - Append нового элемента");
        
        auto* dupSet = newSet->Append("apple");
        assertEqual(5u, dupSet->GetLength(), "string - Append дубликата");
        
        delete newSet;
        delete dupSet;
    }
    
    void testFunctionSet() {
        std::cout << "\n--- Тесты SetSequence<FunctionWrapper<int>> ---" << std::endl;
        
        FunctionWrapper<int> square(squareInt, "square");
        FunctionWrapper<int> doubleFunc(doubleInt, "double");
        FunctionWrapper<int> square2(squareInt, "square"); 
        
        FunctionWrapper<int> items[] = {square, doubleFunc, square2, doubleFunc};
        SetSequence<FunctionWrapper<int>> set(items, 4);
        
        assertEqual(2u, set.GetLength(), "Function - конструктор с дубликатами");
        
        FunctionWrapper<int> newFunc([](int x) { return x + 10; }, "add10");
        auto* newSet = set.Append(newFunc);
        assertEqual(3u, newSet->GetLength(), "Function - Append новой функции");
        
        auto* dupSet = newSet->Append(square);
        assertEqual(3u, dupSet->GetLength(), "Function - Append дубликата");
        
        assertEqual(25, square(5), "Function - вызов square(5)=25");
        assertEqual(10, doubleFunc(5), "Function - вызов double(5)=10");
        
        delete newSet;
        delete dupSet;
    }
    
    void testPersonSet() {
        std::cout << "\n--- Тесты SetSequence<Person> ---" << std::endl;
        
        PersonID id1(1234, 100);
        PersonID id2(1234, 101);
        PersonID id3(1235, 200);
        PersonID id4(1234, 100);
        
        Person items[] = {
            Person(id1, "Иван", "Иванов"),
            Person(id2, "Пётр", "Петров"),
            Person(id3, "Сидор", "Сидоров"),
            Person(id4, "Иван", "Иванов"),
            Person(id2, "Пётр", "Петров")
        };
        
        SetSequence<Person> set(items, 5);
        assertEqual(3u, set.GetLength(), "Person - конструктор с дубликатами");
        
        PersonID id5(1236, 300);
        Person newPerson(id5, "Анна", "Смирнова");
        auto* newSet = set.Append(newPerson);
        assertEqual(4u, newSet->GetLength(), "Person - Append нового элемента");
        
        auto* dupSet = newSet->Append(items[0]);
        assertEqual(4u, dupSet->GetLength(), "Person - Append дубликата");
        
        delete newSet;
        delete dupSet;
    }
    
    void testPairSet() {
        std::cout << "\n--- Тесты SetSequence<Pair<int, std::string>> ---" << std::endl;
        
        Pair<int, std::string> p1(1, "one");
        Pair<int, std::string> p2(2, "two");
        Pair<int, std::string> p3(3, "three");
        Pair<int, std::string> p4(1, "one");
        
        Pair<int, std::string> items[] = {p1, p2, p3, p4, p2};
        SetSequence<Pair<int, std::string>> set(items, 5);
        assertEqual(3u, set.GetLength(), "Pair - конструктор с дубликатами");
        
        Pair<int, std::string> p5(4, "four");
        auto* newSet = set.Append(p5);
        assertEqual(4u, newSet->GetLength(), "Pair - Append нового элемента");
        
        auto* dupSet = newSet->Append(p1);
        assertEqual(4u, dupSet->GetLength(), "Pair - Append дубликата");
        
        assertEqual(1, dupSet->Get(0).GetFirst(), "Pair - GetFirst");
        assertEqual(std::string("one"), dupSet->Get(0).GetSecond(), "Pair - GetSecond");
        
        delete newSet;
        delete dupSet;
    }
    
    void testEdgeCases() {
        std::cout << "\n--- Тесты граничных случаев ---" << std::endl;
        
        SetSequence<int> emptySet;
        assertEqual(0u, emptySet.GetLength(), "Пустое множество - размер 0");
        
        try {
            emptySet.GetFirst();
            assertTrue(false, "GetFirst на пустом - исключение");
        } catch (const EmptyCollectionException&) {
            assertTrue(true, "GetFirst на пустом - исключение перехвачено");
        }
        
        try {
            emptySet.GetLast();
            assertTrue(false, "GetLast на пустом - исключение");
        } catch (const EmptyCollectionException&) {
            assertTrue(true, "GetLast на пустом - исключение перехвачено");
        }
        
        int singleItem[] = {42};
        SetSequence<int> singleSet(singleItem, 1);
        assertEqual(42, singleSet.GetFirst(), "Один элемент - GetFirst");
        assertEqual(42, singleSet.GetLast(), "Один элемент - GetLast");
        
        int items[] = {10, 20, 30, 40, 50};
        SetSequence<int> set(items, 5);
        auto* subseq = set.GetSubsequence(1, 3);
        assertEqual(3u, subseq->GetLength(), "GetSubsequence - длина");
        assertEqual(20, subseq->Get(0), "GetSubsequence - первый элемент");
        assertEqual(40, subseq->Get(2), "GetSubsequence - последний элемент");
        delete subseq;
        
        try {
            set.GetSubsequence(3, 1);
            assertTrue(false, "Неверный диапазон - исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Неверный диапазон - исключение перехвачено");
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
        
        testIntSet();
        testDoubleSet();
        testComplexSet();
        testStringSet();
        testFunctionSet();
        testPersonSet();
        testPairSet();
        
        testEdgeCases();
        
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

