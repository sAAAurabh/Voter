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
    setStyleSheet("background-color:#211f26;");

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
        empty->setStyleSheet("color:#9891a3; font-size:14px; background:transparent;");
        container_layout->addWidget(empty);
    }

    for (const Candidate& c : candidates) {

        QFrame *card = new QFrame;
        card->setStyleSheet(
            "QFrame {"
            "background-color:#2b2833;"
            "border:1px solid #3a3644;"
            "border-radius:12px;"
            "}"
            );

        QGridLayout *card_layout = new QGridLayout(card);
        card_layout->setContentsMargins(16, 14, 16, 14);
        card_layout->setHorizontalSpacing(16);
        card_layout->setVerticalSpacing(6);


        //
        QLabel *photo = new QLabel;
        photo->setFixedSize(85, 95);
        photo->setAlignment(Qt::AlignCenter);
        photo->setStyleSheet(
            "border:1px solid #453f52;"
            "border-radius:8px;"
            "background:#332f3d;"
            );

        QPixmap pix(QString::fromStdString(c.photo_path));
        if (!pix.isNull())
            photo->setPixmap(pix.scaled(photo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else
            photo->setText("No Photo");

        QLabel *party_symbol = new QLabel;
        party_symbol->setFixedSize(55, 55);
        party_symbol->setAlignment(Qt::AlignCenter);
        party_symbol->setStyleSheet(
            "border:1px solid #453f52;"
            "border-radius:8px;"
            "background:#332f3d;"
            );

        QPixmap symbol(QString::fromStdString(c.party_symbol_path));
        if (!symbol.isNull())
            party_symbol->setPixmap(symbol.scaled(
                party_symbol->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
        else
            party_symbol->setText("N/A");

        QString info_style =
            "font-size:13px; border:none; background:transparent; "
            "color:#cdc8d6; font-family:'Segoe UI';";

        QLabel *name   = new QLabel(QString::fromStdString(c.first + " " + c.last));
        QLabel *party  = new QLabel(QString::fromStdString("Party: " + c.party));
        QLabel *gender = new QLabel(QString::fromStdString("Gender: " + c.gender));
        QLabel *age    = new QLabel("Age: " + QString::fromStdString(admin.calculate_age(c.dob)));

        name->setStyleSheet(info_style + "font-weight:bold; font-size:15px; color:#ffffff;");
        party->setStyleSheet(info_style);
        gender->setStyleSheet(info_style);
        age->setStyleSheet(info_style);

        QString manifesto_text = c.manifesto.empty()
                                     ? "No manifesto added yet."
                                     : QString::fromStdString(c.manifesto);

        QLabel *manifesto_title = new QLabel("Manifesto:");
        manifesto_title->setStyleSheet(
            "font-weight:bold; font-size:12px; color:#9891a3;"
            "border:none; background:transparent;"
            );

        QLabel *manifesto = new QLabel(manifesto_text);
        manifesto->setWordWrap(true);
        manifesto->setStyleSheet(
            "font-size:12px; color:#cdc8d6;"
            "border:none; background:#332f3d;"
            "padding:8px; border-radius:6px;"
            );
        //

        card_layout->setColumnStretch(1, 1);
        card_layout->addWidget(photo,         0, 0, 4, 1, Qt::AlignTop);
        card_layout->addWidget(name,          0, 1);
        card_layout->addWidget(party,         1, 1);
        card_layout->addWidget(gender,        2, 1);
        card_layout->addWidget(age,           3, 1);
        card_layout->addWidget(party_symbol,  0, 2, Qt::AlignTop | Qt::AlignRight);
        card_layout->addWidget(manifesto_title, 4, 0, 1, 3);
        card_layout->addWidget(manifesto,       5, 0, 1, 3);

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
        "background-color:#3b82f6;"
        "color:#f5f6fa;"
        "border:1px solid #453f52;"
        "border-radius:8px;"
        "font-size:14px;"
        "font-weight:bold;"
        "font-family:'Segoe UI';"
        "}"
        "QPushButton:hover { background-color:#3d3849; }"
        "QPushButton:pressed { background-color:#2b2833; }"
        );

    connect(back_btn, &QPushButton::clicked, this, [this]() {
        emit back_requested();
    });

    root->addWidget(back_btn, 0, Qt::AlignCenter);
}