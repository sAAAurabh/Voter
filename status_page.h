#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QProgressBar;

class CandidateStatusWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CandidateStatusWindow(const QString &nid, QWidget *parent = nullptr);

private:
    QString candidate_nid;

    QLabel *title;

    // Current Status
    QLabel *votes_label;
    QLabel *position_label;
    QLabel *share_label;

    // Election Information
    QLabel *total_votes_label;
    QLabel *total_candidates_label;
    QLabel *status_label;
    QLabel *time_label;

    QProgressBar *share_bar;

    QPushButton *back_btn;
};
