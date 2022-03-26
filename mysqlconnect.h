#ifndef MYSQLCONNECT_H
#define MYSQLCONNECT_H

#include <QtSql>

class MysqlConnect
{
public:
    MysqlConnect();

private:
    QSqlDatabase factureDB;
};

#endif // MYSQLCONNECT_H
