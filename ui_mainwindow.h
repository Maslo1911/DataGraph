/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *horizontalAxis;
    QAction *verticalAxis;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exportAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QLineEdit *selectedPointY;
    QLineEdit *selectedPointX;
    QCustomPlot *widget;
    QPushButton *changePoint;
    QPushButton *addPoint;
    QPushButton *deletePoint;
    QLabel *pointLabel;
    QMenuBar *menubar;
    QMenu *mainMenu;
    QMenu *axesMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        horizontalAxis = new QAction(MainWindow);
        horizontalAxis->setObjectName(QString::fromUtf8("horizontalAxis"));
        verticalAxis = new QAction(MainWindow);
        verticalAxis->setObjectName(QString::fromUtf8("verticalAxis"));
        newAction = new QAction(MainWindow);
        newAction->setObjectName(QString::fromUtf8("newAction"));
        openAction = new QAction(MainWindow);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        exportAction = new QAction(MainWindow);
        exportAction->setObjectName(QString::fromUtf8("exportAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        selectedPointY = new QLineEdit(centralwidget);
        selectedPointY->setObjectName(QString::fromUtf8("selectedPointY"));

        gridLayout_3->addWidget(selectedPointY, 2, 1, 1, 1);

        selectedPointX = new QLineEdit(centralwidget);
        selectedPointX->setObjectName(QString::fromUtf8("selectedPointX"));

        gridLayout_3->addWidget(selectedPointX, 2, 2, 1, 1);

        widget = new QCustomPlot(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_3->addWidget(widget, 0, 1, 1, 2);

        changePoint = new QPushButton(centralwidget);
        changePoint->setObjectName(QString::fromUtf8("changePoint"));

        gridLayout_3->addWidget(changePoint, 4, 1, 1, 2);

        addPoint = new QPushButton(centralwidget);
        addPoint->setObjectName(QString::fromUtf8("addPoint"));

        gridLayout_3->addWidget(addPoint, 1, 1, 1, 1);

        deletePoint = new QPushButton(centralwidget);
        deletePoint->setObjectName(QString::fromUtf8("deletePoint"));
        deletePoint->setEnabled(false);

        gridLayout_3->addWidget(deletePoint, 1, 2, 1, 1);

        pointLabel = new QLabel(centralwidget);
        pointLabel->setObjectName(QString::fromUtf8("pointLabel"));

        gridLayout_3->addWidget(pointLabel, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        mainMenu = new QMenu(menubar);
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        axesMenu = new QMenu(menubar);
        axesMenu->setObjectName(QString::fromUtf8("axesMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(mainMenu->menuAction());
        menubar->addAction(axesMenu->menuAction());
        mainMenu->addAction(newAction);
        mainMenu->addAction(openAction);
        mainMenu->addAction(saveAction);
        mainMenu->addAction(exportAction);
        axesMenu->addAction(horizontalAxis);
        axesMenu->addAction(verticalAxis);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DataGraph", nullptr));
        horizontalAxis->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\270\320\274\320\265\320\275\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\263\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\320\270", nullptr));
        verticalAxis->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\270\320\274\320\265\320\275\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\262\320\265\321\200\321\202\320\270\320\272\320\260\320\273\320\270", nullptr));
        newAction->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        openAction->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        saveAction->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        exportAction->setText(QApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", nullptr));
        changePoint->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        addPoint->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\321\203", nullptr));
        deletePoint->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\321\203", nullptr));
        pointLabel->setText(QApplication::translate("MainWindow", "\320\242\320\276\321\207\320\272\320\260", nullptr));
        mainMenu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        axesMenu->setTitle(QApplication::translate("MainWindow", "\320\236\321\201\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
