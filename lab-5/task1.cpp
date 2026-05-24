#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

long long calculateFactorial(int n) {
    if (n <= 1) {
        return 1;
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid < 0) {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (pid == 0) {
        close(fd[1]);

        int number;
        read(fd[0], &number, sizeof(number));
        close(fd[0]);

        cout << "Child process received number: " << number << endl;
        long long factorial = calculateFactorial(number);
        cout << "Factorial of " << number << " is: " << factorial << endl;

        exit(0);
    }
    else {
        close(fd[0]);

        int number;
        cout << "Parent: Enter a number to calculate factorial: ";
        cin >> number;

        write(fd[1], &number, sizeof(number));
        close(fd[1]);

        waitpid(pid, nullptr, 0);
        cout << "Parent: Child process finished" << endl;
    }

    return 0;
}
