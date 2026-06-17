#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QSqlDatabase Database::db = QSqlDatabase();

bool Database::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("e_vote.db");

    if (!db.open()) {
        qDebug() << "DB OPEN FAILED:" << db.lastError().text();
        return false;
    }

    qDebug() << "DB OPEN SUCCESS";
    return true;
}

void Database::init()
{
    if (!db.isOpen()) {
        qDebug() << "Database not open!";
        return;
    }

    QSqlQuery q;

    q.exec("CREATE TABLE IF NOT EXISTS voters ("
           "nid TEXT PRIMARY KEY,"
           "first TEXT,"
           "last TEXT,"
           "dob TEXT,"
           "gender TEXT,"
           "password_hash TEXT,"
           "salt TEXT,"
           "photo_path TEXT,"
           "has_voted INTEGER DEFAULT 0,"
           "is_locked INTEGER DEFAULT 0,"
           "attempts_left INTEGER DEFAULT 5"
           ")");

    q.exec("CREATE TABLE IF NOT EXISTS candidates ("
           "nid TEXT PRIMARY KEY,"
           "first TEXT,"
           "last TEXT,"
           "party TEXT,"
           "dob TEXT,"
           "gender TEXT,"
           "password_hash TEXT,"
           "salt TEXT,"
           "photo_path TEXT,"
           "votes INTEGER DEFAULT 0,"
           "is_locked INTEGER DEFAULT 0,"
           "attempts_left INTEGER DEFAULT 5"
           ")");
}