#pragma once

#include <QSqlQuery>
#include <QtSql>

class Database
{
public:
    static QSqlDatabase db;

    static bool connect();
    static void init();
};
