#pragma once

#include <QDateTime>
class ElectionConfig
{
public:

    static QDateTime votingStart() {
        return QDateTime(QDate(2026, 7, 10), QTime(0, 0));
    }
    static QDateTime votingEnd() {
        return QDateTime(QDate(2026, 7, 28), QTime(23, 59, 59));
    }



    static QDateTime registrationStart() {
        return QDateTime(QDate(2026, 7, 16), QTime(0, 0));
    }
    static QDateTime registrationEnd() {
        return QDateTime(QDate(2026, 7, 25), QTime(23, 59, 59));
    }



    static bool isRegistrationOpen() {
        QDateTime now = QDateTime::currentDateTime();
        return now >= registrationStart() && now <= registrationEnd();
    }
    static bool isVotingOpen() {
        QDateTime now = QDateTime::currentDateTime();
        return now >= votingStart() && now <= votingEnd();
    }



};
