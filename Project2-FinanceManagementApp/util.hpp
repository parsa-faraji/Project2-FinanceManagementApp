//
//  util.hpp
//  FinanceManagementApp
//
//  Created by Parsa Faraji on 11/16/24.
//

#ifndef util_hpp
#define util_hpp

#include "Transaction.hpp"
#include <vector>
#include <string>
#include <fstream> // for fstream

namespace FinanceManagement {

// define the categories list
extern const std::vector<std::string> categories;

// validate date in mm/dd/yyyy format
bool isValidDate(const std::string& dateStr);

// validate time in hh:mm format
bool isValidTime(const std::string& timeStr);

// generic function to get validated input
template <typename T>
T getValidatedInput(const std::string& prompt);

// process the file and handle transactions
void processFile();

// record a transaction
void recordTransaction(std::fstream &fout);

// read transactions from the file
std::vector<Transaction> readTransactionsFromFile(const std::string& filename);

// generate a summary for a specific month
void generateMonthlySummary(const std::vector<Transaction>& transactions, short int month);

// display monthly spending patterns for a specific month
void displayMonthlySpendingPattern(const std::vector<Transaction>& transactions, short int month);

// calculate and display the percentage of the budget spent on each category
void calculateBudgetPercentage(const std::vector<Transaction>& transactions, short int month);

} // namespace FinanceManagement

// include implementation of template functions


#endif // util_hpp
