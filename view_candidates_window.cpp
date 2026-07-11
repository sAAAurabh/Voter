#include "view_candidates_window.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QFont>
#include <QPixmap>

ViewCandidatesWindow::ViewCandidatesWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("View Candidates");
    resize(700, 560);
    setStyleSheet("background:#f5f5f5;");

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 20);
    root->setSpacing(15);

    // title
    QLabel *title = new QLabel("All Candidates", this);
    QFont f;
    f.setPointSize(18);
    f.setBold(true);
    title->setFont(f);
    title->setAlignment(Qt::AlignCenter);
    root->addWidget(title);

    // scrollable area
    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("border:none;");

    QWidget *container = new QWidget;
    QVBoxLayout *container_layout = new QVBoxLayout(container);
    container_layout->setSpacing(14);
    container_layout->setContentsMargins(5, 5, 5, 5);

    std::vector<Candidate> candidates = admin.get_all_candidates();

    if (candidates.empty()) {
        QLabel *empty = new QLabel("No candidates registered yet.");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color:#888; font-size:14px;");
        container_layout->addWidget(empty);
    }

    for (const Candidate& c : candidates) {

        QFrame *card = new QFrame;
        card->setStyleSheet(
            "QFrame {"
            "background:white;"
            "border:1px solid #ddd;"
            "border-radius:10px;"
            "padding:12px;"
            "}"
            );

        QGridLayout *card_layout = new QGridLayout(card);
        card_layout->setHorizontalSpacing(16);
        card_layout->setVerticalSpacing(6);

        // photo
        QLabel *photo = new QLabel;
        photo->setFixedSize(85, 95);
        photo->setAlignment(Qt::AlignCenter);
        photo->setStyleSheet("border:1px solid #ccc; border-radius:4px;");
        QPixmap pix(QString::fromStdString(c.photo_path));
        if (!pix.isNull())
            photo->setPixmap(pix.scaled(photo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else
            photo->setText("No Photo");

        // info
        QString info_style = "font-size:13px; border:none; background:transparent;";

        QLabel *name   = new QLabel(QString::fromStdString("Name: " + c.first + " " + c.last));
        QLabel *party  = new QLabel(QString::fromStdString("Party: " + c.party));
        QLabel *gender = new QLabel(QString::fromStdString("Gender: " + c.gender));
        QLabel *votes  = new QLabel("Votes: " + QString::number(c.votes));

        name->setStyleSheet(info_style + "font-weight:bold;");
        party->setStyleSheet(info_style);
        gender->setStyleSheet(info_style);
        votes->setStyleSheet(info_style);

        // manifesto section
        QString manifesto_text = c.manifesto.empty()
                                     ? "No manifesto added yet."
                                     : QString::fromStdString(c.manifesto);

        QLabel *manifesto_title = new QLabel("Manifesto:");
        manifesto_title->setStyleSheet("font-weight:bold; font-size:12px; color:#555; border:none; background:transparent;");

        QLabel *manifesto = new QLabel(manifesto_text);
        manifesto->setWordWrap(true);
        manifesto->setStyleSheet(
            "font-size:12px; color:#333; border:1px solid #eee;"
            "background:#f9f9f9; padding:6px; border-radius:4px;"
            );

        card_layout->addWidget(photo,           0, 0, 4, 1, Qt::AlignTop);
        card_layout->addWidget(name,            0, 1);
        card_layout->addWidget(party,           1, 1);
        card_layout->addWidget(gender,          2, 1);
        card_layout->addWidget(votes,           3, 1);
        card_layout->addWidget(manifesto_title, 4, 0, 1, 2);
        card_layout->addWidget(manifesto,       5, 0, 1, 2);

        container_layout->addWidget(card);
    }

    container_layout->addStretch();
    scroll->setWidget(container);
    root->addWidget(scroll);
}