#include <iostream>
#include <string>
#include <iomanip>
#include "database.hpp"
using namespace std;


int callback (void* NotUsed, int argc, char** argv, char** azColName) {
    static bool isFirstRow = true;
    if (isFirstRow) {
        // Print the column headers only once
        cout << "+-------------------+--------+-------------+------------------+----------------------+------------+--------------+" << endl;
        cout << "| Name              | Type   | Hourly Rate | Health Insurance | Employment Insurance | Other Loan | Loan Payment |" << endl;
        cout << "+-------------------+--------+-------------+------------------+----------------------+------------+--------------+" << endl;
        isFirstRow = false;
    }
    cout << "| " << setw(17) << (argv[0] ? argv[0] : "NULL") << " | "
            << setw(6) << (argv[1] ? argv[1] : "NULL") << " | "
            << setw(11) << (argv[2] ? argv[2] : "NULL") << " | "
            << setw(16) << (argv[3] ? argv[3] : "NULL") << " | "
            << setw(20) << (argv[4] ? argv[4] : "NULL") << " | "
            << setw(10) << (argv[5] ? argv[5] : "NULL") << " | "
            << setw(12) << (argv[6] ? argv[6] : "NULL") << " | " << endl;

    cout << "+-------------------+--------+-------------+------------------+----------------------+------------+--------------+" << endl;
    return 0;
}

void showDatabase(Database* db) {
    string quary = "SELECT * FROM Employee;";
    char* messageError;


    int exit = sqlite3_exec(db->getDBConnection(), quary.c_str(), callback, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in Showing Data: " << messageError << endl;
        sqlite3_free(messageError);
    }
    
}