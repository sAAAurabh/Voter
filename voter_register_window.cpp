#include "voter_register_window.h"
#include <QCalendarWidget>
#include <QDateEdit>
#include <QGuiApplication>
#include <QScreen>
#include <QVBoxLayout>
#include "admin.h"
#include "electionconfig.h"

VoterRegisterWindow::VoterRegisterWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Voter Registration");
    setObjectName("VoterRegisterWindow");

    setStyleSheet(
        "#VoterRegisterWindow {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0f2027, stop:0.5 #203a43, stop:1 #2c5364);"
        "}"
        "QLabel {"
        "   color: #ffffff;"
        "}"
        "QLineEdit, QDateEdit, QComboBox {"
        "   background-color: rgba(20, 30, 48, 150);"
        "   color: #ffffff;"
        "   border: 1px solid #555555;"
        "   border-radius: 5px;"
        "   padding: 6px;"
        "}"
        "QLineEdit:focus, QDateEdit:focus, QComboBox:focus {"
        "   border: 1px solid #3498db;"
        "}"
        );

    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint);

    setMinimumSize(480, 640);
    resize(520, 700);

    title = new QLabel("Voter Registration", this);

    QFont title_font;
    title_font.setPointSize(24);
    title_font.setBold(true);

    title->setFont(title_font);
    title->setAlignment(Qt::AlignCenter);

    f_name_label = new QLabel("First Name", this);
    f_name_input = new QLineEdit(this);
    f_name_warn = new QLabel("●", this);
    f_name_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    f_name_warn->setVisible(false);
    f_name_warn->setFixedWidth(18);

    l_name_label = new QLabel("Last Name", this);
    l_name_input = new QLineEdit(this);
    l_name_warn = new QLabel("●", this);
    l_name_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    l_name_warn->setVisible(false);
    l_name_warn->setFixedWidth(18);

    f_name_input->setPlaceholderText("Enter First Name");
    l_name_input->setPlaceholderText("Enter Last Name");

    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);
    nid_warn = new QLabel("●", this);
    nid_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    nid_warn->setVisible(false);
    nid_warn->setFixedWidth(18);
    nid_input->setPlaceholderText("Enter National ID");

    dob_label = new QLabel("Date of Birth", this);
    dob_input = new QDateEdit(this);
    dob_warn = new QLabel("●", this);
    dob_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    dob_warn->setVisible(false);
    dob_warn->setFixedWidth(18);

    dob_input->setDisplayFormat("yyyy-MM-dd");
    dob_input->setCalendarPopup(true);
    dob_input->setMaximumDate(QDate::currentDate().addYears(-18));
    dob_input->setMinimumDate(QDate(1900, 1, 1));
    dob_input->setDate(QDate(2000, 1, 1));

    gender_label = new QLabel("Gender", this);
    gender_input = new QComboBox(this);
    gender_warn = new QLabel("●", this);
    gender_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    gender_warn->setVisible(false);
    gender_warn->setFixedWidth(18);

    gender_input->addItem("-- Select Gender --");
    gender_input->addItem("Male");
    gender_input->addItem("Female");
    gender_input->addItem("Other");

    photo_label = new QLabel("Photo", this);

    photo_btn = new QPushButton("Upload Photo", this);
    photo_btn->setCursor(Qt::PointingHandCursor);
    photo_btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   padding: 8px;"
        "   border: none;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    photo_warn = new QLabel("●", this);
    photo_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    photo_warn->setVisible(false);
    photo_warn->setFixedWidth(18);

    photo_preview = new QLabel(this);
    photo_preview->setFixedSize(64, 64);
    photo_preview->setStyleSheet("border: 2px dashed #888888; border-radius: 6px; color: #ffffff; background: rgba(0,0,0,50);");
    photo_preview->setAlignment(Qt::AlignCenter);
    photo_preview->setText("No Photo");
    photo_preview->setScaledContents(true);

    QHBoxLayout *photo_row = new QHBoxLayout();
    photo_row->setSpacing(12);
    photo_row->addWidget(photo_btn);
    photo_row->addWidget(photo_preview);
    photo_row->addStretch(1);

    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_warn = new QLabel("●", this);
    pass_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    pass_warn->setVisible(false);
    pass_warn->setFixedWidth(18);

    pass_input->setPlaceholderText("Enter Password");
    pass_input->setEchoMode(QLineEdit::Password);

    reg_btn = new QPushButton("Register", this);
    reg_btn->setCursor(Qt::PointingHandCursor);
    reg_btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #2ecc71;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #27ae60;"
        "}"
        );

    QFont msg_font;
    msg_font.setPointSize(15);
    msg_font.setBold(true);
    msg_font.setItalic(true);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setFont(msg_font);
    msg->setWordWrap(true);
    msg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    back_btn = new QPushButton("← Back to Login", this);
    back_btn->setStyleSheet("background: transparent;"
                            "color: #3498db;"
                            "border: none;"
                            "font-size: 12px;"
                            "text-align: left;");
    back_btn->setFixedSize(120, 20);
    back_btn->setCursor(Qt::PointingHandCursor);

    grid = new QGridLayout(this);
    grid->setContentsMargins(50, 30, 50, 30);
    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(14);
    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);
    grid->setColumnStretch(2, 0);
    grid->setColumnMinimumWidth(0, 110);

    int row = 0;
    grid->addWidget(title, row, 0, 1, 3);
    row++;

    grid->addWidget(f_name_label, row, 0);
    grid->addWidget(f_name_input, row, 1);
    grid->addWidget(f_name_warn, row, 2);
    row++;

    grid->addWidget(l_name_label, row, 0);
    grid->addWidget(l_name_input, row, 1);
    grid->addWidget(l_name_warn, row, 2);
    row++;

    grid->addWidget(nid_label, row, 0);
    grid->addWidget(nid_input, row, 1);
    grid->addWidget(nid_warn, row, 2);
    row++;

    grid->addWidget(dob_label, row, 0);
    grid->addWidget(dob_input, row, 1);
    grid->addWidget(dob_warn, row, 2);
    row++;

    grid->addWidget(gender_label, row, 0);
    grid->addWidget(gender_input, row, 1);
    grid->addWidget(gender_warn, row, 2);
    row++;

    grid->addWidget(photo_label, row, 0);
    grid->addLayout(photo_row, row, 1);
    grid->addWidget(photo_warn, row, 2);
    row++;

    grid->addWidget(pass_label, row, 0);
    grid->addWidget(pass_input, row, 1);
    grid->addWidget(pass_warn, row, 2);
    row++;

    grid->addWidget(msg, row, 0, 1, 3);
    row++;

    grid->addWidget(reg_btn, row, 0, 1, 3);
    row++;

    grid->addWidget(back_btn, row, 0, 1, 1, Qt::AlignLeft);
    row++;

    setLayout(grid);


    connect(reg_btn,  &QPushButton::clicked, this, &VoterRegisterWindow::register_user);
    connect(back_btn, &QPushButton::clicked, this, &VoterRegisterWindow::back_login);
    connect(photo_btn, &QPushButton::clicked, this, &VoterRegisterWindow::upload_photo);
}

void VoterRegisterWindow::register_user()
{
    Voter v;
    Admin a;

    if (!ElectionConfig::isRegistrationOpen()) {
        msg->setStyleSheet("color: red;");
        msg->setText(QString("Registration is only open from %1 to %2.")
                         .arg(ElectionConfig::registrationStart().toString("MMM d, yyyy"))
                         .arg(ElectionConfig::registrationEnd().toString("MMM d, yyyy")));
        return;
    }

    bool f_empty = f_name_input->text().isEmpty();
    bool l_empty = l_name_input->text().isEmpty();
    bool n_empty = nid_input->text().isEmpty();
    bool dob_default = (dob_input->date() == QDate(2000, 1, 1));
    bool gender_empty = (gender_input->currentIndex() == 0);
    bool p_empty = pass_input->text().isEmpty();
    bool photo_empty = photo_path.isEmpty();

    f_name_warn->setVisible(f_empty);
    l_name_warn->setVisible(l_empty);
    nid_warn->setVisible(n_empty);
    dob_warn->setVisible(dob_default);
    gender_warn->setVisible(gender_empty);
    pass_warn->setVisible(p_empty);
    photo_warn->setVisible(photo_empty);

    if (f_empty || l_empty || n_empty || dob_default || gender_empty || photo_empty || p_empty)
        return;

    switch(a.is_valid_nid_voter(nid_input->text().toStdString())){
    case is_valid_nid:
        v.nid = nid_input->text().toStdString();
        break;
    case length:
        msg->setStyleSheet("color: red;");
        msg->setText("NID must be 8 characters long!!");
        return;
    case not_unique:
        msg->setStyleSheet("color: red;");
        msg->setText("Voter already registetered!!");
        return;
    }

    v.first = f_name_input->text().toStdString();
    v.last = l_name_input->text().toStdString();
    v.dob = dob_input->date().toString("dd/MM/yyyy").toStdString();
    v.gender = gender_input->currentText().toStdString();
    v.photo_path = photo_path.toStdString();

    switch (a.is_valid_pass(pass_input->text().toStdString(), v.first)) {
    case is_valid:
        v.salt = admin.gen_salt();
        v.hash = admin.hash_pass(pass_input->text().toStdString(), v.salt);

        v.is_locked = false;
        v.attempts_left = 5;

        admin.add_voter(v);

        msg->setStyleSheet("color: #2ecc71;");
        msg->setText("Registered Successfully");

        clear_fields();
        break;

    case letter:
        msg->setStyleSheet("color: red;");
        msg->setText("Password must be at least 7 characters.");
        break;

    case number:
        msg->setStyleSheet("color: red;");
        msg->setText("At least 3 digits required.");
        break;

    case capital:
        msg->setStyleSheet("color: red;");
        msg->setText("At least 1 capital letter required.");
        break;

    case name:
        msg->setStyleSheet("color: red;");
        msg->setText("Password must not be same as your name");
        break;

    case special:
        msg->setStyleSheet("color: red;");
        msg->setText("At least 1 special character required.");
        break;
    }
}

void VoterRegisterWindow::back_login(){
    emit back_to_login_requested();
}

void VoterRegisterWindow::clear_fields()
{
    f_name_input->clear();
    l_name_input->clear();
    nid_input->clear();
    dob_input->setDate(QDate(2000, 1, 1));
    gender_input->setCurrentIndex(0);
    pass_input->clear();
    photo_path.clear();
    photo_preview->clear();
    photo_preview->setText("No Photo");

    f_name_warn->hide();
    l_name_warn->hide();
    nid_warn->hide();
    dob_warn->hide();
    gender_warn->hide();
    pass_warn->hide();
    photo_warn->hide();
}

void VoterRegisterWindow::clear_msg(){
    msg->clear();
}

void VoterRegisterWindow::upload_photo()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Select Photo", "", "Images (*.*)");

    if (file_path.isEmpty())
        return;

    photo_path = file_path;

    QPixmap pixmap(file_path);
    photo_preview->setPixmap(pixmap);
    photo_preview->setText("");
}