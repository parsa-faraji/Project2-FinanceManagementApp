#ifndef Account_hpp
#define Account_hpp

#include <iostream>

// struct to resemble accounts
struct Account {
    long long accountNumber;
    double balance;

    // constructors
    Account();
    Account(long long accountNumber, double balance);

    // setters
    void setAccountNumber(long long newAccountNumber);
    void setBalance(double newBalance);

    // getters
    long long getAccountNumber() const;
    double getBalance() const;

    // utility functions
    void deposit(double amount);
    void withdraw(double amount);

    // equality operator
    bool operator==(const Account& other) const;

    // stream overload
    friend std::ostream& operator<<(std::ostream& os, const Account& account);
};

#endif /* Account_hpp */
