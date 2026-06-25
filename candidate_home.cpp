#include "candidate_home.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QFrame>

CandidateHomeWindow::CandidateHomeWindow(const QString& nid, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Candidate Dashboard");
    //setFixedSize(600, 480);

    //title
    title = new QLabel("Candidate Dashboard", this);

    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    //divider
    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(1);
    divider->setStyleSheet("border:none; margin:0px 20px;");

    //profile box
    QFrame *profile_box = new QFrame(this);

    profile_box->setStyleSheet(
        "QFrame {"
        "border:1px solid #e0e0e0;"
        "border-radius:8px;"
        "padding:12px;"
        "}"
        );

    QGridLayout *profile_layout = new QGridLayout(profile_box);
    profile_layout->setContentsMargins(12, 12, 12, 12);
    profile_layout->setHorizontalSpacing(18);
    profile_layout->setVerticalSpacing(8);

    Candidate c;
    Admin a;
    a.find_candidate(nid.toStdString(), c);

    QString info_style = "font-size:13px";

    //photo
    photo_label = new QLabel(this);
    photo_label->setAlignment(Qt::AlignCenter);
    photo_label->setFixedSize(120, 140);
    photo_label->setStyleSheet("background: transparent; border: none;");

    QPixmap pix(QString::fromStdString(c.photo_path));

    photo_label->setPixmap(
        pix.scaled(photo_label->size(),
                   Qt::KeepAspectRatio,
                   Qt::SmoothTransformation)
        );

    //information about the candidates
    name_label  = new QLabel(QString::fromStdString("Name: " + c.first + " " + c.last));
    nid_label   = new QLabel(QString::fromStdString("NID: " + c.nid));
    party_label = new QLabel(QString::fromStdString("Party: " + c.party));
    vote_label = new QLabel("Votes: " + QString::number(c.votes));

    name_label->setStyleSheet(info_style);
    nid_label->setStyleSheet(info_style);
    party_label->setStyleSheet(info_style);
    vote_label->setStyleSheet(info_style);

    profile_layout->addWidget(photo_label, 0, 0, 4, 1, Qt::AlignTop);
    profile_layout->addWidget(name_label, 0, 1);
    profile_layout->addWidget(nid_label, 1, 1);
    profile_layout->addWidget(party_label, 2, 1);
    profile_layout->addWidget(vote_label, 3, 1);

    //buttons
    edit_btn = new QPushButton("Edit Manifesto", this);

    edit_btn->setStyleSheet(
        "padding:9px;"
        "border-radius:6px;"
        "font-weight:600;"
        "background:#3498db;"
        "color:white;"
        );

    edit_btn->setMinimumHeight(40);
    edit_btn->setCursor(Qt::PointingHandCursor);

    //message
    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#27ae60; font-weight:600; font-size:13px;");

    //layout
    grid = new QGridLayout(this);
    grid->setContentsMargins(25, 18, 25, 18);
    grid->setVerticalSpacing(10);

    grid->addWidget(title, 0, 0, 1, 2);
    grid->addWidget(divider, 1, 0, 1, 2);
    grid->addWidget(profile_box, 2, 0, 1, 2);
    grid->addWidget(edit_btn, 3, 0, 1, 2);
    grid->addWidget(msg, 4, 0, 1, 2);

    logout_btn = new QPushButton("Logout", this);

    logout_btn->setStyleSheet(
        "background:transparent;"
        "color:#e74c3c;"
        "border:none;"
        "font-size:11px;"
        "padding:2px;"
        );

    logout_btn->setCursor(Qt::PointingHandCursor);

    logout_btn->setGeometry(width() - 65, 6, 60, 20);


    //slots and signals
    connect(edit_btn, &QPushButton::clicked,
            this, &CandidateHomeWindow::edit_manifesto);

    connect(logout_btn, &QPushButton::clicked,
            this, &CandidateHomeWindow::logout);
}


void CandidateHomeWindow::edit_manifesto()
{
    msg->setStyleSheet("color:#2563EB;");
    msg->setText("Edit profile clicked");
}


void CandidateHomeWindow::logout()
{
    emit logout_requested();
}
