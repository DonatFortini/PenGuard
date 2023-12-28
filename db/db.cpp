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
    catch (sql::SQLException &e)
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

    PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(id_user) FROM users WHERE username = ? AND password = ?");
    pstmt->setString(1, username);
    pstmt->setString(2, encrypt(password));

    ResultSet *res = pstmt->executeQuery();
    res->next();
    return res->getInt(1) == 1;
}

bool addUserPassword(std::string user_id, std::string username, std::string password, std::string website)
{
    Connection *con = getDB();
    if (con == NULL)
        return false;

    PreparedStatement *pstmt = con->prepareStatement("INSERT INTO users_passwords (user_id,username, password, website) VALUES (?,?, ?, ?)");
    pstmt->setString(1, user_id);
    pstmt->setString(2, username);
    pstmt->setString(3, encrypt(password));
    pstmt->setString(4, website);

    pstmt->execute();
    return true;
}

bool addUser(std::string username, std::string password)
{
    Connection *con = getDB();
    if (con == NULL)
        return false;

    PreparedStatement *pstmt = con->prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
    pstmt->setString(1, username);
    pstmt->setString(2, encrypt(password));

    pstmt->execute();
    return true;
}

std::vector<Account> getUserPassword(std::string user_id)
{
    Connection *con = getDB();
    if (con == NULL)
        return std::vector<Account>();
    PreparedStatement *pstmt = con->prepareStatement("SELECT username,password,website FROM users_passwords WHERE user_id = ?");
    pstmt->setString(1, user_id);
    pstmt->execute();
    ResultSet *res = pstmt->getResultSet();
    std::vector<Account> accounts;
    while (res->next())
    {
        Account acc;
        acc.username = res->getString(1);
        acc.password = decrypt(res->getString(2));
        acc.website = res->getString(3);
        accounts.push_back(acc);
    }
    return accounts;
}

bool deleteUserPassword(std::string user_id, std::string username, std::string password, std::string website)
{
    Connection *con = getDB();
    if (con == NULL)
        return false;

    PreparedStatement *pstmt = con->prepareStatement("DELETE FROM users_passwords WHERE user_id = ? AND username = ? AND password = ? AND website = ?");
    pstmt->setString(1, user_id);
    pstmt->setString(2, username);
    pstmt->setString(3, encrypt(password));
    pstmt->setString(4, website);

    pstmt->execute();
    return true;
}

bool editUserPassword(std::string user_id, std::string username, std::string password, std::string website, std::string new_username, std::string new_password, std::string new_website)
{
    Connection *con = getDB();
    if (con == NULL)
        return false;

    PreparedStatement *pstmt = con->prepareStatement("UPDATE users_passwords SET username = ?, password = ?, website = ? WHERE user_id = ? AND username = ? AND password = ? AND website = ?");
    pstmt->setString(1, new_username);
    pstmt->setString(2, encrypt(new_password));
    pstmt->setString(3, new_website);
    pstmt->setString(4, user_id);
    pstmt->setString(5, username);
    pstmt->setString(6, encrypt(password));
    pstmt->setString(7, website);

    pstmt->execute();
    return true;
}

std::string encrypt(std::string to_encrypt)
{
    std::string key = "aptenodytes42069";
    std::string encrypted;
    for(size_t i = 0; i < to_encrypt.length(); i++)
    {
        char c = to_encrypt[i];
        char k = key[i % key.length()];
        c = c >> (k % 8);
        encrypted += c;
    }
    
}

std::string decrypt(std::string to_decrypt)
{
    std::string key = "aptenodytes42069";
    std::string decrypted;

    for (size_t i = 0; i < to_decrypt.length(); i++)
    {
        char c = to_decrypt[i];
        char k = key[i % key.length()];
        c = c << (k % 8);
        decrypted += c;
    }

    return decrypted;
}