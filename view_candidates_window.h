#pragma once

#include <QWidget>
#include "admin.h"

class ViewCandidatesWindow : public QWidget
{
    Q_OBJECT

public:
    ViewCandidatesWindow(QWidget *parent = nullptr);

private:
    Admin admin;

signals:
    void back_requested();
};