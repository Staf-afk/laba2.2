#include <iostream>
#include <cstdlib>

void runTest(const std::string& name, const std::string& command) {
    std::cout << "\n\n" << std::string(80, '=') << std::endl;
    std::cout << "‡€“‘: " << name << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    int result = std::system(command.c_str());
    
    if (result == 0) {
        std::cout << "\n[OK] " << name << " “‘… ‚›‹…" << std::endl;
    } else {
        std::cout << "\n[FAIL] " << name << " … ‚›‹… (ª®¤ ®θ¨΅ª¨: " << result << ")" << std::endl;
    }
}

int main() {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "€ ’…‘’‚ ‘’“’“ „€›•" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    runTest("’¥αβλ DynamicArray", "./test_dynamic_array.exe");
    runTest("’¥αβλ LinkedList", "./test_linked_list.exe");
    runTest("’¥αβλ BitSequence", "./test_bit_sequence.exe");
    runTest("’¥αβλ ―®α«¥¤®Ά β¥«μ­®αβ¥© (ArraySequence ¨ ListSequence)", "./test_sequences.exe");
    runTest("’¥αβλ SetSequence (­®¦¥αβΆ®)", "./test_set_sequence.exe");
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "‚‘… ’…‘’› ‡€‚……›" << std::endl;
    std::cout << std::string(80, '=') << std::endl << std::endl;
    
    return 0;
}


