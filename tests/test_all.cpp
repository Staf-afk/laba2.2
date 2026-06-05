#include <iostream>
#include <cstdlib>

void runTest(const std::string& name, const std::string& command) {
    std::cout << "\n\n" << std::string(80, '=') << std::endl;
    std::cout << "‡€“‘Š: " << name << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    int result = std::system(command.c_str());
    
    if (result == 0) {
        std::cout << "\n[OK] " << name << " “‘…˜Ž ‚›Ž‹…" << std::endl;
    } else {
        std::cout << "\n[FAIL] " << name << " … ‚›Ž‹… (ª®¤ ®è¨¡ª¨: " << result << ")" << std::endl;
    }
}

int main() {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "€Ž ’…‘’Ž‚ ‘’“Š’“ „€›•" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    runTest("’¥áâë DynamicArray", "./test_dynamic_array.exe");
    runTest("’¥áâë LinkedList", "./test_linked_list.exe");
    runTest("’¥áâë BitSequence", "./test_bit_sequence.exe");
    runTest("’¥áâë ¯®á«¥¤®¢ â¥«ì­®áâ¥© (ArraySequence ¨ ListSequence)", "./test_sequences.exe");
    runTest("’¥áâë SetSequence (Œ­®¦¥áâ¢®)", "./test_set_sequence.exe");  // ? ¤®¡ ¢¨âì íâã áâà®ªã
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "‚‘… ’…‘’› ‡€‚…˜…›" << std::endl;
    std::cout << std::string(80, '=') << std::endl << std::endl;
    
    return 0;
}


