#pragma once

#include <QWidget>
#include <QVBoxLayout>

class VotingPage : public QWidget
{
    Q_OBJECT

public:
    VotingPage(const QString& voter_nid, QWidget *parent = nullptr);

private:
    QVBoxLayout *main_layout;
    QString current_voter_nid;

    void load_candidates();
};

