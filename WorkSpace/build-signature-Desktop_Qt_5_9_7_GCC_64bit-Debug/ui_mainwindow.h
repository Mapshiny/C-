/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *expimgButton;
    QPushButton *clearButton;
    QPushButton *pointXYButton;
    QPushButton *openImgButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(860, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        expimgButton = new QPushButton(centralWidget);
        expimgButton->setObjectName(QStringLiteral("expimgButton"));
        expimgButton->setGeometry(QRect(70, 300, 91, 31));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(240, 300, 91, 31));
        pointXYButton = new QPushButton(centralWidget);
        pointXYButton->setObjectName(QStringLiteral("pointXYButton"));
        pointXYButton->setGeometry(QRect(410, 300, 91, 31));
        openImgButton = new QPushButton(centralWidget);
        openImgButton->setObjectName(QStringLiteral("openImgButton"));
        openImgButton->setGeometry(QRect(570, 300, 91, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 860, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        expimgButton->setText(QApplication::translate("MainWindow", "ExpImg", Q_NULLPTR));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        pointXYButton->setText(QApplication::translate("MainWindow", "PointXY", Q_NULLPTR));
        openImgButton->setText(QApplication::translate("MainWindow", "OpenImg", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
