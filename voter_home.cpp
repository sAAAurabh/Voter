#include "voter_home.h"
#include "voter_login_window.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QFrame>

VoterHomeWindow::VoterHomeWindow(const QString& nid, QWidget *parent)
    : QWidget(parent), voter_nid(nid)
{
    setWindowTitle("Voter Dashboard");
    setFixedSize(600, 480);



    // tile
    title = new QLabel("Voter Dashboard", this);

    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    // divider
    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(1);
    divider->setStyleSheet("background-color:#dcdcdc; border:none;");

    // profile box
    QFrame *profile_box = new QFrame(this);

    profile_box->setStyleSheet(
        "QFrame {"
        "border:1px solid #e0e0e0;"
        "border-radius:6px;"
        "padding:10px;"
        "}"
        );

    QGridLayout *profile_layout = new QGridLayout(profile_box);
    profile_layout->setContentsMargins(15, 15, 15, 15);
    profile_layout->setHorizontalSpacing(20);
    profile_layout->setVerticalSpacing(10);

    Voter v;
    Admin a;
    a.find_voter(nid.toStdString(), v);

    QString info_style = "font-size:14px;";

    // photo
    photo_label = new QLabel(this);
    photo_label->setAlignment(Qt::AlignCenter);
    photo_label->setFixedSize(120, 140);
    photo_label->setStyleSheet("background: transparent; border: none;");

    QPixmap pix(QString::fromStdString(v.photo_path));

    photo_label->setPixmap(
        pix.scaled(photo_label->size(),
                   Qt::KeepAspectRatio,
                   Qt::SmoothTransformation)
        );


    name_label = new QLabel(
        QString::fromStdString("Name: " + v.first + " " + v.last)
        );
    nid_label = new QLabel(
        QString::fromStdString("NID: " + v.nid)
        );
    gender_label = new QLabel(
        QString::fromStdString("Gender: " + v.gender)
        );
    dob_label = new QLabel(
        QString::fromStdString("Date of Birth: " + v.dob)
        );

    name_label->setStyleSheet(info_style);
    nid_label->setStyleSheet(info_style);
    gender_label->setStyleSheet(info_style);
    dob_label->setStyleSheet(info_style);

    profile_layout->addWidget(photo_label, 0, 0, 4, 1, Qt::AlignTop);
    profile_layout->addWidget(name_label, 0, 1);
    profile_layout->addWidget(nid_label, 1, 1);
    profile_layout->addWidget(gender_label, 2, 1);
    profile_layout->addWidget(dob_label, 3, 1);

    //buttons
    view_candidates_btn = new QPushButton("View Candidates", this);
    view_candidates_btn->setCursor(Qt::PointingHandCursor);
    vote_candidates_btn = new QPushButton("Vote Candidates", this);
    vote_candidates_btn->setCursor(Qt::PointingHandCursor);
    logout_btn = new QPushButton("Logout", this);

    QString base =
        "padding:8px;"
        "border-radius:6px;"
        "font-weight:600;";

    view_candidates_btn->setStyleSheet(base + "background:#3498db; color:white;");
    vote_candidates_btn->setStyleSheet(base + "background:#2ecc71; color:white;");


    logout_btn->setStyleSheet(
        "background:transparent;"
        "color:#e74c3c;"
        "border:none;"
        "font-size:12px;"
        );
    logout_btn->setCursor(Qt::PointingHandCursor);

    view_candidates_btn->setMinimumHeight(38);
    vote_candidates_btn->setMinimumHeight(38);

    // message
    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#27ae60; font-weight:bold;");

    // layout
    grid = new QGridLayout(this);
    grid->setContentsMargins(30, 20, 30, 20);
    grid->setVerticalSpacing(12);

    grid->addWidget(title, 0, 0, 1, 2);
    grid->addWidget(divider, 1, 0, 1, 2);
    grid->addWidget(profile_box, 2, 0, 1, 2);

    grid->addWidget(view_candidates_btn, 3, 0);
    grid->addWidget(vote_candidates_btn, 3, 1);

    grid->addWidget(msg, 4, 0, 1, 2);

    //lagout button
    logout_btn->setParent(this);
    logout_btn->setGeometry(width() - 70, 5, 60, 25);

    connect(logout_btn, &QPushButton::clicked, this, &VoterHomeWindow::logout);

    connect(vote_candidates_btn, &QPushButton::clicked, this, &VoterHomeWindow::vote);
}


void VoterHomeWindow::logout()
{
    this->close();
}

void VoterHomeWindow::vote(){

    this->hide();
    VotingPage *w = new VotingPage(voter_nid);
    w->show();

}


