//
//  Transaction.hpp
//  FinanceManagementApp
//
//  Created by Parsa Faraji on 11/15/24.
//

#ifndef Transaction_hpp
#define Transaction_hpp

#include <string>
#include "Date.hpp"
#include "Account.hpp"
#include "Time.hpp"

using std::string;

// enum for transaction methods
enum class TransactionMethod {
    InStore,
    Online
};

// transaction structure
struct Transaction {
    string transactionType;  // e.g., "Purchase" or "Deposit"
    Date date;
    Time time;
    Account account;
    double amount;
    string category;
    TransactionMethod method;

    // utility functions
    Date getDate() const { return date; }
    double getAmount() const { return amount; }
    string getCategory() const { return category; }
    TransactionMethod getMethod() const { return method; }
    bool isValidTransaction() const;

    // csv serialization
    string toCSV() const;
    static Transaction fromCSV(const string& csvLine);

    // overloaded operators
    bool operator==(const Transaction& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
};

#endif /* Transaction_hpp */
