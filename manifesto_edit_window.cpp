#include "manifesto_edit_window.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFont>

ManifestoEditWindow::ManifestoEditWindow(const QString& nid, QWidget *parent)
    : QWidget(parent), candidate_nid(nid)
{
    setWindowTitle("Edit Manifesto");
    setFixedSize(500, 420);

    Candidate c;
    admin.find_candidate(nid.toStdString(), c);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(25, 20, 25, 20);
    layout->setSpacing(12);

    QLabel *title = new QLabel("Edit Your Manifesto", this);
    QFont titleFont;
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    QLabel *hint = new QLabel("Write your election manifesto below:", this);
    hint->setStyleSheet("color:#555; font-size:12px;");

    manifesto_input = new QTextEdit(this);
    manifesto_input->setPlaceholderText("Enter your manifesto here...");
    manifesto_input->setText(QString::fromStdString(c.manifesto));
    manifesto_input->setStyleSheet(
        "padding:8px; font-size:13px; border:1px solid #ccc; border-radius:6px;"
        );

    save_btn = new QPushButton("Save Manifesto", this);
    save_btn->setStyleSheet(
        "background:#3498db; color:white; padding:10px;"
        "border-radius:6px; font-weight:bold;"
        );
    save_btn->setCursor(Qt::PointingHandCursor);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);

    layout->addWidget(title);
    layout->addWidget(hint);
    layout->addWidget(manifesto_input);
    layout->addWidget(save_btn);
    layout->addWidget(msg);

    connect(save_btn, &QPushButton::clicked, this, &ManifestoEditWindow::save_manifesto);
}

void ManifestoEditWindow::save_manifesto()
{
    QString text = manifesto_input->toPlainText().trimmed();
    admin.update_manifesto(candidate_nid.toStdString(), text.toStdString());
    msg->setStyleSheet("color:#27ae60; font-weight:bold;");
    msg->setText("Manifesto saved successfully!");
}