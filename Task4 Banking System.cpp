#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Simple Transaction Record
struct Transaction {
    char type[20];  // "Deposit", "Withdrawal", or "Transfer"
    double amount;
    char date[20];
};

// Bank Account Class
class Account {
private:
    int accountNumber;
    double balance;
    Transaction transactions[100];
    int transactionCount;

public:
    Account(int num) : accountNumber(num), balance(0), transactionCount(0) {}

    void deposit(double amount) {
        balance += amount;
        addTransaction("Deposit", amount);
        cout << "Deposited $" << amount << " to account #" << accountNumber << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Error: Insufficient funds in account #" << accountNumber << endl;
            return false;
        }
        balance -= amount;
        addTransaction("Withdrawal", amount);
        cout << "Withdrew $" << amount << " from account #" << accountNumber << endl;
        return true;
    }

    void addTransaction(const char* type, double amount) {
        if (transactionCount < 100) {
            strcpy(transactions[transactionCount].type, type);
            transactions[transactionCount].amount = amount;
            strcpy(transactions[transactionCount].date, "01/01/2023"); // Simplified date
            transactionCount++;

            // Save to file
            ofstream file("transactions.txt", ios::app);
            if (file.is_open()) {
                file << accountNumber << " " << type << " " << amount << " " << "01/01/2023" << endl;
                file.close();
            }
        }
    }

    void display() {
        cout << "\nAccount #" << accountNumber << " Balance: $" << balance << endl;
        cout << "Last 5 Transactions:\n";
        int start = transactionCount > 5 ? transactionCount - 5 : 0;
        for (int i = start; i < transactionCount; i++) {
            cout << "- " << transactions[i].type << ": $" << transactions[i].amount 
                 << " on " << transactions[i].date << endl;
        }
    }

    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }
};

// Banking System Menu
int main() {
    Account account1(1001);
    Account account2(1002);
    int choice;
    double amount;

    cout << "Simple Banking System\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Deposit to Account 1001\n";
        cout << "2. Withdraw from Account 1001\n";
        cout << "3. Transfer to Account 1002\n";
        cout << "4. View Account 1001\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter deposit amount: ";
                cin >> amount;
                account1.deposit(amount);
                break;
            case 2:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account1.withdraw(amount);
                break;
            case 3:
                cout << "Enter transfer amount: ";
                cin >> amount;
                if (account1.withdraw(amount)) {
                    account2.deposit(amount);
                    account1.addTransaction("Transfer Out", amount);
                    account2.addTransaction("Transfer In", amount);
                    cout << "Transferred $" << amount << " to Account 1002\n";
                }
                break;
            case 4:
                account1.display();
                break;
            case 5:
                cout << "Exiting system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
