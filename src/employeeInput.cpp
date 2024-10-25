#include <iostream>
#include <string>
#include "database.hpp"
using namespace std;

struct Employee
{
    int id;
    string name;
    int type;
    double hourlyRate;
    int healthInsurace;
    int employeeInsurance;
    int otherLoan;
    double loanPayment;
};


void inputEmployee(Database* db) {
    map<string,function<variant<string, int, double>(const Employee&)>> employeeFieldMapping = {
        {"name", [](const Employee &e) -> variant<string, int, double> {return e.name;}},
        {"type", [](const Employee &e) -> variant<string, int, double> {return e.type;}},
        {"hourly_rate", [](const Employee &e) -> variant<string, int, double> {return e.hourlyRate;}},
        {"bpjs_health_insurance", [](const Employee &e) -> variant<string, int, double> {return e.healthInsurace;}},
        {"bpjs_employment_insurance", [](const Employee &e) -> variant<string, int, double> {return e.employeeInsurance;}},
        {"other_loan", [](const Employee &e) -> variant<string, int, double> {return e.otherLoan;}},
        {"loan_payment", [](const Employee &e) -> variant<string, int, double> {return e.loanPayment;}},
    };
    Employee employee;
    cout << "Input Employee Name: ";
    cin >> employee.name;
    cout << "0 for daily Worker, 1 for permanent Employee\nInput Employee Type: ";
    cin >> employee.type;
    cout << "Input Hourly Rate: ";
    cin >> employee.hourlyRate;
    cout << "0 if dont have, 1 if have\nDoes Employee have BPJS Health Insurance: ";
    cin >> employee.healthInsurace;
    cout << "0 if dont have, 1 if have\nDoes Employee have BPJS Employee Insurance: ";
    cin >> employee.employeeInsurance;
    cout << "0 if dont have, 1 if have\nDoes Employee have loan to company: ";
    cin >> employee.otherLoan;
    if (employee.otherLoan == 1)
    {
        cout << "How much the payment each month: ";
        cin >> employee.loanPayment;
    } else {
        employee.loanPayment = 0;
    }
    db -> insert("Employee", employee, employeeFieldMapping);
}

bool anotherInput() {
    char choice;
    cout << "\nDo you want to add another Employee? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}