# Week 15: System Protection & Security

## Concept

OS protection prevents unauthorized access to resources. File permissions control read/write/execute access by user/group/others. Access control lists provide fine-grained permission management. Authentication and authorization are fundamental security mechanisms.

## Examples

- `file_permission_demo.cpp` - File permission bits demonstration
- `simple_access_control.cpp` - Simple access control list simulation

## Compile

```bash
g++ -std=c++17 -pthread week-15/system-protection-security/file_permission_demo.cpp -o week-15/system-protection-security/file_permission_demo
g++ -std=c++17 -pthread week-15/system-protection-security/simple_access_control.cpp -o week-15/system-protection-security/simple_access_control
```

## Run

```bash
./week-15/system-protection-security/file_permission_demo
./week-15/system-protection-security/simple_access_control
```

## Learning Outcome

Students will understand:
- File permission bits and their meaning
- Access control mechanisms
- User and group concepts in Unix
- Security principles in OS design
