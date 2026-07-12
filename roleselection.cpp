#include "roleselection.h"
#include "voter_login_window.h"
#include "candidate_login_window.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPixmap>

RoleSelection::RoleSelection(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(" E-Voting System Portal");
    //setFixedSize(720, 630);

    titleLabel = new QLabel("Welcome to the Electronic Voting Portal.", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 36px; font-weight: 600; font-family:Arial;");

    subLabel = new QLabel("Please select your role to proceed.", this);
    subLabel->setAlignment(Qt::AlignCenter);
    subLabel->setStyleSheet("font-size: 20px; font-family: Arial;");

    QFrame *voterCard = new QFrame(this);
    voterCard->setFixedSize(270, 320);
    voterCard->setStyleSheet(
        "QFrame { "
        "   background-color: #0B1849; "
        "}"
        );

    QLabel *voterIcon = new QLabel(voterCard);
    voterIcon->setAlignment(Qt::AlignCenter);
    voterIcon->setPixmap(QPixmap("C:/Users/Saurav/Desktop/vottter/icons/vot.png").scaled(180, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation));


    QLabel *voterTitle = new QLabel("I AM A VOTER");
    voterTitle->setAlignment(Qt::AlignCenter);
    voterTitle->setStyleSheet("font-size: 24px; font-weight: bold;");

    QLabel *voterDesc = new QLabel(
        "Register, view candidates, and cast your vote"
    );
    voterDesc->setAlignment(Qt::AlignCenter);
    voterDesc->setStyleSheet("font-size: 17px; color: white; font-family: 'Calibri';");

    voterBtn = new QPushButton("Proceed as Voter");
    voterBtn->setFixedHeight(36);
    voterBtn->setStyleSheet(
        "QPushButton { background-color: #0084ff; color: white; font-weight: 600; font-size: 17px; border-radius: 8px; border: none; font-family: 'Calibri';}"
        "QPushButton:hover { background-color: #0070d2; }"
        );

    QVBoxLayout *voterCardLayout = new QVBoxLayout(voterCard);
    voterCardLayout->setContentsMargins(16, 20, 16, 16);
    voterCardLayout->setSpacing(12);
    voterCardLayout->addWidget(voterIcon);
    voterCardLayout->addWidget(voterTitle);
    voterCardLayout->addWidget(voterDesc);
    voterCardLayout->addStretch();
    voterCardLayout->addWidget(voterBtn);


    QFrame *candidateCard = new QFrame(this);
    candidateCard->setFixedSize(270, 320);
    candidateCard->setStyleSheet(
        "QFrame { "
        "   background-color: #458393; "
        "}"
        );

    QLabel *candidateIcon = new QLabel(candidateCard);
    candidateIcon->setAlignment(Qt::AlignCenter);
    candidateIcon->setPixmap(QPixmap("C:/Users/Saurav/Desktop/vottter/icons/can.png").scaled(180, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel *candidateTitle = new QLabel("I AM A CANDIDATE");
    candidateTitle->setAlignment(Qt::AlignCenter);
    candidateTitle->setStyleSheet("font-size: 24px; font-weight: bold;");

    QLabel *candidateDesc = new QLabel(
        "Register candidacy, manage profile, and view results"
        );
    candidateDesc->setAlignment(Qt::AlignCenter);
    candidateDesc->setStyleSheet("font-size: 17px; font-family: 'Calibri';");

    candidateBtn = new QPushButton("Proceed as Candidate");
    candidateBtn->setFixedHeight(36);
    candidateBtn->setStyleSheet(
        "QPushButton { background-color: #00a878; color: white; font-weight: 600; font-size: 17px; border-radius: 8px; border: none; }"
        "QPushButton:hover { background-color: #008f66; }"
        );

    QVBoxLayout *candidateCardLayout = new QVBoxLayout(candidateCard);
    candidateCardLayout->setContentsMargins(16, 20, 16, 16);
    candidateCardLayout->setSpacing(12);
    candidateCardLayout->addWidget(candidateIcon);
    candidateCardLayout->addWidget(candidateTitle);
    candidateCardLayout->addWidget(candidateDesc);
    candidateCardLayout->addStretch();
    candidateCardLayout->addWidget(candidateBtn);

    QHBoxLayout *cardContainerLayout = new QHBoxLayout();
    cardContainerLayout->addStretch();
    cardContainerLayout->addWidget(voterCard);
    cardContainerLayout->addSpacing(24);
    cardContainerLayout->addWidget(candidateCard);
    cardContainerLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 24, 0, 10);
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(4);
    mainLayout->addWidget(subLabel);
    mainLayout->addSpacing(24);
    mainLayout->addLayout(cardContainerLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(voterBtn, &QPushButton::clicked, this, [this](){ emit is_voter(); });
    connect(candidateBtn, &QPushButton::clicked, this, [this](){ emit is_candidate(); });
}

RoleSelection::~RoleSelection() {}