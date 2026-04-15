#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <cctype>

using namespace std;
namespace fs = filesystem;

// ==================== CONSTANTS ====================
const int MAX_RAM_PER_USER = 2048;
const int MAX_STORAGE_PER_USER = 10240;
const int DEFAULT_RAM = 100;
const int DEFAULT_STORAGE = 1024;
const int MIN_PASSWORD_LENGTH = 4;
const string AUTH_CSV_FILE = "auth.csv";
const string WORK_DIR = "user_files";

// ==================== UTILITY FUNCTIONS ====================

void printHeader(const string& title) {
    cout << "\n╔════════════════════════════════════════════════════════╗\n";
    cout << "║  " << string((50 - title.length()) / 2, ' ') << title 
         << string((51 - title.length()) / 2, ' ') << "║\n";
    cout << "╚════════════════════════════════════════════════════════╝\n";
}

void printSeparator() {
    cout << "──────────────────────────────────────────────────────\n";
}

void printSuccess(const string& message) {
    cout << "✓ " << message << "\n";
}

void printError(const string& message) {
    cout << "✗ " << message << "\n";
}

void printInfo(const string& message) {
    cout << "ℹ " << message << "\n";
}

string encodeBase64(const string& input) {
    string cmd = "echo -n \"" + input + "\" | base64";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw runtime_error("Failed to execute base64 encoding command");
    }
    
    string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    int status = pclose(pipe);
    if (status != 0) {
        throw runtime_error("Base64 encoding failed");
    }
    
    // Remove trailing newline
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}

string decodeBase64(const string& input) {
    string cmd = "echo -n \"" + input + "\" | base64 -d";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw runtime_error("Failed to execute base64 decoding command");
    }
    
    string result;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    int status = pclose(pipe);
    if (status != 0) {
        throw runtime_error("Base64 decoding failed");
    }
    
    return result;
}

bool isValidPassword(const string& password) {
    if (password.length() < MIN_PASSWORD_LENGTH) {
        return false;
    }
    bool hasNumber = false;
    for (char c : password) {
        if (isdigit(c)) {
            hasNumber = true;
            break;
        }
    }
    return hasNumber;
}

// ==================== USER CLASS ====================

class User {
private:
    string username;
    string password; // Stored as plain text in memory
    string role;

public:
    User() = default;

    User(const string& u, const string& p, const string& r) 
        : username(u), password(p), role(r) {
        if (!isValidPassword(p)) {
            throw invalid_argument("Password must be at least 4 characters with at least one number");
        }
        if (r != "Admin" && r != "Employee") {
            throw invalid_argument("Role must be 'Admin' or 'Employee'");
        }
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }

    void setPassword(const string& newPassword) {
        if (!isValidPassword(newPassword)) {
            throw invalid_argument("Password must be at least 4 characters with at least one number");
        }
        password = newPassword;
    }

    bool isAdmin() const { return role == "Admin"; }
};

// ==================== RESOURCE MANAGER CLASS ====================

class ResourceManager {
private:
    unordered_map<string, int> ramAllocations;
    unordered_map<string, int> storageAllocations;

public:
    ResourceManager() = default;

    void addUser(const string& username, int ram, int storage) {
        ramAllocations[username] = ram;
        storageAllocations[username] = storage;
    }

    void allocateRam(const string& username, int amount) {
        if (amount < 0 || amount > MAX_RAM_PER_USER) {
            throw out_of_range("RAM must be between 0 and " + to_string(MAX_RAM_PER_USER) + " MB");
        }
        ramAllocations[username] = amount;
    }

    void allocateStorage(const string& username, int amount) {
        if (amount < 0 || amount > MAX_STORAGE_PER_USER) {
            throw out_of_range("Storage must be between 0 and " + to_string(MAX_STORAGE_PER_USER) + " MB");
        }
        storageAllocations[username] = amount;
    }

    int getRam(const string& username) const {
        auto it = ramAllocations.find(username);
        if (it != ramAllocations.end()) {
            return it->second;
        }
        throw runtime_error("User not found in resource manager");
    }

    int getStorage(const string& username) const {
        auto it = storageAllocations.find(username);
        if (it != storageAllocations.end()) {
            return it->second;
        }
        throw runtime_error("User not found in resource manager");
    }

    void removeUser(const string& username) {
        ramAllocations.erase(username);
        storageAllocations.erase(username);
    }

    unordered_map<string, int> getRamMap() const {
        return ramAllocations;
    }

    unordered_map<string, int> getStorageMap() const {
        return storageAllocations;
    }
};

// ==================== FILE MANAGER CLASS ====================

class FileManager {
private:
    fs::path workingDirectory;

    bool isPathSafe(const string& filename) {
        fs::path filePath = workingDirectory / filename;
        fs::path absPath = fs::absolute(filePath);
        fs::path absWorkDir = fs::absolute(workingDirectory);
        
        return absPath.string().find(absWorkDir.string()) == 0;
    }

public:
    FileManager(const string& baseDir = WORK_DIR) : workingDirectory(baseDir) {
        if (!fs::exists(workingDirectory)) {
            fs::create_directories(workingDirectory);
            printSuccess("Created user_files directory");
        }
    }

    void createFile(const string& filename) {
        if (!isPathSafe(filename)) {
            throw runtime_error("Access denied: File path is outside allowed directory");
        }
        
        fs::path filePath = workingDirectory / filename;
        ofstream file(filePath);
        if (!file) {
            throw runtime_error("Failed to create file: " + filename);
        }
        file.close();
    }

    void deleteFile(const string& filename) {
        if (!isPathSafe(filename)) {
            throw runtime_error("Access denied: File path is outside allowed directory");
        }
        
        fs::path filePath = workingDirectory / filename;
        if (!fs::exists(filePath)) {
            throw runtime_error("File not found: " + filename);
        }
        
        if (fs::remove(filePath) == 0) {
            throw runtime_error("Failed to delete file: " + filename);
        }
    }

    vector<string> listFiles() {
        vector<string> files;
        try {
            for (const auto& entry : fs::directory_iterator(workingDirectory)) {
                if (fs::is_regular_file(entry)) {
                    files.push_back(entry.path().filename().string());
                }
            }
        } catch (const fs::filesystem_error& e) {
            throw runtime_error("Failed to list files: " + string(e.what()));
        }
        return files;
    }

    int getFileSize(const string& filename) {
        if (!isPathSafe(filename)) {
            throw runtime_error("Access denied: Cannot access this file");
        }
        
        fs::path filePath = workingDirectory / filename;
        if (!fs::exists(filePath)) {
            throw runtime_error("File not found: " + filename);
        }
        return fs::file_size(filePath);
    }
};

// ==================== USER MANAGER CLASS ====================

class UserManager {
private:
    unordered_map<string, User> users;
    ResourceManager resourceManager;
    string csvFile;

public:
    UserManager(const string& csvPath = AUTH_CSV_FILE) : csvFile(csvPath) {}

    void initializeCSV() {
        if (!fs::exists(csvFile)) {
            ofstream file(csvFile);
            if (!file) {
                throw runtime_error("Failed to create auth.csv");
            }
            file.close();
            printSuccess("Created auth.csv");
        }
    }

    bool isCSVEmpty() {
        ifstream file(csvFile);
        if (!file) {
            return true;
        }
        string line;
        return !getline(file, line);
    }

    void loadUsers() {
        users.clear();
        ifstream file(csvFile);
        if (!file) {
            throw runtime_error("Failed to open auth.csv");
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string username, encodedPassword, role, ramStr, storageStr;

            if (!getline(ss, username, ',') || 
                !getline(ss, encodedPassword, ',') || 
                !getline(ss, role, ',') || 
                !getline(ss, ramStr, ',') || 
                !getline(ss, storageStr, ',')) {
                continue;
            }

            try {
                string decodedPassword = decodeBase64(encodedPassword);
                int ram = stoi(ramStr);
                int storage = stoi(storageStr);

                users[username] = User(username, decodedPassword, role);
                resourceManager.addUser(username, ram, storage);
            } catch (const exception& e) {
                printError("Error loading user " + username + ": " + string(e.what()));
            }
        }
        file.close();
    }

    void saveUsers() {
        ofstream file(csvFile);
        if (!file) {
            throw runtime_error("Failed to open auth.csv for writing");
        }

        for (const auto& pair : users) {
            const User& user = pair.second;
            string encodedPassword = encodeBase64(user.getPassword());
            int ram = resourceManager.getRam(user.getUsername());
            int storage = resourceManager.getStorage(user.getUsername());

            file << user.getUsername() << "," << encodedPassword << ","
                 << user.getRole() << "," << ram << "," << storage << "\n";
        }
        file.close();
    }

    User* authenticateUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.getPassword() == password) {
            return &it->second;
        }
        throw runtime_error("Invalid credentials");
    }

    void createUser(const string& username, const string& password, const string& role) {
        if (users.find(username) != users.end()) {
            throw runtime_error("Username already exists");
        }

        users[username] = User(username, password, role);
        resourceManager.addUser(username, DEFAULT_RAM, DEFAULT_STORAGE);
        saveUsers();
    }

    void deleteUser(const string& username) {
        if (users.find(username) == users.end()) {
            throw runtime_error("User not found");
        }

        users.erase(username);
        resourceManager.removeUser(username);
        saveUsers();
    }

    vector<User> getAllUsers() {
        vector<User> userList;
        for (const auto& pair : users) {
            userList.push_back(pair.second);
        }
        return userList;
    }

    ResourceManager& getResourceManager() {
        return resourceManager;
    }

    const ResourceManager& getResourceManager() const {
        return resourceManager;
    }

    bool userExists(const string& username) const {
        return users.find(username) != users.end();
    }
};

// ==================== PORTAL BASE CLASS ====================

class Portal {
protected:
    User* currentUser;
    UserManager* userManager;
    FileManager fileManager;

    void displayMenuHeader() {
        cout << "\n┌────────────────────────────────────────────────────────┐\n";
    }

    void displayMenuFooter() {
        cout << "└────────────────────────────────────────────────────────┘\n";
    }

    void displayMenuOption(int number, const string& description) {
        cout << "│ " << number << ". " << description 
             << string(51 - to_string(number).length() - description.length(), ' ') << "│\n";
    }

public:
    Portal(User* user, UserManager* manager) 
        : currentUser(user), userManager(manager) {}

    virtual ~Portal() = default;
    virtual void run() = 0;
};

// ==================== ADMIN PORTAL CLASS ====================

class AdminPortal : public Portal {
private:
    void displayUserList() {
        printHeader("User List");
        
        try {
            vector<User> users = userManager->getAllUsers();
            
            if (users.empty()) {
                printInfo("No users found");
                return;
            }

            cout << "┌──────────────┬──────────────┬─────────┬──────────┬───────────┐\n";
            cout << "│ Username     │ Role         │ RAM(MB) │ Stor(MB) │ Access    │\n";
            cout << "├──────────────┼──────────────┼─────────┼──────────┼───────────┤\n";

            for (const auto& user : users) {
                int ram = userManager->getResourceManager().getRam(user.getUsername());
                int storage = userManager->getResourceManager().getStorage(user.getUsername());
                
                printf("│ %-12s │ %-12s │ %7d │ %8d │ ✓ Full    │\n",
                       user.getUsername().c_str(),
                       user.getRole().c_str(),
                       ram, storage);
            }

            cout << "└──────────────┴──────────────┴─────────┴──────────┴───────────┘\n";
        } catch (const exception& e) {
            printError(e.what());
        }
    }

    void createUserMenu() {
        string username, password, passwordConfirm, role;

        cout << "\n┌────────────────────────────────────────────────────────┐\n";
        cout << "│  Enter Username: ";
        cin >> username;
        cout << "│  Enter Password: ";
        cin >> password;
        cout << "│  Confirm Password: ";
        cin >> passwordConfirm;
        cout << "│  Enter Role (Admin/Employee): ";
        cin >> role;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            if (password != passwordConfirm) {
                printError("Passwords do not match");
                return;
            }

            userManager->createUser(username, password, role);
            printSuccess("User '" + username + "' created successfully");
        } catch (const exception& e) {
            printError(e.what());
        }
    }

    void deleteUserMenu() {
        displayUserList();
        string username;

        cout << "\n│ Enter username to delete: ";
        cin >> username;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            userManager->deleteUser(username);
            printSuccess("User '" + username + "' deleted successfully");
        } catch (const exception& e) {
            printError(e.what());
        }
    }

    void allocateResourcesMenu() {
        displayUserList();
        string username;
        int ram, storage;

        cout << "\n│ Enter username: ";
        cin >> username;
        cout << "│ Enter RAM allocation (MB): ";
        cin >> ram;
        cout << "│ Enter Storage allocation (MB): ";
        cin >> storage;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            if (!userManager->userExists(username)) {
                printError("User not found");
                return;
            }

            userManager->getResourceManager().allocateRam(username, ram);
            userManager->getResourceManager().allocateStorage(username, storage);
            userManager->saveUsers();
            printSuccess("Resources updated for user '" + username + "'");
        } catch (const exception& e) {
            printError(e.what());
        }
    }

    void manageFilesMenu() {
        string command, filename;

        printHeader("File Management");
        cout << "├────────────────────────────────────────────────────────┤\n";
        displayMenuOption(1, "Create File");
        displayMenuOption(2, "Delete File");
        displayMenuOption(3, "List Files");
        displayMenuOption(4, "Back to Main Menu");
        displayMenuFooter();

        cout << "│ Enter choice: ";
        cin >> command;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            if (command == "1") {
                cout << "│ Enter filename: ";
                cin >> filename;
                cout << "└────────────────────────────────────────────────────────┘\n";
                fileManager.createFile(filename);
                printSuccess("File '" + filename + "' created successfully");
            } else if (command == "2") {
                cout << "│ Enter filename: ";
                cin >> filename;
                cout << "└────────────────────────────────────────────────────────┘\n";
                fileManager.deleteFile(filename);
                printSuccess("File '" + filename + "' deleted successfully");
            } else if (command == "3") {
                vector<string> files = fileManager.listFiles();
                printHeader("File List");
                if (files.empty()) {
                    printInfo("No files found");
                } else {
                    cout << "┌──────────────────────────────────────────────────────┐\n";
                    for (size_t i = 0; i < files.size(); ++i) {
                        printf("│ %-54s │\n", files[i].c_str());
                    }
                    cout << "└──────────────────────────────────────────────────────┘\n";
                }
            }
        } catch (const exception& e) {
            printError(e.what());
        }
    }

public:
    AdminPortal(User* user, UserManager* manager) : Portal(user, manager) {}

    void run() override {
        int choice;
        do {
            printHeader("Admin Portal - " + currentUser->getUsername());
            displayMenuHeader();
            displayMenuOption(1, "List All Users");
            displayMenuOption(2, "Create User");
            displayMenuOption(3, "Delete User");
            displayMenuOption(4, "Allocate Resources");
            displayMenuOption(5, "Manage Files");
            displayMenuOption(6, "Logout");
            displayMenuFooter();

            cout << "│ Enter choice: ";
            cin >> choice;
            cout << "└────────────────────────────────────────────────────────┘\n";

            switch (choice) {
            case 1:
                displayUserList();
                break;
            case 2:
                createUserMenu();
                break;
            case 3:
                deleteUserMenu();
                break;
            case 4:
                allocateResourcesMenu();
                break;
            case 5:
                manageFilesMenu();
                break;
            case 6:
                printInfo("Logging out...");
                break;
            default:
                printError("Invalid choice");
            }
        } while (choice != 6);
    }
};

// ==================== EMPLOYEE PORTAL CLASS ====================

class EmployeePortal : public Portal {
private:
    void viewResourcesMenu() {
        printHeader("Resource Allocation");

        try {
            int ram = userManager->getResourceManager().getRam(currentUser->getUsername());
            int storage = userManager->getResourceManager().getStorage(currentUser->getUsername());

            cout << "┌────────────────────────────────────────────────────────┐\n";
            cout << "│ Username:      " << currentUser->getUsername() << "\n";
            cout << "│ RAM Allocated: " << ram << " MB\n";
            cout << "│ Storage:       " << storage << " MB\n";
            cout << "└────────────────────────────────────────────────────────┘\n";
        } catch (const exception& e) {
            printError(e.what());
        }
    }

    void manageFilesMenu() {
        string command, filename;

        printHeader("File Management");
        cout << "├────────────────────────────────────────────────────────┤\n";
        displayMenuOption(1, "Create File");
        displayMenuOption(2, "Delete File");
        displayMenuOption(3, "List Files");
        displayMenuOption(4, "Back to Main Menu");
        displayMenuFooter();

        cout << "│ Enter choice: ";
        cin >> command;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            if (command == "1") {
                cout << "│ Enter filename: ";
                cin >> filename;
                cout << "└────────────────────────────────────────────────────────┘\n";
                fileManager.createFile(filename);
                printSuccess("File '" + filename + "' created successfully");
            } else if (command == "2") {
                cout << "│ Enter filename: ";
                cin >> filename;
                cout << "└────────────────────────────────────────────────────────┘\n";
                fileManager.deleteFile(filename);
                printSuccess("File '" + filename + "' deleted successfully");
            } else if (command == "3") {
                vector<string> files = fileManager.listFiles();
                printHeader("File List");
                if (files.empty()) {
                    printInfo("No files found");
                } else {
                    cout << "┌──────────────────────────────────────────────────────┐\n";
                    for (size_t i = 0; i < files.size(); ++i) {
                        printf("│ %-54s │\n", files[i].c_str());
                    }
                    cout << "└──────────────────────────────────────────────────────┘\n";
                }
            }
        } catch (const exception& e) {
            printError(e.what());
        }
    }

public:
    EmployeePortal(User* user, UserManager* manager) : Portal(user, manager) {}

    void run() override {
        int choice;
        do {
            printHeader("Employee Portal - " + currentUser->getUsername());
            displayMenuHeader();
            displayMenuOption(1, "View Resources");
            displayMenuOption(2, "Manage Files");
            displayMenuOption(3, "Logout");
            displayMenuFooter();

            cout << "│ Enter choice: ";
            cin >> choice;
            cout << "└────────────────────────────────────────────────────────┘\n";

            switch (choice) {
            case 1:
                viewResourcesMenu();
                break;
            case 2:
                manageFilesMenu();
                break;
            case 3:
                printInfo("Logging out...");
                break;
            default:
                printError("Invalid choice");
            }
        } while (choice != 3);
    }
};

// ==================== APPLICATION CLASS ====================

class Application {
private:
    UserManager userManager;
    User* currentUser;

public:
    Application() : currentUser(nullptr) {}

    void initialize() {
        printHeader("System Initialization");

        try {
            // Initialize CSV file
            userManager.initializeCSV();

            // Check if CSV is empty and prompt for first admin
            if (userManager.isCSVEmpty()) {
                printInfo("No admin account found. Creating first admin account...");
                createFirstAdmin();
            } else {
                // Load existing users
                userManager.loadUsers();
                printSuccess("Users loaded successfully");
            }

            // Initialize file manager directory
            FileManager fm;

        } catch (const exception& e) {
            printError("Initialization failed: " + string(e.what()));
            throw;
        }
    }

    void createFirstAdmin() {
        string username, password, passwordConfirm;

        printHeader("Create First Admin Account");

        cout << "│ Enter username: ";
        cin >> username;
        cout << "│ Enter password (min 4 chars, 1 number): ";
        cin >> password;
        cout << "│ Confirm password: ";
        cin >> passwordConfirm;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            if (password != passwordConfirm) {
                printError("Passwords do not match");
                createFirstAdmin();
                return;
            }

            userManager.createUser(username, password, "Admin");
            printSuccess("Admin account '" + username + "' created successfully");
        } catch (const exception& e) {
            printError(e.what());
            createFirstAdmin();
        }
    }

    void login() {
        string username, password;

        printHeader("User Login");

        cout << "│ Enter username: ";
        cin >> username;
        cout << "│ Enter password: ";
        cin >> password;
        cout << "└────────────────────────────────────────────────────────┘\n";

        try {
            currentUser = userManager.authenticateUser(username, password);
            printSuccess("Login successful. Welcome, " + username + "!");
        } catch (const exception& e) {
            printError(e.what());
            login();
        }
    }

    void selectPortal() {
        if (!currentUser) {
            printError("No user logged in");
            return;
        }

        if (currentUser->isAdmin()) {
            AdminPortal adminPortal(currentUser, &userManager);
            adminPortal.run();
        } else {
            EmployeePortal employeePortal(currentUser, &userManager);
            employeePortal.run();
        }

        currentUser = nullptr;
    }

    void run() {
        try {
            initialize();

            bool running = true;
            while (running) {
                login();
                selectPortal();

                cout << "\n│ Login again? (y/n): ";
                char choice;
                cin >> choice;
                cout << "└────────────────────────────────────────────────────────┘\n";

                if (choice != 'y' && choice != 'Y') {
                    running = false;
                }
            }

            printHeader("Goodbye!");
            cout << "╔════════════════════════════════════════════════════════╗\n";
            cout << "║  " << string(19, ' ') << "Thank you for using our system!"
                 << string(10, ' ') << "║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
        } catch (const exception& e) {
            printError("Application error: " + string(e.what()));
        }
    }
};

// ==================== MAIN ====================

int main() {
    try {
        Application app;
        app.run();
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
