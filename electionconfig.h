#ifndef ELECTIONCONFIG_H
#define ELECTIONCONFIG_H

#include <QDateTime>

class ElectionConfig
{
public:
    static QDateTime registrationStart() {
        return QDateTime(QDate(2026, 7, 11), QTime(0, 0));
    }
    static QDateTime registrationEnd() {
        return QDateTime(QDate(2026, 7, 20), QTime(23, 59, 59));
    }
    static QDateTime votingStart() {
        return QDateTime(QDate(2026, 7, 21), QTime(0, 0));
    }
    static QDateTime votingEnd() {
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

#endif // ELECTIONCONFIG_H