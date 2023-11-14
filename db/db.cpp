#include "db.h"

Connection *getDB(void)
{
    try
    {
        Driver *driver = get_driver_instance();
        Connection *con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
        con->setSchema("pwmanager");
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

std::string sha256(const std::string &input)
{
    unsigned char hash[EVP_MAX_MD_SIZE];
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    EVP_DigestFinal_ex(mdctx, hash, &md_len);
    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for (int i = 0; i < (int)md_len; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}