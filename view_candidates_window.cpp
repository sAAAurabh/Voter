#include "view_candidates_window.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QFont>
#include <QPixmap>
#include <QPushButton>
#include <QComboBox>

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

    QFrame *filter_frame = new QFrame;
    filter_frame->setStyleSheet(
        "QFrame {"
        "background:rgba(255,255,255,0.08);"
        "border:1px solid rgba(255,255,255,0.15);"
        "border-radius:8px;"
        "}"
        );

    QHBoxLayout *filter_layout = new QHBoxLayout(filter_frame);
    filter_layout->setContentsMargins(15, 10, 15, 10);
    filter_layout->setSpacing(12);

    QLabel *party_label = new QLabel("Party:");
    QLabel *gender_label = new QLabel("Gender:");
    QLabel *age_label = new QLabel("Age:");

    party_label->setStyleSheet("color:white; background:transparent;");
    gender_label->setStyleSheet("color:white; background:transparent;");
    age_label->setStyleSheet("color:white; background:transparent;");

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
        "background:rgba(255,255,255,0.12);"
        "color:white;"
        "border:1px solid rgba(255,255,255,0.25);"
        "border-radius:6px;"
        "padding:5px 10px;"
        "min-width:110px;"
        "}"
        "QComboBox::drop-down {"
        "border:none;"
        "}"
        "QComboBox QAbstractItemView {"
        "background:#24243e;"
        "color:white;"
        "selection-background-color:#4facfe;"
        "}";

    party_filter->setStyleSheet(combo_style);
    gender_filter->setStyleSheet(combo_style);
    age_filter->setStyleSheet(combo_style);

    QPushButton *apply_button = new QPushButton("Apply Filters");
    QPushButton *reset_button = new QPushButton("Reset");

    apply_button->setCursor(Qt::PointingHandCursor);
    apply_button->setStyleSheet(
        "QPushButton {"
        "background:#4facfe;"
        "color:white;"
        "border:none;"
        "border-radius:6px;"
        "padding:6px 14px;"
        "font-weight:bold;"
        "}"
        "QPushButton:hover { background:#0084ff; }"
        );

    reset_button->setCursor(Qt::PointingHandCursor);
    reset_button->setStyleSheet(
        "QPushButton {"
        "background:rgba(255,255,255,0.12);"
        "color:white;"
        "border:1px solid rgba(255,255,255,0.25);"
        "border-radius:6px;"
        "padding:6px 14px;"
        "}"
        "QPushButton:hover { background:rgba(255,255,255,0.2); }"
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

    root->addWidget(filter_frame);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("background:transparent; border:none;");

    QWidget *container = new QWidget;
    container->setStyleSheet("background:transparent;");
    container_layout = new QVBoxLayout(container);
    container_layout->setSpacing(14);
    container_layout->setContentsMargins(5, 5, 5, 5);

    scroll->setWidget(container);
    root->addWidget(scroll);

    load_candidates();

    connect(apply_button, &QPushButton::clicked, this, [this]()
            {
                load_candidates(party_filter->currentText(), gender_filter->currentText(), age_filter->currentText());
            });

    connect(reset_button, &QPushButton::clicked, this, [this]()
            {
                party_filter->setCurrentIndex(0);
                gender_filter->setCurrentIndex(0);
                age_filter->setCurrentIndex(0);
                load_candidates();
            });

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

void ViewCandidatesWindow::load_candidates(QString party, QString gender, QString age)
{
    QLayoutItem *item;
    while ((item = container_layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    std::vector<Candidate> candidates = admin.get_all_candidates();

    bool any_shown = false;

    for (const Candidate& c : candidates) {

        QString c_party = QString::fromStdString(c.party);
        QString c_gender = QString::fromStdString(c.gender);

        if (party != "All Parties" && c_party != party)
            continue;

        if (gender != "All" && c_gender != gender)
            continue;

        if (age != "Any Age") {
            int candidate_age = std::stoi(admin.calculate_age(c.dob));
            bool match = true;

            if (age == "18-25")
                match = (candidate_age >= 18 && candidate_age <= 25);
            else if (age == "26-35")
                match = (candidate_age >= 26 && candidate_age <= 35);
            else if (age == "36-45")
                match = (candidate_age >= 36 && candidate_age <= 45);
            else if (age == "46-60")
                match = (candidate_age >= 46 && candidate_age <= 60);
            else if (age == "60+")
                match = (candidate_age > 60);

            if (!match)
                continue;
        }

        any_shown = true;

        QString card_bg = "white";
        if (c_party == "UML")
            card_bg = "#fdeaea";
        else if (c_party == "NC")
            card_bg = "#eafaf1";
        else if (c_party == "RSP")
            card_bg = "#eaf2fd";

        QFrame *card = new QFrame;
        card->setStyleSheet(
            "QFrame {"
            "background-color:" + card_bg + ";"
                        "border:none;"
                        "border-radius:12px;"
                        "}"
            );

        QVBoxLayout *card_layout = new QVBoxLayout(card);
        card_layout->setContentsMargins(18, 16, 18, 16);
        card_layout->setSpacing(12);

        QHBoxLayout *top_row = new QHBoxLayout;
        top_row->setSpacing(16);

        QLabel *photo = new QLabel;
        photo->setFixedSize(85, 95);
        photo->setAlignment(Qt::AlignCenter);
        photo->setStyleSheet("border:2px dashed #dcdde1; border-radius:8px; background:#f1f2f6;");

        QPixmap pix(QString::fromStdString(c.photo_path));
        if (!pix.isNull())
            photo->setPixmap(pix.scaled(photo->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        else
            photo->setText("No Photo");

        QVBoxLayout *text_layout = new QVBoxLayout;
        text_layout->setSpacing(6);

        QString info_style = "font-size:16px; border:none; background:transparent; color:#2f3640; font-family:'Segoe UI';";

        QLabel *name = new QLabel(QString::fromStdString(c.first + " " + c.last));
        name->setStyleSheet(info_style + "font-weight:bold; font-size:22px;");

        QLabel *age_lbl = new QLabel("Age: " + QString::fromStdString(admin.calculate_age(c.dob)));
        age_lbl->setStyleSheet(info_style);

        QLabel *party_lbl = new QLabel("Party: " + c_party);
        party_lbl->setStyleSheet(info_style);

        QLabel *gender_lbl = new QLabel("Gender: " + c_gender);
        gender_lbl->setStyleSheet(info_style);

        QLabel *votes = new QLabel("Votes: " + QString::number(c.votes));
        votes->setStyleSheet(info_style + "color:#00a878; font-weight:bold; font-size:17px;");

        text_layout->addWidget(name);
        text_layout->addWidget(age_lbl);
        text_layout->addWidget(party_lbl);
        text_layout->addWidget(gender_lbl);
        text_layout->addWidget(votes);

        QLabel *party_symbol = new QLabel;
        party_symbol->setFixedSize(75, 75);
        party_symbol->setStyleSheet("border:none; background:transparent;");

        QPixmap symbol_pix(QString::fromStdString(c.party_symbol_path));
        if (!symbol_pix.isNull())
            party_symbol->setPixmap(symbol_pix.scaled(party_symbol->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        top_row->addWidget(photo);
        top_row->addLayout(text_layout);
        top_row->addStretch();
        top_row->addWidget(party_symbol);

        card_layout->addLayout(top_row);

        QFrame *manifesto_box = new QFrame;
        manifesto_box->setStyleSheet(
            "QFrame {"
            "background:#eef4ff;"
            "border-left:4px solid #4facfe;"
            "border-radius:6px;"
            "}"
            );

        QVBoxLayout *manifesto_layout = new QVBoxLayout(manifesto_box);
        manifesto_layout->setContentsMargins(14, 10, 14, 12);
        manifesto_layout->setSpacing(6);

        QLabel *manifesto_title = new QLabel("Manifesto");
        manifesto_title->setStyleSheet(
            "font-weight:bold; font-size:16px; color:#1b74e4; border:none; background:transparent;"
            );

        QString manifesto_text = c.manifesto.empty()
                                     ? "No manifesto added yet."
                                     : QString::fromStdString(c.manifesto);

        QLabel *manifesto = new QLabel(manifesto_text);
        manifesto->setWordWrap(true);
        manifesto->setStyleSheet(
            "font-size:15px; color:#2f3640; border:none; background:transparent;"
            );

        manifesto_layout->addWidget(manifesto_title);
        manifesto_layout->addWidget(manifesto);

        card_layout->addWidget(manifesto_box);

        container_layout->addWidget(card);
    }

    if (!any_shown) {
        QLabel *empty = new QLabel("No candidates found.");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color:#dcdde1; font-size:14px; background:transparent;");
        container_layout->addWidget(empty);
    }

    container_layout->addStretch();
}