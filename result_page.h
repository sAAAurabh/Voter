#pragma once

#include <QWidget>

class ResultPage : public QWidget
{
    Q_OBJECT

public:
    ResultPage(QWidget *parent=nullptr);

signals:
    void back_requested();
};

