#include <unistd.h>     // pipe(), fork(), read(), write(), close()
#include <sys/wait.h>   // wait()
#include <iostream>
#include <string>

using namespace std;

int main() {
    int fd[2];

    // Create a pipe (a simple one-way data tunnel)
    // fd[0] → read end (take data out)
    // fd[1] → write end (put data in)
    pipe(fd);

    // fork() makes a copy of this program
    // Now there are TWO processes running the same code
    pid_t pid = fork();

    if (pid == 0) {
        // ===== CHILD PROCESS =====
        // This side will WRITE into the pipe

        // We are not reading here → close read end
        close(fd[0]);

        // Message we want to send through the pipe
        // Using std::string instead of raw char*
        string msg = "hello world\nthis is a test\n";

        // Write the string into the pipe
        // msg.data() → pointer to raw bytes
        // msg.size() → how many bytes to write
        write(fd[1], msg.data(), msg.size());

        // Done writing → close write end
        // This is important so the reader knows "no more data is coming"
        close(fd[1]);
    } else {
        // ===== PARENT PROCESS =====
        // This side will READ from the pipe

        // We are not writing here → close write end
        close(fd[1]);

        // Buffer = temporary box to hold incoming data
        const size_t BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];

        ssize_t bytesRead;

        // Keep reading until there is no more data
        // read(...) returns:
        // >0 → number of bytes read
        //  0 → no more data (writer closed pipe)
        while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0) {

            // Take whatever we received and print it directly
            // STDOUT_FILENO = standard output (your terminal)
            write(STDOUT_FILENO, buffer, bytesRead);
        }

        // Done reading → close read end
        close(fd[0]);

        // Wait for child process to finish
        // Prevents zombie process
        wait(nullptr);
    }
}
