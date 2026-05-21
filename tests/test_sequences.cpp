#include <iostream>
#include <string>
#include "../include/arraySequence.hpp"
#include "../include/listSequence.hpp"

class SequenceTests {
private:
    int passed = 0;
    int failed = 0;
    
    template<typename T>
    void assertEqual(T expected, T actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } else {
            std::cout << "  " << testName << " - НЕ ПРОЙДЕН (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "  " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } else {
            std::cout << "  " << testName << " - НЕ ПРОЙДЕН" << std::endl;
            failed++;
        }
    }
    
    template<typename T>
    void printSequence(Sequence<T>* seq, const std::string& label) {
        std::cout << "    " << label << ": [";
        for (int i = 0; i < seq->GetLength(); i++) {
            std::cout << seq->Get(i);
            if (i < seq->GetLength() - 1) std::cout << ", ";
        }
        std::cout << "] (длина: " << seq->GetLength() << ")" << std::endl;
    }
    
public:
    void testArraySequenceConstructors() {
        std::cout << "\n--- Конструкторы ArraySequence ---" << std::endl;
        
        ArraySequence<int> seq1;
        assertEqual(0, seq1.GetLength(), "Конструктор по умолчанию");
        
        int items[] = {10, 20, 30, 40, 50};
        ArraySequence<int> seq2(items, 5);
        assertEqual(5, seq2.GetLength(), "Конструктор из массива - длина");
        assertEqual(10, seq2.GetFirst(), "Первый элемент");
        assertEqual(50, seq2.GetLast(), "Последний элемент");
        assertEqual(30, seq2.Get(2), "Элемент с индексом 2");
        
        printSequence(&seq2, "ArraySequence из массива");
        
        LinkedList<int> list;
        list.Append(1);
        list.Append(2);
        list.Append(3);
        ArraySequence<int> seq3(list);
        assertEqual(3, seq3.GetLength(), "Конструктор из LinkedList");
        printSequence(&seq3, "ArraySequence из LinkedList");
    }
    
    void testListSequenceConstructors() {
        std::cout << "\n--- Конструкторы ListSequence ---" << std::endl;
        
        ListSequence<int> seq1;
        assertEqual(0, seq1.GetLength(), "Конструктор по умолчанию");
        
        int items[] = {5, 15, 25, 35, 45};
        ListSequence<int> seq2(items, 5);
        assertEqual(5, seq2.GetLength(), "Конструктор из массива");
        assertEqual(5, seq2.GetFirst(), "Первый элемент");
        assertEqual(45, seq2.GetLast(), "Последний элемент");
        
        printSequence(&seq2, "ListSequence из массива");
        
        LinkedList<int> list;
        list.Append(100);
        list.Append(200);
        list.Append(300);
        ListSequence<int> seq3(list);
        assertEqual(3, seq3.GetLength(), "Конструктор из LinkedList");
        printSequence(&seq3, "ListSequence из LinkedList");
    }
    
    void testAppendPrependInsert() {
        std::cout << "\n--- Тесты Append/Prepend/Insert ---" << std::endl;
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq;
        arrSeq.Append(10)->Append(20)->Append(30);
        printSequence(&arrSeq, "После Append");
        assertEqual(3, arrSeq.GetLength(), "Append - длина");
        assertEqual(30, arrSeq.GetLast(), "Последний элемент после Append");
        
        arrSeq.Prepend(5);
        printSequence(&arrSeq, "После Prepend(5)");
        assertEqual(4, arrSeq.GetLength(), "Prepend - длина");
        assertEqual(5, arrSeq.GetFirst(), "Первый элемент после Prepend");
        
        arrSeq.InsertAt(99, 2);
        printSequence(&arrSeq, "После InsertAt(99, 2)");
        assertEqual(5, arrSeq.GetLength(), "Insert - длина");
        assertEqual(99, arrSeq.Get(2), "Значение на индексе 2");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq;
        listSeq.Append(10)->Append(20)->Append(30);
        printSequence(&listSeq, "После Append");
        assertEqual(3, listSeq.GetLength(), "Append - длина");
        
        listSeq.Prepend(5);
        printSequence(&listSeq, "После Prepend(5)");
        assertEqual(4, listSeq.GetLength(), "Prepend - длина");
        assertEqual(5, listSeq.GetFirst(), "Первый элемент");
        
        listSeq.InsertAt(99, 2);
        printSequence(&listSeq, "После InsertAt(99, 2)");
        assertEqual(5, listSeq.GetLength(), "Insert - длина");
        assertEqual(99, listSeq.Get(2), "Значение на индексе 2");
    }
    
    void testMap() {
        std::cout << "\n--- Тесты Map (+1 к каждому элементу) ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 5);
        printSequence(&arrSeq, "Исходная");
        
        auto* mapped1 = arrSeq.Map();
        printSequence(mapped1, "Результат Map");
        assertEqual(5, mapped1->GetLength(), "Длина не изменилась");
        assertEqual(2, mapped1->Get(0), "1+1=2");
        assertEqual(3, mapped1->Get(1), "2+1=3");
        assertEqual(4, mapped1->Get(2), "3+1=4");
        assertEqual(5, mapped1->Get(3), "4+1=5");
        assertEqual(6, mapped1->Get(4), "5+1=6");
        delete mapped1;
        
        ArraySequence<int> emptySeq;
        auto* mappedEmpty = emptySeq.Map();
        assertEqual(0, mappedEmpty->GetLength(), "Пустая последовательность");
        delete mappedEmpty;
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 5);
        printSequence(&listSeq, "Исходная");
        
        auto* mapped2 = listSeq.Map();
        printSequence(mapped2, "Результат Map");
        assertEqual(5, mapped2->GetLength(), "Длина не изменилась");
        assertEqual(2, mapped2->Get(0), "1+1=2");
        assertEqual(3, mapped2->Get(1), "2+1=3");
        assertEqual(4, mapped2->Get(2), "3+1=4");
        assertEqual(5, mapped2->Get(3), "4+1=5");
        assertEqual(6, mapped2->Get(4), "5+1=6");
        delete mapped2;
        
        int negItems[] = {-5, -3, -1, 0, 2};
        ListSequence<int> negSeq(negItems, 5);
        auto* mappedNeg = negSeq.Map();
        assertEqual(-4, mappedNeg->Get(0), "-5+1=-4");
        assertEqual(-2, mappedNeg->Get(1), "-3+1=-2");
        assertEqual(0, mappedNeg->Get(2), "-1+1=0");
        assertEqual(1, mappedNeg->Get(3), "0+1=1");
        assertEqual(3, mappedNeg->Get(4), "2+1=3");
        delete mappedNeg;
    }
    
    void testWhere() {
        std::cout << "\n--- Тесты Where (только четные числа) ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 10);
        printSequence(&arrSeq, "Исходная");
        
        auto* filtered1 = arrSeq.Where();
        printSequence(filtered1, "Результат Where");
        assertEqual(5, filtered1->GetLength(), "Только четные числа");
        assertEqual(2, filtered1->Get(0), "Первый четный = 2");
        assertEqual(4, filtered1->Get(1), "Второй четный = 4");
        assertEqual(6, filtered1->Get(2), "Третий четный = 6");
        assertEqual(8, filtered1->Get(3), "Четвертый четный = 8");
        assertEqual(10, filtered1->Get(4), "Пятый четный = 10");
        delete filtered1;
        
        int oddItems[] = {1, 3, 5, 7, 9};
        ArraySequence<int> oddSeq(oddItems, 5);
        auto* filteredOdd = oddSeq.Where();
        assertEqual(0, filteredOdd->GetLength(), "Нет четных чисел");
        delete filteredOdd;
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 10);
        
        auto* filtered2 = listSeq.Where();
        printSequence(filtered2, "Результат Where");
        assertEqual(5, filtered2->GetLength(), "Только четные числа");
        assertEqual(2, filtered2->Get(0), "Первый четный = 2");
        assertEqual(4, filtered2->Get(1), "Второй четный = 4");
        assertEqual(6, filtered2->Get(2), "Третий четный = 6");
        assertEqual(8, filtered2->Get(3), "Четвертый четный = 8");
        assertEqual(10, filtered2->Get(4), "Пятый четный = 10");
        delete filtered2;
        
        int evenItems[] = {2, 4, 6, 8, 10};
        ListSequence<int> evenSeq(evenItems, 5);
        auto* filteredEven = evenSeq.Where();
        assertEqual(5, filteredEven->GetLength(), "Все числа четные");
        delete filteredEven;
    }
    
    void testReduce() {
        std::cout << "\n--- Тесты Reduce (сумма всех элементов) ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 5);
        printSequence(&arrSeq, "Последовательность");
        
        int sum = arrSeq.Reduce();
        assertEqual(15, sum, "Сумма = 15");
        
        ArraySequence<int> emptySeq;
        int sumEmpty = emptySeq.Reduce();
        assertEqual(0, sumEmpty, "Пустая последовательность - сумма = 0");
        
        int singleItem[] = {42};
        ArraySequence<int> singleSeq(singleItem, 1);
        int sumSingle = singleSeq.Reduce();
        assertEqual(42, sumSingle, "Один элемент - сумма = 42");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 5);
        printSequence(&listSeq, "Последовательность");
        
        int sum2 = listSeq.Reduce();
        assertEqual(15, sum2, "Сумма = 15");
        
        int negItems[] = {-5, -3, 10, -2, 5};
        ListSequence<int> negSeq(negItems, 5);
        int sumNeg = negSeq.Reduce();
        assertEqual(5, sumNeg, "Сумма с отрицательными = 5");
        
        int largeItems[] = {1000, 2000, 3000, 4000, 5000};
        ListSequence<int> largeSeq(largeItems, 5);
        int sumLarge = largeSeq.Reduce();
        assertEqual(15000, sumLarge, "Сумма больших чисел = 15000");
    }
    
    void testFind() {
        std::cout << "\n--- Тесты Find (поиск значения 3) ---" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 5);
        printSequence(&arrSeq, "Последовательность");
        
        Option<int> found1 = arrSeq.Find([](int x) { return x == 30; });
        assertTrue(found1.IsSome(), "Поиск существующего значения");
        assertEqual(30, found1.GetValue(), "Найденное значение");
        
        Option<int> found2 = arrSeq.Find([](int x) { return x == 100; });
        assertTrue(found2.IsNone(), "Поиск несуществующего значения");
        
        Option<int> found3 = arrSeq.Find([](int x) { return x == 3; });
        assertTrue(found3.IsNone(), "Поиск значения 3 - не найдено");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 5);
        
        Option<int> found4 = listSeq.Find([](int x) { return x == 50; });
        assertTrue(found4.IsSome(), "Поиск последнего элемента");
        assertEqual(50, found4.GetValue(), "Найденное значение");
        
        Option<int> found5 = listSeq.Find([](int x) { return x == 3; });
        assertTrue(found5.IsNone(), "Поиск значения 3 - не найдено");
    }
    
    void testGetSubsequence() {
        std::cout << "\n--- Тесты GetSubsequence ---" << std::endl;
        
        int items[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 10);
        printSequence(&arrSeq, "Исходная");
        
        auto* sub1 = arrSeq.GetSubsequence(2, 6);
        printSequence(sub1, "Подпоследовательность [2-6]");
        assertEqual(5, sub1->GetLength(), "Длина");
        assertEqual(300, sub1->Get(0), "Начало на индексе 2");
        assertEqual(700, sub1->Get(4), "Конец на индексе 6");
        delete sub1;
        
        auto* sub2 = arrSeq.GetSubsequence(0, 4);
        printSequence(sub2, "Подпоследовательность [0-4]");
        assertEqual(5, sub2->GetLength(), "Длина");
        assertEqual(100, sub2->GetFirst(), "Первый элемент");
        delete sub2;
        
        try {
            arrSeq.GetSubsequence(5, 2);
            assertTrue(false, "Неверный диапазон");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Неверный диапазон - исключение");
        }
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 10);
        
        auto* sub3 = listSeq.GetSubsequence(3, 8);
        printSequence(sub3, "Подпоследовательность [3-8]");
        assertEqual(6, sub3->GetLength(), "Длина");
        assertEqual(400, sub3->GetFirst(), "Начало на индексе 3");
        assertEqual(900, sub3->GetLast(), "Конец на индексе 8");
        delete sub3;
    }
    
    void testCombinedOperations() {
        std::cout << "\n--- Комплексный тест ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 10);
        printSequence(&arrSeq, "Исходная");
        
        auto* evens = arrSeq.Where();
        printSequence(evens, "Where (четные)");
        
        auto* mapped = evens->Map();
        printSequence(mapped, "Map (+1)");
        
        int sum = mapped->Reduce();
        assertEqual(35, sum, "Сумма = 35");
        
        delete evens;
        delete mapped;
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 10);
        printSequence(&listSeq, "Исходная");
        
        auto* mapped2 = listSeq.Map();
        printSequence(mapped2, "Map (+1)");
        
        auto* evens2 = mapped2->Where();
        printSequence(evens2, "Where (четные)");
        
        int sum2 = evens2->Reduce();
        assertEqual(30, sum2, "Сумма = 30");
        
        delete mapped2;
        delete evens2;
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nТЕСТЫ ПОСЛЕДОВАТЕЛЬНОСТЕЙ";
        std::cout << "\n========================================";
        
        testArraySequenceConstructors();
        testListSequenceConstructors();
        testAppendPrependInsert();
        testMap();
        testWhere();
        testReduce();
        testFind();
        testGetSubsequence();
        testCombinedOperations();
        
        std::cout << "\n--- Результат ---" << std::endl;
        std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

int main() {
    SequenceTests tests;
    tests.runAll();
    return 0;
}