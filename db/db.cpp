#include "db.h"


Connection* getDB(void) {
    try {
        Driver* driver = get_driver_instance();
        Connection* con = driver->connect("tcp://127.0.0.1:3306", "username", "password");

        con->setSchema("database_name");
        return con;
        
    }
    catch (SQLException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return NULL;
    }
}