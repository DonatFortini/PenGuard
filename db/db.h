#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>


using namespace sql;

typedef struct
{
    std::string username;
    std::string password;
    std::string website;
} Account;

std::string encrypt(std::string to_encrypt);
std::string decrypt(std::string to_decrypt);
Connection *getDB(void);
void closeDB(Connection *con);
bool checkUser(std::string username, std::string password);
bool addUserPassword(std::string user_id, std::string username, std::string password, std::string website);
bool addUser(std::string username, std::string password);
std::vector<Account> getUserPassword(std::string user_id);
bool deleteUserPassword(std::string user_id, std::string username, std::string password, std::string website);
bool editUserPassword(std::string user_id, std::string username, std::string password, std::string website, std::string new_username, std::string new_password, std::string new_website);
#endif // DATABASE_H