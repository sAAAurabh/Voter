#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class RoleSelection : public QWidget
{
    Q_OBJECT

public:
    explicit RoleSelection(QWidget *parent = nullptr);
    ~RoleSelection();

private:
    QLabel      *titleLabel;
    QLabel      *subLabel;
    QPushButton *voterBtn;
    QPushButton *candidateBtn;

signals:
    void is_voter();
    void is_candidate();
};

