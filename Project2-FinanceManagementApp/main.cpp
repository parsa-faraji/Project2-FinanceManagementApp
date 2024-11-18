#include <iostream>
#include "util.hpp"

using namespace std;

int main() {
    // display welcome message
    cout << "welcome to the finance management app!" << endl;
    
    // call the principal function
    FinanceManagement::processFile();

    return 0;
}
