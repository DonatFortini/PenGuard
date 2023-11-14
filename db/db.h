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
#include <openssl/evp.h>
#include <iomanip>

using namespace sql;
std::string sha256(const std::string& input);
Connection* getDB(void) ;
void closeDB(Connection* con);
bool checkUser(std::string username, std::string password);



#endif // DATABASE_H