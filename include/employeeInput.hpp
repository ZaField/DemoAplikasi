#ifndef INPUTEMPLOYEE_HPP
#define INPUTEMPLOYEE_HPP

#include "database.hpp"
#include <iostream>
#include <string>
using namespace std;

struct Employee
{
    int id;
    string name;
    int type;
    double hourlyRate;
    int healthInsurance;
    int employeeInsurance;
    int otherLoan;
    double loanPayment;
};

void inputEmployee(Database* db);

bool anotherInput();

#endif
