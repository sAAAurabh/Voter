#include "candidate_login_window.h"
#include "candidate_home.h"
#include "candidate_register_window.h"
#include "election_config.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

CandidateLoginWindow::CandidateLoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Candidate Login");

    // Logo
    QLabel *logo = new QLabel(this);
    QPixmap pix(":/icons/icons/ok.png");
    logo->setPixmap(pix.scaled(110,110,
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignCenter);

    // Title
    title = new QLabel("CANDIDATE PORTAL", this);
    title->setAlignment(Qt::AlignCenter);

    QFont titleFont;
    titleFont.setPointSize(26);
    titleFont.setBold(true);

    title->setFont(titleFont);


    // Subtitle
    QLabel *subtitle =
        new QLabel("Manage Your Campaign Securely", this);

    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet(
        "font-size:20px;"
        "font-weight:600;"
        "margin-bottom:20px;"
        );

    // National ID
    nid_label = new QLabel("National ID", this);
    nid_label->setStyleSheet(
        "margin-top:10px;"
        "font-size:16px;"
        );

    nid_input = new QLineEdit(this);
    nid_input->setPlaceholderText("Enter National ID");
    nid_input->setStyleSheet(
        "font-size:16px;"
        "padding:15px;"
        );

    // Password
    pass_label = new QLabel("Password", this);
    pass_label->setStyleSheet(
        "margin-top:10px;"
        "font-size:16px;"
        );

    pass_input = new QLineEdit(this);
    pass_input->setPlaceholderText("Enter Password");
    pass_input->setEchoMode(QLineEdit::Password);
    pass_input->setStyleSheet(
        "font-size:16px;"
        "padding:15px;"
        "margin-bottom:20px;"
        );

    // Buttons
    login_btn = new QPushButton("Login", this);
    reg_btn = new QPushButton("Register", this);

    login_btn->setStyleSheet(
        "background-color:#3b82f6;"
        "padding:12px;"
        "font-size:15px;"
        "font-weight:bold;"
        );


    reg_btn->setStyleSheet(
        "background-color:#10b981;"
        "padding:12px;"
        "font-size:15px;"
        "font-weight:bold;"
        );


    // Message
    QFont msgFont;
    msgFont.setPointSize(11);
    msgFont.setItalic(true);

    msg = new QLabel(this);
    msg->setFont(msgFont);

    // Layout
    grid = new QGridLayout(this);

    grid->setContentsMargins(50,30,50,30);
    grid->setHorizontalSpacing(15);
    grid->setVerticalSpacing(5);

    grid->addWidget(logo,      0,0,1,2);
    grid->addWidget(title,     1,0,1,2);
    grid->addWidget(subtitle,  2,0,1,2);

    grid->addWidget(nid_label, 3,0,1,2);
    grid->addWidget(nid_input, 4,0,1,2);

    grid->addWidget(pass_label,5,0,1,2);
    grid->addWidget(pass_input,6,0,1,2);

    grid->addWidget(login_btn,7,0);
    grid->addWidget(reg_btn,7,1);

    grid->addWidget(msg,8,0,1,2);

    connect(login_btn, &QPushButton::clicked,
            this, &CandidateLoginWindow::login);

    connect(reg_btn, &QPushButton::clicked,
            this, [this]()
            {
                if (!ElectionConfig::isRegistrationOpen()) {
                    QMessageBox::warning(this, "Registration Closed",
                                         QString("Registration is only open from %1 to %2.")
                                             .arg(ElectionConfig::registrationStart().toString("MMM d, yyyy"))
                                             .arg(ElectionConfig::registrationEnd().toString("MMM d, yyyy")));
                    return;
                }
                emit register_requested();
            });
}

void CandidateLoginWindow::login()
{
    if (nid_input->text().isEmpty() && pass_input->text().isEmpty()) {
        msg->setStyleSheet("color: red;");
        msg->setText("Enter details!");
        return;
    } else if (nid_input->text().isEmpty()) {
        msg->setStyleSheet("color: red;");
        msg->setText("nid field : empty");
        return;
    } else if (pass_input->text().isEmpty()) {
        msg->setStyleSheet("color: red;");
        msg->setText("password field: empty!");
        return;
    }

    std::string nid
        = nid_input->text()
              .toStdString(); //because nid_input has Qstring, it needs to be converted to string explici
    std::string pass = pass_input->text().toStdString();

    int rsp = admin.login_candidate(nid, pass);

    switch (rsp) {
    case login_success:
    {
        emit login_successful(nid_input->text());
        clear_fields();
        break;
    }
    case not_found: {
        msg->setStyleSheet("color: red;");
        msg->setText("Candidate Not Found");
        clear_fields();
        break;
    }
    case wrong_pass:
        msg->setStyleSheet("color: red;");
        msg->setText("Wrong Password");
        clear_fields();
        break;

    case acc_locked:
        msg->setStyleSheet("color: red;");
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


