#include "database.hpp"
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

Database::Database(const string &dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::init(){
    // Initialize Employee Table
    const char *Employee = "CREATE TABLE IF NOT EXISTS Employee ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL,"
                      "type INTEGER NOT NULL,"
                      "hourly_rate REAL NOT NULL, "
                      "bpjs_health_insurance INTEGER NOT NULL,"
                      "bpjs_employment_insurance INTEGER NOT NULL,"
                      "other_loan INTEGER NOT NULL DEFAULT 0.0,"
                      "loan_payment REAL DEFAULT 0.0)";
    char *errMsg = 0;
    int execute_sql = sqlite3_exec(db, Employee, nullptr, nullptr, &errMsg);

    if (execute_sql != SQLITE_OK) {
        cerr << "Error Creating Employee Table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Enabling Foreign Key support on SQLite
    const char* foreignKeySupport = "PRAGMA foreign_keys = ON;";
    execute_sql = sqlite3_exec(db, foreignKeySupport, 0, 0, &errMsg);
    
    if (execute_sql!= SQLITE_OK) {
        cerr << "Error enabling foreign keys: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

sqlite3 *Database::getDBConnection() const{
    return db;
}

template <typename T>
bool Database::update(const string &tableName, int id, const T &data, const map<string, function<variant<string, int, double>(const T&)>> &fieldMapping){
    string sql = "UPDATE " + tableName + " SET ";
    for (auto &[columnName, getter] : fieldMapping){
        sql += columnName + " = ?, ";
    }

    sql.pop_back();
    sql += " WHERE id = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error preparing update statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    int index = 1;
    
    for(auto &[columnName, getter] : fieldMapping){
        variant<string, int, double> value = getter(data);
        
        if(holds_alternative<int>(value)){
            sqlite3_bind_int(stmt, index++, get<int>(value));
        }else if(holds_alternative<double>(value)){
            sqlite3_bind_double(stmt, index++, get<double>(value));
        }else if(holds_alternative<string>(value)){
            const string &strValue = get<string>(value);
            sqlite3_bind_text(stmt, index++, strValue.c_str(), -1, SQLITE_STATIC);
        }
    }

    if (sqlite3_step(stmt) != SQLITE_DONE){
        cerr << "Error executing update statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Database::remove(const string &tableName, int id){
    string sql = "DELETE FROM " + tableName + " WHERE id = ?;";

    sqlite3_stmt *stmt;

    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
        cerr << "Error preparing delete statement: " << sqlite3_errmsg(db) <<endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    if(sqlite3_step(stmt) != SQLITE_DONE){
        cerr << "Error executing delete statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}