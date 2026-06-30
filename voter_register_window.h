#pragma once

#include <QCalendarWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include "admin.h"

class VoterRegisterWindow : public QWidget
{
    Q_OBJECT

public:
    VoterRegisterWindow(QWidget *parent = nullptr);

private slots:
    void register_user();
    void back_login();
    void clear_fields();
    void upload_photo();

private:
    QLabel *title, *f_name_label, *l_name_label, *nid_label, *pass_label, *msg, *f_name_warn,
        *l_name_warn, *pass_warn, *nid_warn;
    QLineEdit *f_name_input, *l_name_input, *nid_input, *pass_input;
    QLabel *dob_label;
    QDateEdit *dob_input;
    QLabel *dob_warn;
    QLabel *gender_label;
    QComboBox *gender_input;
    QLabel *gender_warn;
    QLabel *photo_label;
    QPushButton *photo_btn;
    QLabel *photo_warn;
    QLabel *photo_preview;
    QString photo_path;
    QPushButton *reg_btn, *back_btn;
    QGridLayout *grid;
    Admin admin;

signals:
    void back_to_login_requested();
};