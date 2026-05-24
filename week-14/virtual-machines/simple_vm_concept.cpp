// g++ -std=c++17 simple_vm_concept.cpp -o simple_vm_concept

#include <iostream>
using namespace std;

struct VirtualMachine {
    int registers[4];       // R0-R3
    int memory[256];        // Virtual memory
    int programCounter;
    int instructionCount;
};

int main() {
    VirtualMachine vm;
    
    // Initialize VM
    for (int i = 0; i < 4; i++) vm.registers[i] = 0;
    for (int i = 0; i < 256; i++) vm.memory[i] = 0;
    vm.programCounter = 0;
    vm.instructionCount = 0;
    
    cout << "=== SIMPLE VIRTUAL MACHINE ===" << endl << endl;
    
    cout << "VM Architecture:" << endl;
    cout << "- 4 general-purpose registers (R0-R3)" << endl;
    cout << "- 256-byte virtual memory" << endl;
    cout << "- Simple instruction set" << endl << endl;
    
    // Simulate some instructions
    cout << "Simulating instructions..." << endl << endl;
    
    // Instruction 1: LOAD R0, 42
    cout << "1. LOAD R0, 42" << endl;
    vm.registers[0] = 42;
    cout << "   R0 = " << vm.registers[0] << endl;
    
    // Instruction 2: LOAD R1, 8
    cout << "2. LOAD R1, 8" << endl;
    vm.registers[1] = 8;
    cout << "   R1 = " << vm.registers[1] << endl;
    
    // Instruction 3: ADD R2, R0, R1
    cout << "3. ADD R2, R0, R1" << endl;
    vm.registers[2] = vm.registers[0] + vm.registers[1];
    cout << "   R2 = " << vm.registers[2] << endl;
    
    // Instruction 4: STORE R2, address 10
    cout << "4. STORE R2, address 10" << endl;
    vm.memory[10] = vm.registers[2];
    cout << "   memory[10] = " << vm.memory[10] << endl;
    
    // Instruction 5: LOAD R3, address 10
    cout << "5. LOAD R3, address 10" << endl;
    vm.registers[3] = vm.memory[10];
    cout << "   R3 = " << vm.registers[3] << endl;
    
    cout << "\nVM State After Execution:" << endl;
    cout << "Registers: R0=" << vm.registers[0] << " R1=" << vm.registers[1] 
         << " R2=" << vm.registers[2] << " R3=" << vm.registers[3] << endl;
    cout << "Memory[10]: " << vm.memory[10] << endl;
    
    return 0;
}
