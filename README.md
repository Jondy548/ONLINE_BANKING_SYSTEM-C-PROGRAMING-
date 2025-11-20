## Student Number: 2025014196

# Online Banking System (C Project)

A simple console-based **Banking Management System** written in C.
The program allows users to register bank accounts, log in, deposit funds, withdraw money, transfer between accounts, change passwords, and view account details.
All account data is saved using **binary file handling**, making it persistent between program launches.

## 📌 Features

### User Account Operations

* Create/Register a new bank account
* Login using account number + password
* Deposit funds
* Withdraw funds
* Transfer funds between accounts
* Change password
* View account details
* Logout

### System Features

* Data persistence using `bank_data.dat`
* Supports up to 100 user accounts
* Auto-generated account numbers
* Input validation and error handling
* Simple menu-driven interface

## 📁 File Structure

├── bank_system.c
├── bank_data.dat     (auto-generated)
└── README.md

## 🛠️ How It Works

### Account Structure

Each account is stored as:

c
typedef struct {
    char full_name[100];
    long account_number;
    char password[20];
    double balance;
} Account;

### Data Storage

The program saves:

* Number of accounts
* All account structs

into a binary file:
bank_data.dat
Using:
c
fwrite()
fread()
## 🚀 How to Compile & Run

### Using GCC
bash
gcc bank_system.c -o bank_system
./bank_system
### On Windows (MinGW)

bash
gcc bank_system.c -o bank_system.exe
bank_system.exe

## 📷 Program Flow

1. Load all saved accounts from file
2. Display main menu:
   1. Login
   2. Register Account
   0. Exit
3. If logged in → show full banking menu:

   1. Deposit
   2. Withdraw
   3. Transfer
   4. Change Password
   5. Show Account Details
   6. Logout
4. Data is saved every time a balance or password is modified.

## 💾 Data Persistence

All operations that modify an account call:

c
save_data();

which updates `bank_data.dat`.
This ensures no information is lost after closing the program.

## 🔐 Security Notes

This is an educational project—passwords are stored in plain text.
For real banking systems:

* Use hashing (SHA-256, bcrypt)
* Use encryption for file storage
* Add multi-factor authentication

##  Possible Improvements

You may add:

* Input validation improvements
* Password masking (`*` while typing)
* Transaction history
* Admin mode
* Modularize the program (separate .c and .h files)

## Author

Basic C banking system created for learning file handling, structs, and menu-driven programming.
