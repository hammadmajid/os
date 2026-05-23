// g++ -std=c++17 bytecode_interpreter.cpp -o bytecode_interpreter

#include <iostream>
using namespace std;

int main() {
    // Simple bytecode: stack-based VM
    const int MAX_STACK = 256;
    int stack[MAX_STACK];
    int stackPointer = 0;
    
    // Bytecode instructions
    enum Instruction {
        PUSH,  // Push value onto stack
        POP,   // Pop from stack
        ADD,   // Add top two stack values
        SUB,   // Subtract
        MUL,   // Multiply
        PRINT  // Print top of stack
    };
    
    cout << "=== BYTECODE INTERPRETER ===" << endl;
    cout << "Stack-based virtual machine with simple bytecode\n" << endl;
    
    // Helper lambda for stack operations
    auto push = [&](int value) {
        if (stackPointer < MAX_STACK) {
            stack[stackPointer++] = value;
            cout << "PUSH " << value << " -> stack: [";
            for (int i = 0; i < stackPointer; i++) {
                cout << stack[i] << (i < stackPointer - 1 ? ", " : "");
            }
            cout << "]" << endl;
        }
    };
    
    auto binaryOp = [&](const char* op, int (*func)(int, int)) {
        if (stackPointer >= 2) {
            int b = stack[--stackPointer];
            int a = stack[--stackPointer];
            int result = func(a, b);
            push(result);
            cout << "Executed: " << a << " " << op << " " << b << " = " << result << endl;
        }
    };
    
    // Execute bytecode sequence
    cout << "Executing bytecode: PUSH 10, PUSH 20, ADD, PRINT\n" << endl;
    
    // PUSH 10
    push(10);
    
    // PUSH 20
    push(20);
    
    // ADD
    cout << "ADD" << endl;
    binaryOp("+", [](int a, int b) { return a + b; });
    
    // PRINT
    cout << "PRINT" << endl;
    if (stackPointer > 0) {
        cout << "Result: " << stack[stackPointer - 1] << endl;
    }
    
    cout << "\nExecuting more bytecode: PUSH 5, PUSH 3, MUL\n" << endl;
    
    // PUSH 5
    push(5);
    
    // PUSH 3
    push(3);
    
    // MUL
    cout << "MUL" << endl;
    binaryOp("*", [](int a, int b) { return a * b; });
    
    cout << "\nFinal stack state: [";
    for (int i = 0; i < stackPointer; i++) {
        cout << stack[i] << (i < stackPointer - 1 ? ", " : "");
    }
    cout << "]" << endl;
    
    return 0;
}
