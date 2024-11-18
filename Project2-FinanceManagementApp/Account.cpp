#include "Account.hpp"
#include <stdexcept>

Account::Account() : accountNumber(0), balance(0.0) {}

Account::Account(long long accountNumber, double balance)
    : accountNumber(accountNumber), balance(balance) {}

void Account::setAccountNumber(long long newAccountNumber) {
    if (newAccountNumber < 0) {
        throw std::invalid_argument("Account number cannot be negative.");
    }
    accountNumber = newAccountNumber;
}

void Account::setBalance(double newBalance) {
    if (newBalance < 0) {
        throw std::invalid_argument("Balance cannot be negative.");
    }
    balance = newBalance;
}

long long Account::getAccountNumber() const { return accountNumber; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Deposit amount cannot be negative.");
    }
    balance += amount;
}

void Account::withdraw(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Withdrawal amount cannot be negative.");
    }
    if (amount > balance) {
        throw std::invalid_argument("Insufficient funds for withdrawal.");
    }
    balance -= amount;
}

bool Account::operator==(const Account& other) const {
    return accountNumber == other.accountNumber &&
           balance == other.balance;
}

std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "Account Number: " << account.accountNumber << "\n"
       << "Balance: $" << account.balance;
    return os;
}
