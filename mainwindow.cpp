#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customPlot = ui->widget;
    customPlot->addGraph();
    myScatter.setShape(QCPScatterStyle::ssCircle);
    myScatter.setSize(5);
    customPlot->graph(0)->setScatterStyle(myScatter);
    customPlot->graph(0)->setSelectable(QCP::stDataRange);


    // Настройка осей
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);

    // Включение интерактивности
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(customPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::onSelectionChanged);

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
    double x = QInputDialog::getDouble(this, "Добавить точку", "Введите x:", 0, -1.7E308, 1.7E308, 2, &ok);
    if (!ok) return;
    double y = QInputDialog::getDouble(this, "Добавить точку", "Введите y:", 0, -1.7E308, 1.7E308, 2, &ok);
    if (!ok) return;

    auto dataContainer = customPlot->graph(0)->data();

    // Итерация по контейнеру
    for (auto it = dataContainer->constBegin(); it != dataContainer->constEnd(); ++it) {
        xData.append(it->key);
        yData.append(it->value);
    }

    // Добавление новой точки
    xData.append(x);
    yData.append(y);

    // Установка обновленных данных
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
}


void MainWindow::on_deletePoint_clicked()
{
    xData.pop_back();
    yData.pop_back();
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
}


void MainWindow::on_horizontalAxis_triggered()
{
    bool ok;
    QString horizontalAxisText = QInputDialog::getText(this, "Переименовать горизонтальную ось", "Введите название:", QLineEdit::Normal, customPlot->xAxis->label(), &ok);
    if (!ok) return;
    customPlot->xAxis->setLabel(horizontalAxisText);
    customPlot->replot();
}

void MainWindow::on_verticalAxis_triggered()
{
    bool ok;
    QString verticalAxisText = QInputDialog::getText(this, "Переименовать вертикальную ось", "Введите название:", QLineEdit::Normal, customPlot->yAxis->label(), &ok);
    if (!ok) return;
    customPlot->xAxis->setLabel(verticalAxisText);
    customPlot->replot();
}

void MainWindow::onSelectionChanged()
{
    // Проверяем, выбран ли график
    if (customPlot->graph(0)->selection().isEmpty()) {
        ui->selectedPointX->setText("");
        ui->selectedPointY->setText("");
        return;
    }

    // Получаем данные графика
    auto data = customPlot->graph(0)->data();
    QCPDataSelection selection = customPlot->graph(0)->selection();

    // Получаем индекс выбранной точки
    int selectedIndex = selection.dataRange().begin();

    // Ищем точку по индексу
    auto it = data->constBegin();
    for (int i = 0; i < selectedIndex && it != data->constEnd(); ++i, ++it);

    if (it != data->constEnd()) {
        double x = it->key;
        double y = it->value;
        ui->selectedPointX->setText(QString("%1").arg(x));
        ui->selectedPointY->setText(QString("%1").arg(y));
    }
}

void MainWindow::on_changePoint_clicked()
{
    double newX = ui->selectedPointX->text().toDouble();
    double newY = ui->selectedPointY->text().toDouble();
    auto data = customPlot->graph(0)->data();
    QCPDataSelection selection = customPlot->graph(0)->selection();

    int selectedIndex = selection.dataRange().begin();
    if (selectedIndex >= 0 && selectedIndex < xData.size()) {
            xData[selectedIndex] = newX;
            yData[selectedIndex] = newY;
        }
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
}

