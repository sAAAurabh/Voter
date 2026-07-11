#include "status_page.h"
#include "election_config.h"
#include "admin.h"
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFont>

CandidateStatusWindow::CandidateStatusWindow(const QString &nid, QWidget *parent)
    : QWidget(parent), candidate_nid(nid)
{
    Candidate c;
    Admin a;
    a.find_candidate(nid.toStdString(), c);

    int vote_total = a.total_votes();
    int voter_total = a.total_voters();
    double vote_share = ((double)c.votes/vote_total)*100;

    setWindowTitle("Election Status");
    resize(650,500);

    setAttribute(Qt::WA_StyledBackground,true);

    setStyleSheet(
        "background:#131a24;"
        );

    title = new QLabel("Election Status");

    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "color:white;"
        "background:transparent;"
        );

    //
    // YOUR STATUS
    //

    QGroupBox *statusBox = new QGroupBox("Your Current Status");

    statusBox->setStyleSheet(
        "QGroupBox{"
        "color:white;"
        "font-size:15px;"
        "font-weight:bold;"
        "border:1px solid #2d3d52;"
        "border-radius:10px;"
        "margin-top:12px;"
        "padding-top:10px;"
        "background:#1a2532;"
        "}"

        "QGroupBox::title{"
        "subcontrol-origin:margin;"
        "left:12px;"
        "padding:0 5px;"
        "}"
        );

    votes_label = new QLabel("Votes Received : " + QString::number(c.votes));
    position_label = new QLabel("Current Position : " + QString::number(a.calculate_position(c.nid)) + "/" + QString::number(a.total_candidates()));
    share_label = new QLabel("Vote Share : " + QString::number(vote_share, 'f', 2) + "%");

    QString infoStyle =
        "color:#d8dee9;"
        "font-size:14px;"
        "background:transparent;";

    votes_label->setStyleSheet(infoStyle);
    position_label->setStyleSheet(infoStyle);
    share_label->setStyleSheet(infoStyle);

    share_bar = new QProgressBar;
    share_bar->setRange(0,100);
    share_bar->setValue(vote_share);

    share_bar->setStyleSheet(
        "QProgressBar{"
        "border:none;"
        "background:#243243;"
        "height:18px;"
        "border-radius:9px;"
        "text-align:center;"
        "color:white;"
        "}"

        "QProgressBar::chunk{"
        "background:#008f66;"
        "border-radius:9px;"
        "}"
        );

    QVBoxLayout *statusLayout = new QVBoxLayout(statusBox);

    statusLayout->addWidget(votes_label);
    statusLayout->addWidget(position_label);
    statusLayout->addWidget(share_label);
    statusLayout->addWidget(share_bar);



    QGroupBox *electionBox = new QGroupBox("Election Information");

    electionBox->setStyleSheet(statusBox->styleSheet());

    total_votes_label = new QLabel("Total Votes Cast : " + QString::number(vote_total));
    total_candidates_label = new QLabel("Total Registered Voters : " + QString::number(voter_total));
    status_label = new QLabel("Number of Voters Yet to Vote : " + QString::number(voter_total-vote_total));

    QDateTime now = QDateTime::currentDateTime();
    QDateTime end = ElectionConfig::votingEnd();
    qint64 seconds = now.secsTo(end);
    int days = seconds / 86400;
    int hours = (seconds % 86400) / 3600;
    time_label = new QLabel(
        "Time Remaining : "
        + QString::number(days) + " Days "
        + QString::number(hours) + " Hours"
        );

    total_votes_label->setStyleSheet(infoStyle);
    total_candidates_label->setStyleSheet(infoStyle);
    status_label->setStyleSheet(infoStyle);
    time_label->setStyleSheet(infoStyle);

    QVBoxLayout *electionLayout = new QVBoxLayout(electionBox);

    electionLayout->addWidget(total_votes_label);
    electionLayout->addWidget(total_candidates_label);
    electionLayout->addWidget(status_label);
    electionLayout->addWidget(time_label);



    back_btn = new QPushButton("Back");

    back_btn->setMinimumHeight(42);

    back_btn->setStyleSheet(
        "QPushButton{"
        "background:#2f9bda;"
        "color:white;"
        "font-size:14px;"
        "font-weight:600;"
        "border:none;"
        "border-radius:8px;"
        "padding:8px;"
        "}"

        "QPushButton:hover{"
        "background:#2785bc;"
        "}"
        );

    connect(back_btn, &QPushButton::clicked, this, [this]() {
        emit back_requested();
    });



    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(35,25,35,25);
    mainLayout->setSpacing(20);

    mainLayout->addWidget(title);
    mainLayout->addWidget(statusBox);
    mainLayout->addWidget(electionBox);
    mainLayout->addStretch();
    mainLayout->addWidget(back_btn);
}