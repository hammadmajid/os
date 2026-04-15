#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

struct User {
  string username;
  string password;
  string role; // Admin or Employee
};

unordered_map<string, User> users;
unordered_map<string, int> userResources; // RAM & Storage tracking

// Function to load users from auth.csv
void loadUsers() {
  ifstream file("auth.csv");
  string line, username, password, role;
  while (getline(file, line)) {
    stringstream ss(line);
    getline(ss, username, ',');
    getline(ss, password, ',');
    getline(ss, role, ',');
    users[username] = {username, password, role};
    userResources[username] = 100; // Default resource allocation
  }
  file.close();
}

// Function to save users to auth.csv
void saveUsers() {
  ofstream file("auth.csv");
  for (const auto &pair : users) {
    file << pair.second.username << "," << pair.second.password << ","
         << pair.second.role << "\n";
  }
  file.close();
}

// Function to authenticate user
User *authenticateUser(string username, string password) {
  if (users.find(username) != users.end() &&
      users[username].password == password) {
    return &users[username];
  }
  return nullptr;
}

// Function to create a new user (Admin only)
void createUser() {
  string username, password, role;
  cout << "Enter new username: ";
  cin >> username;
  cout << "Enter password: ";
  cin >> password;
  cout << "Enter role (Admin/Employee): ";
  cin >> role;
  if (role != "Admin" && role != "Employee") {
    cout << "Invalid role!\n";
    return;
  }
  users[username] = {username, password, role};
  userResources[username] = 100;
  saveUsers();
  cout << "User created successfully!\n";
}

// Function to delete a user (Admin only)
void deleteUser() {
  string username;
  cout << "Enter username to delete: ";
  cin >> username;
  if (users.erase(username)) {
    saveUsers();
    cout << "User deleted successfully!\n";
  } else {
    cout << "User not found!\n";
  }
}

// Function to allocate resources (Admin only)
void allocateResources() {
  string username;
  int ram;
  cout << "Enter username: ";
  cin >> username;
  if (users.find(username) == users.end()) {
    cout << "User not found!\n";
    return;
  }
  cout << "Enter RAM allocation: ";
  cin >> ram;
  userResources[username] = ram;
  cout << "Resources updated!\n";
}

// Function to manage file operations
void manageFiles() {
  string command, filename;
  cout << "Enter operation (create/delete) and filename: ";
  cin >> command >> filename;
  if (command == "create") {
    ofstream file(filename);
    if (file) {
      cout << "File created successfully!\n";
    }
  } else if (command == "delete") {
    if (remove(filename.c_str()) == 0) {
      cout << "File deleted successfully!\n";
    } else {
      cout << "File deletion failed!\n";
    }
  } else {
    cout << "Invalid command!\n";
  }
}


void adminPortal(User *user) {
  cout << "Welcome, Admin " << user->username << "!\n";
  int choice;
  do {
    cout << "1. Create User\n2. Delete User\n3. Allocate Resources\n4. Manage "
            "Files\n5. Logout\n";
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      createUser();
      break;
    case 2:
      deleteUser();
      break;
    case 3:
      allocateResources();
      break;
    case 4:
      manageFiles();
      break;
    case 5:
      cout << "Logging out...\n";
      break;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 5);
}

void employeePortal(User *user) {
  cout << "Welcome, Employee " << user->username << "!\n";
  int choice;
  do {
    cout << "1. View Resources\n2. Manage Files\n3. Logout\n";
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "Allocated RAM: " << userResources[user->username] << "MB\n";
      break;
    case 2:
      manageFiles();
      break;
    case 3:
      cout << "Logging out...\n";
      break;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 3);
}

int main() {
  loadUsers();
  string username, password;
  cout << "Enter username: ";
  cin >> username;
  cout << "Enter password: ";
  cin >> password;
  User *user = authenticateUser(username, password);
  if (user) {
    if (user->role == "Admin") {
      adminPortal(user);
    } else {
      employeePortal(user);
    }
  } else {
    cout << "Invalid credentials!\n";
  }
  return 0;
}
