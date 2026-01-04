#include <iostream>
#include <string>
#include <vector>

using namespace std;


const string DB_USERNAME = "admin";
const string DB_PASSWORD = "12345";


bool containsSQLInjection(const string& input) {
    vector<string> patterns = {
        "OR 1=1",
        "OR 'a'='a'",
        "' --",
        "'--",
        "UNION SELECT",
        "DROP TABLE",
        "INSERT INTO",
        "OR 1=0",
        "\" OR \"1\"=\"1"
    };

    for (const string& pattern : patterns) {
        if (input.find(pattern) != string::npos) {
            return true;
        }
    }
    return false;
}


bool vulnerableLogin(const string& username, const string& password) {
    string query =
        "SELECT * FROM users WHERE username = '" +
        username + "' AND password = '" + password + "'";

    cout << "\n[DEBUG] SQL Query Sent to Database:" << endl;
    cout << query << endl;


    if (containsSQLInjection(username) || containsSQLInjection(password)) {
        cout << "[WARNING] SQL Injection pattern detected, but query was executed anyway." << endl;
        return true;
    }

    return (username == DB_USERNAME && password == DB_PASSWORD);
}


bool secureLogin(const string& username, const string& password) {

    if (containsSQLInjection(username) || containsSQLInjection(password)) {
        cout << "[INFO] Input rejected due to unsafe characters." << endl;
        return false;
    }

    return (username == DB_USERNAME && password == DB_PASSWORD);
}

int main() {
    while (true) {
        string username, password;
        int choice;

        cout << "\n==============================" << endl;
        cout << "Mini SQL Injection Lab" << endl;
        cout << "==============================" << endl;
        cout << "1. Vulnerable Login" << endl;
        cout << "2. Secure Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose mode: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "\nExiting program. Goodbye." << endl;
            break;
        }

        cout << "\nEnter username: ";
        getline(cin, username);

        cout << "Enter password: ";
        getline(cin, password);

        bool result = false;

        if (choice == 1) {
            result = vulnerableLogin(username, password);
        } else if (choice == 2) {
            result = secureLogin(username, password);
        } else {
            cout << "Invalid option. Try again." << endl;
            continue;
        }

        cout << "\nResult: ";
        if (result) {
            cout << "Login successful." << endl;
        } else {
            cout << "Login failed." << endl;
        }
    }

    return 0;
}
