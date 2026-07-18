#include "candidate_register_window.h"
#include <QCalendarWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include "admin.h"


CandidateRegisterWindow::CandidateRegisterWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Candidate Registration");
    setObjectName("CandidateRegisterWindow");

    setStyleSheet(
        "QLineEdit, QDateEdit, QComboBox {"
        "   color: #ffffff;"
        "   border: 1px solid #555555;"
        "   border-radius: 5px;"
        "   padding: 6px;"
        "}"
        );

    setMinimumSize(560, 760);
    resize(600, 820);


    //title
    title = new QLabel("Candidate Registration", this);

    QFont title_font;
    title_font.setPointSize(24);
    title_font.setBold(true);

    title->setFont(title_font);
    title->setAlignment(Qt::AlignCenter);

    QLabel *candi_logo = new QLabel(this);
    QPixmap candi_pix(":/icons/icons/candi.png");
    candi_logo->setPixmap(candi_pix.scaled(92, 88, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    candi_logo->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    candi_logo->setContentsMargins(0, 0, 0, 10);

    QHBoxLayout *title_row = new QHBoxLayout();
    title_row->setAlignment(Qt::AlignCenter);
    title_row->setSpacing(20);
    title_row->addStretch(5);
    title_row->addWidget(title);
    title_row->addSpacing(20);
    title_row->addWidget(candi_logo);
    title_row->addStretch(2);

    //names
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

    //nid
    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);
    nid_warn = new QLabel("●", this);
    nid_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    nid_warn->setVisible(false);
    nid_warn->setFixedWidth(18);
    nid_input->setPlaceholderText("Enter National ID");

    //date of birth
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

    //party
    party_label = new QLabel("Party", this);
    party_input = new QLineEdit(this);
    party_warn = new QLabel("●", this);
    party_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    party_warn->setVisible(false);
    party_warn->setFixedWidth(18);
    party_input->setPlaceholderText("Enter Your Party");

    //gender
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

    //photo
    photo_label = new QLabel("Photo", this);

    photo_btn = new QPushButton("Upload Photo", this);
    photo_btn->setCursor(Qt::PointingHandCursor);
    photo_btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
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
    photo_preview->setStyleSheet("border: 2px dashed #888888; border-radius: 6px;");
    photo_preview->setAlignment(Qt::AlignCenter);
    photo_preview->setText("No Photo");
    photo_preview->setScaledContents(true);

    //party_symbol
    party_symbol_label = new QLabel("Party Symbol", this);

    party_symbol_btn = new QPushButton("Upload Symbol", this);
    party_symbol_btn->setCursor(Qt::PointingHandCursor);
    party_symbol_btn->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498db;"
        "   padding: 8px;"
        "   border: none;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        );

    party_symbol_warn = new QLabel("●", this);
    party_symbol_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    party_symbol_warn->setVisible(false);
    party_symbol_warn->setFixedWidth(18);

    party_symbol_preview = new QLabel(this);
    party_symbol_preview->setFixedSize(64, 64);
    party_symbol_preview->setStyleSheet("border: 2px dashed #888888; border-radius: 6px;");
    party_symbol_preview->setAlignment(Qt::AlignCenter);
    party_symbol_preview->setText("No Symbol");
    party_symbol_preview->setScaledContents(true);


    //upload widget
    uploadWidget = new QWidget(this);

    uploadGrid = new QGridLayout(uploadWidget);
    uploadGrid->setHorizontalSpacing(35);
    uploadGrid->setVerticalSpacing(8);
    uploadGrid->setContentsMargins(0,0,0,0);

    uploadGrid->addWidget(photo_label, 0, 0);
    uploadGrid->addWidget(party_symbol_label, 0, 1);

    uploadGrid->addWidget(photo_btn, 1, 0);
    uploadGrid->addWidget(party_symbol_btn, 1, 1);

    uploadGrid->addWidget(photo_preview, 2, 0, Qt::AlignCenter);
    uploadGrid->addWidget(party_symbol_preview, 2, 1, Qt::AlignCenter);

    //pass
    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_warn = new QLabel("●", this);
    pass_warn->setStyleSheet("color:red; font-size:18px; background: transparent;");
    pass_warn->setVisible(false);
    pass_warn->setFixedWidth(18);

    pass_input->setPlaceholderText("Enter Password");
    pass_input->setEchoMode(QLineEdit::Password);


    declare_checkbox = new QCheckBox(
        "I hereby declare that all the information provided are factual and correct.",
        this
        );
    declare_checkbox->setStyleSheet("color:#cccccc; font-size:12px;");
    declare_checkbox->setCursor(Qt::PointingHandCursor);

    declare_warn = new QLabel("Please confirm the declaration before registering.", this);
    declare_warn->setStyleSheet("color:red; font-size:12px; background: transparent;");
    declare_warn->setVisible(false);

    //registration button
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


    // grid layout
    grid = new QGridLayout(this);
    grid->setContentsMargins(50, 30, 50, 30);
    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(10);
    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);
    grid->setColumnStretch(2, 0);
    grid->setColumnMinimumWidth(0, 110);

    int row = 0;
    grid->addLayout(title_row, row, 0, 1, 3);
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

    grid->addWidget(party_label, row, 0);
    grid->addWidget(party_input, row, 1);
    grid->addWidget(party_warn, row, 2);
    row++;

    grid->addWidget(pass_label, row, 0);
    grid->addWidget(pass_input, row, 1);
    grid->addWidget(pass_warn, row, 2);
    row++;

    grid->addWidget(uploadWidget, row, 0, 1, 3);
    row++;

    grid->addWidget(declare_checkbox, row, 0, 1, 3);
    row++;

    grid->addWidget(declare_warn, row, 0, 1, 3);
    row++;

    grid->addWidget(msg, row, 0, 1, 3);
    row++;

    grid->addWidget(reg_btn, row, 0, 1, 3);
    row++;

    grid->addWidget(back_btn, row, 0, 1, 1, Qt::AlignLeft);
    row++;

    //signals and slots
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
    bool declare_unchecked = !declare_checkbox->isChecked();

    f_name_warn->setVisible(f_empty);
    l_name_warn->setVisible(l_empty);
    party_warn->setVisible(pty_empty);
    nid_warn->setVisible(n_empty);
    dob_warn->setVisible(dob_default);
    gender_warn->setVisible(gender_empty);
    pass_warn->setVisible(p_empty);
    photo_warn->setVisible(photo_empty);
    party_symbol_warn->setVisible(party_symbol_empty);
    declare_warn->setVisible(declare_unchecked);


    if(f_empty || l_empty || n_empty || dob_default || gender_empty || photo_empty || party_symbol_empty|| p_empty || declare_unchecked) return;

    switch(a.is_valid_nid_candidate(nid_input->text().toStdString())){
    case is_valid_nid:
        c.nid = nid_input->text().toStdString();
        break;
    case length:
        msg->setStyleSheet("color: red;");
        msg->setText("NID must be 8 characters long!!");
        return;
    case not_unique:
        msg->setStyleSheet("color: red;");
        msg->setText("Candidate already registetered!!");
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

        msg->setStyleSheet("color: green;");
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
    party_symbol_preview->setText("No Photo");
    declare_checkbox->setChecked(false);


    f_name_warn->hide();
    l_name_warn->hide();
    nid_warn->hide();
    dob_warn->hide();
    gender_warn->hide();
    pass_warn->hide();
    photo_warn->hide();
    party_warn->hide();
    party_symbol_warn->hide();
    declare_warn->hide();
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