#ifndef ROLESELECTION_H
#define ROLESELECTION_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class RoleSelection : public QWidget
{
    Q_OBJECT

public:
    explicit RoleSelection(QWidget *parent = nullptr);
    ~RoleSelection();

private slots:
    void onVoterBtnClicked();
    void onCandidateBtnClicked();

private:
    QLabel      *titleLabel;
    QLabel      *subLabel;
    QPushButton *voterBtn;
    QPushButton *candidateBtn;
};

#endif // ROLESELECTION_H