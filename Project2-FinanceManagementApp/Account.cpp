#include "Account.hpp"
#include <stdexcept>

// default constructor: initializes account number to 0 and balance to 0.0
Account::Account() : accountNumber(0), balance(0.0) {}

// parameterized constructor: initializes account number and balance with given values
Account::Account(long long accountNumber, double balance)
    : accountNumber(accountNumber), balance(balance) {}

// sets the account number with validation to ensure it is non-negative
void Account::setAccountNumber(long long newAccountNumber) {
    // a bank account number should have at least 8 digits
    if (newAccountNumber < 0 || (std::to_string(newAccountNumber).length() < 8)) {
        throw std::invalid_argument("Account number cannot be negative.");
    }
    accountNumber = newAccountNumber;
}

// sets the account balance with validation to ensure it is non-negative
void Account::setBalance(double newBalance) {
    if (newBalance < 0) {
        throw std::invalid_argument("Balance cannot be negative.");
    }
    balance = newBalance;
}

// getter for account number
long long Account::getAccountNumber() const { return accountNumber; }

// getter for account balance
double Account::getBalance() const { return balance; }

// deposits a specified amount into the account, ensuring it is non-negative
void Account::deposit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Deposit amount cannot be negative.");
    }
    balance += amount;
}

// withdraws a specified amount from the account, ensuring it is non-negative and does not exceed the current balance
void Account::withdraw(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Withdrawal amount cannot be negative.");
    }
    if (amount > balance) {
        throw std::invalid_argument("Insufficient funds for withdrawal.");
    }
    balance -= amount;
}

// equality operator: compares two accounts for equality based on account number and balance
bool Account::operator==(const Account& other) const {
    return accountNumber == other.accountNumber &&
           balance == other.balance;
}

// stream insertion operator: outputs the account details (number and balance)
std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "Account Number: " << account.accountNumber << "\n"
       << "Balance: $" << account.balance;
    return os;
}
