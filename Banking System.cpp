#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define FILENAME "accounts.txt"

// Structure to represent a bank account
struct BankAccount {
    int accountNumber;
    char accountHolderName[100];
    float balance;
};

// Function prototypes
void deposit(struct BankAccount *account, float amount); 
void withdraw(struct BankAccount *account, float amount);
void balanceInquiry(struct BankAccount *account);
void saveAccountsToFile(struct BankAccount accounts[], int count);
void loadAccountsFromFile(struct BankAccount accounts[], int *count);

int main() {
    struct BankAccount accounts[MAX_ACCOUNTS];
    int numAccounts = 0;
    loadAccountsFromFile(accounts, &numAccounts);
    
    int choice, accountNum;
    float amount;
    
    do {
        printf("\nBanking System Menu\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Inquiry\n");
        printf("4. Add New Account\n"); // New option to add a new account
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
		case 1:
		printf("Enter account number: ");
		scanf("%d", &accountNum);
		printf("Enter amount to deposit: ");
		scanf("%f", &amount);
		deposit(&accounts[accountNum - 1], amount);
		 break;
		case 2:
	    printf("Enter account number: ");
		scanf("%d", &accountNum);
		printf("Enter amount to withdraw: ");
		scanf("%f", &amount);
		withdraw(&accounts[accountNum - 1], amount);
		break;
	    case 3:
		printf("Enter account number: ");
		scanf("%d", &accountNum);
		balanceInquiry(&accounts[accountNum - 1]);
		break;
		case 4:
		 if (numAccounts < MAX_ACCOUNTS) {
		printf("Enter account number: ");
		scanf("%d", &accounts[numAccounts].accountNumber);
		printf("Enter account holder name: ");
		scanf("%s", accounts[numAccounts].accountHolderName);
		printf("Enter initial balance: ");
		scanf("%f", &accounts[numAccounts].balance);
	    numAccounts++;
		printf("Account added successfully.\n");
		} else {
		printf("Maximum number of accounts reached. Cannot add new account.\n");
		}
		break;
		case 5:
		saveAccountsToFile(accounts, numAccounts);
		printf("Exiting...\n");
		break;
		default:
	    printf("Invalid choice. Please enter a number between 1 and 5.\n");
		}
		} while(choice != 5);
		return 0;
}

// Function to deposit money into an account
void deposit(struct BankAccount *account, float amount) {
    account->balance += amount;
    printf("Deposit successful. New balance: %.2f\n", account->balance);
}

// Function to withdraw money from an account
void withdraw(struct BankAccount *account, float amount) {
    if (amount <= account->balance) {
        account->balance -= amount;
        printf("Withdrawal successful. New balance: %.2f\n", account->balance);
    } else {
        printf("Insufficient funds.\n");
    }
}

// Function to check the balance of an account
void balanceInquiry(struct BankAccount *account) {
    printf("Account balance: %.2f\n", account->balance);
}

// Function to save account details to a file
void saveAccountsToFile(struct BankAccount accounts[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f\n", accounts[i].accountNumber, accounts[i].accountHolderName, accounts[i].balance);
    }
    
    fclose(file);
}

// Function to load account details from a file
void loadAccountsFromFile(struct BankAccount accounts[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File not found. Starting with no accounts.\n");
        return;
    }
    
    while ((*count < MAX_ACCOUNTS) && (fscanf(file, "%d %s %f", &accounts[*count].accountNumber, accounts[*count].accountHolderName, &accounts[*count].balance) == 3)) {
        (*count)++;
    }
    
    fclose(file);
}
