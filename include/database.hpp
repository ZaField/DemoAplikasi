#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <variant>
#include <sqlite3.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <sstream>

using namespace std;


class Database {
    private:
        sqlite3 *db;

    public:
        Database(const std::string &dbName);
        ~Database();

        void init();
        sqlite3* getDBConnection() const;

        template <typename T>
        bool insert(const string &tableName, const T &data, const map<string, function<variant<string, int, double>(const T&)>> &fieldMapping){
            string sql = "INSERT INTO " + tableName + " (";
            string placeholders = " VALUES (";
            for (auto &[columnName, getter] : fieldMapping){
                sql += columnName + ",";
                placeholders += "?,";
            }

            sql.pop_back();
            placeholders.pop_back();

            sql += ")";
            placeholders += ");";

            sql += placeholders;

            sqlite3_stmt *stmt;
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){
                cerr << "Error preparing insert statement: " << sqlite3_errmsg(db) << endl;
                return false;
            }

            int index = 1;

            for (auto &[columnName, getter] : fieldMapping){
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
                cerr << "Error executing insert statement: " << sqlite3_errmsg(db) << endl;
                sqlite3_finalize(stmt);
                return false;
            }

            sqlite3_finalize(stmt);
            return true;
        }

        template <typename T>
        bool update(const string &tableName, int id, const T &data, const map<string, function<variant<string, int, double>(const T&)>> &fieldMapping);

        bool remove(const string &tableName, int id);
};

#endif