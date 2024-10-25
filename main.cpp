#include <iostream>
#include "weekPayroll.hpp"
#include "employeeInput.hpp"
#include "database.hpp"
#include "showDatabase.hpp"
using namespace std;

void displayMenu1();
void displayMenu2();
bool rewindMenu();

int main() {
    Database* db = new Database("Employee.db");
    db->init();
    int choice1, choice2;
    bool continueProgram = true;
    welcomeMessage();

    do {
        system("clear");
        displayMenu1();
        cin >> choice1;
        switch (choice1) {
            case 1:
                do {
                    inputEmployee(db);
                } while (anotherInput());
                break;
                
            
            case 2:
                system("clear");
                showDatabase(db);
                displayMenu2();
                cin >> choice2;
                switch (choice2) {
                    case 1:
                        cout << "not yet wait." << endl;
                        break;
                    
                    case 2:
                        cout << "not yet wait." << endl;
                        break;

                    case 3:
                        cout << "not yet wait." << endl;
                        break;

                    case 4:
                        cout << "not yet wait." << endl;
                        break;

                    case 5:
                        cout << "not yet wait." << endl;
                        break;

                    case 6:
                        cout << "not yet wait." << endl;
                        break;

                    case 7:
                        break;

                    default:
                        cout << "Invalid Choice, Try Again\n";
                }
            
            case 3:
                cout << "Exiting Program";
                continueProgram = false;
                break;

            default:
                cout << "Invalid Choice, Try Again\n";
        }
    } while (continueProgram && rewindMenu());

    cout << "Terimakasih telah menggunakan kalkulator gaji. Sampai jumpa!" << endl;

    return 0;
}

bool rewindMenu() {
    char choice;
    cout << "\nDo you want to back to menu 1? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void displayMenu1() {
    cout << "\nMenu\n";
    cout << "1. Add Employee\n";
    cout << "2. Search Employee\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void displayMenu2() {
    cout << "\nMenu\n";
    cout << "1. Next Table\n";
    cout << "2. Previous Table\n";
    cout << "3. Search Employee\n";
    cout << "4. Remove Employee\n";
    cout << "5. Change Employee Data\n";
    cout << "6. Payroll Counter\n";
    cout << "7. Back\n";
    cout << "Enter your choice: ";
}