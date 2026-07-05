#include "candidate_login_window.h"
#include "candidate_home.h"
#include "candidate_register_window.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>

CandidateLoginWindow::CandidateLoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Candidate Login");
    //setFixedSize(720, 660);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("candidateLoginWindow");

    this->setStyleSheet(
        "#candidateLoginWindow { background-color: #1c1c22; }"
        "QLabel { color: #ffffff; font-weight: bold; }"
        );

    QLabel *logo = new QLabel(this);
    QPixmap pix("C:/Users/Lenovo/Desktop/final/Voter/icons/new.png");
    logo->setPixmap(pix.scaled(140, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignCenter);

    title = new QLabel("CANDIDATE LOGIN", this);

    title->setStyleSheet(
        "font-size: 38px;"
        "font-weight: bold;"
        "color: white;"
        );

    title->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel("Manage Your Campaign. Reach Every Voter.", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet(
        "color: #cbd5e1;"
        "font-weight: 600;"
        "margin-bottom: 20px;"
        "font-size: 19px;"
        );

    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);
    nid_label->setStyleSheet("margin-top: 10px; font-size: 16px;");
    nid_input->setPlaceholderText("Enter National ID");
    nid_input->setStyleSheet("font-size: 16px; padding: 15px; background-color: #ffffff; color: #1e293b; border-radius: 5px; border: none; font-weight: normal;");

    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_label->setStyleSheet("margin-top: 10px; font-size: 16px;");
    pass_input->setPlaceholderText("Enter Password");
    pass_input->setEchoMode(QLineEdit::Password);
    pass_input->setStyleSheet("font-size: 16px; padding: 15px; background-color: #ffffff; color: #1e293b; border-radius: 5px; border: none; font-weight: normal; margin-bottom: 20px;");

    login_btn = new QPushButton("Login", this);
    reg_btn = new QPushButton("Register", this);

    login_btn->setStyleSheet("background-color: #3b82f6; color: white; padding: 12px; border-radius: 5px; font-size: 15px; font-weight: bold; border: 2px solid #ffffff;");
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

    connect(login_btn, &QPushButton::clicked, this, &CandidateLoginWindow::login);
    connect(reg_btn, &QPushButton::clicked, this, [this](){emit register_requested();});
}

void CandidateLoginWindow::login()
{
    if (nid_input->text().isEmpty() && pass_input->text().isEmpty()) {
        msg->setStyleSheet("color: #e53e3e; font-size: 24px;");
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

    std::string nid = nid_input->text().toStdString();
    std::string pass = pass_input->text().toStdString();

    int rsp = admin.login_candidate(nid, pass);

    switch (rsp) {
    case login_success:
    {
        emit login_successful(nid_input->text());
        clear_fields();
        break;
    }
    case not_found:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Candidate Not Found");
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

void CandidateLoginWindow::clear_fields()
{
    nid_input->clear();
    pass_input->clear();
}