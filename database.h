#pragma once

#include <QtSql>
#include <QSqlQuery>

class Database {
public:
    static QSqlDatabase db;

    static bool connect();
    static void init();
};

