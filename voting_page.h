#pragma once

#include <QWidget>
#include <QVBoxLayout>

class VotingPage : public QWidget
{
    Q_OBJECT

public:
    explicit VotingPage(QWidget *parent = nullptr);

private:
    QVBoxLayout *main_layout;

    void load_candidates();
};

