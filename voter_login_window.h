#pragma once

#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "admin.h"

class VoterLoginWindow : public QWidget
{
    Q_OBJECT

public:
    VoterLoginWindow(QWidget *parent = nullptr);

private slots:
    void login();
    void open_register();
    void clear_fields();

private:
    QLabel *title;

    QLabel *nid_label;
    QLineEdit *nid_input;

    QLabel *pass_label;
    QLineEdit *pass_input;

    QPushButton *reg_btn;
    QPushButton *login_btn;

    QLabel *msg;
    QGridLayout *grid;

    Admin admin;

signals:
    void register_requested();
    void login_successful(QString nid);



};