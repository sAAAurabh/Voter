#include "candidate_register_window.h"
#include <QCalendarWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QFileDialog>
#include "admin.h"

CandidateRegisterWindow::CandidateRegisterWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Candidate Registration");

    QRect screen = QGuiApplication::primaryScreen()->availableGeometry();
    move(screen.center() - QPoint(width() / 2, height() / 2));

    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                   | Qt::WindowMaximizeButtonHint);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("candidateRegisterWindow");

    this->setStyleSheet(
        "#candidateRegisterWindow { "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #1c1c22,"
        "stop:0.5 #14161a,"
        "stop:1 #0f1115);"
        "}"
        "QLabel { color: #ffffff; font-weight: bold; }"
        );

    QString inputStyle = "padding: 8px; font-size: 14px; background-color: #ffffff; color: #1e293b; border-radius: 5px; border: none; font-weight: normal;";

    title = new QLabel("Candidate Registration", this);

    QFont title_font("Segoe UI", 30, QFont::Bold);
    title->setFont(title_font);

    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
        "color: white;"
        "font-size: 26px;"
        "font-weight: bold;"
        );

    f_name_label = new QLabel("First Name", this);
    f_name_input = new QLineEdit(this);
    f_name_warn = new QLabel("●", this);
    f_name_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    f_name_warn->setVisible(false);
    f_name_input->setPlaceholderText("First Name");
    f_name_input->setStyleSheet(inputStyle);

    l_name_label = new QLabel("Last Name", this);
    l_name_input = new QLineEdit(this);
    l_name_warn = new QLabel("●", this);
    l_name_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    l_name_warn->setVisible(false);
    l_name_input->setPlaceholderText("Last Name");
    l_name_input->setStyleSheet(inputStyle);

    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);
    nid_warn = new QLabel("●", this);
    nid_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    nid_warn->setVisible(false);
    nid_input->setPlaceholderText("Enter National ID");
    nid_input->setStyleSheet(inputStyle);

    dob_label = new QLabel("Date of Birth", this);
    dob_input = new QDateEdit(this);
    dob_warn = new QLabel("●", this);
    dob_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    dob_warn->setVisible(false);
    dob_input->setDisplayFormat("yyyy-MM-dd");
    dob_input->setCalendarPopup(true);
    dob_input->setMaximumDate(QDate::currentDate().addYears(-18));
    dob_input->setMinimumDate(QDate(1900, 1, 1));
    dob_input->setDate(QDate(2000, 1, 1));
    dob_input->setStyleSheet(inputStyle);

    party_label = new QLabel("Party", this);
    party_input = new QLineEdit(this);
    party_warn = new QLabel("●", this);
    party_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    party_warn->setVisible(false);
    party_input->setPlaceholderText("Enter Your Party");
    party_input->setStyleSheet(inputStyle);

    gender_label = new QLabel("Gender", this);
    gender_input = new QComboBox(this);
    gender_warn = new QLabel("●", this);
    gender_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    gender_warn->setVisible(false);
    gender_input->addItem("-- Select Gender --");
    gender_input->addItem("Male");
    gender_input->addItem("Female");
    gender_input->addItem("Other");
    gender_input->setStyleSheet(inputStyle);

    photo_label = new QLabel("Photo", this);
    photo_btn = new QPushButton("Upload Photo", this);
    photo_btn->setCursor(Qt::PointingHandCursor);
    photo_btn->setStyleSheet("background-color:#3498db; color:white; padding:8px; border-radius:5px; font-size: 13px;");

    photo_warn = new QLabel("●", this);
    photo_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    photo_warn->setVisible(false);

    photo_preview = new QLabel(this);
    photo_preview->setFixedSize(80, 80);
    photo_preview->setStyleSheet("border:2px dashed #9cb4d8; border-radius:6px; color: #e2e8f0; font-weight: normal;");
    photo_preview->setAlignment(Qt::AlignCenter);
    photo_preview->setText("No Photo");
    photo_preview->setScaledContents(true);

    party_symbol_label = new QLabel("Party Symbol", this);
    party_symbol_btn = new QPushButton("Upload Symbol", this);
    party_symbol_btn->setCursor(Qt::PointingHandCursor);
    party_symbol_btn->setStyleSheet("background-color:#3498db; color:white; padding:8px; border-radius:5px; font-size: 13px;");

    party_symbol_warn = new QLabel("●", this);
    party_symbol_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    party_symbol_warn->setVisible(false);

    party_symbol_preview = new QLabel(this);
    party_symbol_preview->setFixedSize(80, 80);
    party_symbol_preview->setStyleSheet("border:2px dashed #9cb4d8; border-radius:6px; color: #e2e8f0; font-weight: normal;");
    party_symbol_preview->setAlignment(Qt::AlignCenter);
    party_symbol_preview->setText("No Symbol");
    party_symbol_preview->setScaledContents(true);

    uploadWidget = new QWidget(this);
    uploadGrid = new QGridLayout(uploadWidget);
    uploadGrid->setHorizontalSpacing(35);
    uploadGrid->setVerticalSpacing(8);
    uploadGrid->setContentsMargins(0,0,0,0);
    uploadGrid->addWidget(photo_label, 0, 0, Qt::AlignCenter);
    uploadGrid->addWidget(party_symbol_label, 0, 1, Qt::AlignCenter);
    uploadGrid->addWidget(photo_btn, 1, 0);
    uploadGrid->addWidget(party_symbol_btn, 1, 1);
    uploadGrid->addWidget(photo_preview, 2, 0, Qt::AlignCenter);
    uploadGrid->addWidget(party_symbol_preview, 2, 1, Qt::AlignCenter);

    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_warn = new QLabel("●", this);
    pass_warn->setStyleSheet("color:#ff4c4c; font-size:18px");
    pass_warn->setVisible(false);
    pass_input->setPlaceholderText("Enter Password");
    pass_input->setStyleSheet(inputStyle);
    pass_input->setEchoMode(QLineEdit::Password);

    QCheckBox *terms_checkbox = new QCheckBox("I hereby declare that all information provided is true and correct.", this);
    terms_checkbox->setObjectName("terms_checkbox");
    terms_checkbox->setStyleSheet("color: white; font-weight: bold; font-size: 14px; spacing: 10px;");

    reg_btn = new QPushButton("Register", this);
    reg_btn->setCursor(Qt::PointingHandCursor);
    reg_btn->setStyleSheet("background-color:#10b981; color:white; padding:12px; border-radius:5px; font-size: 15px; font-weight: bold;");

    QFont msg_font;
    msg_font.setPointSize(12);
    msg_font.setBold(true);
    msg_font.setItalic(true);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setFont(msg_font);
    msg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    back_btn = new QPushButton("← Back to Login", this);
    back_btn->setStyleSheet("background: transparent; color: #93c5fd; border: none; font-size: 13px; font-weight: bold;");
    back_btn->setCursor(Qt::PointingHandCursor);

    grid = new QGridLayout(this);
    grid->setContentsMargins(50, 25, 50, 20);
    grid->setHorizontalSpacing(15);
    grid->setVerticalSpacing(8);

    grid->addWidget(title, 0, 0, 1, 6);

    grid->addWidget(f_name_label, 1, 0);
    grid->addWidget(f_name_input, 1, 1);
    grid->addWidget(f_name_warn, 1, 2);
    grid->addWidget(l_name_label, 1, 3);
    grid->addWidget(l_name_input, 1, 4);
    grid->addWidget(l_name_warn, 1, 5);

    grid->addWidget(nid_label, 2, 0);
    grid->addWidget(nid_input, 2, 1, 1, 4);
    grid->addWidget(nid_warn, 2, 5);

    grid->addWidget(dob_label, 3, 0);
    grid->addWidget(dob_input, 3, 1, 1, 4);
    grid->addWidget(dob_warn, 3, 5);

    grid->addWidget(gender_label, 4, 0);
    grid->addWidget(gender_input, 4, 1, 1, 4);
    grid->addWidget(gender_warn, 4, 5);

    grid->addWidget(party_label, 5, 0);
    grid->addWidget(party_input, 5, 1, 1, 4);
    grid->addWidget(party_warn, 5, 5);

    grid->addWidget(pass_label, 6, 0);
    grid->addWidget(pass_input, 6, 1, 1, 4);
    grid->addWidget(pass_warn, 6, 5);

    grid->addWidget(uploadWidget, 7, 0, 1, 6);
    grid->addWidget(terms_checkbox, 8, 0, 1, 6, Qt::AlignCenter);
    grid->addWidget(msg, 9, 0, 1, 6);
    grid->addWidget(reg_btn, 10, 0, 1, 6);
    grid->addWidget(back_btn, 11, 0, 1, 6, Qt::AlignCenter);

    connect(reg_btn, &QPushButton::clicked, this, &CandidateRegisterWindow::register_user);
    connect(back_btn, &QPushButton::clicked, this, [this](){emit back_to_login_requested();});
    connect(photo_btn, &QPushButton::clicked, this, &CandidateRegisterWindow::upload_photo);
    connect(party_symbol_btn, &QPushButton::clicked, this, &CandidateRegisterWindow::upload_party_symbol);
}

void CandidateRegisterWindow::register_user()
{
    Candidate c;
    Admin a;

    bool f_empty = f_name_input->text().isEmpty();
    bool l_empty = l_name_input->text().isEmpty();
    bool pty_empty = party_input->text().isEmpty();
    bool n_empty = nid_input->text().isEmpty();
    bool dob_default = (dob_input->date() == QDate(2000, 1, 1));
    bool gender_empty = (gender_input->currentIndex() == 0);
    bool p_empty = pass_input->text().isEmpty();
    bool photo_empty = photo_path.isEmpty();
    bool party_symbol_empty = party_symbol_path.isEmpty();

    QCheckBox* terms = this->findChild<QCheckBox*>("terms_checkbox");
    bool terms_checked = terms ? terms->isChecked() : false;

    f_name_warn->setVisible(f_empty);
    l_name_warn->setVisible(l_empty);
    party_warn->setVisible(pty_empty);
    nid_warn->setVisible(n_empty);
    dob_warn->setVisible(dob_default);
    gender_warn->setVisible(gender_empty);
    pass_warn->setVisible(p_empty);
    photo_warn->setVisible(photo_empty);

    if(!terms_checked) {
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Please declare that the details are correct.");
        return;
    }

    if(f_empty || l_empty || n_empty || dob_default || gender_empty || photo_empty || party_symbol_empty|| p_empty) return;

    switch(a.is_valid_nid_candidate(nid_input->text().toStdString())){
    case is_valid_nid:
        c.nid = nid_input->text().toStdString();
        break;
    case length:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("NID must be 8 characters long!!");
        return;
    case not_unique:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Candidate already registered!!");
        return;
    }

    c.first = f_name_input->text().toStdString();
    c.last = l_name_input->text().toStdString();
    c.party = party_input->text().toStdString();
    c.dob = dob_input->date().toString("dd/MM/yyyy").toStdString();
    c.gender = gender_input->currentText().toStdString();
    c.photo_path = photo_path.toStdString();
    c.party_symbol_path = party_symbol_path.toStdString();

    switch (a.is_valid_pass(pass_input->text().toStdString(), c.first)) {
    case is_valid:
        c.salt = admin.gen_salt();
        c.hash = admin.hash_pass(pass_input->text().toStdString(), c.salt);

        c.is_locked = false;
        c.attempts_left = 5;

        admin.add_candidate(c);

        msg->setStyleSheet("color: #10b981;");
        msg->setText("Registered Successfully");

        clear_fields();
        break;

    case letter:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Password must be at least 7 characters.");
        break;

    case number:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("At least 3 digits required.");
        break;

    case capital:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("At least 1 capital letter required.");
        break;

    case name:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("Password must not be same as your name");
        break;

    case special:
        msg->setStyleSheet("color: #ffcccc;");
        msg->setText("At least 1 special character required.");
        break;
    }
}

void CandidateRegisterWindow::clear_fields()
{
    f_name_input->clear();
    l_name_input->clear();
    nid_input->clear();
    party_input->clear();
    dob_input->setDate(QDate(2000, 1, 1));
    gender_input->setCurrentIndex(0);
    pass_input->clear();
    photo_path.clear();
    photo_preview->clear();
    photo_preview->setText("No Photo");
    party_symbol_path.clear();
    party_symbol_preview->clear();
    party_symbol_preview->setText("No Symbol");

    QCheckBox* terms = this->findChild<QCheckBox*>("terms_checkbox");
    if(terms) terms->setChecked(false);

    f_name_warn->hide();
    l_name_warn->hide();
    nid_warn->hide();
    dob_warn->hide();
    gender_warn->hide();
    pass_warn->hide();
    photo_warn->hide();
    party_warn->hide();
    party_symbol_warn->hide();
}

void CandidateRegisterWindow::clear_msg(){
    msg->clear();
}

void CandidateRegisterWindow::upload_photo()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Select Photo", "", "Images (*.*)");

    if (file_path.isEmpty())
        return;

    photo_path = file_path;

    QPixmap pixmap(file_path);
    photo_preview->setPixmap(pixmap);
    photo_preview->setText("");
}

void CandidateRegisterWindow::upload_party_symbol()
{
    QString file_path = QFileDialog::getOpenFileName(
        this,
        "Select Photo",
        "",
        "Images (*.*)"
        );

    if(file_path.isEmpty()) return;

    party_symbol_path = file_path;

    QPixmap pixmap(file_path);
    party_symbol_preview->setPixmap(pixmap);
    party_symbol_preview->setText("");
}