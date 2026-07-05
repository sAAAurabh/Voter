#include "manifesto_edit_window.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFont>
#include <QFrame>
#include <QGuiApplication>
#include <QScreen>

ManifestoEditWindow::ManifestoEditWindow(const QString& nid, QWidget *parent)
    : QWidget(parent), candidate_nid(nid)
{
    setWindowTitle("Edit Manifesto");

    Candidate c;
    admin.find_candidate(nid.toStdString(), c);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color:#131a24;");

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(30, 26, 30, 26);
    root->setSpacing(0);

    QLabel *title = new QLabel("Edit Your Manifesto", this);
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:#f5f6fa; background:transparent; font-family:'Segoe UI';");

    QLabel *subtitle = new QLabel(
        QString::fromStdString("For candidate: " + c.first + " " + c.last), this
        );
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color:#a9b8cc; font-size:12px; background:transparent; font-family:'Segoe UI';");

    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(1);
    divider->setStyleSheet("background-color: rgba(255,255,255,30); border:none;");

    QFrame *card = new QFrame(this);
    card->setStyleSheet(
        "QFrame {"
        "background-color:#1a2532;"
        "border: none;"
        "border-radius: 16px;"
        "}"
        );

    QVBoxLayout *card_layout = new QVBoxLayout(card);
    card_layout->setContentsMargins(26, 24, 26, 24);
    card_layout->setSpacing(10);

    QLabel *hint = new QLabel(
        "Write your election manifesto below. Voters will see this on your candidate profile.", card
        );
    hint->setWordWrap(true);
    hint->setStyleSheet("color:#a9b8cc; font-size:13px; background:transparent; font-family:'Segoe UI';");

    manifesto_input = new QTextEdit(card);
    manifesto_input->setPlaceholderText("Enter your manifesto here...");
    manifesto_input->setText(QString::fromStdString(c.manifesto));
    manifesto_input->setMinimumHeight(180);
    manifesto_input->setStyleSheet(
        "QTextEdit {"
        "padding:12px;"
        "font-size:14px;"
        "color:#e6ebf2;"
        "background-color:#22334a;"
        "border: none;"
        "border-radius:8px;"
        "font-family:'Segoe UI';"
        "}"
        );

    save_btn = new QPushButton("Save Manifesto", card);
    save_btn->setMinimumHeight(44);
    save_btn->setCursor(Qt::PointingHandCursor);
    save_btn->setStyleSheet(
        "QPushButton {"
        "background-color:#2f9bda;"
        "color:white;"
        "padding:10px;"
        "border-radius:10px;"
        "font-weight:600;"
        "font-size:15px;"
        "font-family:'Segoe UI';"
        "border:none;"
        "}"
        "QPushButton:hover { background-color:#2585bd; }"
        "QPushButton:pressed { background-color:#1c6c9c; }"
        );

    msg = new QLabel(card);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#4fc3f7; background:transparent; font-family:'Segoe UI'; font-size:13px;");

    card_layout->addWidget(hint);
    card_layout->addWidget(manifesto_input);
    card_layout->addWidget(save_btn);
    card_layout->addWidget(msg);

    root->addWidget(title);
    root->addSpacing(4);
    root->addWidget(subtitle);
    root->addSpacing(14);
    root->addWidget(divider);
    root->addSpacing(18);
    root->addWidget(card);

    connect(save_btn, &QPushButton::clicked, this, &ManifestoEditWindow::save_manifesto);
}

void ManifestoEditWindow::save_manifesto()
{
    QString text = manifesto_input->toPlainText().trimmed();
    admin.update_manifesto(candidate_nid.toStdString(), text.toStdString());
    msg->setStyleSheet("color:#00c896; font-weight:bold; background:transparent; font-family:'Segoe UI'; font-size:13px;");
    msg->setText("Manifesto saved successfully!");
}