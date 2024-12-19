#include <iostream>
#include <string>
#include <cctype>
#include <memory>
#include <regex>
using namespace std;

// Structure to represent a bank account
struct BankAccount {
    string name;
    string password;
    string aadhaarNumber;
    string phoneNumber;
    float balance;
    unique_ptr<BankAccount> next;

    BankAccount(const string& name, const string& password, const string& aadhaarNumber,
                const string& phoneNumber, float balance)
        : name(name), password(password), aadhaarNumber(aadhaarNumber),
          phoneNumber(phoneNumber), balance(balance), next(nullptr) {}
};

// Function prototypes
void applyForLoan();
void checkAccountStatus();
void depositAmount();
void withdrawAmount();
void createAccount();
void displayMenu();
bool validatePassword(const string& password);
bool isNameUnique(const string& name);
bool isAadhaarUnique(const string& aadhaarNumber);
bool isPhoneUnique(const string& phoneNumber);

// Global variable: head of the linked list
unique_ptr<BankAccount> head = nullptr;

int main() {
    int choice;

    while (true) {
        if (!head) {
            cout << "No bank account is created, so bank user is empty.\n";
            createAccount();
            continue;
        }

        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                applyForLoan();
                break;
            case 2:
                checkAccountStatus();
                break;
            case 3:
                depositAmount();
                break;
            case 4:
                withdrawAmount();
                break;
            case 5:
                createAccount();
                break;
            case 6:
                // Exit the program
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 6.\n";
        }
    }

    return 0;
}

void displayMenu() {
    cout << "\n===== Bank Account Management System =====\n";
    cout << "1. Apply for the loan\n";
    cout << "2. Check Bank Account Status\n";
    cout << "3. Deposit Amount\n";
    cout << "4. Withdraw Amount\n";
    cout << "5. Create a Bank Account\n";
    cout << "6. Exit\n";
}

void applyForLoan() {
    float familyIncome;

    cout << "Enter your family income: ";
    cin >> familyIncome;

    if (familyIncome < 600000) {
        cout << "Loan cannot be sanctioned.\n";
    } else {
        cout << "Loan amount will be sanctioned.\n";
    }
}

void checkAccountStatus() {
    string name, password;

    cout << "Enter bank account holder name: ";
    cin >> name;
    cout << "Enter bank account holder password: ";
    cin >> password;

    BankAccount* current = head.get();
    while (current) {
        if (current->name == name && current->password == password) {
            cout << "Aadhaar Number: " << current->aadhaarNumber << "\n";
            cout << "Phone Number: " << current->phoneNumber << "\n";
            cout << "Updated balance: " << current->balance << "\n";
            return;
        }
        current = current->next.get();
    }

    cout << "Invalid Bank User name and Password.\n";
}

void depositAmount() {
    string name, password;
    float deposit;

    cout << "Enter bank account holder name: ";
    cin >> name;
    cout << "Enter bank account holder password: ";
    cin >> password;

    BankAccount* current = head.get();
    while (current) {
        if (current->name == name && current->password == password) {
            cout << "Enter amount to deposit: ";
            cin >> deposit;
            current->balance += deposit;
            cout << "Updated balance: " << current->balance << "\n";
            return;
        }
        current = current->next.get();
    }

    cout << "Invalid Bank User name and Password.\n";
}

void withdrawAmount() {
    string name, password;
    float withdraw;

    cout << "Enter bank account holder name: ";
    cin >> name;
    cout << "Enter bank account holder password: ";
    cin >> password;

    BankAccount* current = head.get();
    while (current) {
        if (current->name == name && current->password == password) {
            cout << "Enter amount to withdraw: ";
            cin >> withdraw;

            if (withdraw > current->balance) {
                cout << "You do not have that much amount in your account to withdraw.\n";
            } else if (current->balance - withdraw < 1000) {
                cout << "Penalty withdraw of 10 rupees.\n";
                current->balance -= (withdraw + 10);
                cout << "Updated balance: " << current->balance << "\n";
            } else {
                current->balance -= withdraw;
                cout << "Updated balance: " << current->balance << "\n";
            }
            return;
        }
        current = current->next.get();
    }

    cout << "Invalid Bank User name and Password.\n";
}

void createAccount() {
    string name, password, aadhaarNumber, phoneNumber;

    while (true) {
        cout << "Enter your name: ";
        cin >> name;
        if (!isNameUnique(name)) {
            cout << "This name is already taken. Please choose another name.\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter a password for your account: ";
        cin >> password;

        if (validatePassword(password)) {
            break;
        } else {
            cout << "Password must be at least 8 characters long, include at least one uppercase letter, one lowercase letter, and one digit.\n";
        }
    }

    while (true) {
        cout << "Enter your Aadhaar Number: ";
        cin >> aadhaarNumber;
        if (!isAadhaarUnique(aadhaarNumber)) {
            cout << "This Aadhaar Number is already linked to another account. Please enter a unique Aadhaar Number.\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter your Phone Number: ";
        cin >> phoneNumber;
        if (!isPhoneUnique(phoneNumber)) {
            cout << "This Phone Number is already linked to another account. Please enter a unique Phone Number.\n";
        } else {
            break;
        }
    }

    auto newAccount = make_unique<BankAccount>(name, password, aadhaarNumber, phoneNumber, 1000.0); // Initial deposit of 1000 rupees

    if (!head) {
        head = move(newAccount);
    } else {
        BankAccount* temp = head.get();
        while (temp->next) {
            temp = temp->next.get();
        }
        temp->next = move(newAccount);
    }

    cout << "Bank account has been created with an initial deposit of 1000 rupees.\n";
}

bool validatePassword(const string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false;

    if (password.length() < 8) {
        return false;
    }

    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}

bool isNameUnique(const string& name) {
    BankAccount* current = head.get();
    while (current) {
        if (current->name == name) {
            return false;
        }
        current = current->next.get();
    }
    return true;
}

bool isAadhaarUnique(const string& aadhaarNumber) {
    BankAccount* current = head.get();
    while (current) {
        if (current->aadhaarNumber == aadhaarNumber) {
            return false;
        }
        current = current->next.get();
    }
    return true;
}

bool isPhoneUnique(const string& phoneNumber) {
    BankAccount* current = head.get();
    while (current) {
        if (current->phoneNumber == phoneNumber) {
            return false;
        }
        current = current->next.get();
    }
    return true;
}
