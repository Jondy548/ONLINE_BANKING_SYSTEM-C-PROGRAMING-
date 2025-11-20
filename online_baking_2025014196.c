#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define FILENAME "bank_data.dat"

typedef struct {
    char full_name[100];
    long account_number;
    char password[20];
    double balance;
}

Account;
Account accounts[MAX_ACCOUNTS];
int account_count = 0;
int logged_in_index = -1;

// Function Prototypes
void save_data();
void load_data();
int find_account(long acc_no);
void register_account();
void login();
void deposit();
void withdraw();
void transfer();
void change_password();
void display_details();
void main_menu();

// FILE HANDLING
void save_data() {
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp) return;
    fwrite(&account_count, sizeof(int), 1, fp);
    fwrite(accounts, sizeof(Account), account_count, fp);
    fclose(fp);
}

void load_data() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) return;
    fread(&account_count, sizeof(int), 1, fp);
    fread(accounts, sizeof(Account), account_count, fp);
    fclose(fp);
}

// SEARCH
int find_account(long acc_no) {
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].account_number == acc_no)
            return i;
    }
    return -1;
}

// REGISTER
void register_account() {
    if (account_count >= MAX_ACCOUNTS) {
        printf(" Bank database full!\n");
        return;
    }

    Account new_acc;
    printf("\nEnter full name: ");
    getchar(); // clear newline
    fgets(new_acc.full_name, sizeof(new_acc.full_name), stdin);
    new_acc.full_name[strcspn(new_acc.full_name, "\n")] = 0;

    new_acc.account_number = 19999 + account_count;

    printf("Create password: ");
    scanf("%s", new_acc.password);

    printf("Enter initial deposit: ");
    scanf("%lf", &new_acc.balance);

    accounts[account_count++] = new_acc;
    save_data();

    printf("\n Account created successfully!\n");
    printf("Your Account Number: %ld\n", new_acc.account_number);
}

// LOGIN
void login() {
    long acc;
    char pass[20];

    printf("\nEnter account number: ");
    scanf("%ld", &acc);
    printf("Enter password: ");
    scanf("%s", pass);

    int index = find_account(acc);
    if (index == -1 || strcmp(accounts[index].password, pass) != 0) {
        printf(" Invalid login details.\n");
        return;
    }

    logged_in_index = index;
    printf("\n Login successful. Welcome, %s!\n", accounts[index].full_name);
    main_menu();
}

// DEPOSIT
void deposit() {
    double amount;
    printf("\nEnter amount to deposit: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    accounts[logged_in_index].balance += amount;
    save_data();
    printf("Deposited successfully. New balance: K%.2f\n", accounts[logged_in_index].balance);
}

// WITHDRAW
void withdraw() {
    double amount;
    printf("\nEnter amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount <= 0 || amount > accounts[logged_in_index].balance) {
        printf("Insufficient funds or invalid amount.\n");
        return;
    }

    accounts[logged_in_index].balance -= amount;
    save_data();
    printf("Withdrawal successful. Remaining balance: K%.2f\n", accounts[logged_in_index].balance);
}

// RANSFER
void transfer() {
    long target_acc;
    double amount;

    printf("\nEnter target account number: ");
    scanf("%ld", &target_acc);
    int target_index = find_account(target_acc);

    if (target_index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);

    if (amount <= 0 || amount > accounts[logged_in_index].balance) {
        printf("Insufficient funds.\n");
        return;
    }

    accounts[logged_in_index].balance -= amount;
    accounts[target_index].balance += amount;
    save_data();

    printf("Transferred K%.2f to %s (Acc: %ld)\n",
           amount, accounts[target_index].full_name, accounts[target_index].account_number);
}

// CHANGE PASSWORD
void change_password() {
    char old_pass[20], new_pass[20];

    printf("\nEnter old password: ");
    scanf("%s", old_pass);

    if (strcmp(old_pass, accounts[logged_in_index].password) != 0) {
        printf("Wrong password.\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", new_pass);
    strcpy(accounts[logged_in_index].password, new_pass);
    save_data();

    printf("Password changed successfully.\n");
}

// DISPLAY DETAILS
void display_details() {
    printf("\n ACCOUNT DETAILS \n");
    printf("Name: %s\n", accounts[logged_in_index].full_name);
    printf("Account Number: %ld\n", accounts[logged_in_index].account_number);
    printf("Balance: K%.2f\n", accounts[logged_in_index].balance);
}

// MAIN MENU
void main_menu() {
    int choice;
    do {
        printf("\n MAIN MENU \n");
        printf("1. Deposit Funds\n");
        printf("2. Withdraw Funds\n");
        printf("3. Transfer Funds\n");
        printf("4. Change Password\n");
        printf("5. Display Account Details\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: deposit();

            break;
            case 2: withdraw();

            break;
            case 3: transfer();

            break;
            case 4: change_password();

            break;
            case 5: display_details();

            break;
            case 6:
                logged_in_index = -1;
                printf("Logged out successfully.\n");
                return;
            default: printf("Invalid choice.\n");
        }
    } while (1);
}

// MAIN FUNCTION
int main() {
    load_data();
    int choice;

    while (1) {

        printf("\n===================\n");
        printf("\n ONLINE BANKING SYSTEM\n");

        printf("\n===================\n");

        printf("\n                   \n");
        printf("1. Login\n");
        printf("2. Register Account\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: login();

            break;
            case 2: register_account();

            break;
            case 0:
                save_data();
                printf(" THANK YOU!\n");
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}

