#pragma once

#include <QString>
#include <QWidget>
#include "admin.h"

class QLabel;
class QPushButton;
class QGridLayout;

class VoterHomeWindow : public QWidget
{
    Q_OBJECT

public:
    VoterHomeWindow(const QString &nid, QWidget *parent = nullptr);

private:
    QLabel *title;
    QLabel *photo_label;
    QLabel *name_label;
    QLabel *dob_label;
    QLabel *gender_label;
    QLabel *nid_label;
    QLabel *msg;

    QPushButton *view_candidates_btn;
    QPushButton *vote_candidates_btn;
    QPushButton *logout_btn;

    QGridLayout *grid;

    QString voter_nid;

private slots:
    void logout();
    void vote();
<<<<<<< HEAD

signals:
    void logout_requested();
    void vote_page_requested(QString nid);
=======
    void view_candidates();
>>>>>>> 66122f6f8cb9dcfdb07fdedad9498476192afe7b
};