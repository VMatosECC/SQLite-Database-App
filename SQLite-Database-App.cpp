/* ----------------------------------------------------------------------------
Goal:
- Create a SQL (sqlite3) database,
- create a table,
- insert data,
- select data,
- update data,
- delete data.

--------------------------------------------------------------------------------- */
#include <iostream>
#include <sqlite3.h>
using namespace std;

int main() {
    sqlite3* db;
    int fd = sqlite3_open("mydb.db", &db);

    if (fd == SQLITE_OK) {
        cout << "Success opening/creating the database.\n";
    }
    else {
        cout << "Error:\n";
        cout << sqlite3_errmsg(db) << '\n';
        exit(1);
    }
    cout << "\nDatabase mydb.sql opened successfully.\n";
    //create a table
    string sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
    char* errMsg;
    fd = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (fd != SQLITE_OK) {
        cout << "Error:\n";
        cout << errMsg << '\n';
        sqlite3_free(errMsg);
        exit(1);
    }
    cout << "\nTable created successfully.\n";

    //insert data
    sql = "INSERT INTO users (name, age) VALUES ('Homer', 39);";
    fd = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (fd != SQLITE_OK) {
        cout << "Error:\n";
        cout << errMsg << '\n';
        sqlite3_free(errMsg);
        exit(1);
    }
    sql = "INSERT INTO users (name, age) VALUES ('Bart', 10);";
    fd = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (fd != SQLITE_OK) {
        cout << "Error:\n";
        cout << errMsg << '\n';
        sqlite3_free(errMsg);
        exit(1);
    }
    cout << "\nData inserted successfully.\n";

    //select data put results in a table
    sql = "SELECT * FROM users;";
    sqlite3_stmt* stmt;
    fd = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (fd != SQLITE_OK) {
        cout << "Error:\n";
        cout << sqlite3_errmsg(db) << '\n';
        exit(1);
    }
    while ((fd = sqlite3_step(stmt)) == SQLITE_ROW) {
        cout << "Record:\n";
        cout << " id:   " << sqlite3_column_int(stmt, 0) << '\n';
        cout << " name: " << sqlite3_column_text(stmt, 1) << '\n';
        cout << " age:  " << sqlite3_column_int(stmt, 2) << '\n';
    }
    sqlite3_finalize(stmt);
    cout << "\nData selected successfully.\n";

    //update data
    sql = "UPDATE users SET age = 40 WHERE name = 'Homer';";
    fd = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (fd != SQLITE_OK) {
        cout << "Error:\n";
        cout << errMsg << '\n';
        sqlite3_free(errMsg);
        exit(1);
    }
    cout << "\nData updated successfully.\n";

    //delete data
    sql = "DELETE FROM users WHERE name = 'Bart';";
    fd = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (fd != SQLITE_OK) {
        cout << "Error:\n";
        cout << errMsg << '\n';
        sqlite3_free(errMsg);
        exit(1);
    }
    cout << "\nData deleted successfully.\n";


    sqlite3_close(db);
    cout << "\nDatabase mydb.sql closed successfully.\n";
}