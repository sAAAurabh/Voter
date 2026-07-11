#include "result_page.h"
#include "admin.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

#include <QPieSeries>
#include <QChart>
#include <QChartView>

ResultPage::ResultPage(QWidget *parent)
    : QWidget(parent)
{
    Candidate c;
    Admin a;

    a.find_winner(c);

    resize(700,650);
    setWindowTitle("Election Results");

    setStyleSheet("background:#131a24;");

    QString boxStyle =
        "QGroupBox{"
        "background:#1a2532;"
        "border:1px solid #2d3d52;"
        "border-radius:10px;"
        "margin-top:10px;"
        "padding-top:10px;"
        "color:white;"
        "font-weight:bold;"
        "}"
        "QGroupBox::title{"
        "subcontrol-origin:margin;"
        "left:10px;"
        "}";

    QLabel *title = new QLabel("Election Results");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:white;font-size:22px;font-weight:bold;");

    // ---------------- Winner ----------------

    QGroupBox *winnerBox = new QGroupBox("Winner");
    winnerBox->setStyleSheet(boxStyle);



    QLabel *photo = new QLabel;
    photo->setPixmap(
        QPixmap(QString::fromStdString(c.photo_path))
            .scaled(100, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );

    QLabel *symbol = new QLabel;
    symbol->setPixmap(
        QPixmap(QString::fromStdString(c.party_symbol_path))
            .scaled(100, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );


    QLabel *name = new QLabel("Name :" + QString::fromStdString(c.first) + " " + QString::fromStdString(c.last));
    QLabel *party = new QLabel("Party :" + QString::fromStdString(c.party));

    name->setStyleSheet("color:white;");
    party->setStyleSheet("color:white;");

    QVBoxLayout *info = new QVBoxLayout;
    info->addWidget(name);
    info->addWidget(party);
    info->addWidget(symbol);

    QHBoxLayout *winnerLayout = new QHBoxLayout(winnerBox);
    winnerLayout->addWidget(photo);
    winnerLayout->addLayout(info);

    // ---------------- Summary ----------------

    QGroupBox *summary = new QGroupBox("Election Summary");
    summary->setStyleSheet(boxStyle);

    QVBoxLayout *summaryLayout = new QVBoxLayout(summary);
    summaryLayout->addWidget(new QLabel("Total Votes Cast : 500"));
    summaryLayout->addWidget(new QLabel("Total Candidates : 6"));

    // Make labels white
    for(auto lbl : summary->findChildren<QLabel*>())
        lbl->setStyleSheet("color:white;");

    // ---------------- Pie Chart ----------------

    QPieSeries *series = new QPieSeries;
    series->append("Ram",180);
    series->append("Hari",150);
    series->append("Sita",100);
    series->append("John",70);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Vote Distribution");
    chart->setBackgroundBrush(QColor("#1a2532"));
    chart->legend()->setLabelColor(Qt::white);
    chart->setTitleBrush(Qt::white);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("border:none;background:#1a2532;");

    // ---------------- Back ----------------

    QPushButton *back = new QPushButton("Back");

    back->setStyleSheet(
        "QPushButton{"
        "background:#2f9bda;"
        "color:white;"
        "border:none;"
        "border-radius:8px;"
        "padding:10px;"
        "font-weight:bold;"
        "}"
        "QPushButton:hover{background:#2585bd;}"
        );

    connect(back,&QPushButton::clicked,this,&QWidget::close);

    // ---------------- Main Layout ----------------

    QVBoxLayout *main = new QVBoxLayout(this);
    main->addWidget(title);
    main->addWidget(winnerBox);
    main->addWidget(summary);
    main->addWidget(chartView);
    main->addWidget(back);
}