#include "voting_page.h"
#include "database.h"

#include <QDebug>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QSqlQuery>
#include <QVBoxLayout>

VotingPage::VotingPage(const QString &voter_nid, QWidget *parent)
    : QWidget(parent)
    , current_voter_nid(voter_nid)
{
    //setFixedSize(700, 500);
    setWindowTitle("Voting Page");

    setStyleSheet("background:#1b1b1b; color:white;");

    QVBoxLayout *root_layout = new QVBoxLayout(this);
    root_layout->setContentsMargins(20, 20, 20, 20);
    root_layout->setSpacing(18);

    // title
    QLabel *title = new QLabel("Cast Your Vote");
    title->setAlignment(Qt::AlignCenter);

    QFont f;
    f.setPointSize(17);
    f.setWeight(QFont::Medium);
    title->setFont(f);

    title->setStyleSheet("color:#eaeaea;");
    root_layout->addWidget(title);

    // filter bar
    QFrame *filter_frame = new QFrame;
    filter_frame->setStyleSheet(
        "QFrame {"
        "background:#252525;"
        "border:1px solid #3a3a3a;"
        "border-radius:8px;"
        "}"
        );

    QHBoxLayout *filter_layout = new QHBoxLayout(filter_frame);
    filter_layout->setContentsMargins(15, 10, 15, 10);
    filter_layout->setSpacing(12);

    QLabel *party_label = new QLabel("Party:");
    QLabel *gender_label = new QLabel("Gender:");
    QLabel *age_label = new QLabel("Age:");

    party_label->setStyleSheet("color:white;");
    gender_label->setStyleSheet("color:white;");
    age_label->setStyleSheet("color:white;");

    party_filter = new QComboBox;
    gender_filter = new QComboBox;
    age_filter = new QComboBox;

    party_filter->addItems({
        "All Parties",
        "NC",
        "UML",
        "RSP"
    });

    gender_filter->addItems({
        "All",
        "Male",
        "Female",
        "Other"
    });

    age_filter->addItems({
        "Any Age",
        "18-25",
        "26-35",
        "36-45",
        "46-60",
        "60+"
    });

    QString combo_style =
        "QComboBox {"
        "background:#2f2f2f;"
        "color:white;"
        "border:1px solid #555;"
        "border-radius:6px;"
        "padding:5px 10px;"
        "min-width:120px;"
        "}"
        "QComboBox::drop-down {"
        "border:none;"
        "}"
        "QComboBox::down-arrow {"
        "image:none;"
        "}"
        "QComboBox QAbstractItemView {"
        "background:#2f2f2f;"
        "color:white;"
        "selection-background-color:#4b7bec;"
        "}";

    party_filter->setStyleSheet(combo_style);
    gender_filter->setStyleSheet(combo_style);
    age_filter->setStyleSheet(combo_style);

    QPushButton *apply_button = new QPushButton("Apply Filters");
    QPushButton *reset_button = new QPushButton("Reset");

    apply_button->setStyleSheet(
        "QPushButton {"
        "background:#4b7bec;"
        "color:white;"
        "border:none;"
        "border-radius:6px;"
        "padding:6px 14px;"
        "}"
        "QPushButton:hover {"
        "background:#6797ff;"
        "}"
        );

    reset_button->setStyleSheet(
        "QPushButton {"
        "background:#444444;"
        "color:white;"
        "border:none;"
        "border-radius:6px;"
        "padding:6px 14px;"
        "}"
        "QPushButton:hover {"
        "background:#5a5a5a;"
        "}"
        );

    filter_layout->addWidget(party_label);
    filter_layout->addWidget(party_filter);

    filter_layout->addWidget(gender_label);
    filter_layout->addWidget(gender_filter);

    filter_layout->addWidget(age_label);
    filter_layout->addWidget(age_filter);

    filter_layout->addStretch();

    filter_layout->addWidget(apply_button);
    filter_layout->addWidget(reset_button);

    root_layout->addWidget(filter_frame);

    // candidate list
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

    //default
    load_candidates();



    // button connections
    connect(apply_button, &QPushButton::clicked, this, [this]()
            {
                QString pty = party_filter->currentText();
                QString gen = gender_filter->currentText();
                QString ag = age_filter->currentText();

                clear_candidate_cards();
                load_candidates(pty, gen, ag);
            });

    connect(reset_button, &QPushButton::clicked, this, [this]()
            {
                party_filter->setCurrentIndex(0);
                gender_filter->setCurrentIndex(0);
                age_filter->setCurrentIndex(0);

                clear_candidate_cards();
                load_candidates();
            });


}

void VotingPage::load_candidates()
{
    Admin a;
    QSqlQuery q(Database::db);

    if(!q.exec("SELECT nid, first, last, dob, party, photo_path, party_symbol_path FROM candidates"))
    {
        qDebug() << "Query failed:" << q.lastError().text();
        return;
    }

    while (q.next()) {
        QString nid = q.value(0).toString();
        QString name = q.value(1).toString() + " " + q.value(2).toString();
        QString dob = q.value(3).toString();
        QString party = q.value(4).toString();
        QString photo_path = q.value(5).toString();
        QString party_symbol_path = q.value(6).toString();

        //candidates card
        QWidget *card = new QWidget;
        card->setMinimumHeight(135);

        card->setStyleSheet("QWidget {"
                            "background:#232323;"
                            "border:1px solid #2f2f2f;"
                            "border-radius:14px;"
                            "}"
                            "QWidget:hover {"
                            "border:1px solid #2ecc71;"
                            "}");

        QHBoxLayout *layout = new QHBoxLayout(card);
        layout->setContentsMargins(18, 14, 18, 14);
        layout->setSpacing(18);

        //photo
        QLabel *photo = new QLabel;
        photo->setFixedSize(88, 88);
        photo->setStyleSheet("border:1px solid #444; border-radius:10px;");

        QPixmap pix(photo_path);
        photo->setPixmap(
            pix.scaled(photo->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

        // Party Symbol
        QLabel *party_symbol = new QLabel;
        party_symbol->setFixedSize(75, 75);
        party_symbol->setStyleSheet("border:none");

        QPixmap symbolPix(party_symbol_path);
        party_symbol->setPixmap(
            symbolPix.scaled(
                party_symbol->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation)
            );

        // text
        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(6);

        QLabel *name_label = new QLabel(name);
        name_label->setStyleSheet(
            "font-size:20px;"
            "border:none;"
            "font-weight:600;"
            "color:#eaeaea;"
            );

        QLabel *age_label = new QLabel(
            "Age: " + QString::fromStdString(a.calculate_age(dob.toStdString()))
            );
        age_label->setStyleSheet("font-size:15px; color:#aaaaaa; font-weight:500; border:none;");

        QLabel *party_label = new QLabel("Party: " + party);
        party_label->setStyleSheet("font-size:15px; color:#aaaaaa; border:none; font-weight:500;");

        textLayout->addWidget(name_label);
        textLayout->addWidget(age_label);
        textLayout->addWidget(party_label);

        //button
        QPushButton *vote_btn = new QPushButton("Vote");
        vote_btn->setFixedSize(85, 34);

        vote_btn->setStyleSheet("QPushButton {"
                                "border:1px solid #2ecc71;"
                                "color:#2ecc71;"
                                "background:transparent;"
                                "border-radius:8px;"
                                "font-weight:500;"
                                "}"
                                "QPushButton:hover {"
                                "background:rgba(46,204,113,0.15);"
                                "}");

        connect(vote_btn, &QPushButton::clicked, this, [=]() {
            QSqlQuery check_voter(Database::db);
            check_voter.prepare("Select has_voted from voters WHERE nid = ?");
            check_voter.addBindValue(current_voter_nid);

            if (!check_voter.exec()) {
                QMessageBox::critical(this, "Error", check_voter.lastError().text());
                return;
            }

            if (!check_voter.next()) {
                QMessageBox::critical(this, "Error", "Voter not found.");
                return;
            }

            if (check_voter.value(0).toBool()) {
                QMessageBox::warning(this, "Blocked", "You have already voted.");
                return;
            }

            auto reply = QMessageBox::question(this,
                                               "Confirm Vote",
                                               "Vote for " + name + "?",
                                               QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                QSqlQuery vote(Database::db);
                vote.prepare("UPDATE candidates SET votes=votes+1 WHERE nid=?");
                vote.addBindValue(nid);

                QSqlQuery updateVoter(Database::db);
                updateVoter.prepare("UPDATE voters SET has_voted = 1 WHERE nid = ?");
                updateVoter.addBindValue(current_voter_nid);

                if (vote.exec() && updateVoter.exec())
                    QMessageBox::information(this, "Success", "Vote cast successfully.");
                else
                    QMessageBox::critical(this, "Error", vote.lastError().text());
            }
        });

        layout->addWidget(photo);
        layout->addLayout(textLayout);
        layout->addStretch();
        layout->addWidget(party_symbol);
        layout->addSpacing(10);
        layout->addWidget(vote_btn);
        main_layout->addWidget(card);
    }

    main_layout->addStretch();
}




void VotingPage::load_candidates(QString party, QString gender, QString age )
{
    Admin a;
    QSqlQuery q(Database::db);


    q.prepare(
            "SELECT nid, first, last, dob, party, photo_path, party_symbol_path "
            "FROM candidates "
            "WHERE (:p = 'All Parties' OR party = :p) "
            "AND (:g = 'All' OR gender = :g) "
            "AND (:dob = 'Any Age' OR (dob BETWEEN :min_age AND :max_age))"
        );

    q.bindValue(":p", party);
    q.bindValue(":g", gender);
    q.bindValue(":dob", age);



    if(!q.exec())
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
        QString party_symbol_path = q.value(6).toString();

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

        // Party Symbol
        QLabel *party_symbol = new QLabel;
        party_symbol->setFixedSize(50, 50);
        party_symbol->setStyleSheet("border:1px solid #444; border-radius:6px;");

        QPixmap symbolPix(party_symbol_path);
        party_symbol->setPixmap(
            symbolPix.scaled(
                party_symbol->size(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation)
            );
        party_symbol->setAlignment(Qt::AlignCenter);


        // text
        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(6);

        QLabel *name_label = new QLabel(name);
        name_label->setStyleSheet(
            "font-size:20px;"
            "border:none;"
            "font-weight:600;"
            "color:#eaeaea;"
            );


        QLabel *age_label = new QLabel(
            "Age: " + QString::fromStdString(a.calculate_age(dob.toStdString()))
            );
        age_label->setStyleSheet("font-size:15px; color:#aaaaaa; font-weight:500; border:none;");


        QLabel *party_label = new QLabel("Party: " + party);
        party_label->setStyleSheet("font-size:15px; color:#aaaaaa; border:none; font-weight:500;");

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
        layout->addWidget(party_symbol);
        layout->addSpacing(10);
        layout->addWidget(vote_btn);

        main_layout->addWidget(card);
    }

    main_layout->addStretch();
}




void VotingPage::clear_candidate_cards()     //uses "this" pointer to know the current main_layout
{
    QLayoutItem *item;

    while ((item = main_layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
}