#include "voter_home.h"
#include "voter_login_window.h"
#include "main_window.h"
#include "voting_page.h"
#include "view_candidates_window.h"
#include "election_config.h"

#include <QFont>
#include <QFrame>
#include <QPixmap>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>
#include <QMessageBox>


VoterHomeWindow::VoterHomeWindow(const QString &nid, QWidget *parent)
    : QWidget(parent)
    , voter_nid(nid)
{
    setWindowTitle("Voter Dashboard");

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color:#1b1f27;");

    title = new QLabel("Voter Dashboard", this);

    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    title->setStyleSheet("color:#f5f6fa; background:transparent; font-family:'Segoe UI';");

    QLabel *vote_icon = new QLabel(this);
    vote_icon->setFixedSize(38, 38);
    vote_icon->setAlignment(Qt::AlignCenter);
    vote_icon->setStyleSheet("background:transparent;");
    QPixmap icon_pix("C:/Users/Saurav/Desktop/vottter/icons/evote.png");
    vote_icon->setPixmap(
        icon_pix.scaled(38, 38, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    logout_btn = new QPushButton("Logout", this);
    logout_btn->setCursor(Qt::PointingHandCursor);
    logout_btn->setFixedSize(90, 38);
    logout_btn->setStyleSheet(
        "QPushButton {"
        "background-color:#e74c3c;"
        "color:#ffffff;"
        "border: none;"
        "border-radius:8px;"
        "font-size:13px;"
        "font-weight:600;"
        "font-family:'Segoe UI';"
        "}"
        "QPushButton:hover { background-color:#d43a2c; }"
        "QPushButton:pressed { background-color:#b8321f; }"
        );

    QHBoxLayout *header_layout = new QHBoxLayout;
    header_layout->setSpacing(14);
    header_layout->addWidget(vote_icon, 0, Qt::AlignVCenter);
    header_layout->addWidget(title, 1, Qt::AlignVCenter);
    header_layout->addWidget(logout_btn, 0, Qt::AlignVCenter);

    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(1);
    divider->setStyleSheet("background-color: rgba(255,255,255,30); border:none;");

    QFrame *profile_box = new QFrame(this);
    profile_box->setMinimumHeight(320);
    profile_box->setMinimumWidth(600);
    profile_box->setStyleSheet(
        "QFrame {"
        "background-color: #232833;"
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
    profile_layout->setVerticalSpacing(14);

    card_layout->addWidget(content_area);

    Voter v;
    Admin a;
    a.find_voter(voter_nid.toStdString(), v);

    QString info_style =
        "font-size:15px; color:#c8ccd6; font-family:'Segoe UI'; background:transparent;";
    QString info_style_bold =
        "font-size:18px; font-weight:600; color:#ffffff; font-family:'Segoe UI'; background:transparent;";

    photo_label = new QLabel(content_area);
    photo_label->setAlignment(Qt::AlignCenter);
    photo_label->setFixedSize(140, 160);
    photo_label->setStyleSheet(
        "background:#2c313d; border:1px solid #3a3f4b; border-radius:10px;"
        );

    QPixmap pix(QString::fromStdString(v.photo_path));
    photo_label->setPixmap(
        pix.scaled(photo_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    name_label = new QLabel(
        QString::fromStdString(v.first + " " + v.last), content_area
        );
    nid_label = new QLabel(
        QString::fromStdString("NID   :  " + v.nid), content_area
        );
    gender_label = new QLabel(
        QString::fromStdString("Gender  :  " + v.gender), content_area
        );
    dob_label = new QLabel(
        QString::fromStdString("Age   :  " + a.calculate_age(v.dob)), content_area
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

    vote_candidates_btn = new QPushButton(
        v.has_voted ? "Already Voted" : "Vote Candidates", this
        );
    vote_candidates_btn->setCursor(
        v.has_voted ? Qt::ForbiddenCursor : Qt::PointingHandCursor
        );
    vote_candidates_btn->setEnabled(!v.has_voted);

    QString primary_btn_style =
        "QPushButton {"
        "background-color:#10b981;"
        "color:white;"
        "padding:12px;"
        "border-radius:10px;"
        "font-weight:600;"
        "font-size:15px;"
        "font-family:'Segoe UI';"
        "border:none;"
        "}"
        "QPushButton:hover { background-color:#0ea271; }"
        "QPushButton:pressed { background-color:#0c8a5f; }"
        "QPushButton:disabled { background-color:#2c313d; color:#6b7280; }";

    vote_candidates_btn->setStyleSheet(primary_btn_style);

    QString secondary_btn_style =
        "QPushButton {"
        "background-color:#2f9bda;"
        "color:#ffffff;"
        "padding:12px;"
        "border-radius:10px;"
        "font-weight:600;"
        "font-size:15px;"
        "font-family:'Segoe UI';"
        "border:none;"
        "}"
        "QPushButton:hover { background-color:#2585bd; }"
        "QPushButton:pressed { background-color:#1c6c9c; }";

    view_candidates_btn->setStyleSheet(secondary_btn_style);

    view_candidates_btn->setMinimumHeight(46);
    vote_candidates_btn->setMinimumHeight(46);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#4f9dff; font-weight:bold; background:transparent; font-family:'Segoe UI';");

    grid = new QGridLayout(this);
    grid->setContentsMargins(40, 24, 40, 24);
    grid->setVerticalSpacing(20);
    grid->setHorizontalSpacing(20);

    grid->addLayout(header_layout,       0, 0, 1, 2);
    grid->addWidget(divider,             1, 0, 1, 2);
    grid->addWidget(profile_box,         2, 0, 1, 2);
    grid->addWidget(view_candidates_btn, 3, 0);
    grid->addWidget(vote_candidates_btn, 3, 1);
    grid->addWidget(msg,                 4, 0, 1, 2);

    connect(logout_btn, &QPushButton::clicked, this, [this](){emit logout_requested();});
    connect(vote_candidates_btn, &QPushButton::clicked, this, [this](){

        if (!ElectionConfig::isVotingOpen()) {
            qDebug() << "Voting Start:"
                     << ElectionConfig::votingStart();

            qDebug() << "Voting End:"
                     << ElectionConfig::votingEnd();

            qDebug() << "Voting Open:"
                     << ElectionConfig::isVotingOpen();

            QMessageBox::warning(this, "Voting Closed",
                                 QString("Voting is only open from %1 to %2.")
                                     .arg(ElectionConfig::votingStart().toString("MMM d, yyyy"))
                                     .arg(ElectionConfig::votingEnd().toString("MMM d, yyyy")));
            return;
        }
        emit vote_page_requested(voter_nid);
    });
    connect(view_candidates_btn, &QPushButton::clicked, this, [this](){emit candidate_view_requested();});
}

void VoterHomeWindow::refreshVoteStatus()
{
    Admin a;
    Voter v;
    a.find_voter(voter_nid.toStdString(), v);
    vote_candidates_btn->setText(v.has_voted ? "Already Voted" : "Vote Candidates");
    vote_candidates_btn->setEnabled(!v.has_voted);
    vote_candidates_btn->setCursor(v.has_voted ? Qt::ForbiddenCursor : Qt::PointingHandCursor);
}