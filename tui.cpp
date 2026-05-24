#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>

using namespace std;

struct Item {
  string name;
  bool isDirectory;
  string fullPath;
};

// Scan directory and return items (dirs first, then files)
vector<Item> scanDirectory(const string &path) {
  vector<Item> items;
  DIR *dir = opendir(path.c_str());

  if (!dir) {
    cerr << "Error: Could not open directory: " << path << endl;
    return items;
  }

  vector<Item> directories;
  vector<Item> files;

  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    string name = entry->d_name;

    // Skip . (current directory)
    if (name == ".")
      continue;

    string fullPath = path + "/" + name;
    struct stat statbuf;

    if (stat(fullPath.c_str(), &statbuf) == 0) {
      if (S_ISDIR(statbuf.st_mode)) {
        directories.push_back({name, true, fullPath});
      } else if (name.size() > 4 && name.substr(name.size() - 4) == ".cpp") {
        files.push_back({name, false, fullPath});
      }
    }
  }

  closedir(dir);

  // Sort directories and files alphabetically
  sort(directories.begin(), directories.end(),
       [](const Item &a, const Item &b) { return a.name < b.name; });
  sort(files.begin(), files.end(),
       [](const Item &a, const Item &b) { return a.name < b.name; });

  // Add ".." at the beginning for going up
  items.push_back({"..", true, path + "/.."});

  // Add directories, then files
  items.insert(items.end(), directories.begin(), directories.end());
  items.insert(items.end(), files.begin(), files.end());

  return items;
}

// Compile a .cpp file and return success status
bool compileFile(const string &cppPath, string &errorMsg) {
  // Extract filename without extension for the binary
  string filename = cppPath.substr(cppPath.find_last_of("/") + 1);
  string binaryName = filename.substr(0, filename.find_last_of("."));
  string binaryPath = "/tmp/" + binaryName + "_tui";

  // Build compilation command with error redirection
  string command = "g++ -Wall -Wextra -std=c++17 -pthread \"" + cppPath +
                   "\" -o \"" + binaryPath + "\" 2>&1";

  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    errorMsg = "Error: Could not execute compiler";
    return false;
  }

  // Capture compilation output
  errorMsg = "";
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    errorMsg += buffer;
  }

  int status = pclose(pipe);

  if (status != 0) {
    return false;
  }

  return true;
}

// Execute a compiled binary and show output
void executeFile(const string &cppPath) {
  // Extract filename without extension for the binary
  string filename = cppPath.substr(cppPath.find_last_of("/") + 1);
  string binaryName = filename.substr(0, filename.find_last_of("."));
  string binaryPath = "/tmp/" + binaryName + "_tui";

  cout << "\n" << string(50, '=') << endl;
  cout << "Executing: " << filename << endl;
  cout << string(50, '=') << "\n" << endl;

  // Execute binary and capture output
  string command = "\"" + binaryPath + "\" 2>&1; echo \"__EXIT_CODE__:$?\"";
  FILE *pipe = popen(command.c_str(), "r");

  if (!pipe) {
    cerr << "Error: Could not execute binary" << endl;
    return;
  }

  string output;
  string exitCodeLine;
  char buffer[256];

  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    string line = buffer;
    if (line.find("__EXIT_CODE__:") == 0) {
      exitCodeLine = line;
    } else {
      output += line;
    }
  }

  pclose(pipe);

  // Display output
  if (!output.empty()) {
    cout << output;
  }

  // Extract and display exit code
  if (!exitCodeLine.empty()) {
    int exitCode = atoi(exitCodeLine.substr(14).c_str());
    cout << "\n" << string(50, '=') << endl;
    cout << "Exit Code: " << exitCode;
    if (exitCode == 0) {
      cout << " (Success)";
    } else {
      cout << " (Error)";
    }
    cout << endl;
    cout << string(50, '=') << "\n" << endl;
  }

  // Press any key to continue
  cout << "Press Enter to continue...";
  cin.ignore();
  cout << "\n" << endl;
}

// Display menu and return user choice
void displayMenu(const string &currentPath, const vector<Item> &items) {
  system("clear");

  cout << "\n=== C++ File Explorer & Executor ===\n" << endl;
  cout << "Current Directory: " << currentPath << "\n" << endl;
  cout << "Items:\n" << endl;

  for (size_t i = 0; i < items.size(); ++i) {
    string prefix = items[i].isDirectory ? "[D] " : "[F] ";
    cout << (i + 1) << ". " << prefix << items[i].name << endl;
  }

  cout << "\n0. Quit" << endl;
  cout << "\n" << endl;
}

// Get and validate user input
int getUserInput(int maxOption) {
  int choice = -1;

  while (choice < 0 || choice > maxOption) {
    cout << "Select option (0-" << maxOption << "): ";

    string input;
    getline(cin, input);

    // Try to parse input
    try {
      choice = stoi(input);
      if (choice < 0 || choice > maxOption) {
        cout << "Invalid selection. Please enter a number between 0 and "
             << maxOption << endl;
        choice = -1;
      }
    } catch (...) {
      cout << "Invalid input. Please enter a number." << endl;
      choice = -1;
    }
  }

  return choice;
}

// Normalize path (resolve .. references)
string normalizePath(const string &path) {
  vector<string> parts;
  stringstream ss(path);
  string part;

  while (getline(ss, part, '/')) {
    if (part.empty() || part == ".") {
      continue;
    } else if (part == "..") {
      if (!parts.empty()) {
        parts.pop_back();
      }
    } else {
      parts.push_back(part);
    }
  }

  string result = "";
  for (const auto &p : parts) {
    result += "/" + p;
  }

  return result.empty() ? "/" : result;
}

int main() {
  string currentPath = ".";

  while (true) {
    vector<Item> items = scanDirectory(currentPath);

    displayMenu(currentPath, items);
    int choice = getUserInput(items.size());

    if (choice == 0) {
      // Quit
      cout << "Goodbye!" << endl;
      break;
    }

    const Item &selected = items[choice - 1];

    if (selected.isDirectory) {
      // Navigate to directory
      if (selected.name == "..") {
        // Go up one level
        size_t lastSlash = currentPath.find_last_of("/");
        if (lastSlash != string::npos && lastSlash > 0) {
          currentPath = currentPath.substr(0, lastSlash);
        } else if (lastSlash == 0) {
          currentPath = "/";
        }
        // If at root, stay at root
      } else {
        // Enter subdirectory
        currentPath = selected.fullPath;
      }
    } else {
      // Execute C++ file
      string errorMsg;

      cout << "\nCompiling: " << selected.name << "..." << endl;

      if (!compileFile(selected.fullPath, errorMsg)) {
        system("clear");
        cout << "\n=== Compilation Error ===\n" << endl;
        cout << errorMsg << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cout << "\n" << endl;
      } else {
        cout << "Compilation successful!" << endl;

        // Execute the compiled binary
        executeFile(selected.fullPath);
      }
    }
  }

  return 0;
}
