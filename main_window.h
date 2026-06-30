#pragma once

#include <QScreen>
#include <QGuiApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include "voter_login_window.h"
#include "voter_register_window.h"
#include "candidate_login_window.h"
#include "candidate_register_window.h"
#include "candidate_home.h"
#include "voter_home.h"
#include "voting_page.h"
#include "view_candidates_window.h"
#include "roleselection.h"
#include "manifesto_edit_window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


private:

    void center_window();
    QStackedWidget *stack;

    VoterLoginWindow *voter_login_page;
    VoterRegisterWindow *voter_register_page;

    CandidateLoginWindow *candidate_login_page;
    CandidateRegisterWindow *candidate_register_page;

    RoleSelection *role_selection_page;


};