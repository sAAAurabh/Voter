#include "voter_login_window.h"
#include "voter_home.h"
#include "voter_register_window.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QAction>
#include <QPixmap>

VoterLoginWindow::VoterLoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Login");

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("loginWindow");

    this->setStyleSheet(
        "#loginWindow { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.0 #0c1e3d, stop:0.3 #1d3966, stop:0.55 #2c4a7c, stop:0.8 #4a6da3, stop:1.0 #6f8fc7); }"
        "QLabel { color: #ffffff; font-weight: bold; }"
        );

    QLabel *logo = new QLabel(this);
    QPixmap pix("C:/Users/Lenovo/Desktop/final/Voter/icons/evote.png");
    logo->setPixmap(pix.scaled(110, 110, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignCenter);

    title = new QLabel("E-VOTE", this);
    QFont titleFont;
    titleFont.setPointSize(26);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel("Secure & Transparent Digital Democracy.", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #e2e8f0; font-weight: 600; margin-bottom: 20px; font-size: 22px;");

    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);
    nid_label->setStyleSheet("margin-top: 10px;font-size: 16px;");
    nid_input->setPlaceholderText("Enter National ID");
    nid_input->setStyleSheet("font-size: 16px; padding: 15px; background-color: #ffffff; color: #1e293b; border-radius: 5px; border: none; font-weight: normal;");

    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_label->setStyleSheet("margin-top: 10px;font-size: 16px;");
    pass_input->setPlaceholderText("Enter Password");
    pass_input->setEchoMode(QLineEdit::Password);
    pass_input->setStyleSheet("font-size: 16px; padding: 15px; background-color: #ffffff; color: #1e293b; border-radius: 5px; border: none; font-weight: normal; margin-bottom: 20px;");

    login_btn = new QPushButton("Login", this);
    reg_btn = new QPushButton("Register", this);
login_btn->setStyleSheet("background-color: #3b82f6; color: white; padding: 12px; border-radius: 5px; font-size: 15px; font-weight: bold; border: 2px solid #ffffff;");;
    login_btn->setCursor(Qt::PointingHandCursor);

    reg_btn->setStyleSheet("background-color: #10b981; color: white; padding: 12px; border-radius: 5px; font-size: 15px; font-weight: bold; border: 2px solid #ffffff;");
    reg_btn->setCursor(Qt::PointingHandCursor);

    QFont msg_font;
    msg_font.setPointSize(11);
    msg_font.setItalic(true);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setFont(msg_font);

    grid = new QGridLayout(this);
    grid->setContentsMargins(50, 30, 50, 30);
    grid->setHorizontalSpacing(15);
    grid->setVerticalSpacing(5);

    grid->addWidget(logo, 0, 0, 1, 2);
    grid->addWidget(title, 1, 0, 1, 2);
    grid->addWidget(subtitle, 2, 0, 1, 2);
    grid->addWidget(nid_label, 3, 0, 1, 2);
    grid->addWidget(nid_input, 4, 0, 1, 2);
    grid->addWidget(pass_label, 5, 0, 1, 2);
    grid->addWidget(pass_input, 6, 0, 1, 2);
    grid->addWidget(login_btn, 7, 0, 1, 1);
    grid->addWidget(reg_btn, 7, 1, 1, 1);
    grid->addWidget(msg, 8, 0, 1, 2);

    connect(login_btn, &QPushButton::clicked, this, &VoterLoginWindow::login);
    connect(reg_btn, &QPushButton::clicked, this, [this](){emit register_requested();});
}

void VoterLoginWindow::login()
{
    if (nid_input->text().isEmpty() && pass_input->text().isEmpty()) {
        msg->setStyleSheet("color: #e53e3e;font-size:32 px;");
        msg->setText("Enter details!");
        return;
    } else if (nid_input->text().isEmpty()) {
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("nid field : empty");
        return;
    } else if (pass_input->text().isEmpty()) {
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("password field: empty!");
        return;
    }

    int rsp = admin.login_voter(nid_input->text().toStdString(), pass_input->text().toStdString());

    switch(rsp)
    {
    case login_success:
    {
        emit login_successful(nid_input->text());
        clear_fields();
        break;
    }
    case not_found:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Voter Not Found");
        clear_fields();
        break;
    case wrong_pass:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Wrong Password");
        clear_fields();
        break;
    case acc_locked:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Account Locked. Contact Admin");
        clear_fields();
        break;
    }
}

void VoterLoginWindow::clear_fields()
{
    nid_input->clear();
    pass_input->clear();
}