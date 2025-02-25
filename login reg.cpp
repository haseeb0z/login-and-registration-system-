#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;
string hashPassword(const string& password) {
    string hashed = password;
    for (char &ch : hashed) {
        ch ^= 0x5A;  
    }
    return hashed;
}
void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    string hashedPassword = hashPassword(password);

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << hashedPassword << endl;
        file.close();
        cout << "Registration successful!\n";
    } else {
        cout << "Error opening file!\n";
    }
}
bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string hashedPassword = hashPassword(password);
    ifstream file("users.txt");
    string storedUser, storedPass;

    if (file.is_open()) {
        while (file >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == hashedPassword) {
                cout << "Login successful!\n";
                return true;
            }
        }
        file.close();
    }
    
    cout << "Invalid username or password!\n";
    return false;
}

void resetPassword() {
    string username, newPassword;
    cout << "Enter your username: ";
    cin >> username;
    
    unordered_map<string, string> userData;
    ifstream file("users.txt");
    string storedUser, storedPass;
    
    if (file.is_open()) {
        while (file >> storedUser >> storedPass) {
            userData[storedUser] = storedPass;
        }
        file.close();
    } else {
        cout << "Error opening file!\n";
        return;
    }

    if (userData.find(username) == userData.end()) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> newPassword;
    userData[username] = hashPassword(newPassword);
    ofstream outFile("users.txt");
    for (const auto& pair : userData) {
        outFile << pair.first << " " << pair.second << endl;
    }
    outFile.close();

    cout << "Password reset successful!\n";
}

//Main function
int main() {
    int choice;
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Reset Password\n4. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: resetPassword(); break;
            case 4: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice, try again!\n";
        }
    }
}
