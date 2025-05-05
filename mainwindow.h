#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<double> xData;
    QVector<double> yData;

private slots:
    void on_addPoint_clicked();

private:
    QCustomPlot *customPlot;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
