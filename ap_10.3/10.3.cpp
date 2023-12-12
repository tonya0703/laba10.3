#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Friend {
    string name;
    string phoneNumber;
    int birthday[3];
};

const string friendsFilename = "/Users/TONYA/source/repos/ap_10.3/file.txt";

void createList(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to create file " << filename << endl;
        return;
    }
    cout << "File created: " << filename << endl;
    file.close();
}

void displayList(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void addFriendToFile(const Friend& newFriend, const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << " for appending" << endl;
        return;
    }

    file << newFriend.name << "; " << newFriend.phoneNumber << "; "
        << newFriend.birthday[0] << " " << newFriend.birthday[1] << " " << newFriend.birthday[2] << endl;

    file.close();
}

void findFriendByPhone(const string& phoneNumber, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, birthday;
        getline(ss, name, ';');
        getline(ss, phone, ';');
        getline(ss, birthday);

        // Видаляємо пробіли з номера телефону для порівняння
        phone.erase(remove_if(phone.begin(), phone.end(), ::isspace), phone.end());

        if (phone == phoneNumber) {
            cout << "Friend found:" << endl;
            cout << "Name: " << name << endl;
            cout << "Phone Number: " << phone << endl;
            cout << "Birthday: " << birthday << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Friend with this phone number not found." << endl;
    }

    file.close();
}

int main() {
    int choice;
    do {
        cout << "\nMenu:\n1. Create list\n2. Display list\n3. Add friend\n4. Find friend by phone number\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createList(friendsFilename);
            break;
        case 2:
            displayList(friendsFilename);
            break;
        case 3: {
            Friend newFriend;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, newFriend.name);
            cout << "Enter phone number: ";
            cin >> newFriend.phoneNumber;
            cout << "Enter birthday (day month year): ";
            cin >> newFriend.birthday[0] >> newFriend.birthday[1] >> newFriend.birthday[2];
            addFriendToFile(newFriend, friendsFilename);
            break;
        }
        case 4: {
            string phoneNumber;
            cout << "Enter phone number to search: ";
            cin >> phoneNumber;
            findFriendByPhone(phoneNumber, friendsFilename);
            break;
        }
        case 5:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}
