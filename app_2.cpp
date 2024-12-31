#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void)
{
    cout << endl;

    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        std::string userArea;
        std::cout << "Enter the user's area: ";
        getline(cin , userArea);


        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
        /* Connect to the MySQL test database */
        con->setSchema("rta");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT DISTINCT StopName FROM ROUTE,STOPS_AT WHERE ROUTE.RouteID=STOPS_AT.RouteID AND ROUTE.RouteName LIKE '%" + userArea + "%';");
        //res = stmt->executeQuery("SELECT StopName FROM STOPS_AT,ROUTE WHERE ROUTE.RouteID=STOPS_AT.RouteID ;");
        //res = stmt->executeQuery("SELECT RouteName FROM route");
        std::cout << "Routes with stops in " << userArea << " : " << endl;

        while (res->next()) {
            std::cout <<"\t"<< res->getString("StopName") << endl;
        }
        
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}
