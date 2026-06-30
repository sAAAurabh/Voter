#pragma once

#include <QWidget>
#include <QString>
#include "admin.h"

class QLabel;
class QPushButton;
class QGridLayout;

class CandidateHomeWindow : public QWidget
{
    Q_OBJECT

public:
    CandidateHomeWindow(const QString &nid, QWidget *parent = nullptr);

private:
    QString candidate_nid;   // NEW — store nid

    QLabel *title;
    QLabel *name_label;
    QLabel *nid_label;
    QLabel *party_label;
    QLabel *vote_label;
    QLabel *manifesto_label;
    QLabel *msg;
    QLabel *photo_label;

    QPushButton *edit_btn;
    QPushButton *logout_btn;

    QGridLayout *grid;

private slots:
    void edit_manifesto();



signals:
    void logout_requested();
};