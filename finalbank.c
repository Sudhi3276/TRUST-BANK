#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a bank account
struct BankAccount {
    char name[50];
    char password[20];
    float balance;
    struct BankAccount* next;
};

// Function prototypes
void applyForLoan();
void checkAccountStatus();
void depositAmount();
void withdrawAmount();
void createAccount();
void displayMenu();
int validatePassword(const char* password);

// Global variable: head of the linked list
struct BankAccount* head = NULL;

int main() {
    int choice;

    while (1) {
        if (head == NULL) {
            printf("No bank account is created, so bank user is empty.\n");
            createAccount();
            continue;
        }

        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\n===== Bank Account Management System =====\n");
    printf("1. Apply for the loan\n");
    printf("2. Check Bank Account Status\n");
    printf("3. Deposit Amount\n");
    printf("4. Withdraw Amount\n");
    printf("5. Create a Bank Account\n");
    printf("6. Exit\n");
}

void applyForLoan() {
    float familyIncome;

    printf("Enter your family income: ");
    scanf("%f", &familyIncome);

    if (familyIncome < 600000) {
        printf("Loan cannot be sanctioned.\n");
    } else {
        printf("Loan amount will be sanctioned.\n");
    }
}

void checkAccountStatus() {
    char name[50];
    char password[20];

    printf("Enter bank account holder name: ");
    scanf("%s", name);
    printf("Enter bank account holder password: ");
    scanf("%s", password);

    struct BankAccount* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->password, password) == 0) {
            printf("Updated balance: %.2f\n", current->balance);
            return;
        }
        current = current->next;
    }

    printf("Invalid Bank User name and Password.\n");
}

void depositAmount() {
    char name[50];
    char password[20];
    float deposit;

    printf("Enter bank account holder name: ");
    scanf("%s", name);
    printf("Enter bank account holder password: ");
    scanf("%s", password);

    struct BankAccount* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->password, password) == 0) {
            printf("Enter amount to deposit: ");
            scanf("%f", &deposit);
            current->balance += deposit;
            printf("Updated balance: %.2f\n", current->balance);
            return;
        }
        current = current->next;
    }

    printf("Invalid Bank User name and Password.\n");
}

void withdrawAmount() {
    char name[50];
    char password[20];
    float withdraw;

    printf("Enter bank account holder name: ");
    scanf("%s", name);
    printf("Enter bank account holder password: ");
    scanf("%s", password);

    struct BankAccount* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->password, password) == 0) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &withdraw);

            if (withdraw > current->balance) {
                printf("You do not have that much amount in your account to withdraw.\n");
            } else if (current->balance - withdraw < 1000) {
                printf("Penalty withdraw of 10 rupees.\n");
                current->balance -= (withdraw + 10);
                printf("Updated balance: %.2f\n", current->balance);
            } else {
                current->balance -= withdraw;
                printf("Updated balance: %.2f\n", current->balance);
            }
            return;
        }
        current = current->next;
    }

    printf("Invalid Bank User name and Password.\n");
}

void createAccount() {
    struct BankAccount* newAccount = (struct BankAccount*)malloc(sizeof(struct BankAccount));
    if (newAccount == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter your name: ");
    scanf("%s", newAccount->name);

    while (1) {
        printf("Enter a password for your account: ");
        scanf("%s", newAccount->password);

        if (validatePassword(newAccount->password)) {
            break;
        } else {
            printf("Password must be at least 8 characters long, include at least one uppercase letter, one lowercase letter, and one digit.\n");
        }
    }

    newAccount->balance = 1000.0; // Initial deposit of 1000 rupees
    newAccount->next = NULL;

    if (head == NULL) {
        head = newAccount;
    } else {
        struct BankAccount* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAccount;
    }

    printf("Bank account has been created with an initial deposit of 1000 rupees.\n");
}

int validatePassword(const char* password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0;

    if (strlen(password) < 8) {
        return 0;
    }

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (islower(password[i])) hasLower = 1;
        if (isdigit(password[i])) hasDigit = 1;
    }

    return hasUpper && hasLower && hasDigit;
}
