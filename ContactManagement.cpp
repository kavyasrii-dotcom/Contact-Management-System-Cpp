#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Contact Class to handle individual contact details
class Contact {
public:
    string name;
    string phone;
    string email;

    void inputContact() {
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);
    }
};

// Function to add a new contact
void addContact() {
    ofstream outFile("contacts.txt", ios::app);
    if (!outFile) {
        cout << "\nError opening file for writing!\n";
        return;
    }

    Contact c;
    c.inputContact();
    // Using '|' as a delimiter to separate fields in the text file
    outFile << c.name << "|" << c.phone << "|" << c.email << "\n";
    outFile.close();
    cout << "\n[+] Contact added successfully!\n";
}

// Function to view all saved contacts
void viewContacts() {
    ifstream inFile("contacts.txt");
    if (!inFile) {
        cout << "\nNo contacts found! (File does not exist yet)\n";
        return;
    }

    cout << "\n============================================================\n";
    cout << left << setw(20) << "NAME" << setw(15) << "PHONE" << setw(25) << "EMAIL" << endl;
    cout << "============================================================\n";

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');
        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            string name = line.substr(0, pos1);
            string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string email = line.substr(pos2 + 1);
            cout << left << setw(20) << name << setw(15) << phone << setw(25) << email << endl;
            found = true;
        }
    }
    inFile.close();
    
    if (!found) {
        cout << "No contacts available in the storage.\n";
    }
    cout << "============================================================\n";
}

// Function to search for a contact by name
void searchContact() {
    ifstream inFile("contacts.txt");
    if (!inFile) {
        cout << "\nNo contacts found!\n";
        return;
    }

    cin.ignore();
    string searchName;
    cout << "Enter Name to Search: ";
    getline(cin, searchName);

    string line;
    bool found = false;
    cout << "\n--- Search Results ---\n";
    while (getline(inFile, line)) {
        size_t pos1 = line.find('|');
        if (pos1 != string::npos) {
            string name = line.substr(0, pos1);
            if (name == searchName) {
                size_t pos2 = line.rfind('|');
                string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string email = line.substr(pos2 + 1);
                cout << "Name  : " << name << "\nPhone : " << phone << "\nEmail : " << email << "\n";
                found = true;
                break;
            }
        }
    }
    inFile.close();
    
    if (!found) {
        cout << "Contact not found with name: " << searchName << "\n";
    }
}

// Function to delete a contact by name
void deleteContact() {
    ifstream inFile("contacts.txt");
    if (!inFile) {
        cout << "\nNo contacts found!\n";
        return;
    }

    cin.ignore();
    string delName;
    cout << "Enter Name of Contact to Delete: ";
    getline(cin, delName);

    ofstream outFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        size_t pos1 = line.find('|');
        if (pos1 != string::npos) {
            string name = line.substr(0, pos1);
            if (name == delName) {
                found = true;
                continue; // Skip copying this record to the temporary file
            }
        }
        outFile << line << "\n";
    }

    inFile.close();
    outFile.close();

    // Replace old file with updated temporary file
    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found) {
        cout << "\n[+] Contact deleted successfully!\n";
    } else {
        cout << "\nContact not found!\n";
    }
}

// Main function with menu loop
int main() {
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "        CONTACT MANAGEMENT SYSTEM       \n";
        cout << "========================================\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                cout << "\nExiting Contact Management System. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}