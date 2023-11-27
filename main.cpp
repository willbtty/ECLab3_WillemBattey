#include <iostream>
#include <string>
using namespace std;


class Account {
public:
    string accountNumber;
    string accountHolder;
    float balance;
    string AccType = "basic";
    Account(string num, string holder, float bal) { // Constructor
        accountNumber = num;
        accountHolder = holder;
        balance = bal;
    }


    void deposit(float amount) { // Add amount getting depsitted to the balance
        balance += amount;
    }

    void withdraw(float amount) {
        if ((balance - amount) > 0) { // Check if the amount being withdrawn will keep the account above 0
            balance -= amount; // If it is subtract the amount
        }
        else {
            cout << "Insufficient Funds." << endl; // Else show insufficient funds
        }
    }

    // Print out details of the account
    virtual void displayDetails() const {
            cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
            cout << "Holder: " << accountHolder << endl;
            printf("Balance: $%.2f\n", balance);
    }
   
   
    // Overload + operator for easy transfer of fixed amount. Fixed amount is 300 as per insturctions
    Account& operator+ (Account& other) {
        const float fixedAmt = 300; // Fixed amount of 300
       
        // Make sure there is sufficient funds in other account
        if (other.balance >= fixedAmt) {
            this->balance += fixedAmt;
            other.balance -= fixedAmt;
        }
        else {
            cout << "Insufficient Funds in the Transfer of $300" << endl;
        }
        return *this;
    }
};


class SavingsAccount : public Account {
private:
    float interestRate;
    float minAmount = 200.00;

public:
    SavingsAccount(string num, string holder, float bal, float interestRate)
        : Account(num, holder, bal),
        interestRate(interestRate) {}

    // Withdraw, however checks if the base amount will still be left in the account after withdraw. If it's not cancels withdraw.
    void withdraw(int amount) {
        cout << "Withdrawing from Savings Account" << endl;
        if ((balance - amount) < minAmount) {
            cout << "Minimum balance exceeded. Withdraw caneled." << endl;
        }
        else if ((balance - amount) > 0) {
            balance -= amount;
        }
        else {
            cout << "Insufficient Funds." << endl;
        }
    }


    void displayDetails() const override{
        Account::displayDetails(); // Calls original call
        printf("Interest Rate: %.2f%%", interestRate*100); // Prints out new part
        cout << endl;
        cout << endl;
    }

};


class CurrentAccount : public Account {
private:
    float overdraftlimit;

public:
    // Constructor
    CurrentAccount(string num, string holder, float bal, float overdraftlimit)
        : Account(num, holder, bal),
        overdraftlimit(overdraftlimit) {}

    // Calls parent method. Prints out new stuff
    void displayDetails() const override {
        Account::displayDetails();
        printf("Overdraft Limit: $%.2f", overdraftlimit);
        cout << endl;
        cout << endl;
    }

    // Checks if withdraw is in range of overdraft limit. If so withdraw request is granted
    void withdraw(int amount) {
        cout << "Withdrawing from Current Account" << endl;
        if (((balance + overdraftlimit) - amount) < 0) {
            cout << "Minimum balance exceeded. Withdraw caneled." << endl;
        }
        else if (((balance + overdraftlimit) - amount) > 0) {
            balance -= amount;
        }
        else {
            cout << "Insufficient Funds." << endl;
        }
    }
};


int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);

    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    current + savings;
    savings.displayDetails();
    current.displayDetails();

    return 0;
}
