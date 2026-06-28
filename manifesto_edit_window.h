#pragma once

#include <QWidget>
#include <QString>
#include "admin.h"

class QTextEdit;
class QPushButton;
class QLabel;

class ManifestoEditWindow : public QWidget
{
    Q_OBJECT

public:
    ManifestoEditWindow(const QString& nid, QWidget *parent = nullptr);

private:
    QString candidate_nid;
    QTextEdit *manifesto_input;
    QPushButton *save_btn;
    QLabel *msg;
    Admin admin;

private slots:
    void save_manifesto();
};