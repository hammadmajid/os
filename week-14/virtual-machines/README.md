# Week 14: Virtual Machines

## Concept

Virtual machines abstract hardware by simulating a complete computer system. Hypervisors manage multiple VMs on shared physical hardware. VMs can run different OSes and provide isolation between guest systems. Bytecode interpreters simulate instruction execution.

## Examples

- `simple_vm_concept.cpp` - Basic virtual machine structure
- `bytecode_interpreter.cpp` - Simple bytecode instruction interpreter

## Compile

```bash
g++ -std=c++17 -pthread week-14/virtual-machines/simple_vm_concept.cpp -o week-14/virtual-machines/simple_vm_concept
g++ -std=c++17 -pthread week-14/virtual-machines/bytecode_interpreter.cpp -o week-14/virtual-machines/bytecode_interpreter
```

## Run

```bash
./week-14/virtual-machines/simple_vm_concept
./week-14/virtual-machines/bytecode_interpreter
```

## Learning Outcome

Students will understand:
- Virtual machine architecture
- CPU virtualization concepts
- Bytecode execution models
- How VMs provide abstraction and isolation
