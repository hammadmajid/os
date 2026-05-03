#include <unistd.h>     // pipe(), fork(), read(), write(), close()
#include <sys/wait.h>   // wait()
#include <iostream>

int main() {
    int fd[2];

    // Create a pipe
    // Think of this like a tube:
    // fd[1] = where we put data INTO the tube (write end)
    // fd[0] = where we TAKE data OUT of the tube (read end)
    pipe(fd);

    // Create a new process (clone of this program)
    pid_t pid = fork();

    if (pid == 0) {
        // === CHILD PROCESS ===
        // This will act like: cat (it writes data)

        // We do NOT need the read side here
        close(fd[0]);

        // This is the data we will send into the pipe
        const char* msg = "hello\nworld\n";

        // Put data into the pipe (like pouring water into a tube)
        write(fd[1], msg, 12);

        // Done writing → close the pipe end
        close(fd[1]);
    } else {
        // === PARENT PROCESS ===
        // This will act like: wc -l (it reads data and counts lines)

        // We do NOT need the write side here
        close(fd[1]);

        char c;
        int lines = 0;

        // Read ONE BYTE at a time from the pipe
        // This keeps going until there is no more data
        while (read(fd[0], &c, 1) > 0) {

            // If we see a newline, count it
            if (c == '\n') {
                lines++;
            }
        }

        // Done reading → close pipe
        close(fd[0]);

        // Wait for child process to finish
        wait(nullptr);

        // Print result
        std::cout << lines << "\n";
    }
}
