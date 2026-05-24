#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex accountMutex, logMutex;
int account_balance = 5000;

void transactionWithoutAvoidance1() {
    cout << "Transaction 1: Attempting to lock Account Record..." << endl;
    accountMutex.lock();
    cout << "Transaction 1: Locked Account Record" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Transaction 1: Attempting to lock Transaction Log..." << endl;
    logMutex.lock();
    cout << "Transaction 1: Locked Transaction Log" << endl;
    
    cout << "Transaction 1: Processing transaction..." << endl;
    account_balance += 1000;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    logMutex.unlock();
    accountMutex.unlock();
    cout << "Transaction 1: Released both resources" << endl;
}

void transactionWithoutAvoidance2() {
    cout << "Transaction 2: Attempting to lock Transaction Log..." << endl;
    logMutex.lock();
    cout << "Transaction 2: Locked Transaction Log" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Transaction 2: Attempting to lock Account Record..." << endl;
    accountMutex.lock();
    cout << "Transaction 2: Locked Account Record" << endl;
    
    cout << "Transaction 2: Processing transaction..." << endl;
    account_balance -= 500;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    accountMutex.unlock();
    logMutex.unlock();
    cout << "Transaction 2: Released both resources" << endl;
}

void transactionWithAvoidance1() {
    cout << "Transaction 1: Attempting to lock Account Record (First)..." << endl;
    accountMutex.lock();
    cout << "Transaction 1: Locked Account Record" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Transaction 1: Attempting to lock Transaction Log (Second)..." << endl;
    logMutex.lock();
    cout << "Transaction 1: Locked Transaction Log" << endl;
    
    cout << "Transaction 1: Processing transaction..." << endl;
    account_balance += 1000;
    this_thread::sleep_for(chrono::milliseconds(50));
    
    logMutex.unlock();
    cout << "Transaction 1: Released Transaction Log" << endl;
    accountMutex.unlock();
    cout << "Transaction 1: Released Account Record" << endl;
}

void transactionWithAvoidance2() {
    cout << "Transaction 2: Attempting to lock Account Record (First)..." << endl;
    accountMutex.lock();
    cout << "Transaction 2: Locked Account Record" << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "Transaction 2: Attempting to lock Transaction Log (Second)..." << endl;
    logMutex.lock();
    cout << "Transaction 2: Locked Transaction Log" << endl;
    
    cout << "Transaction 2: Processing transaction..." << endl;
    account_balance -= 500;
    this_thread::sleep_for(chrono::milliseconds(50));
    
    logMutex.unlock();
    cout << "Transaction 2: Released Transaction Log" << endl;
    accountMutex.unlock();
    cout << "Transaction 2: Released Account Record" << endl;
}

int main() {
    cout << "Banking System - Deadlock Scenario and Avoidance" << endl;
    cout << string(70, '=') << endl;
    
    cout << "\nScenario 1: WITHOUT Deadlock Avoidance (May cause deadlock)" << endl;
    cout << string(70, '-') << endl;
    cout << "Transaction 1: Account Record -> Transaction Log" << endl;
    cout << "Transaction 2: Transaction Log -> Account Record (REVERSED ORDER!)" << endl;
    cout << "\nPossible Result: DEADLOCK (Circular Wait)" << endl;
    cout << string(70, '-') << endl;
    
    cout << "\nScenario 2: WITH Deadlock Avoidance (Resource Ordering)" << endl;
    cout << string(70, '-') << endl;
    cout << "Resource Ordering Rule:" << endl;
    cout << "  1. Account Record (Resource 1 - Higher priority)" << endl;
    cout << "  2. Transaction Log (Resource 2 - Lower priority)" << endl;
    cout << "\nTransaction 1: Account Record -> Transaction Log" << endl;
    cout << "Transaction 2: Account Record -> Transaction Log (SAME ORDER)" << endl;
    cout << "\nResult: NO DEADLOCK (Circular wait prevented)" << endl;
    cout << string(70, '-') << endl;
    
    cout << "\nInitial Account Balance: " << account_balance << endl;
    cout << "\nExecuting transactions with avoidance:\n" << endl;
    
    account_balance = 5000;  // Reset balance
    
    thread t1(transactionWithAvoidance1);
    thread t2(transactionWithAvoidance2);
    
    t1.join();
    t2.join();
    
    cout << "\nFinal Account Balance: " << account_balance << endl;
    cout << "Expected: " << (5000 + 1000 - 500) << endl;
    
    cout << "\n" << string(70, '=') << endl;
    cout << "Analysis:" << endl;
    cout << string(70, '=') << endl;
    cout << "\nDeadlock Avoidance Technique Applied: RESOURCE ORDERING" << endl;
    cout << "\nBenefits:" << endl;
    cout << "1. All transactions follow the same lock acquisition order" << endl;
    cout << "2. Circular wait condition is impossible" << endl;
    cout << "3. System remains live and transactions complete" << endl;
    cout << "4. Account consistency is maintained\n" << endl;
    
    cout << "Resource Utilization: GOOD" << endl;
    cout << "- Resources are held briefly and in order" << endl;
    cout << "- No idle waiting due to circular dependencies\n" << endl;
    
    cout << "Process Execution: SMOOTH" << endl;
    cout << "- Transactions proceed without blocking" << endl;
    cout << "- All operations complete successfully" << endl;
    
    return 0;
}
