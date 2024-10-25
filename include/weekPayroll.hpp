#ifndef WEEKPAYROLL_HPP
#define WEEKPAYROLL_HPP

#include <string>
using namespace std;

void welcomeMessage();
void getEmployeeDetails(string& name, string& id, double& hoursWorked, double& hourlyRate);
double calculateGrossPay(double hoursWorked, double hourlyRate);
double askForDeductions(double hoursWorked, double hourlyRate);
void displayPayrollSummary(string name, string id, double grossPay, double totalDeductions, double netPay);
bool anotherEmployee();
void processPayroll();

#endif
