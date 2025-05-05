#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Добавление графика
    customPlot = ui->widget;
    customPlot->addGraph();

    // Настройка осей
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);

    // Включение интерактивности
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // Обновление графика
    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPoint_clicked()
{
    bool ok;
    double x = QInputDialog::getDouble(this, "Добавить точку", "Введите x:", 0, -1000, 1000, 2, &ok);
    if (!ok) return;
    double y = QInputDialog::getDouble(this, "Добавить точку", "Введите y:", 0, -1000, 1000, 2, &ok);
    if (!ok) return;

    auto dataContainer = customPlot->graph(0)->data();

    // Итерация по контейнеру
    for (auto it = dataContainer->constBegin(); it != dataContainer->constEnd(); ++it) {
        xData.append(it->key);   // Добавляем x-координату
        yData.append(it->value); // Добавляем y-координату
    }

    // Добавление новой точки
    xData.append(x);
    yData.append(y);

    // Установка обновленных данных
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
}

