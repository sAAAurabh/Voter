#include "manifesto_edit_window.h"
#include "candidate_home.h"
#include "election_config.h"

#include <QFont>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>


CandidateHomeWindow::CandidateHomeWindow(const QString& nid, QWidget *parent)
    : QWidget(parent), candidate_nid(nid)
{
    setWindowTitle("Candidate Dashboard");
    //setFixedSize(700, 480);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color:#131a24;");

    title = new QLabel("Candidate Dashboard", this);

    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    title->setStyleSheet("color:#f5f6fa; background:transparent; font-family:'Segoe UI';");

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
    header_layout->addWidget(title, 1, Qt::AlignVCenter);
    header_layout->addWidget(logout_btn, 0, Qt::AlignVCenter);

    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(1);
    divider->setStyleSheet("background-color: rgba(255,255,255,30); border:none;");

    QFrame *profile_box = new QFrame(this);
    profile_box->setStyleSheet(
        "QFrame {"
        "background-color:#1a2532;"
        "border:1px solid #263344;"
        "border-radius:16px;"
        "}"
        );

    QGridLayout *profile_layout = new QGridLayout(profile_box);
    profile_layout->setContentsMargins(24, 22, 24, 22);
    profile_layout->setHorizontalSpacing(24);
    profile_layout->setVerticalSpacing(10);

    Candidate c;
    Admin a;
    a.find_candidate(nid.toStdString(), c);

    QString info_style =
        "font-size:14px; color:#a9b8cc; font-family:'Segoe UI'; background:transparent;";
    QString info_style_bold =
        "font-size:17px; font-weight:600; color:#ffffff; font-family:'Segoe UI'; background:transparent;";

    photo_label = new QLabel(this);
    photo_label->setAlignment(Qt::AlignCenter);
    photo_label->setFixedSize(120, 140);
    photo_label->setStyleSheet(
        "background:#22334a; border:1px solid #2f4258; border-radius:10px;"
        );

    QPixmap pix(QString::fromStdString(c.photo_path));
    photo_label->setPixmap(
        pix.scaled(photo_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    name_label = new QLabel(QString::fromStdString(c.first + " " + c.last));
    nid_label = new QLabel(QString::fromStdString("NID   :  " + c.nid));
    party_label = new QLabel(QString::fromStdString("Party  :  " + c.party));
    vote_label = new QLabel("Votes  :  " + QString::number(c.votes));

    name_label->setStyleSheet(info_style_bold);
    nid_label->setStyleSheet(info_style);
    party_label->setStyleSheet(info_style);
    vote_label->setStyleSheet(info_style + "color:#4fc3f7; font-weight:600;");

    profile_layout->addWidget(photo_label, 0, 0, 4, 1, Qt::AlignTop);
    profile_layout->addWidget(name_label,  0, 1);
    profile_layout->addWidget(nid_label,   1, 1);
    profile_layout->addWidget(party_label, 2, 1);
    profile_layout->addWidget(vote_label,  3, 1);

    edit_btn = new QPushButton("Edit Manifesto", this);
    edit_btn->setCursor(Qt::PointingHandCursor);
    edit_btn->setMinimumHeight(46);
    edit_btn->setStyleSheet(
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
        "QPushButton:pressed { background-color:#1c6c9c; }"
        );



    status_btn = new QPushButton("View Status/Result", this);
    status_btn->setCursor(Qt::PointingHandCursor);
    status_btn->setMinimumHeight(46);
    status_btn->setStyleSheet(
        "QPushButton {"
        "background-color:#008f66;"
        "color:#ffffff;"
        "padding:12px;"
        "border-radius:10px;"
        "font-weight:600;"
        "font-size:15px;"
        "font-family:'Segoe UI';"
        "border:none;"
        "}"
        "QPushButton:hover { background-color:#00a878; }"
        );


    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#4fc3f7; font-weight:bold; background:transparent; font-family:'Segoe UI';");

    grid = new QGridLayout(this);
    grid->setContentsMargins(40, 24, 40, 24);
    grid->setVerticalSpacing(20);

    grid->addLayout(header_layout, 0, 0, 1, 2);
    grid->addWidget(divider,       1, 0, 1, 2);
    grid->addWidget(profile_box,   2, 0, 1, 2);
    grid->addWidget(edit_btn,      3, 0, 1, 2);
    grid->addWidget(status_btn,    4, 0, 1, 2);
    grid->addWidget(msg,           5, 0, 1, 2);

    connect(edit_btn, &QPushButton::clicked, this, &CandidateHomeWindow::edit_manifesto);

    connect(logout_btn, &QPushButton::clicked, this, [this](){
        emit logout_requested();
    });

    connect(status_btn, &QPushButton::clicked, this, [this](){

        qDebug() << "Now:" << QDateTime::currentDateTime();
        qDebug() << "Start:" << ElectionConfig::votingStart();
        qDebug() << "End:" << ElectionConfig::votingEnd();
        qDebug() << "Open:" << ElectionConfig::isVotingOpen();

        if (ElectionConfig::isVotingOpen())
            emit status_requested(candidate_nid);
        else
            emit result_page_requested();
    });
}
void CandidateHomeWindow::edit_manifesto()
{
    ManifestoEditWindow *w = new ManifestoEditWindow(candidate_nid);
    w->show();
}


