#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <time.h>
#include <QPixmap>
#include <QLineEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pic1(":/resources/img/photo1710771600.jpeg");
    int widthP1 = ui->pic1->width();
    int heightP1 = ui->pic1->height();
    ui->pic1->setPixmap(pic1.scaled(widthP1, heightP1, Qt::KeepAspectRatio));

    varA = new QLineEdit;
    varB = new QLineEdit;
    varC = new QLineEdit;
    varD = new QLineEdit;

    doGraph = new QPushButton("graphs");
    //clearGraph = new QPushButton("clear graphs");

    connect(doGraph, SIGNAL(clicked()), SLOT(on_doGraph_clicked()));
    //connect(clearGraph, SIGNAL(clicked()), SLOT(on_clearGraph_clicked()));
    connect(ui->varA, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->varB, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->varC, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->varD, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_doGraph_clicked()
{
    ui->pic2->clear();
    ui->DmensheO->clear();

    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    double variableA = ui->varA->text().toDouble();
    double variableB = ui->varB->text().toDouble();
    double variableC = ui->varC->text().toDouble();
    double variableD = ui->varD->text().toDouble();

    double sum1 = variableA + variableD;
    double sum2 = variableA*variableD - variableB*variableC;
    const1 = 1;
    const2 = 2;

    double disk = sum1 * sum1 - 4 * sum2;

    if(disk>=0){
        gamma2 = (sum1 + sqrt(disk)) / 2;
        gamma1 = (sum1 - sqrt(disk)) / 2;
        xi1 = (gamma1 - variableA) / variableB;
        xi2 = (gamma2 - variableA) / variableB;


        QPixmap pic2(":/resources/img/photo1710771600(2).jpeg");
        int widthP1 = ui->pic2->width();
        int heightP1 = ui->pic2->height();
        ui->pic2->setPixmap(pic2.scaled(widthP1, heightP1, Qt::KeepAspectRatio));
        ui->reshenie->setText("Общее решение данного уравнения:");
        //ui->reshenie->setText(QString::number(xi1));
        //ui->DmensheO->setText(QString::number(xi2));

        h = 0.001;
        tBegin = 0;
        tEnd = 1 + h;

        ui->widget->xAxis->setRange(0, 1);
        ui->widget->yAxis->setRange(0, 300);

        //N = (xEnd-xBegin)/h + 2;

        for(t = tBegin; t<=tEnd; t+=h){

           // y.push_back(const1*exp(gamma1*t)+const2*exp(gamma2*t));
            y.push_back(const1*xi1*exp(gamma1*t)+const2*xi2*exp(gamma2*t));
            x.push_back(t);
        }

        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x, y);
        ui->widget->xAxis->setLabel("t");
        ui->widget->yAxis->setLabel("X(t), Y(t)");
        ui->widget->replot();

        x.clear();
        y.clear();

        for(t = tBegin; t<=tEnd; t+=h){

            y.push_back(const1*exp(gamma1*t)+const2*exp(gamma2*t));
           // y.push_back(const1*xi1*exp(gamma1*t)+const2*xi2*exp(gamma2*t));
            x.push_back(t);
        }
        ui->widget->addGraph();
        ui->widget->graph(1)->addData(x, y);
        ui->widget->xAxis->setLabel("t");
        ui->widget->yAxis->setLabel("X(t), Y(t)");
        ui->widget->replot();

    }
    else if(disk<0){
        ui->DmensheO->setText("Дискриминант меньше 0, нет корней");
    }



}
