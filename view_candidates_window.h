#pragma once

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include "admin.h"

class ViewCandidatesWindow : public QWidget
{
    Q_OBJECT

public:
    ViewCandidatesWindow(QWidget *parent = nullptr);

private:
    Admin admin;

    QVBoxLayout *container_layout;
    QComboBox *party_filter;
    QComboBox *gender_filter;
    QComboBox *age_filter;

    void load_candidates(QString party = "All Parties", QString gender = "All", QString age = "Any Age");

signals:
    void back_requested();
};