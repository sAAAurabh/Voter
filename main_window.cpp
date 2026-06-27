#include "main_window.h"
#include <QDebug>
#include <QApplication>

void MainWindow::center_window()
{
    QRect screen = QGuiApplication::primaryScreen()->availableGeometry();

    QRect frame = frameGeometry();
    frame.moveCenter(screen.center());

    move(frame.topLeft());
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget(this);

    voter_login_page = new VoterLoginWindow;
    voter_register_page = new VoterRegisterWindow;

    candidate_login_page = new CandidateLoginWindow;
    candidate_register_page = new CandidateRegisterWindow;

    stack->addWidget(voter_login_page);
    stack->addWidget(voter_register_page);
    stack->addWidget(candidate_login_page);
    stack->addWidget(candidate_register_page);

    setCentralWidget(stack);
    stack->setCurrentWidget(voter_login_page);
    setFixedSize(450,300);



    connect(
        voter_login_page,
        &VoterLoginWindow::register_requested,
        this,
        [this]()
        {
            stack->setCurrentWidget(voter_register_page);
            setFixedSize(550,680);
            center_window();
        }
        );


    connect(
        voter_login_page,
        &VoterLoginWindow::login_successful,
        this,
        [this](QString nid)
        {
            VoterHomeWindow *voter_home = new VoterHomeWindow(nid);
            stack->addWidget(voter_home);
            stack->setCurrentWidget(voter_home);
            setFixedSize(650,480);
            center_window();

            connect(
                voter_home,
                &VoterHomeWindow::logout_requested,
                this,
                [this, voter_home]()
                {
                    stack->setCurrentWidget(voter_login_page);
                    setFixedSize(450,300);
                    center_window();
                    stack->removeWidget(voter_home);
                    delete voter_home;
                }
            );

            connect(
                voter_home,
                &VoterHomeWindow::vote_page_requested,
                this,
                [this](QString nid)
                {
                    VotingPage *voting_page = new VotingPage(nid);
                    stack->addWidget(voting_page);
                    stack->setCurrentWidget(voting_page);
                    setFixedSize(850,600);
                    center_window();
                }
                );


        }
    );


    connect(
        voter_register_page,
        &VoterRegisterWindow::back_to_login_requested,
        this,
        [this]()
        {
            setFixedSize(450,300);
            stack->setCurrentWidget(voter_login_page);
            center_window();

        }
        );







    connect(
        candidate_login_page,
        &CandidateLoginWindow::register_requested,
        this,
        [this]()
        {
            stack->setCurrentWidget(candidate_register_page);
            setFixedSize(550,680);
            center_window();
        }
        );


    connect(
        candidate_login_page,
        &CandidateLoginWindow::login_successful,
        this,
        [this](QString nid)
        {
            CandidateHomeWindow *candidate_home = new CandidateHomeWindow(nid);
            stack->addWidget(candidate_home);
            stack->setCurrentWidget(candidate_home);
            setFixedSize(650,480);
            center_window();

            connect(
                candidate_home,
                &CandidateHomeWindow::logout_requested,
                this,
                [this, candidate_home]()
                {
                    stack->setCurrentWidget(candidate_login_page);
                    setFixedSize(450,300);
                    center_window();
                    stack->removeWidget(candidate_home);
                    delete candidate_home;
                }
                );

        }
        );


    connect(
        candidate_register_page,
        &CandidateRegisterWindow::back_to_login_requested,
        this,
        [this]()
        {

            setFixedSize(450,300);
            stack->setCurrentWidget(candidate_login_page);
            center_window();

        }
        );


}
