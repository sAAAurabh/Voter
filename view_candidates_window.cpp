#include "view_candidates_window.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QFont>
#include <QPixmap>
#include <QPushButton>

ViewCandidatesWindow::ViewCandidatesWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("View Candidates");

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(
        "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #0f0c29, stop:0.5 #1a1a2e, stop:1 #24243e);"
        );

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 20);
    root->setSpacing(15);

    QLabel *title = new QLabel("All Candidates", this);
    QFont f;
    f.setPointSize(18);
    f.setBold(true);
    title->setFont(f);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:#f5f6fa; background:transparent; font-family:'Segoe UI';");
    root->addWidget(title);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("background:transparent; border:none;");

    QWidget *container = new QWidget;
    container->setStyleSheet("background:transparent;");
    QVBoxLayout *container_layout = new QVBoxLayout(container);
    container_layout->setSpacing(14);
    container_layout->setContentsMargins(5, 5, 5, 5);

    std::vector<Candidate> candidates = admin.get_all_candidates();

    if (candidates.empty()) {
        QLabel *empty = new QLabel("No candidates registered yet.");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color:#dcdde1; font-size:14px; background:transparent;");
        container_layout->addWidget(empty);
    }

    for (const Candidate& c : candidates) {

        QFrame *card = new QFrame;
        card->setStyleSheet(
            "QFrame {"
            "background-color:white;"
            "border:none;"
            "border-radius:12px;"
            "}"
            );

        QGridLayout *card_layout = new QGridLayout(card);
        card_layout->setContentsMargins(16, 14, 16, 14);
        card_layout->setHorizontalSpacing(16);
        card_layout->setVerticalSpacing(6);

        QLabel *photo = new QLabel;
        photo->setFixedSize(85, 95);
        photo->setAlignment(Qt::AlignCenter);
        photo->setStyleSheet("border:2px dashed #dcdde1; border-radius:8px; background:#f1f2f6;");

        QPixmap pix(QString::fromStdString(c.photo_path));
        if (!pix.isNull())
            photo->setPixmap(pix.scaled(photo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else
            photo->setText("No Photo");

        QString info_style = "font-size:13px; border:none; background:transparent; color:#2f3640; font-family:'Segoe UI';";

        QLabel *name   = new QLabel(QString::fromStdString("Name: " + c.first + " " + c.last));
        QLabel *party  = new QLabel(QString::fromStdString("Party: " + c.party));
        QLabel *gender = new QLabel(QString::fromStdString("Gender: " + c.gender));
        QLabel *votes  = new QLabel("Votes: " + QString::number(c.votes));

        name->setStyleSheet(info_style + "font-weight:bold; font-size:15px;");
        party->setStyleSheet(info_style);
        gender->setStyleSheet(info_style);
        votes->setStyleSheet(info_style + "color:#00a878; font-weight:bold;");

        QString manifesto_text = c.manifesto.empty()
                                     ? "No manifesto added yet."
                                     : QString::fromStdString(c.manifesto);

        QLabel *manifesto_title = new QLabel("Manifesto:");
        manifesto_title->setStyleSheet(
            "font-weight:bold; font-size:12px; color:#636e72; border:none; background:transparent;"
            );

        QLabel *manifesto = new QLabel(manifesto_text);
        manifesto->setWordWrap(true);
        manifesto->setStyleSheet(
            "font-size:12px; color:#2f3640; border:none;"
            "background:#f1f2f6; padding:8px; border-radius:6px;"
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

    QPushButton *back_btn = new QPushButton("Back");
    back_btn->setFixedSize(120, 40);
    back_btn->setCursor(Qt::PointingHandCursor);
    back_btn->setStyleSheet(
        "QPushButton {"
        "background-color:#4facfe;"
        "color:white;"
        "border:none;"
        "border-radius:8px;"
        "font-size:14px;"
        "font-weight:bold;"
        "font-family:'Segoe UI';"
        "}"
        "QPushButton:hover { background-color:#0084ff; }"
        "QPushButton:pressed { background-color:#0066cc; }"
        );

    connect(back_btn, &QPushButton::clicked, this, [this]() {
        emit back_requested();
    });

    root->addWidget(back_btn, 0, Qt::AlignCenter);
}