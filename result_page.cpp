#include "result_page.h"
#include "admin.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QSqlQuery>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
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

    //election summary

    QGroupBox *summary = new QGroupBox("Election Summary");
    summary->setStyleSheet(boxStyle);

    QVBoxLayout *summaryLayout = new QVBoxLayout(summary);
    summaryLayout->addWidget(new QLabel("Total Votes Cast : " + QString::number(a.total_votes())));
    summaryLayout->addWidget(new QLabel("Total Candidates : "+ QString::number(a.total_candidates())));
    for(auto lbl : summary->findChildren<QLabel*>())
        lbl->setStyleSheet("color:white;");





    //bar chart result

    QBarSet *set = new QBarSet("Votes");
    QStringList names;

    QSqlQuery query(
        "SELECT first, votes FROM candidates "
        "ORDER BY votes DESC LIMIT 5"
        );

    while (query.next())
    {
        names << query.value(0).toString();
        *set << query.value(1).toInt();
    }

    QBarSeries *series = new QBarSeries;
    series->append(set);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setBackgroundBrush(QColor("#1a2532"));
    chart->setTitle("Top Candidates");
    chart->setTitleBrush(Qt::white);

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(names);
    QFont font;
    font.setPointSize(10);

    axisX->setLabelsFont(font);
    axisX->setLabelsColor(Qt::white);


    QValueAxis *axisY = new QValueAxis;

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    axisX->setGridLineVisible(false);
    axisX->setLineVisible(false);
    axisY->setVisible(false);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background:#1a2532;border:none;");





    QPushButton *back = new QPushButton("Back");

    back->setStyleSheet(
        "QPushButton{"
        "background:#00a878;"
        "color:white;"
        "border:none;"
        "border-radius:8px;"
        "padding:10px;"
        "font-weight:bold;"
        "}"
        "QPushButton:hover{background:#008f66;}"
        );

    connect(back,&QPushButton::clicked,this,&QWidget::close);



    //mainlayout
    QVBoxLayout *main = new QVBoxLayout(this);
    main->addWidget(title);
    main->addWidget(winnerBox);
    main->addWidget(summary);
    main->addWidget(chartView);
    main->addWidget(back);
}