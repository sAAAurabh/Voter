#include "voter_home.h"
#include "voter_login_window.h"
#include "main_window.h"
#include "voting_page.h"
#include "view_candidates_window.h"

#include <QFont>
#include <QFrame>
#include <QPixmap>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


VoterHomeWindow::VoterHomeWindow(const QString &nid, QWidget *parent)
    : QWidget(parent)
    , voter_nid(nid)
{
    setWindowTitle("Voter Dashboard");
    //setFixedSize(720, 630);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(
        "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #0f0c29, stop:0.5 #1a1a2e, stop:1 #24243e);"
        );

    title = new QLabel("Voter Dashboard", this);

    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:#f5f6fa; background:transparent; font-family:'Segoe UI';");

    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(1);
    divider->setStyleSheet("background-color: rgba(255,255,255,60); border:none;");

    QFrame *profile_box = new QFrame(this);
    profile_box->setMinimumHeight(320);
    profile_box->setMinimumWidth(600);
    profile_box->setStyleSheet(
        "QFrame {"
        "background-color: white;"
        "border: none;"
        "border-radius: 16px;"
        "}"
        );

    QVBoxLayout *card_layout = new QVBoxLayout(profile_box);
    card_layout->setContentsMargins(0, 0, 0, 0);
    card_layout->setSpacing(0);

    QFrame *content_area = new QFrame(profile_box);
    content_area->setStyleSheet("background: transparent; border: none;");

    QGridLayout *profile_layout = new QGridLayout(content_area);
    profile_layout->setContentsMargins(36, 34, 36, 34);
    profile_layout->setHorizontalSpacing(32);
    profile_layout->setVerticalSpacing(18);

    card_layout->addWidget(content_area);

    Voter v;
    Admin a;
    a.find_voter(voter_nid.toStdString(), v);

    QString info_style =
        "font-size:15px; color:#2f3640; font-family:'Segoe UI';"
        "background-color:#dcdde1; border-radius:8px; padding:10px 16px;";
    QString info_style_bold =
        "font-size:16px; font-weight:600; color:#2f3640; font-family:'Segoe UI';"
        "background-color:#ced6e0; border-radius:8px; padding:10px 16px;";

    photo_label = new QLabel(content_area);
    photo_label->setAlignment(Qt::AlignCenter);
    photo_label->setFixedSize(140, 160);
    photo_label->setStyleSheet(
        "background:#f1f2f6; border:2px dashed #dcdde1; border-radius:10px;"
        );

    QPixmap pix(QString::fromStdString(v.photo_path));
    photo_label->setPixmap(
        pix.scaled(photo_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    name_label = new QLabel(
        QString::fromStdString("NAME       :  " + v.first + " " + v.last), content_area
        );
    nid_label = new QLabel(
        QString::fromStdString("NID           :  " + v.nid), content_area
        );
    gender_label = new QLabel(
        QString::fromStdString("GENDER     :  " + v.gender), content_area
        );
    dob_label = new QLabel(
        QString::fromStdString("AGE           :  " + a.calculate_age(v.dob)), content_area
        );
    name_label->setStyleSheet(info_style_bold);
    nid_label->setStyleSheet(info_style);
    gender_label->setStyleSheet(info_style);
    dob_label->setStyleSheet(info_style);

    profile_layout->addWidget(photo_label, 0, 0, 4, 1, Qt::AlignTop);
    profile_layout->addWidget(name_label,   0, 1);
    profile_layout->addWidget(nid_label,    1, 1);
    profile_layout->addWidget(gender_label, 2, 1);
    profile_layout->addWidget(dob_label,    3, 1);

    view_candidates_btn = new QPushButton("View Candidates", this);
    view_candidates_btn->setCursor(Qt::PointingHandCursor);

    vote_candidates_btn = new QPushButton("Vote Candidates", this);
    vote_candidates_btn->setCursor(Qt::PointingHandCursor);

    logout_btn = new QPushButton("Logout", this);

    view_candidates_btn->setStyleSheet(
        "QPushButton {"
        "background-color:#4facfe;"
        "color:white;"
        "padding:12px;"
        "border-radius:10px;"
        "font-weight:600;"
        "font-size:15px;"
        "font-family:'Segoe UI';"
        "border:none;"
        "}"
        "QPushButton:hover { background-color:#0084ff; }"
        "QPushButton:pressed { background-color:#0066cc; }"
        );

    vote_candidates_btn->setStyleSheet(
        "QPushButton {"
        "background-color:#00c896;"
        "color:white;"
        "padding:12px;"
        "border-radius:10px;"
        "font-weight:600;"
        "font-size:15px;"
        "font-family:'Segoe UI';"
        "border:none;"
        "}"
        "QPushButton:hover { background-color:#00a878; }"
        "QPushButton:pressed { background-color:#008f66; }"
        );

    logout_btn->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(255,255,255,25);"
        "color:#ff6b6b;"
        "border: 1px solid rgba(255,107,107,120);"
        "border-radius:12px;"
        "font-size:12px;"
        "font-weight:600;"
        "font-family:'Segoe UI';"
        "}"
        "QPushButton:hover { background-color: rgba(255,107,107,40); }"
        );
    logout_btn->setCursor(Qt::PointingHandCursor);

    view_candidates_btn->setMinimumHeight(46);
    vote_candidates_btn->setMinimumHeight(46);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#00e396; font-weight:bold; background:transparent; font-family:'Segoe UI';");

    grid = new QGridLayout(this);
    grid->setContentsMargins(40, 28, 40, 24);
    grid->setVerticalSpacing(20);
    grid->setHorizontalSpacing(20);

    grid->addWidget(title,              0, 0, 1, 2);
    grid->addWidget(divider,            1, 0, 1, 2);
    grid->addWidget(profile_box,        2, 0, 1, 2);
    grid->addWidget(view_candidates_btn,3, 0);
    grid->addWidget(vote_candidates_btn,3, 1);
    grid->addWidget(msg,                4, 0, 1, 2);

    logout_btn->setParent(this);
    logout_btn->setFixedSize(70, 28);
    logout_btn->move(width() - 90, 12);

    connect(logout_btn, &QPushButton::clicked, this, [this](){emit logout_requested();});
    connect(vote_candidates_btn, &QPushButton::clicked, this, [this](){emit vote_page_requested(voter_nid);});
    connect(view_candidates_btn, &QPushButton::clicked, this, [this](){emit candidate_view_requested();});
}