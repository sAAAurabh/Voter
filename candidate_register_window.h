#pragma once

#include <QWidget>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "admin.h"
#include <fstream>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QPixmap>
#include <QHBoxLayout>


class CandidateRegisterWindow : public QWidget
{
    Q_OBJECT

public:
    CandidateRegisterWindow(QWidget *parent = nullptr);

private slots:
    void register_user();
    void close_register();
    void clear_fields();
    void upload_photo();
    void upload_party_symbol();

private:
private:
    QLabel *title, *f_name_label, *l_name_label, *nid_label, *pass_label, *msg, *f_name_warn, *l_name_warn;
    QLabel *pass_warn, *nid_warn, *party_label, *party_warn;
    QLineEdit *f_name_input, *l_name_input, *nid_input, *pass_input, *party_input;
    QLabel    *dob_label;
    QDateEdit *dob_input;
    QLabel    *dob_warn;
    QLabel    *gender_label;
    QComboBox *gender_input;
    QLabel    *gender_warn;

    QLabel      *photo_label;
    QPushButton *photo_btn;
    QLabel      *photo_warn;
    QLabel      *photo_preview;
    QString      photo_path;

    QLabel *party_symbol_label;
    QPushButton *party_symbol_btn;
    QLabel *party_symbol_warn;
    QLabel *party_symbol_preview;
    QString party_symbol_path;

    QWidget *uploadWidget;
    QGridLayout *uploadGrid;

    QPushButton *reg_btn, *back_btn;
    QGridLayout *grid;
    Admin admin;
};