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
        std::cout << "\n--- Тесты конструкторов ArraySequence ---" << std::endl;
        
        ArraySequence<int> seq1;
        assertEqual(0, seq1.GetLength(), "Конструктор по умолчанию - длина");
        std::cout << "    Создана пустая последовательность" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        ArraySequence<int> seq2(items, 5);
        assertEqual(5, seq2.GetLength(), "Конструктор из массива - длина");
        assertEqual(10, seq2.GetFirst(), "Конструктор из массива - первый");
        assertEqual(50, seq2.GetLast(), "Конструктор из массива - последний");
        assertEqual(30, seq2.Get(2), "Конструктор из массива - индекс 2");
        
        std::cout << "    Входные данные: [10, 20, 30, 40, 50]" << std::endl;
        printSequence(&seq2, "ArraySequence из массива");
        
        LinkedList<int> list;
        list.Append(1);
        list.Append(2);
        list.Append(3);
        ArraySequence<int> seq3(list);
        assertEqual(3, seq3.GetLength(), "Конструктор из LinkedList - длина");
        printSequence(&seq3, "ArraySequence из LinkedList");
        std::cout << "    Ожидаемый результат: [1, 2, 3]" << std::endl;
    }
    
    void testListSequenceConstructors() {
        std::cout << "\n--- Тесты конструкторов ListSequence ---" << std::endl;
        
        ListSequence<int> seq1;
        assertEqual(0, seq1.GetLength(), "Конструктор по умолчанию - длина");
        std::cout << "    Создана пустая последовательность" << std::endl;
        
        int items[] = {5, 15, 25, 35, 45};
        ListSequence<int> seq2(items, 5);
        assertEqual(5, seq2.GetLength(), "Конструктор из массива - длина");
        assertEqual(5, seq2.GetFirst(), "Конструктор из массива - первый");
        assertEqual(45, seq2.GetLast(), "Конструктор из массива - последний");
        
        std::cout << "    Входные данные: [5, 15, 25, 35, 45]" << std::endl;
        printSequence(&seq2, "ListSequence из массива");
        
        LinkedList<int> list;
        list.Append(100);
        list.Append(200);
        list.Append(300);
        ListSequence<int> seq3(list);
        assertEqual(3, seq3.GetLength(), "Конструктор из LinkedList - длина");
        printSequence(&seq3, "ListSequence из LinkedList");
        std::cout << "    Ожидаемый результат: [100, 200, 300]" << std::endl;
    }
    
    void testAppendPrependInsert() {
        std::cout << "\n--- Тесты Append/Prepend/Insert для последовательностей ---" << std::endl;
        
        std::cout << "\n  Тестирование ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq;
        arrSeq.Append(10)->Append(20)->Append(30);
        printSequence(&arrSeq, "После Append");
        assertEqual(3, arrSeq.GetLength(), "ArraySequence append - длина");
        assertEqual(30, arrSeq.GetLast(), "ArraySequence append - последний элемент");
        std::cout << "    Ожидаемый результат: [10, 20, 30]" << std::endl;
        
        arrSeq.Prepend(5);
        printSequence(&arrSeq, "После Prepend(5)");
        assertEqual(4, arrSeq.GetLength(), "ArraySequence prepend - длина");
        assertEqual(5, arrSeq.GetFirst(), "ArraySequence prepend - первый элемент");
        std::cout << "    Ожидаемый результат: [5, 10, 20, 30]" << std::endl;
        
        arrSeq.InsertAt(99, 2);
        printSequence(&arrSeq, "После InsertAt(99, 2)");
        assertEqual(5, arrSeq.GetLength(), "ArraySequence insert - длина");
        assertEqual(99, arrSeq.Get(2), "ArraySequence insert - значение на индексе 2");
        std::cout << "    Ожидаемый результат: [5, 10, 99, 20, 30]" << std::endl;
        
        std::cout << "\n  Тестирование ListSequence:" << std::endl;
        ListSequence<int> listSeq;
        listSeq.Append(10)->Append(20)->Append(30);
        printSequence(&listSeq, "После Append");
        assertEqual(3, listSeq.GetLength(), "ListSequence append - длина");
        
        listSeq.Prepend(5);
        printSequence(&listSeq, "После Prepend(5)");
        assertEqual(4, listSeq.GetLength(), "ListSequence prepend - длина");
        assertEqual(5, listSeq.GetFirst(), "ListSequence prepend - первый элемент");
        
        listSeq.InsertAt(99, 2);
        printSequence(&listSeq, "После InsertAt(99, 2)");
        assertEqual(5, listSeq.GetLength(), "ListSequence insert - длина");
        assertEqual(99, listSeq.Get(2), "ListSequence insert - значение на индексе 2");
    }
    
    void testMap() {
        std::cout << "\n--- Тесты Map для последовательностей ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        
        std::cout << "\n  Тестирование ArraySequence Map:" << std::endl;
        ArraySequence<int> arrSeq(items, 5);
        printSequence(&arrSeq, "Исходная последовательность");
        std::cout << "    Входные данные: [1, 2, 3, 4, 5]" << std::endl;
        
        auto* mapped1 = arrSeq.Map<int>([](int x) { return x * 2; });
        printSequence(mapped1, "Map(x*2)");
        assertEqual(5, mapped1->GetLength(), "Map - длина не изменилась");
        assertEqual(2, mapped1->Get(0), "Map(1*2) = 2");
        assertEqual(10, mapped1->Get(4), "Map(5*2) = 10");
        std::cout << "    Ожидаемый результат: [2, 4, 6, 8, 10]" << std::endl;
        delete mapped1;
        
        auto* mapped2 = arrSeq.Map<int>([](int x) { return x + 10; });
        printSequence(mapped2, "Map(x+10)");
        assertEqual(11, mapped2->Get(0), "Map(1+10) = 11");
        assertEqual(15, mapped2->Get(4), "Map(5+10) = 15");
        std::cout << "    Ожидаемый результат: [11, 12, 13, 14, 15]" << std::endl;
        delete mapped2;
        
        std::cout << "\n  Тестирование ListSequence Map:" << std::endl;
        ListSequence<int> listSeq(items, 5);
        printSequence(&listSeq, "Исходная последовательность");
        
        auto* mapped3 = listSeq.Map<int>([](int x) { return x * 3; });
        printSequence(mapped3, "Map(x*3)");
        assertEqual(3, mapped3->Get(0), "Map(1*3) = 3");
        assertEqual(15, mapped3->Get(4), "Map(5*3) = 15");
        std::cout << "    Ожидаемый результат: [3, 6, 9, 12, 15]" << std::endl;
        delete mapped3;
    }
    
    void testWhere() {
        std::cout << "\n--- Тесты Where для последовательностей ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        std::cout << "\n  Тестирование ArraySequence Where:" << std::endl;
        ArraySequence<int> arrSeq(items, 10);
        printSequence(&arrSeq, "Исходная последовательность");
        std::cout << "    Входные данные: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]" << std::endl;
        
        auto* filtered1 = arrSeq.Where([](int x) { return x > 5; });
        printSequence(filtered1, "Where(x>5)");
        assertEqual(5, filtered1->GetLength(), "Where(x>5) - правильное количество");
        assertEqual(6, filtered1->GetFirst(), "Where(x>5) - первый элемент 6");
        assertEqual(10, filtered1->GetLast(), "Where(x>5) - последний элемент 10");
        std::cout << "    Ожидаемый результат: [6, 7, 8, 9, 10]" << std::endl;
        delete filtered1;
        
        auto* filtered2 = arrSeq.Where([](int x) { return x % 2 == 0; });
        printSequence(filtered2, "Where(четные)");
        assertEqual(5, filtered2->GetLength(), "Where(четные) - правильное количество");
        assertEqual(2, filtered2->GetFirst(), "Where(четные) - первый четный 2");
        assertEqual(10, filtered2->GetLast(), "Where(четные) - последний четный 10");
        std::cout << "    Ожидаемый результат: [2, 4, 6, 8, 10]" << std::endl;
        delete filtered2;
        
        auto* filtered3 = arrSeq.Where([](int x) { return x > 100; });
        assertEqual(0, filtered3->GetLength(), "Where(нет совпадений) - пустой результат");
        delete filtered3;
        
        std::cout << "\n  Тестирование ListSequence Where:" << std::endl;
        ListSequence<int> listSeq(items, 10);
        
        auto* filtered4 = listSeq.Where([](int x) { return x <= 3; });
        printSequence(filtered4, "Where(x<=3)");
        assertEqual(3, filtered4->GetLength(), "Where(x<=3) - правильное количество");
        assertEqual(1, filtered4->GetFirst(), "Where(x<=3) - первый элемент 1");
        assertEqual(3, filtered4->GetLast(), "Where(x<=3) - последний элемент 3");
        std::cout << "    Ожидаемый результат: [1, 2, 3]" << std::endl;
        delete filtered4;
    }
    
    void testReduce() {
        std::cout << "\n--- Тесты Reduce для последовательностей ---" << std::endl;
        
        int items[] = {1, 2, 3, 4, 5};
        
        std::cout << "\n  Тестирование ArraySequence Reduce:" << std::endl;
        ArraySequence<int> arrSeq(items, 5);
        printSequence(&arrSeq, "Последовательность");
        
        int sum = arrSeq.Reduce<int>([](int acc, int x) { return acc + x; }, 0);
        assertEqual(15, sum, "Reduce(сумма) = 15");
        std::cout << "    Вход: [1,2,3,4,5], Начальное: 0, Ожидалось: 15, Получено: " << sum << std::endl;
        
        int product = arrSeq.Reduce<int>([](int acc, int x) { return acc * x; }, 1);
        assertEqual(120, product, "Reduce(произведение) = 120");
        std::cout << "    Вход: [1,2,3,4,5], Начальное: 1, Ожидалось: 120, Получено: " << product << std::endl;
        
        int max = arrSeq.Reduce<int>([](int acc, int x) { return acc > x ? acc : x; }, 0);
        assertEqual(5, max, "Reduce(максимум) = 5");
        std::cout << "    Вход: [1,2,3,4,5], Начальное: 0, Ожидалось: 5, Получено: " << max << std::endl;
        
        std::cout << "\n  Тестирование ListSequence Reduce:" << std::endl;
        ListSequence<int> listSeq(items, 5);
        
        int sum2 = listSeq.Reduce<int>([](int acc, int x) { return acc + x; }, 10);
        assertEqual(25, sum2, "Reduce(сумма, начальное 10) = 25");
        std::cout << "    Вход: [1,2,3,4,5], Начальное: 10, Ожидалось: 25, Получено: " << sum2 << std::endl;
    }
    
    void testFind() {
        std::cout << "\n--- Тесты Find для последовательностей ---" << std::endl;
        
        int items[] = {10, 20, 30, 40, 50};
        
        std::cout << "\n  Тестирование ArraySequence Find:" << std::endl;
        ArraySequence<int> arrSeq(items, 5);
        printSequence(&arrSeq, "Последовательность");
        
        Option<int> found1 = arrSeq.Find([](int x) { return x == 30; });
        assertTrue(found1.IsSome(), "Поиск существующего значения - найдено");
        assertEqual(30, found1.GetValue(), "Поиск существующего значения - правильное значение");
        std::cout << "    Ищем: 30, Ожидалось: найдено, Получено: " << found1.GetValue() << std::endl;
        
        Option<int> found2 = arrSeq.Find([](int x) { return x == 100; });
        assertTrue(found2.IsNone(), "Поиск несуществующего значения - не найдено");
        std::cout << "    Ищем: 100, Ожидалось: не найдено, Получено: не найдено" << std::endl;
        
        Option<int> found3 = arrSeq.Find([](int x) { return x > 25; });
        assertTrue(found3.IsSome(), "Поиск по предикату - найдено первое совпадение");
        assertEqual(30, found3.GetValue(), "Поиск по предикату - первый элемент >25 это 30");
        std::cout << "    Ищем первый >25, Ожидалось: 30, Получено: " << found3.GetValue() << std::endl;
        
        std::cout << "\n  Тестирование ListSequence Find:" << std::endl;
        ListSequence<int> listSeq(items, 5);
        
        Option<int> found4 = listSeq.Find([](int x) { return x == 50; });
        assertTrue(found4.IsSome(), "Поиск последнего элемента - найден");
        assertEqual(50, found4.GetValue(), "Поиск последнего элемента - правильное значение");
    }
    
    void testGetSubsequence() {
        std::cout << "\n--- Тесты GetSubsequence для последовательностей ---" << std::endl;
        
        int items[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
        
        std::cout << "\n  Тестирование ArraySequence GetSubsequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 10);
        printSequence(&arrSeq, "Исходная последовательность");
        
        auto* sub1 = arrSeq.GetSubsequence(2, 6);
        printSequence(sub1, "Подпоследовательность [2-6]");
        assertEqual(5, sub1->GetLength(), "Подпоследовательность - длина");
        assertEqual(300, sub1->Get(0), "Подпоследовательность - начало на индексе 2");
        assertEqual(700, sub1->Get(4), "Подпоследовательность - конец на индексе 6");
        std::cout << "    Ожидаемый результат: [300, 400, 500, 600, 700]" << std::endl;
        delete sub1;
        
        auto* sub2 = arrSeq.GetSubsequence(0, 4);
        printSequence(sub2, "Подпоследовательность [0-4]");
        assertEqual(5, sub2->GetLength(), "Подпоследовательность с начала");
        assertEqual(100, sub2->GetFirst(), "Первый элемент сохранен");
        std::cout << "    Ожидаемый результат: [100, 200, 300, 400, 500]" << std::endl;
        delete sub2;
        
        try {
            arrSeq.GetSubsequence(5, 2);
            assertTrue(false, "Неверный диапазон - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "Неверный диапазон - исключение перехвачено");
        }
        
        std::cout << "\n  Тестирование ListSequence GetSubsequence:" << std::endl;
        ListSequence<int> listSeq(items, 10);
        
        auto* sub3 = listSeq.GetSubsequence(3, 8);
        printSequence(sub3, "Подпоследовательность [3-8]");
        assertEqual(6, sub3->GetLength(), "Подпоследовательность - длина");
        assertEqual(400, sub3->GetFirst(), "Подпоследовательность - начало на индексе 3");
        assertEqual(900, sub3->GetLast(), "Подпоследовательность - конец на индексе 8");
        std::cout << "    Ожидаемый результат: [400, 500, 600, 700, 800, 900]" << std::endl;
        delete sub3;
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nЗАПУСК ТЕСТОВ ПОСЛЕДОВАТЕЛЬНОСТЕЙ (ArraySequence и ListSequence)";
        std::cout << "\n========================================";
        
        testArraySequenceConstructors();
        testListSequenceConstructors();
        testAppendPrependInsert();
        testMap();
        testWhere();
        testReduce();
        testFind();
        testGetSubsequence();
        
        std::cout << "\n--- Итог ---" << std::endl;
        std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

int main() {
    SequenceTests tests;
    tests.runAll();
    return 0;
}