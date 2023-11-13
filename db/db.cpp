#include "db.h"

Connection *getDB(void)
{
    try
    {
        Driver *driver = get_driver_instance();
        Connection *con = driver->connect("tcp://127.0.0.1:3306", "root", "1973");

        con->setSchema("penGuard");
        return con;
    }
    catch (SQLException &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return NULL;
    }
}

void closeDB(Connection *con)
{
    try
    {
        con->close();
    }
    catch (SQLException &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}



bool checkUser(std::string username, std::string password)
{
    Connection *con = getDB();
    if (con == NULL)
        return false;

    PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(id_user) FROM user WHERE username = ? AND password = ?");
    pstmt->setString(1, username);
    pstmt->setString(2, password);

    ResultSet *res = pstmt->executeQuery();
    int result = res->next();

    delete res;
    delete pstmt;
    closeDB(con);

    return result == 1;
}
