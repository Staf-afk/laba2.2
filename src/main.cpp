#include <iostream>
#include <string>
#include <limits>
#include <functional>
#include "dynamicArray.hpp"
#include "linkedList.hpp"
#include "arraySequence.hpp"
#include "listSequence.hpp"
#include "bitSequence.hpp"
#include "option.hpp"
#include "exceptions.hpp"

using namespace std;

// ... остальной код main.cpp без изменений ...

int SafeIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        cerr << "[!] Ошибка: введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool SafeBoolInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt << " (1/0): ";
        if (cin >> val) return val != 0;
        string s; cin >> s;
        if (s == "true" || s == "1") return true;
        if (s == "false" || s == "0") return false;
        cerr << "[!] Ошибка ввода.\n";
    }
}

void PrintDA(const DynamicArray<int>& arr, const string& name = "DynamicArray") {
    cout << "\n[" << name << " | Size: " << arr.GetSize() << "]: ";
    for (int i = 0; i < arr.GetSize(); ++i) cout << arr.Get(i) << " ";
    cout << "\n";
}

void PrintLL(const LinkedList<int>& list, const string& name = "LinkedList") {
    cout << "\n[" << name << " | Length: " << list.GetLength() << "]: ";
    for (int i = 0; i < list.GetLength(); ++i) cout << list.Get(i) << " ";
    cout << "\n";
}

void PrintSeq(const Sequence<int>& seq, const string& name = "Последовательность") {
    cout << "\n[" << name << " | Длина: " << seq.GetLength() << "]: ";
    for (int i = 0; i < seq.GetLength(); ++i) cout << seq.Get(i) << " ";
    cout << "\n";
}

void PrintBits(const BitSequence& bs, const string& name = "BitSequence") {
    cout << "\n[" << name << " | Длина: " << bs.GetLength() << "]: ";
    for (int i = 0; i < bs.GetLength(); ++i) cout << (bs.Get(i).GetValue() ? "1" : "0");
    cout << "\n";
}

void Pause() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void RunDynamicArrayUI() {
    cout << "\n=== ДИНАМИЧЕСКИЙ МАССИВ ===\n";
    int size = SafeIntInput("Начальный размер: ");
    DynamicArray<int> arr(size);
    for (int i = 0; i < size; ++i) arr.Set(i, SafeIntInput("  arr[" + to_string(i) + "] = "));
    PrintDA(arr, "Исходный");

    int choice;
    do {
        cout << "\n[МЕНЮ] 1.Get 2.Set 3.Resize 4.Print 0.Назад\nВыбор: ";
        cin >> choice;
        try {
            switch (choice) {
                case 1: { int idx = SafeIntInput("Index: "); cout << "arr[" << idx << "] = " << arr.Get(idx) << "\n"; break; }
                case 2: arr.Set(SafeIntInput("Index: "), SafeIntInput("Value: ")); break;
                case 3: arr.Resize(SafeIntInput("New Size: ")); break;
                case 4: PrintDA(arr); break;
                case 0: break;
                default: cerr << "[!] Неверный пункт.\n";
            }
        } catch (const exception& e) { cerr << "[ERR] " << e.what() << "\n"; }
    } while (choice != 0);
}

void RunLinkedListUI() {
    cout << "\n=== СВЯЗАННЫЙ СПИСОК ===\n";
    LinkedList<int> list;
    int cnt = SafeIntInput("Кол-во элементов: ");
    for (int i = 0; i < cnt; ++i) list.Append(SafeIntInput("  el: "));
    PrintLL(list, "Исходный");

    int choice;
    do {
        cout << "\n[МЕНЮ] 1.Append 2.Prepend 3.InsertAt 4.SubList 5.Concat 6.Print 0.Назад\nВыбор: ";
        cin >> choice;
        try {
            switch (choice) {
                case 1: list.Append(SafeIntInput("Value: ")); break;
                case 2: list.Prepend(SafeIntInput("Value: ")); break;
                case 3: list.InsertAt(SafeIntInput("Value: "), SafeIntInput("Index: ")); break;
                case 4: {
                    int s = SafeIntInput("Start: "), e = SafeIntInput("End: ");
                    auto sub = list.GetSubList(s, e);
                    PrintLL(*sub, "SubList"); delete sub; break;
                }
                case 5: {
                    LinkedList<int> other;
                    int oc = SafeIntInput("Элементов для сцепления: ");
                    for(int i=0;i<oc;++i) other.Append(SafeIntInput("  other: "));
                    auto res = list.Concat(&other);
                    PrintLL(*res, "Concat"); delete res; break;
                }
                case 6: PrintLL(list); break;
                case 0: break;
                default: cerr << "[!] Неверный пункт.\n";
            }
        } catch (const exception& e) { cerr << "[ERR] " << e.what() << "\n"; }
    } while (choice != 0);
}

void RunSequenceUI(bool useArray, bool isImmutable) {
    string name = useArray ? "ArraySequence" : "ListSequence";
    if (isImmutable) name += " (Immutable)";
    cout << "\n=== " << name << " ===\n";

    Sequence<int>* seq = nullptr;
    try {
        int cnt = SafeIntInput("Начальных элементов: ");
        int* arr = new int[cnt];
        for(int i=0;i<cnt;++i) arr[i] = SafeIntInput("  el: ");
        
        if (useArray) seq = isImmutable ? (Sequence<int>*)new ImmutableArraySequence<int>(arr, cnt) 
                                        : (Sequence<int>*)new MutableArraySequence<int>(arr, cnt);
        else seq = isImmutable ? (Sequence<int>*)new ImmutableListSequence<int>(arr, cnt)
                               : (Sequence<int>*)new MutableListSequence<int>(arr, cnt);
        delete[] arr;
        PrintSeq(*seq, "Текущая");
    } catch (const exception& e) { cerr << "[ERR] " << e.what() << "\n"; return; }

    int choice;
    do {
        cout << "\n[МЕНЮ] 1.Append 2.Prepend 3.InsertAt 4.Subsequence 5.Concat\n6.Map(x*x) 7.Where(even) 8.Reduce(Sum) 9.TryFind(>X) 10.Print 0.Назад\nВыбор: ";
        cin >> choice;
        try {
            Sequence<int>* newSeq = nullptr;
            switch (choice) {
                case 1: newSeq = seq->Append(SafeIntInput("Value: ")); break;
                case 2: newSeq = seq->Prepend(SafeIntInput("Value: ")); break;
                case 3: newSeq = seq->InsertAt(SafeIntInput("Value: "), SafeIntInput("Index: ")); break;
                case 4: {
                    int s = SafeIntInput("Start: "), e = SafeIntInput("End: ");
                    newSeq = seq->GetSubsequence(s, e);
                    PrintSeq(*newSeq, "Subsequence"); delete newSeq; break;
                }
                case 5: {
                    newSeq = seq->Concat(seq);
                    PrintSeq(*newSeq, "Concat"); delete newSeq; break;
                }
                case 6: {
                    newSeq = seq->Map<int>([](int x){ return x*x; });
                    PrintSeq(*newSeq, "Map(x*x)"); delete newSeq; break;
                }
                case 7: {
                    newSeq = seq->Where([](int x){ return x % 2 == 0; });
                    PrintSeq(*newSeq, "Where(isEven)"); delete newSeq; break;
                }
                case 8: cout << "Reduce(Sum) = " << seq->Reduce<int>([](int a, int b){ return a+b; }, 0) << "\n"; break;
                case 9: {
                    int val = SafeIntInput("Найти элемент > X (X="); 
                    auto opt = seq->Find([val](int x){ return x > val; });
                    if (opt.IsSome()) cout << "TryFind: Found -> " << opt.GetValue() << "\n";
                    else cout << "TryFind: None\n";
                    break;
                }
                case 10: PrintSeq(*seq); break;
                case 0: break;
                default: cerr << "[!] Неверный пункт.\n";
            }

            if (newSeq != nullptr) {
                if (isImmutable) { delete seq; seq = newSeq; cout << "[Immutable] Создана новая копия.\n"; }
                else { delete newSeq; cout << "[Mutable] Объект изменен.\n"; }
                PrintSeq(*seq, "Обновленная");
            }
        } catch (const exception& e) { cerr << "[ERR] " << e.what() << "\n"; }
    } while (choice != 0);
    delete seq;
}

void RunBitSequenceUI() {
    cout << "\n=== БИТОВАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ===\n";
    int len = SafeIntInput("Длина маски: ");
    bool* bits = new bool[len];
    for(int i=0;i<len;++i) bits[i] = SafeBoolInput("  bit[" + to_string(i) + "]: ");
    BitSequence* bs = new BitSequence(bits, len);
    delete[] bits;
    PrintBits(*bs, "Исходная");

    int choice;
    do {
        cout << "\n[МЕНЮ] 1.Append 2.Prepend 3.InsertAt 4.Subsequence 5.Concat\n6.AND 7.OR 8.XOR 9.NOT 10.Print 0.Назад\nВыбор: ";
        cin >> choice;
        try {
            switch (choice) {
                case 1: bs->Append(Bit(SafeBoolInput("Бит: "))); break;
                case 2: bs->Prepend(Bit(SafeBoolInput("Бит: "))); break;
                case 3: bs->InsertAt(Bit(SafeBoolInput("Бит: ")), SafeIntInput("Index: ")); break;
                case 4: {
                    int s = SafeIntInput("Start: "), e = SafeIntInput("End: ");
                    auto sub = bs->GetSubsequence(s, e);
                    PrintBits(*sub, "Subsequence"); delete sub; break;
                }
                case 5: {
                    int ol = SafeIntInput("Длина второй маски: ");
                    bool* ob = new bool[ol];
                    for(int i=0;i<ol;++i) ob[i] = SafeBoolInput("  other: ");
                    BitSequence other(ob, ol); delete[] ob;
                    bs->Concat(&other); break;
                }
                case 6: {
                    int ol = SafeIntInput("Длина маски AND: ");
                    bool* ob = new bool[ol];
                    for(int i=0;i<ol;++i) ob[i] = SafeBoolInput("  mask: ");
                    BitSequence other(ob, ol); delete[] ob;
                    auto res = bs->And(other); PrintBits(*res, "AND"); delete res; break;
                }
                case 7: {
                    int ol = SafeIntInput("Длина маски OR: ");
                    bool* ob = new bool[ol];
                    for(int i=0;i<ol;++i) ob[i] = SafeBoolInput("  mask: ");
                    BitSequence other(ob, ol); delete[] ob;
                    auto res = bs->Or(other); PrintBits(*res, "OR"); delete res; break;
                }
                case 8: {
                    int ol = SafeIntInput("Длина маски XOR: ");
                    bool* ob = new bool[ol];
                    for(int i=0;i<ol;++i) ob[i] = SafeBoolInput("  mask: ");
                    BitSequence other(ob, ol); delete[] ob;
                    auto res = bs->Xor(other); PrintBits(*res, "XOR"); delete res; break;
                }
                case 9: {
                    auto res = bs->Not(); PrintBits(*res, "NOT"); delete res; break;
                }
                case 10: PrintBits(*bs); break;
                case 0: break;
                default: cerr << "[!] Неверный пункт.\n";
            }
        } catch (const exception& e) { cerr << "[ERR] " << e.what() << "\n"; }
    } while (choice != 0);
    delete bs;
}

int main() {
    cout << "========================================\n";
    cout << "  Лабораторная работа №2: Линейные АТД  \n";
    cout << "========================================\n\n";

    int choice;
    do {
        cout << "[ГЛАВНОЕ МЕНЮ]\n";
        cout << "1. DynamicArray<int>\n2. LinkedList<int>\n3. ArraySequence (Mutable)\n4. ArraySequence (Immutable)\n5. ListSequence (Mutable)\n6. ListSequence (Immutable)\n7. BitSequence\n0. Выход\nВыберите: ";

        if (!(cin >> choice)) {
            cerr << "\n[!] Некорректный ввод.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: RunDynamicArrayUI(); break;
            case 2: RunLinkedListUI(); break;
            case 3: RunSequenceUI(true, false); break;
            case 4: RunSequenceUI(true, true); break;
            case 5: RunSequenceUI(false, false); break;
            case 6: RunSequenceUI(false, true); break;
            case 7: RunBitSequenceUI(); break;
            case 0: cout << "\nЗавершение.\n"; break;
            default: cerr << "\n[!] Пункт не найден.\n";
        }
    } while (choice != 0);
    return 0;
}