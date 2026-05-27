#include <iostream>
#include <string>
#include "../include/bitSequence.hpp"

class BitSequenceTests {
private:
    int passed = 0;
    int failed = 0;
    
    void assertEqual(bool expected, bool actual, const std::string& testName) {
        if (expected == actual) {
            std::cout << "  ? " << testName << " - ПРОЙДЕН" << std::endl;
            passed++;
        } else {
            std::cout << "  ? " << testName << " - НЕ ПРОЙДЕН (Ожидалось: " << expected 
                      << ", Получено: " << actual << ")" << std::endl;
            failed++;
        }
    }
    
    void assertEqual(int expected, int actual, const std::string& testName) {
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
    
    void printBits(BitSequence* seq, const std::string& label) {
        std::cout << "    " << label << ": ";
        for (int i = 0; i < seq->GetLength(); i++) {
            std::cout << seq->GetBit(i);
            if ((i + 1) % 8 == 0 && i < seq->GetLength() - 1) std::cout << " ";
        }
        std::cout << " (длина: " << seq->GetLength() << " бит)" << std::endl;
    }
    
public:
    void testConstructor() {
        std::cout << "\n--- Тесты конструкторов BitSequence ---" << std::endl;
        
        BitSequence seq1;
        assertEqual(0, seq1.GetLength(), "Конструктор по умолчанию - длина");
        std::cout << "    Создана пустая битовая последовательность" << std::endl;
        
        BitSequence seq2(16);
        assertEqual(16, seq2.GetLength(), "Конструктор с размером - длина");
        for (int i = 0; i < 16; i++) {
            assertEqual(false, seq2.GetBit(i), "Конструктор с размером - бит " + std::to_string(i) + " = 0");
        }
        std::cout << "    Создана последовательность из 16 битов, все = 0" << std::endl;
        
        bool bits[] = {1, 0, 1, 0, 1, 0, 1, 0};
        BitSequence seq3(bits, 8);
        assertEqual(8, seq3.GetLength(), "Конструктор из массива - длина");
        assertEqual(true, seq3.GetBit(0), "Конструктор из массива - бит 0 = 1");
        assertEqual(false, seq3.GetBit(1), "Конструктор из массива - бит 1 = 0");
        assertEqual(true, seq3.GetBit(2), "Конструктор из массива - бит 2 = 1");
        
        std::cout << "    Входные данные: [1,0,1,0,1,0,1,0]" << std::endl;
        printBits(&seq3, "Созданная последовательность");
    }
    
    void testSetGetBit() {
        std::cout << "\n--- Тесты SetBit/GetBit BitSequence ---" << std::endl;
        
        BitSequence seq(16);
        std::cout << "    Исходная последовательность: 16 нулей" << std::endl;
        
        seq.SetBit(0, true);
        assertEqual(true, seq.GetBit(0), "SetBit(0, true)");
        std::cout << "    Установлен бит 0 в 1" << std::endl;
        
        seq.SetBit(7, true);
        assertEqual(true, seq.GetBit(7), "SetBit(7, true)");
        std::cout << "    Установлен бит 7 в 1" << std::endl;
        
        seq.SetBit(15, true);
        assertEqual(true, seq.GetBit(15), "SetBit(15, true)");
        std::cout << "    Установлен бит 15 в 1" << std::endl;
        
        seq.SetBit(5, true);
        seq.SetBit(5, false);
        assertEqual(false, seq.GetBit(5), "SetBit установка в false");
        std::cout << "    Бит 5: установлен в 1, затем сброшен в 0" << std::endl;
        
        printBits(&seq, "После операций установки");
        
        try {
            seq.GetBit(20);
            assertTrue(false, "GetBit за пределами - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "GetBit за пределами - исключение перехвачено");
            std::cout << "    Ожидалось исключение IndexOutOfRangeException - получено" << std::endl;
        }
        
        try {
            seq.SetBit(20, true);
            assertTrue(false, "SetBit за пределами - должно быть исключение");
        } catch (const IndexOutOfRangeException&) {
            assertTrue(true, "SetBit за пределами - исключение перехвачено");
        }
    }
    
    void testPattern() {
        std::cout << "\n--- Тесты BitSequence с паттерном ---" << std::endl;
        
        BitSequence seq(16);
        for (int i = 0; i < 16; i++) {
            seq.SetBit(i, i % 2 == 0);
        }
        
        printBits(&seq, "Чередующийся паттерн (четные позиции = 1)");
        std::cout << "    Ожидаемый результат: 10101010 10101010" << std::endl;
        
        for (int i = 0; i < 16; i++) {
            assertEqual(i % 2 == 0, seq.GetBit(i), "Паттерн на позиции " + std::to_string(i));
        }
    }
    
    void testBitwiseOperations() {
        std::cout << "\n--- Тесты битовых операций BitSequence ---" << std::endl;
        
        bool bits1[] = {1, 1, 1, 1, 0, 0, 0, 0};
        bool bits2[] = {1, 0, 1, 0, 1, 0, 1, 0};
        BitSequence seq1(bits1, 8);
        BitSequence seq2(bits2, 8);
        
        printBits(&seq1, "Последовательность A");
        std::cout << "    A = 11110000" << std::endl;
        printBits(&seq2, "Последовательность B");
        std::cout << "    B = 10101010" << std::endl;
        
        std::cout << "\n  Операция AND:" << std::endl;
        BitSequence* andResult = seq1.And(seq2);
        assertEqual(8, andResult->GetLength(), "AND - длина результата");
        assertEqual(true, andResult->GetBit(0), "AND бит 0 (1 & 1) = 1");
        assertEqual(false, andResult->GetBit(1), "AND бит 1 (1 & 0) = 0");
        assertEqual(false, andResult->GetBit(4), "AND бит 4 (0 & 1) = 0");
        printBits(andResult, "A AND B");
        std::cout << "    Ожидаемый результат: 10100000" << std::endl;
        delete andResult;
        
        std::cout << "\n  Операция OR:" << std::endl;
        BitSequence* orResult = seq1.Or(seq2);
        assertEqual(true, orResult->GetBit(0), "OR бит 0 (1 | 1) = 1");
        assertEqual(true, orResult->GetBit(1), "OR бит 1 (1 | 0) = 1");
        assertEqual(true, orResult->GetBit(4), "OR бит 4 (0 | 1) = 1");
        assertEqual(false, orResult->GetBit(7), "OR бит 7 (0 | 0) = 0");
        printBits(orResult, "A OR B");
        std::cout << "    Ожидаемый результат: 11111010" << std::endl;
        delete orResult;
        
        std::cout << "\n  Операция XOR:" << std::endl;
        BitSequence* xorResult = seq1.Xor(seq2);
        assertEqual(false, xorResult->GetBit(0), "XOR бит 0 (1 ^ 1) = 0");
        assertEqual(true, xorResult->GetBit(1), "XOR бит 1 (1 ^ 0) = 1");
        assertEqual(true, xorResult->GetBit(4), "XOR бит 4 (0 ^ 1) = 1");
        assertEqual(false, xorResult->GetBit(7), "XOR бит 7 (0 ^ 0) = 0");
        printBits(xorResult, "A XOR B");
        std::cout << "    Ожидаемый результат: 01011010" << std::endl;
        delete xorResult;
        
        std::cout << "\n  Операция NOT:" << std::endl;
        BitSequence* notResult = seq1.Not();
        assertEqual(8, notResult->GetLength(), "NOT - длина результата");
        assertEqual(false, notResult->GetBit(0), "NOT бит 0 = 0");
        assertEqual(true, notResult->GetBit(4), "NOT бит 4 = 1");
        printBits(notResult, "NOT A");
        std::cout << "    Ожидаемый результат: 00001111" << std::endl;
        delete notResult;
    }
    
    void testAppendInsert() {
        std::cout << "\n--- Тесты Append/Insert BitSequence ---" << std::endl;
        
        BitSequence seq(4);
        for (int i = 0; i < 4; i++) seq.SetBit(i, i % 2 == 0);
        printBits(&seq, "Исходная последовательность");
        std::cout << "    Исходная: 1010" << std::endl;
        
        seq.Append(Bit(true));
        assertEqual(5, seq.GetLength(), "Append - длина увеличена");
        assertEqual(true, seq.GetBit(4), "Append - значение добавлено в конец");
        printBits(&seq, "После Append(1)");
        std::cout << "    Результат: 10101" << std::endl;
        
        seq.Prepend(Bit(false));
        assertEqual(6, seq.GetLength(), "Prepend - длина увеличена");
        assertEqual(false, seq.GetBit(0), "Prepend - значение в начале");
        assertEqual(true, seq.GetBit(1), "Prepend - исходные значения сдвинуты");
        printBits(&seq, "После Prepend(0)");
        std::cout << "    Результат: 010101" << std::endl;
        
        seq.InsertAt(Bit(1), 3);
        assertEqual(7, seq.GetLength(), "InsertAt - длина увеличена");
        assertEqual(true, seq.GetBit(3), "InsertAt - значение вставлено на индекс 3");
        printBits(&seq, "После InsertAt(1, 3)");
        std::cout << "    Результат: 0101101" << std::endl;
    }
    
    void testGetSubsequence() {
        std::cout << "\n--- Тесты GetSubsequence BitSequence ---" << std::endl;
        
        bool bits[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
        BitSequence seq(bits, 16);
        printBits(&seq, "Исходная последовательность");
        std::cout << "    Исходная: 10101010 10101010" << std::endl;
        
        BitSequence* subseq = seq.GetSubsequence(2, 5);
        assertEqual(4, subseq->GetLength(), "Подпоследовательность [2-5] - длина");
        assertEqual(true, subseq->GetBit(0), "Подпоследовательность бит 0 = 1");
        assertEqual(false, subseq->GetBit(1), "Подпоследовательность бит 1 = 0");
        assertEqual(true, subseq->GetBit(2), "Подпоследовательность бит 2 = 1");
        assertEqual(false, subseq->GetBit(3), "Подпоследовательность бит 3 = 0");
        printBits(subseq, "Подпоследовательность [2-5]");
        std::cout << "    Ожидаемый результат: 1010" << std::endl;
        delete subseq;
    }
    
    void runAll() {
        std::cout << "\n========================================";
        std::cout << "\nЗАПУСК ТЕСТОВ BIT SEQUENCE";
        std::cout << "\n========================================";
        
        testConstructor();
        testSetGetBit();
        testPattern();
        testBitwiseOperations();
        testAppendInsert();
        testGetSubsequence();
        
        std::cout << "\n--- Итог ---" << std::endl;
        std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

int main() {
    BitSequenceTests tests;
    tests.runAll();
    return 0;
}

