#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    string accountHolder;
    double balance;
    int pin;

    bool isValidAmount(double amount) {
        return amount > 0;
    }

public:
    BankAccount(string name, double initialBalance, int pinCode) {
        accountHolder = name;
        balance = max(0.0, initialBalance);

        while (pinCode < 1000 || pinCode > 9999) {
            cout << "Invalid PIN. Must be a 4-digit number. Enter again: ";
            cin >> pinCode;
        }
        pin = pinCode;
    }

    string getAccountHolder() { return accountHolder; }

    bool authenticate(int enteredPin) { return enteredPin == pin; }

    bool changePin(int oldPin, int newPin) {
        if (!authenticate(oldPin)) {
            cout << "Incorrect current PIN. PIN change failed." << endl;
            return false;
        }
        if (newPin < 1000 || newPin > 9999) {
            cout << "Invalid new PIN. Must be a 4-digit number." << endl;
            return false;
        }
        pin = newPin;
        cout << "PIN successfully changed." << endl;
        return true;
    }

    void deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (isValidAmount(amount) && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }

    void applyInterest(double rate, int years) {
        if (rate > 0 && years > 0) {
            balance *= pow((1 + rate / 100), years);
            cout << "Interest applied! New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid interest rate or years!" << endl;
        }
    }

    void displayBalance() {
        cout << "\nAccount Holder: " << accountHolder << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

vector<BankAccount> accounts;

BankAccount* findAccount(string name, int pin) {
    for (auto& account : accounts) {
        if (account.getAccountHolder() == name && account.authenticate(pin)) {
            return &account;
        }
    }
    return nullptr;
}

void createAccount() {
    string name;
    double initialDeposit;
    int pinCode;

    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter initial deposit amount: $";
    cin >> initialDeposit;

    while (true) {
        cout << "Set a 4-digit PIN: ";
        cin >> pinCode;
        if (pinCode >= 1000 && pinCode <= 9999) break;
        cout << "Invalid PIN. Try again." << endl;
    }

    accounts.emplace_back(name, initialDeposit, pinCode);
    cout << "Account created successfully!" << endl;
}

void accountMenu(BankAccount* account) {
    int choice;
    do {
        cout << "\n1. Deposit Money\n2. Withdraw Money\n3. Check Balance\n4. Apply Interest\n5. Change PIN\n6. Logout\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double amount;
                cout << "Enter deposit amount: $";
                cin >> amount;
                account->deposit(amount);
                break;
            }
            case 2: {
                double amount;
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                account->withdraw(amount);
                break;
            }
            case 3:
                account->displayBalance();
                break;
            case 4: {
                double rate;
                int years;
                cout << "Enter annual interest rate (%): ";
                cin >> rate;
                cout << "Enter number of years: ";
                cin >> years;
                account->applyInterest(rate, years);
                break;
            }
            case 5: {
                int oldPin, newPin;
                cout << "Enter current PIN: ";
                cin >> oldPin;
                cout << "Enter new 4-digit PIN: ";
                cin >> newPin;
                account->changePin(oldPin, newPin);
                break;
            }
            case 6:
                cout << "Logged out successfully." << endl;
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (true);
}

void login() {
    string name;
    int pin;

    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter PIN: ";
    cin >> pin;

    BankAccount* account = findAccount(name, pin);
    if (account) {
        cout << "Login successful!" << endl;
        accountMenu(account);
    } else {
        cout << "Invalid credentials!" << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Create Account\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (true);
}
