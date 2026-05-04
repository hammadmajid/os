#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    // File descriptor arrays for pipes: [0] for read, [1] for write
    int p2c[2], c2p[2]; 
    char question[40] = "What is 5+3?";
    char answer[20], reply[20];

    // Initialize pipes for inter-process communication
    pipe(p2c); // Parent-to-child pipe
    pipe(c2p); // Child-to-parent pipe

    // Create a child process
    if (fork() == 0) { 
        // Child Process (Student)
        // Read data sent by the parent from the p2c pipe
        read(p2c[0], question, sizeof(question));
        printf("Student recieved question: %s\n", question);
        
        // Prepare and write response to the c2p pipe
        strcpy(answer, "8");
        write(c2p[1], answer, strlen(answer) + 1);
    } else { 
        // Parent Process (Teacher)
        // Write data to the p2c pipe for the child to receive
        write(p2c[1], question, strlen(question) + 1);
        
        // Read the child's response from the c2p pipe
        read(c2p[0], reply, sizeof(reply));
        printf("Teacher recieved answer: %s\n", reply);
        
        // Logic to verify the received string
        if (strcmp(reply, "8") == 0) {
            printf("Correct answer\n");
        } else {
            printf("Wrong Answer\n");
        }
        return 0;
    }
}
