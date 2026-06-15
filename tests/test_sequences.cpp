#include <iostream>
#include <string>
#include "../include/arraySequence.hpp"
#include "../include/listSequence.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

class SequenceTests {
private:
    int passed = 0;
    int failed = 0;
    
    template<typename T>
    void assertEqual(T expected, T actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << GREEN << "  [OK] " << RESET << testName << std::endl;
            passed++;
        } else {
            std::cout << RED << "  [FAIL] " << RESET << testName << " (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertEqual(size_t expected, size_t actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << GREEN << "  [OK] " << RESET << testName << std::endl;
            passed++;
        } else {
            std::cout << RED << "  [FAIL] " << RESET << testName << " (ожидалось: " << expected 
                      << ", получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << GREEN << "  [OK] " << RESET << testName << std::endl;
            passed++;
        } else {
            std::cout << RED << "  [FAIL] " << RESET << testName << std::endl;
            failed++;
        }
    }
    
    template<typename T>
    void printSequence(Sequence<T>* seq, const std::string& label) {
        std::cout << "    " << label << ": [";
        for (size_t i = 0; i < seq->GetLength(); i++) {
            std::cout << seq->Get(i);
            if (i < seq->GetLength() - 1) std::cout << ", ";
        }
        std::cout << "] (длина: " << seq->GetLength() << ")" << std::endl;
    }
    
public:
    void testArraySequenceConstructors() {
        std::cout << "\n--- Конструкторы ArraySequence ---" << std::endl;
        
        ArraySequence<int> seq1;
        assertEqual((size_t)0, seq1.GetLength(), "Конструктор по умолчанию");
        
        int items[] = {10, 20, 30, 40, 50};
        ArraySequence<int> seq2(items, 5);
        assertEqual((size_t)5, seq2.GetLength(), "Конструктор из массива - длина");
        assertEqual(10, seq2.GetFirst(), "Первый элемент");
        assertEqual(50, seq2.GetLast(), "Последний элемент");
        assertEqual(30, seq2.Get(2), "Элемент с индексом 2");
        
        printSequence(&seq2, "ArraySequence из массива");
        
        LinkedList<int> list;
        list.Append(1);
        list.Append(2);
        list.Append(3);
        ArraySequence<int> seq3(list);
        assertEqual((size_t)3, seq3.GetLength(), "Конструктор из LinkedList");
        printSequence(&seq3, "ArraySequence из LinkedList");
        
        ArraySequence<int> seq4(seq2);
        assertEqual((size_t)5, seq4.GetLength(), "Конструктор копирования");
        
        ArraySequence<int> seq5(std::move(seq2));
        assertEqual((size_t)5, seq5.GetLength(), "Конструктор перемещения");
        assertEqual((size_t)0, seq2.GetLength(), "Конструктор перемещения - источник опустошён");
    }
    
    void testListSequenceConstructors() {
        std::cout << "\n--- Конструкторы ListSequence ---" << std::endl;
        
        ListSequence<int> seq1;
        assertEqual((size_t)0, seq1.GetLength(), "Конструктор по умолчанию");
        
        int items[] = {5, 15, 25, 35, 45};
        ListSequence<int> seq2(items, 5);
        assertEqual((size_t)5, seq2.GetLength(), "Конструктор из массива");
        assertEqual(5, seq2.GetFirst(), "Первый элемент");
        assertEqual(45, seq2.GetLast(), "Последний элемент");
        
        printSequence(&seq2, "ListSequence из массива");
        
        LinkedList<int> list;
        list.Append(100);
        list.Append(200);
        list.Append(300);
        ListSequence<int> seq3(list);
        assertEqual((size_t)3, seq3.GetLength(), "Конструктор из LinkedList");
        printSequence(&seq3, "ListSequence из LinkedList");
        
        ListSequence<int> seq4(seq2);
        assertEqual((size_t)5, seq4.GetLength(), "Конструктор копирования");
        
        ListSequence<int> seq5(std::move(seq2));
        assertEqual((size_t)5, seq5.GetLength(), "Конструктор перемещения");
        assertEqual((size_t)0, seq2.GetLength(), "Конструктор перемещения - источник опустошён");
    }
    
    void testAppendPrependInsert() {
        std::cout << "\n--- Тесты Append/Prepend/Insert ---" << std::endl;
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq;
        arrSeq.Append(10);
        arrSeq.Append(20);
        arrSeq.Append(30);
        printSequence(&arrSeq, "После Append");
        assertEqual((size_t)3, arrSeq.GetLength(), "Append - длина");
        assertEqual(30, arrSeq.GetLast(), "Последний элемент после Append");
        
        arrSeq.Prepend(5);
        printSequence(&arrSeq, "После Prepend(5)");
        assertEqual((size_t)4, arrSeq.GetLength(), "Prepend - длина");
        assertEqual(5, arrSeq.GetFirst(), "Первый элемент после Prepend");
        
        arrSeq.InsertAt(99, 2);
        printSequence(&arrSeq, "После InsertAt(99, 2)");
        assertEqual((size_t)5, arrSeq.GetLength(), "Insert - длина");
        assertEqual(99, arrSeq.Get(2), "Значение на индексе 2");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq;
        listSeq.Append(10);
        listSeq.Append(20);
        listSeq.Append(30);
        printSequence(&listSeq, "После Append");
        assertEqual((size_t)3, listSeq.GetLength(), "Append - длина");
        
        listSeq.Prepend(5);
        printSequence(&listSeq, "После Prepend(5)");
        assertEqual((size_t)4, listSeq.GetLength(), "Prepend - длина");
        assertEqual(5, listSeq.GetFirst(), "Первый элемент");
        
        listSeq.InsertAt(99, 2);
        printSequence(&listSeq, "После InsertAt(99, 2)");
        assertEqual((size_t)5, listSeq.GetLength(), "Insert - длина");
        assertEqual(99, listSeq.Get(2), "Значение на индексе 2");
    }
    
    void testGetSubsequence() {
        std::cout << "\n--- Тесты GetSubsequence ---" << std::endl;
        
        int items[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 10);
        printSequence(&arrSeq, "Исходная");
        
        ArraySequence<int>* sub1 = arrSeq.GetSubsequence(2, 6);
        printSequence(sub1, "Подпоследовательность [2-6]");
        assertEqual((size_t)5, sub1->GetLength(), "Длина");
        assertEqual(300, sub1->Get(0), "Начало на индексе 2");
        assertEqual(700, sub1->Get(4), "Конец на индексе 6");
        delete sub1;
        
        ArraySequence<int>* sub2 = arrSeq.GetSubsequence(0, 4);
        printSequence(sub2, "Подпоследовательность [0-4]");
        assertEqual((size_t)5, sub2->GetLength(), "Длина");
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
        
        ListSequence<int>* sub3 = listSeq.GetSubsequence(3, 8);
        printSequence(sub3, "Подпоследовательность [3-8]");
        assertEqual((size_t)6, sub3->GetLength(), "Длина");
        assertEqual(400, sub3->GetFirst(), "Начало на индексе 3");
        assertEqual(900, sub3->GetLast(), "Конец на индексе 8");
        delete sub3;
    }
    
    void testCopyAssignment() {
        std::cout << "\n--- Тесты копирующего присваивания ---" << std::endl;
        
        std::cout << "\n  ArraySequence:" << std::endl;
        int items[] = {1, 2, 3};
        ArraySequence<int> arr1(items, 3);
        ArraySequence<int> arr2;
        
        arr2 = arr1;
        assertEqual((size_t)3, arr2.GetLength(), "Копирующее присваивание - длина");
        assertEqual(1, arr2.GetFirst(), "Копирующее присваивание - первый элемент");
        
        std::cout << "    Копирующее присваивание создало копию" << std::endl;
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> list1(items, 3);
        ListSequence<int> list2;
        
        list2 = list1;
        assertEqual((size_t)3, list2.GetLength(), "Копирующее присваивание - длина");
        assertEqual(1, list2.GetFirst(), "Копирующее присваивание - первый элемент");
        
        std::cout << "    Копирующее присваивание создало копию" << std::endl;
    }
    
    void testMoveAssignment() {
        std::cout << "\n--- Тесты перемещающего присваивания ---" << std::endl;
        
        std::cout << "\n  ArraySequence:" << std::endl;
        int items[] = {10, 20, 30};
        ArraySequence<int> arr1(items, 3);
        ArraySequence<int> arr2;
        
        arr2 = std::move(arr1);
        assertEqual((size_t)3, arr2.GetLength(), "Перемещающее присваивание - длина");
        assertEqual(10, arr2.GetFirst(), "Перемещающее присваивание - первый элемент");
        assertEqual((size_t)0, arr1.GetLength(), "Перемещающее присваивание - источник опустошён");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> list1(items, 3);
        ListSequence<int> list2;
        
        list2 = std::move(list1);
        assertEqual((size_t)3, list2.GetLength(), "Перемещающее присваивание - длина");
        assertEqual(10, list2.GetFirst(), "Перемещающее присваивание - первый элемент");
        assertEqual((size_t)0, list1.GetLength(), "Перемещающее присваивание - источник опустошён");
    }
    
    void testIterators() {
        std::cout << "\n--- Тесты итераторов ---" << std::endl;
        
        int items[] = {10, 20, 30, 40};
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq(items, 4);
        
        std::cout << "    range-based for: ";
        int sum = 0;
        for (int val : arrSeq) {
            std::cout << val << " ";
            sum += val;
        }
        std::cout << std::endl;
        assertEqual(100, sum, "Сумма через range-based for");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq(items, 4);
        
        std::cout << "    range-based for: ";
        sum = 0;
        for (int val : listSeq) {
            std::cout << val << " ";
            sum += val;
        }
        std::cout << std::endl;
        assertEqual(100, sum, "Сумма через range-based for");
    }
    
    void testChaining() {
        std::cout << "\n--- Тесты последовательных вызовов ---" << std::endl;
        
        std::cout << "\n  ArraySequence:" << std::endl;
        ArraySequence<int> arrSeq;
        arrSeq.Append(1);
        arrSeq.Append(2);
        arrSeq.Append(3);
        arrSeq.Prepend(0);
        arrSeq.InsertAt(5, 2);
        
        assertEqual((size_t)5, arrSeq.GetLength(), "Длина после операций");
        assertEqual(0, arrSeq.Get(0), "Элемент 0");
        assertEqual(1, arrSeq.Get(1), "Элемент 1");
        assertEqual(5, arrSeq.Get(2), "Элемент 2");
        assertEqual(2, arrSeq.Get(3), "Элемент 3");
        assertEqual(3, arrSeq.Get(4), "Элемент 4");
        printSequence(&arrSeq, "Результат");
        
        std::cout << "\n  ListSequence:" << std::endl;
        ListSequence<int> listSeq;
        listSeq.Append(1);
        listSeq.Append(2);
        listSeq.Append(3);
        listSeq.Prepend(0);
        listSeq.InsertAt(5, 2);
        
        assertEqual((size_t)5, listSeq.GetLength(), "Длина после операций");
        assertEqual(0, listSeq.Get(0), "Элемент 0");
        assertEqual(1, listSeq.Get(1), "Элемент 1");
        assertEqual(5, listSeq.Get(2), "Элемент 2");
        assertEqual(2, listSeq.Get(3), "Элемент 3");
        assertEqual(3, listSeq.Get(4), "Элемент 4");
        printSequence(&listSeq, "Результат");
        
        std::cout << "\n  Проверка возврата this:" << std::endl;
        ArraySequence<int> seq;
        Sequence<int>* ptr = &seq;
        Sequence<int>* ret = seq.Append(1);
        assertTrue(ptr == ret, "Append возвращает this");
        
        ret = seq.Prepend(1);
        assertTrue(ptr == ret, "Prepend возвращает this");
        
        ret = seq.InsertAt(1, 0);
        assertTrue(ptr == ret, "InsertAt возвращает this");
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nТЕСТЫ ПОСЛЕДОВАТЕЛЬНОСТЕЙ";
        std::cout << "\n========================================";
        
        testArraySequenceConstructors();
        testListSequenceConstructors();
        testAppendPrependInsert();
        testGetSubsequence();
        testCopyAssignment();
        testMoveAssignment();
        testIterators();
        testChaining();
        
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

