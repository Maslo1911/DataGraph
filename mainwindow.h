#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
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

private slots:
    void onSelectionChanged();

    void on_addPoint_clicked();

    void on_deletePoint_clicked();

    void on_horizontalAxis_triggered();

    void on_verticalAxis_triggered();

    void on_changePoint_clicked();

    void exportGraph();

    void on_saveAction_triggered();

    void on_openAction_triggered();

private:
    QCPScatterStyle myScatter;
    QCustomPlot *customPlot;
    Ui::MainWindow *ui;
    int selectedIndex;
    void saveData(const QString &fileName, const QVector<double> &xData, const QVector<double> &yData);
    void loadData(const QString &fileName);
};
#endif // MAINWINDOW_H
