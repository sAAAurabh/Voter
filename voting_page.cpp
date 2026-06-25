#include "voting_page.h"
#include "database.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QSqlQuery>
#include <QScrollArea>
#include <QFont>
#include <QDebug>

VotingPage::VotingPage(const QString& voter_nid, QWidget *parent)
    : QWidget(parent), current_voter_nid(voter_nid)
{
    //setFixedSize(700, 500);
    setWindowTitle("Voting Page");


    this->setStyleSheet("background:#1b1b1b; color:white;");

    QVBoxLayout *root_layout = new QVBoxLayout(this);
    root_layout->setContentsMargins(20, 20, 20, 20);
    root_layout->setSpacing(18);

    //title
    QLabel *title = new QLabel("Cast Your Vote");
    title->setAlignment(Qt::AlignCenter);

    QFont f;
    f.setPointSize(17);
    f.setWeight(QFont::Medium);
    title->setFont(f);

    title->setStyleSheet("color:#eaeaea;");
    root_layout->addWidget(title);

    //scrolling
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("background:transparent;");
    scroll->viewport()->setStyleSheet("background:transparent;");

    QWidget *container = new QWidget;
    container->setStyleSheet("background:transparent;");

    main_layout = new QVBoxLayout(container);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(14);

    scroll->setWidget(container);
    root_layout->addWidget(scroll);

    load_candidates();
}


void VotingPage::load_candidates()
{
    QSqlQuery q(Database::db);

    if(!q.exec("SELECT nid, first, last, dob, party, photo_path FROM candidates"))
    {
        qDebug() << "Query failed:" << q.lastError().text();
        return;
    }

    while(q.next())
    {
        QString nid = q.value(0).toString();
        QString name = q.value(1).toString() + " " + q.value(2).toString();
        QString dob = q.value(3).toString();
        QString party = q.value(4).toString();
        QString photo_path = q.value(5).toString();

        //candidates card
        QWidget *card = new QWidget;
        card->setMinimumHeight(135);

        card->setStyleSheet(
            "QWidget {"
            "background:#232323;"
            "border:1px solid #2f2f2f;"
            "border-radius:14px;"
            "}"
            "QWidget:hover {"
            "border:1px solid #2ecc71;"
            "}"
            );

        QHBoxLayout *layout = new QHBoxLayout(card);
        layout->setContentsMargins(18, 14, 18, 14);
        layout->setSpacing(18);

        //photo
        QLabel *photo = new QLabel;
        photo->setFixedSize(88, 88);
        photo->setStyleSheet("border:1px solid #444; border-radius:10px;");

        QPixmap pix(photo_path);
        photo->setPixmap(
            pix.scaled(photo->size(),
                       Qt::KeepAspectRatioByExpanding,
                       Qt::SmoothTransformation)
            );

        // text
        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(6);

        QLabel *name_label = new QLabel(name);
        name_label->setStyleSheet(
            "font-size:16px;"
            "font-weight:600;"
            "color:#eaeaea;"
            );

        QLabel *age_label = new QLabel("Age: " + dob);
        age_label->setStyleSheet("font-size:13px; color:#aaaaaa;");

        QLabel *party_label = new QLabel("Party: " + party);
        party_label->setStyleSheet("font-size:13px; color:#aaaaaa;");

        textLayout->addWidget(name_label);
        textLayout->addWidget(age_label);
        textLayout->addWidget(party_label);

        //button
        QPushButton *vote_btn = new QPushButton("Vote");
        vote_btn->setFixedSize(85, 34);

        vote_btn->setStyleSheet(
            "QPushButton {"
            "border:1px solid #2ecc71;"
            "color:#2ecc71;"
            "background:transparent;"
            "border-radius:8px;"
            "font-weight:500;"
            "}"
            "QPushButton:hover {"
            "background:rgba(46,204,113,0.15);"
            "}"
            );

        connect(vote_btn, &QPushButton::clicked, this, [=]()
                {
                    QSqlQuery check_voter(Database::db);
                    check_voter.prepare("Select has_voted from voters WHERE nid = ?");
                    check_voter.addBindValue(current_voter_nid);

                    if(!check_voter.exec())
                    {
                        QMessageBox::critical(this, "Error", check_voter.lastError().text());
                        return;
                    }

                    if(!check_voter.next())
                    {
                        QMessageBox::critical(this, "Error", "Voter not found.");
                        return;
                    }

                    if(check_voter.value(0).toBool())
                    {
                        QMessageBox::warning(this, "Blocked", "You have already voted.");
                        return;
                    }


                    auto reply = QMessageBox::question(
                        this,
                        "Confirm Vote",
                        "Vote for " + name + "?",
                        QMessageBox::Yes | QMessageBox::No
                        );

                    if(reply == QMessageBox::Yes)
                    {
                        QSqlQuery vote(Database::db);
                        vote.prepare("UPDATE candidates SET votes=votes+1 WHERE nid=?");
                        vote.addBindValue(nid);

                        QSqlQuery updateVoter(Database::db);
                        updateVoter.prepare("UPDATE voters SET has_voted = 1 WHERE nid = ?");
                        updateVoter.addBindValue(current_voter_nid);


                        if(vote.exec() && updateVoter.exec())
                            QMessageBox::information(this, "Success", "Vote cast successfully.");
                        else
                            QMessageBox::critical(this, "Error", vote.lastError().text());
                    }
                });

        layout->addWidget(photo);
        layout->addLayout(textLayout);
        layout->addStretch();
        layout->addWidget(vote_btn);
        main_layout->addWidget(card);
    }

    main_layout->addStretch();
}