#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->customPlot->addGraph();


    float x1 = ui->lineEdit_x->text().toFloat();
    float y1 = ui->lineEdit_y->text().toFloat();

    x.append(x1);
    y.append(y1);

    if (ui->customPlot->selectedGraphs().isEmpty())
        ui->customPlot->graph()->setData(x, y);
    else
        ui->customPlot->selectedGraphs().first()->addData(x, y);
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

