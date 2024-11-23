//
//  Transaction.cpp
//  FinanceManagementApp
//
//  Created by Parsa Faraji on 11/15/24.
//

#include "Transaction.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

using namespace std;

// check if the transaction is valid
bool Transaction::isValidTransaction() const {
    return !transactionType.empty() && date.isValidDate() && time.isValidTime() && !category.empty();
}

// serialize transaction to csv format
string Transaction::toCSV() const {
    ostringstream oss;
    oss << transactionType << ","
        << setfill('0') << setw(2) << date.getMonth() << "/"
        << setfill('0') << setw(2) << date.getDay() << "/"
        << setw(4) << date.getYear() << "," // ensure year is always 4 digits
        << setfill('0') << setw(2) << time.getHour() << ":"
        << setfill('0') << setw(2) << time.getMinute()
        << setw(2) << time.getDayOrNight()
        << account.getAccountNumber() << ","
        << fixed << setprecision(2) << amount << ","
        << category << ","
        << (method == TransactionMethod::InStore ? "In-store" : "Online");
    return oss.str();
}

// deserialize transaction from csv format
Transaction Transaction::fromCSV(const string& csvLine) {
    stringstream ss(csvLine);
    string type, dateStr, timeStr, accountStr, amountStr, categoryStr, methodStr;

    getline(ss, type, ',');
    getline(ss, dateStr, ',');
    getline(ss, timeStr, ',');
    getline(ss, accountStr, ',');
    getline(ss, amountStr, ',');
    getline(ss, categoryStr, ',');
    getline(ss, methodStr, ',');

    // parse and validate the date
    if (dateStr.size() != 10 || dateStr[2] != '/' || dateStr[5] != '/') {
        throw invalid_argument("Invalid date format: " + dateStr);
    }
    int month = stoi(dateStr.substr(0, 2));
    int day = stoi(dateStr.substr(3, 2));
    int year = stoi(dateStr.substr(6, 4)); // ensure we extract 4 digits for the year
    Date date(month, day, year);

    // parse and validate the time
    if (timeStr.size() != 5 || timeStr[2] != ':') {
        throw invalid_argument("Invalid time format: " + timeStr);
    }
    int hour = stoi(timeStr.substr(0, 2));
    int minute = stoi(timeStr.substr(3, 2));
    Time time(hour, minute);

    // parse account number
    long long accountNumber;
    try {
        accountNumber = stoll(accountStr);
    } catch (const exception& e) {
        throw invalid_argument("Invalid account number: " + accountStr);
    }

    // parse amount
    double amount;
    try {
        amount = stod(amountStr);
    } catch (const exception& e) {
        throw invalid_argument("Invalid amount: " + amountStr);
    }

    // parse transaction method
    TransactionMethod method;
    if (methodStr == "In-store") {
        method = TransactionMethod::InStore;
    } else if (methodStr == "Online") {
        method = TransactionMethod::Online;
    } else {
        throw invalid_argument("Invalid transaction method: " + methodStr);
    }

    // construct and return the transaction object
    return Transaction{type, date, time, Account(accountNumber, 0.0), amount, categoryStr, method};
}

// equality operator
bool Transaction::operator==(const Transaction& other) const {
    return transactionType == other.transactionType &&
           date == other.date &&
           time == other.time &&
           account == other.account &&
           amount == other.amount &&
           category == other.category &&
           method == other.method;
}

// stream insertion operator
ostream& operator<<(ostream& os, const Transaction& transaction) {
    os << "Transaction Details:\n"
       << "  Type: " << transaction.transactionType << "\n"
       << "  Date: " << transaction.date << "\n"
       << "  Time: " << transaction.time << "\n"
       << "  Account: " << transaction.account.getAccountNumber() << "\n"
       << "  Amount: $" << transaction.amount << "\n"
       << "  Category: " << transaction.category << "\n"
       << "  Method: " << (transaction.method == TransactionMethod::InStore ? "In-store" : "Online") << "\n";
    return os;
}
