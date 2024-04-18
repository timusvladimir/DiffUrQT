#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLineEdit>
#include <QPushButton>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:
    void on_doGraph_clicked();



private:
    Ui::MainWindow *ui;
    double tBegin, tEnd, h, xi1, xi2, const1, const2, gamma1, gamma2, t;
    int N;
    QLineEdit* varA;
    QLineEdit* varB;
    QLineEdit* varC;
    QLineEdit* varD;

    QPushButton* doGraph;

    QVector<double> x, y;


};
#endif // MAINWINDOW_H
