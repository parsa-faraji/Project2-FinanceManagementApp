//
//  util.cpp
//  FinanceManagementApp
//
//  Created by Parsa Faraji on 11/16/24.
//

#include "util.hpp"
#include "Transaction.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <memory> // for smart pointers

using namespace std;

// define namespace
namespace FinanceManagement {

// define the categories list
const vector<string> categories = {
    "Food", "Housing", "Transport", "Healthcare",
    "Entertainment", "Education", "Savings", "Income",
    "Debt", "Other"
};

// auxilliary function to validate date mm/dd/yyyy
bool isValidDate(const string& dateStr) {
    if (dateStr.size() != 10 || dateStr[2] != '/' || dateStr[5] != '/') return false;

    try {
        int month = stoi(dateStr.substr(0, 2));
        int day = stoi(dateStr.substr(3, 2));
        int year = stoi(dateStr.substr(6));

        if (month < 1 || month > 12 || day < 1 || year < 1) return false;

        static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxDays = daysInMonth[month - 1];

        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
            maxDays = 29;
        }
        return (day <= maxDays);
    } catch (const invalid_argument& e) {
        cerr << "Error parsing date: " << dateStr << " (" << e.what() << ")" << endl;
        return false;
    } catch (const out_of_range& e) {
        cerr << "Date out of range: " << dateStr << " (" << e.what() << ")" << endl;
        return false;
    }
}

// auxilliary function to validate time hh:mm
bool isValidTime(const string& timeStr) {
    if (timeStr.size() != 5 || timeStr[2] != ':') return false;

    try {
        int hour = stoi(timeStr.substr(0, 2));
        int minute = stoi(timeStr.substr(3, 2));
        return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
    } catch (const invalid_argument& e) {
        cerr << "Error parsing time: " << timeStr << " (" << e.what() << ")" << endl;
        return false;
    } catch (const out_of_range& e) {
        cerr << "Time out of range: " << timeStr << " (" << e.what() << ")" << endl;
        return false;
    }
}

// generic function to handle errors
template <typename T>
T getValidatedInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please try again." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

// processFile function
void processFile() {
    fstream fout("/Users/parsafaraji/Desktop/Project2-FinanceManagementApp/Project2-FinanceManagementApp", ios::out | ios::app);
    if (!fout.is_open()) {
        cerr << "Error opening file. Please check file directory or permissions." << endl;
        return;
    }

    while (true) {
        cout << "\n===============================================\n";
        cout << "Welcome to Finance Management App\n";
        cout << "===============================================\n";
        cout << "1) Record a transaction\n2) View monthly summary\n3) Exit\n";
        cout << "===============================================\n";

        int choice = getValidatedInput<int>("Enter your choice: ");
        switch (choice) {
            case 1:
                recordTransaction(fout);
                break;
            case 2: {
                int month = getValidatedInput<int>("Enter the month (1-12) for the summary: ");
                if (month < 1 || month > 12) {
                    cerr << "Invalid month. Please enter a value between 1 and 12." << endl;
                    break;
                }
                vector<Transaction> transactions = readTransactionsFromFile("/Users/parsafaraji/Desktop/Project2-FinanceManagementApp/Project2-FinanceManagementApp");
                if (!transactions.empty()) {
                    displayMonthlySpendingPattern(transactions, month);
                } else {
                    cerr << "No transactions found." << endl;
                }
                break;
            }
            case 3:
                fout.close();
                return;
            default:
                cerr << "Invalid choice. Please try again." << endl;
        }
    }
}

// record a transaction by passing output stream
void recordTransaction(fstream &fout) {
    string dateStr, timeStr, type, category;
    int choice, categoryChoice, methodChoice;
    long long accountNumber;
    double amount;

    do {
        cout << "\n-----------------------------------------------\n";
        cout << "Transaction Entry\n";
        cout << "-----------------------------------------------\n";

        cout << "Are you recording a Purchase or Deposit?\n1) Purchase\n2) Deposit\n0) Exit\nEnter your choice: ";
        choice = getValidatedInput<int>("");

        if (choice == 0) return;
        if (choice != 1 && choice != 2) {
            cerr << "Invalid choice. Please try again." << endl;
            continue;
        }

        type = (choice == 1 ? "Purchase" : "Deposit");

        while (true) {
            cout << "Enter the date (MM/DD/YYYY): ";
            getline(cin >> ws, dateStr); // use ws to clear leading whitespace
            if (isValidDate(dateStr)) break;
            cerr << "Invalid date format. Please use MM/DD/YYYY." << endl;
        }

        while (true) {
            cout << "Enter the time (HH:MM): ";
            getline(cin >> ws, timeStr); // use ws to clear leading whitespace
            if (isValidTime(timeStr)) break;
            cerr << "Invalid time format. Please use HH:MM." << endl;
        }

        accountNumber = getValidatedInput<long long>("Enter the account/card number: ");
        amount = getValidatedInput<double>("Enter the amount (e.g., 100.50): ");
        if (type == "Purchase") amount *= -1;

        cout << "Select a category: ";
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << i + 1 << ") " << categories[i] << " ";
        }
        cout << endl;

        while (true) {
            categoryChoice = getValidatedInput<int>("Enter your choice: ");
            if (categoryChoice >= 1 && categoryChoice <= categories.size()) break;
            cerr << "Invalid category. Please choose a valid option." << endl;
        }
        category = categories[categoryChoice - 1];

        while (true) {
            methodChoice = getValidatedInput<int>("Enter transaction method (1: In-store, 2: Online): ");
            if (methodChoice == 1 || methodChoice == 2) break;
            cerr << "Invalid method. Please choose 1 or 2." << endl;
        }
        TransactionMethod method = (methodChoice == 1) ? TransactionMethod::InStore : TransactionMethod::Online;

        int month = stoi(dateStr.substr(0, 2));
        int day = stoi(dateStr.substr(3, 2));
        int year = stoi(dateStr.substr(6));
        Date date(year, month, day);

        int hour = stoi(timeStr.substr(0, 2));
        int minute = stoi(timeStr.substr(3, 2));
        Time time(hour, minute);

        Transaction transaction = {type, date, time, Account(accountNumber, 0.0), amount, category, method};

        fout << transaction.toCSV() << endl;
        fout.flush();
        cout << "Transaction recorded successfully!" << endl;

        choice = getValidatedInput<int>("Do you want to record another transaction? (1: Yes, 0: No): ");
    } while (choice != 0);
}

// read transactions from the file
vector<Transaction> readTransactionsFromFile(const string &filename) {
    fstream fin(filename, ios::in);
    if (!fin.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return {};
    }

    vector<Transaction> transactions;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            cerr << "Skipping empty line in file." << endl;
            continue;
        }
        try {
            cout << "Processing line: " << line << endl;
            transactions.push_back(Transaction::fromCSV(line));
        } catch (const exception& e) {
            cerr << "Error parsing line: " << line << "\nReason: " << e.what() << endl;
        }
    }
    fin.close();
    return transactions;
}

// generate monthly summary
void generateMonthlySummary(const vector<Transaction>& transactions, short int month) {
    double income = 0.0, expenses = 0.0, total = 0.0;
    for (const auto& transaction : transactions) {
        if (transaction.getDate().getMonth() == month) {
            if (transaction.getAmount() > 0) {
                income += transaction.getAmount();
                total += transaction.getAmount();
            } else {
                expenses -= transaction.getAmount();
                total += transaction.getAmount();
            }
        }
    }

    cout << "Monthly Summary for Month " << month << ":\n";
    cout << "Total Income: $" << income << "\nTotal Expenses: $" << expenses << "\nNet Total: $" << total << endl;
}

// display monthly spending patterns
void displayMonthlySpendingPattern(const vector<Transaction>& transactions, short int month) {
    generateMonthlySummary(transactions, month);

    for (const auto& category : categories) {
        double categorySum = 0.0;
        for (const auto& transaction : transactions) {
            if (transaction.getDate().getMonth() == month && transaction.getCategory() == category) {
                categorySum += transaction.getAmount();
            }
        }
        cout << "Category: " << category << "\n  Total: $" << categorySum;
        cout << endl;
    }
}

} // namespace FinanceManagement
