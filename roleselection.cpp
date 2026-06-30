#include "roleselection.h"
#include "voter_login_window.h"
#include "candidate_login_window.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

RoleSelection::RoleSelection(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("E-Voting System");
    //setFixedSize(400, 300);

    titleLabel = new QLabel("Welcome to E-Voting System", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    subLabel = new QLabel("Please select your role to continue", this);
    subLabel->setAlignment(Qt::AlignCenter);
    subLabel->setStyleSheet("font-size: 13px; color: gray;");

    voterBtn = new QPushButton("Voter", this);
    voterBtn->setFixedSize(150, 80);
    voterBtn->setStyleSheet("font-size: 16px;");

    candidateBtn = new QPushButton("Candidate", this);
    candidateBtn->setFixedSize(150, 80);
    candidateBtn->setStyleSheet("font-size: 16px;");

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(voterBtn);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(candidateBtn);
    btnLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(subLabel);
    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(voterBtn,     &QPushButton::clicked, this, [this](){emit is_voter();});
    connect(candidateBtn, &QPushButton::clicked, this, [this](){emit is_candidate();});
}

RoleSelection::~RoleSelection() {}