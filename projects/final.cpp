#include <cstring>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

// ================= GLOBAL VARIABLES =================

pthread_mutex_t runwayLock;
pthread_mutex_t ticketLock;
pthread_mutex_t baggageLock;

sem_t emptySlots;
sem_t fullSlots;

queue<int> baggageBuffer;

const int BUFFER_SIZE = 5;
int tickets = 10;

// ================= RUNWAY MANAGEMENT =================

void *airplane(void *arg) {
  int id = *((int *)arg);

  cout << "\nPlane " << id << " requesting runway..." << endl;

  pthread_mutex_lock(&runwayLock);

  cout << "Plane " << id << " using runway" << endl;

  sleep(2);

  cout << "Plane " << id << " completed operation" << endl;

  pthread_mutex_unlock(&runwayLock);

  pthread_exit(NULL);
}

// ================= TICKET BOOKING =================

void *passenger(void *arg) {
  int id = *((int *)arg);

  pthread_mutex_lock(&ticketLock);

  if (tickets > 0) {
    cout << "Passenger " << id << " booked ticket" << endl;

    tickets--;

    cout << "Remaining Tickets: " << tickets << endl;
  }

  else {
    cout << "No tickets available for Passenger " << id << endl;
  }

  pthread_mutex_unlock(&ticketLock);

  pthread_exit(NULL);
}

// ================= PRODUCER =================

void *producer(void *arg) {
  for (int i = 1; i <= 10; i++) {
    sem_wait(&emptySlots);

    pthread_mutex_lock(&baggageLock);

    baggageBuffer.push(i);

    cout << "Produced baggage " << i << endl;

    pthread_mutex_unlock(&baggageLock);

    sem_post(&fullSlots);

    sleep(1);
  }

  pthread_exit(NULL);
}

// ================= CONSUMER =================

void *consumer(void *arg) {
  for (int i = 1; i <= 10; i++) {
    sem_wait(&fullSlots);

    pthread_mutex_lock(&baggageLock);

    int item = baggageBuffer.front();

    baggageBuffer.pop();

    cout << "Loaded baggage " << item << endl;

    pthread_mutex_unlock(&baggageLock);

    sem_post(&emptySlots);

    sleep(2);
  }

  pthread_exit(NULL);
}

// ================= FCFS SCHEDULING =================

class Flight {
public:
  string name;
  int arrival;

  Flight(string n, int a) {
    name = n;
    arrival = a;
  }
};

void FCFS() {
  cout << "\n===== FCFS Scheduling =====\n";

  vector<Flight> flights;

  flights.push_back(Flight("PK101", 1));

  flights.push_back(Flight("EK202", 2));

  flights.push_back(Flight("QR303", 3));

  cout << "\nArrival Order:\n";

  for (auto x : flights) {
    cout << x.name << " Time=" << x.arrival << endl;
  }

  cout << "\nExecution Order:\n";

  for (auto x : flights) {
    cout << x.name << " ";
  }

  cout << endl;
}

// ================= IPC USING PIPE =================

void IPC() {
  int fd[2];

  if (pipe(fd) == -1) {
    cout << "Pipe creation failed\n";
    return;
  }

  pid_t pid = fork();

  if (pid < 0) {
    cout << "Fork failed\n";
    return;
  }

  if (pid == 0) {
    close(fd[1]);

    char message[100];

    int bytes = read(fd[0], message, sizeof(message) - 1);

    if (bytes > 0) {
      message[bytes] = '\0';
    }

    cout << "\nAirplane Process Received:\n" << message << endl;

    close(fd[0]);
  }

  else {
    close(fd[0]);

    char msg[] = "Permission Granted To Land";

    if (write(fd[1], msg, strlen(msg) + 1) == -1) {
      cout << "Write Error" << endl;
    }

    wait(NULL);

    close(fd[1]);
  }
}

// ================= MAIN =================

int main() {
  pthread_mutex_init(&runwayLock, NULL);

  pthread_mutex_init(&ticketLock, NULL);

  pthread_mutex_init(&baggageLock, NULL);

  sem_init(&emptySlots, 0, BUFFER_SIZE);

  sem_init(&fullSlots, 0, 0);

  cout << "\n==========================";
  cout << "\nAIRPORT MANAGEMENT SYSTEM";
  cout << "\n==========================\n";

  // Runway Module

  pthread_t planes[3];

  int planeID[3] = {1, 2, 3};

  for (int i = 0; i < 3; i++) {
    pthread_create(&planes[i], NULL, airplane, &planeID[i]);
  }

  for (int i = 0; i < 3; i++) {
    pthread_join(planes[i], NULL);
  }

  // Ticket Booking

  pthread_t passengers[5];

  int ids[5] = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; i++) {
    pthread_create(&passengers[i], NULL, passenger, &ids[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(passengers[i], NULL);
  }

  // Producer Consumer

  pthread_t prod;
  pthread_t cons;

  pthread_create(&prod, NULL, producer, NULL);

  pthread_create(&cons, NULL, consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  // Scheduling

  FCFS();

  // IPC

  IPC();

  // Cleanup

  pthread_mutex_destroy(&runwayLock);

  pthread_mutex_destroy(&ticketLock);

  pthread_mutex_destroy(&baggageLock);

  sem_destroy(&emptySlots);

  sem_destroy(&fullSlots);

  return 0;
}
