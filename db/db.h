#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string.h>

using namespace sql;

Connection* getDB(void) ;
void closeDB(Connection* con);


#endif // DATABASE_H