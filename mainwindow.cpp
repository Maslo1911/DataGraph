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

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(customPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::onSelectionChanged);
    connect(ui->exportAction, &QAction::triggered, this, &MainWindow::exportGraph);

    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exportGraph()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить график", "", "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf);;BMP Files (*.bmp)");
        if (fileName.isEmpty()) return;

        if (fileName.endsWith(".png", Qt::CaseInsensitive)) {
            customPlot->savePng(fileName, 0, 0, 2.0);
        } else if (fileName.endsWith(".jpg", Qt::CaseInsensitive)) {
            customPlot->saveJpg(fileName, 0, 0, 2.0, 85);
        } else if (fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
            customPlot->savePdf(fileName);
        } else if (fileName.endsWith(".bmp", Qt::CaseInsensitive)) {
            customPlot->saveBmp(fileName);
        } else {
            fileName += ".png";
            customPlot->savePng(fileName, 0, 0, 2.0);
        }
}

void MainWindow::on_addPoint_clicked()
{
    bool ok;
    double x = QInputDialog::getDouble(this, "Добавить точку", "Введите x:", 0, -1.7E308, 1.7E308, 2, &ok);
    if (!ok) return;
    double y = QInputDialog::getDouble(this, "Добавить точку", "Введите y:", 0, -1.7E308, 1.7E308, 2, &ok);
    if (!ok) return;
    auto dataContainer = customPlot->graph(0)->data();
    QVector<double> xData, yData;
    for (auto it = dataContainer->constBegin(); it != dataContainer->constEnd(); ++it) {
        xData.append(it->key);
        yData.append(it->value);
    }
    xData.append(x);
    yData.append(y);
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
    isChanged = true;
}


void MainWindow::on_deletePoint_clicked()
{
    if (customPlot->graph(0)->selection().isEmpty())
        return;
    auto dataContainer = customPlot->graph(0)->data();
    QCPDataSelection selection = customPlot->graph(0)->selection();
    selectedIndex = selection.dataRange().begin();
    auto it = dataContainer->constBegin();
    for (int i = 0; i < selectedIndex && it != dataContainer->constEnd(); ++i, ++it);
    if (it != dataContainer->constEnd()) {
        customPlot->graph(0)->data()->remove(it->key);
    }
    customPlot->replot();
    isChanged = true;
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
    customPlot->yAxis->setLabel(verticalAxisText);
    customPlot->replot();
}

void MainWindow::onSelectionChanged()
{
    if (customPlot->graph(0)->selection().isEmpty()) {
        ui->selectedPointX->setText("");
        ui->selectedPointY->setText("");
        ui->deletePoint->setEnabled(false);
        return;
    }
    ui->deletePoint->setEnabled(true);
    auto dataContainer = customPlot->graph(0)->data();
    QCPDataSelection selection = customPlot->graph(0)->selection();
    selectedIndex = selection.dataRange().begin();
    auto it = dataContainer->constBegin();
    for (int i = 0; i < selectedIndex && it != dataContainer->constEnd(); ++i, ++it);

    if (it != dataContainer->constEnd()) {
        double x = it->value;
        double y = it->key;
        ui->selectedPointX->setText(QString("%1").arg(x));
        ui->selectedPointY->setText(QString("%1").arg(y));
    }
}

void MainWindow::on_changePoint_clicked()
{
    double newX = ui->selectedPointX->text().toDouble();
    double newY = ui->selectedPointY->text().toDouble();
    QCPDataSelection selection = customPlot->graph(0)->selection();
    auto dataContainer = customPlot->graph(0)->data();
    QVector<double> xData, yData;
    for (auto it = dataContainer->constBegin(); it != dataContainer->constEnd(); ++it) {
        xData.append(it->value);
        yData.append(it->key);
    }

    int selectedIndex = selection.dataRange().begin();
    if (selectedIndex >= 0 && selectedIndex < xData.size()) {
            xData[selectedIndex] = newX;
            yData[selectedIndex] = newY;
        }
    customPlot->graph(0)->data().clear();
    customPlot->graph(0)->setData(xData, yData);
    customPlot->replot();
    isChanged = true;
}

void MainWindow::on_saveAction_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить проект", "", "CSV Files (*.csv);;Text Files (*.txt)");
    if (fileName.isEmpty()) return;
    auto dataContainer = customPlot->graph(0)->data();
    QVector<double> xData, yData;
    for (auto it = dataContainer->constBegin(); it != dataContainer->constEnd(); ++it) {
        xData.append(it->key);
        yData.append(it->value);
    }
    saveData(fileName, xData, yData);
}

void MainWindow::on_openAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить проект", "", "CSV Files (*.csv);;Text Files (*.txt)");
    if (fileName.isEmpty()) return;
    loadData(fileName);
}

void MainWindow::loadData(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QVector<double> xData, yData;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList values = line.split(",");
            if (values.size() == 2) {
                xData.append(values[0].toDouble());
                yData.append(values[1].toDouble());
            }
        }
        file.close();
        customPlot->graph(0)->setData(xData, yData);
        customPlot->replot();
    }
}

void MainWindow::saveData(const QString &fileName, const QVector<double> &xData, const QVector<double> &yData)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < xData.size(); ++i) {
            out << xData[i] << "," << yData[i] << "\n";
        }
        file.close();
    }
    isChanged = false;
}

void MainWindow::on_newAction_triggered()
{
    if (isChanged)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Документ был изменён.");
        msgBox.setInformativeText("Хотите сохранить изменения?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            on_saveAction_triggered();
            customPlot->graph(0)->data().data()->clear();
            customPlot->replot();
            break;
        case QMessageBox::Discard:
            customPlot->graph(0)->data().data()->clear();
            customPlot->replot();
            break;
        case QMessageBox::Cancel:

            break;
        default:
            on_saveAction_triggered();
            customPlot->graph(0)->data().data()->clear();
            customPlot->replot();
            break;
        }
    }
    else {
        customPlot->graph(0)->data().data()->clear();
        customPlot->replot();
    }
}

