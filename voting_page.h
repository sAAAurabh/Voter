#pragma once

#include <QVBoxLayout>
#include <QComboBox>
#include "admin.h"
#include <QWidget>


class VotingPage : public QWidget
{
    Q_OBJECT

public:
    VotingPage(const QString &voter_nid, QWidget *parent = nullptr);

private:
    QVBoxLayout *main_layout;
    QString current_voter_nid;

    QComboBox *party_filter;
    QComboBox *gender_filter;
    QComboBox *age_filter;

    void load_candidates();
    void load_candidates(QString party, QString gender, QString age);
    void clear_candidate_cards();
};
