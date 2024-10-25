#include "weekPayroll.hpp"
#include <iostream>
#include "database.hpp"
using namespace std;

void welcomeMessage() {
    cout << "Selamat datang di Kalkulator Gaji!" << endl;
    cout << "----------------------------------" << endl;
}

void getEmployeeDetails(string& name, string& id, double& hoursWorked, double& hourlyRate) {
    cout << "\nMasukan Nama Karyawan: ";
    cin >> name;
    cout << "Masukan ID Karyawan: ";
    cin >> id;
    cout << "Masukan Total Jam kerja per Minggu: ";
    cin >> hoursWorked;
    cout << "Masukan Upah Perjam: ";
    cin >> hourlyRate;
}

double calculateGrossPay(double hoursWorked, double hourlyRate) {
    double overtimeRate = 1.5 * hourlyRate;
    if (hoursWorked > 40) {
        return (40 * hourlyRate) + ((hoursWorked - 40) * overtimeRate);
    } else {
        return hoursWorked * hourlyRate;
    }
}

double askForDeductions(double hoursWorked, double hourlyRate) {
    double totalDeductions = 0.0;
    char hasDeduction;

    // BPJS Kesehatan
    cout << "Apakah Karyawan memiliki potongan BPJS Kesehatan? (y/n): ";
    cin >> hasDeduction;
    if (hasDeduction == 'y' || hasDeduction == 'Y') {
        double bpjsKesehatan;
        bpjsKesehatan = calculateGrossPay(hoursWorked, hourlyRate) * 0.01;
        totalDeductions += bpjsKesehatan;
    }

    // BPJS Ketenagakerjaan
    cout << "Apakah Karyawan memiliki potongan BPJS Ketenagakerjaan? (y/n): ";
    cin >> hasDeduction;
    if (hasDeduction == 'y' || hasDeduction == 'Y') {
        double bpjsKetenagakerjaan = 0.0;
        cout << "Apakah BPJS Ketenagakerjaan termasuk Jaminan Hari Tua? (y/n): ";
        cin >> hasDeduction;
        if (hasDeduction == 'y' || hasDeduction == 'Y') {
            bpjsKetenagakerjaan += calculateGrossPay(hoursWorked, hourlyRate) * 0.02;
        }
        cout << "Apakah BPJS Ketenagakerjaan termasuk Jaminan Pensiun? (y/n): ";
        cin >> hasDeduction;
        if (hasDeduction == 'y' || hasDeduction == 'Y') {
            bpjsKetenagakerjaan += calculateGrossPay(hoursWorked, hourlyRate) * 0.01;
        }
        cout << "Apakah BPJS Ketenagakerjaan termasuk Kecelakaan Kerja? (y/n): ";
        cin >> hasDeduction;
        if (hasDeduction == 'y' || hasDeduction == 'Y') {
            bpjsKetenagakerjaan += calculateGrossPay(hoursWorked, hourlyRate) * 0.0054;
        }
        cout << "Apakah BPJS Ketenagakerjaan termasuk Jaminan Kematian? (y/n): ";
        cin >> hasDeduction;
        if (hasDeduction == 'y' || hasDeduction == 'Y') {
            bpjsKetenagakerjaan += calculateGrossPay(hoursWorked, hourlyRate) * 0.003;
        }
        totalDeductions += bpjsKetenagakerjaan;
    }

    // Pemotongan untuk Pinjaman atau Perjanjian Lainnya
    cout << "Apakah Karyawan memiliki potongan lain seperti pinjaman? (y/n): ";
    cin >> hasDeduction;
    if (hasDeduction == 'y' || hasDeduction == 'Y') {
        double otherDeductions;
        cout << "Masukan jumlah dari potongan lain: ";
        cin >> otherDeductions;
        totalDeductions += otherDeductions;
    }

    return totalDeductions;
}

void displayPayrollSummary(string name, string id, double grossPay, double totalDeductions, double netPay) {
    cout << "\nRingkasan Gaji untuk karyawan: " << name << " (ID: " << id << ")\n";
    cout << "------------------------------------------" << endl;
    cout << "Gaji Kotor: " << grossPay << endl;
    cout << "Total Potongan: " << totalDeductions << endl;
    cout << "Gaji Bersih: " << netPay << endl;
}

bool anotherEmployee() {
    char choice;
    cout << "\nApakah Anda ingin menghitung Gaji untuk karyawan lain? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void processPayroll() {
    string employeeName;
    string employeeID;
    double hoursWorked, hourlyRate;
    double grossPay, totalDeductions, netPay;

    getEmployeeDetails(employeeName, employeeID, hoursWorked, hourlyRate);
    grossPay = calculateGrossPay(hoursWorked, hourlyRate);
    totalDeductions = askForDeductions(hoursWorked, hourlyRate);
    netPay = grossPay - totalDeductions;
    displayPayrollSummary(employeeName, employeeID, grossPay, totalDeductions, netPay);
}
