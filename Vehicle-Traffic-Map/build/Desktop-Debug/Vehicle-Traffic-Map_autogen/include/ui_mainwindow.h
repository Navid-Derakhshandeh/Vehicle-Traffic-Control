/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "marble/MarbleWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    Marble::MarbleWidget *widget;
    QLabel *labelVideo;
    QLabel *labelCount;
    QLineEdit *IplineEdit;
    QPushButton *opencap;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1427, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new Marble::MarbleWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 761, 481));
        labelVideo = new QLabel(centralwidget);
        labelVideo->setObjectName("labelVideo");
        labelVideo->setGeometry(QRect(800, 10, 591, 451));
        labelCount = new QLabel(centralwidget);
        labelCount->setObjectName("labelCount");
        labelCount->setGeometry(QRect(800, 510, 101, 41));
        IplineEdit = new QLineEdit(centralwidget);
        IplineEdit->setObjectName("IplineEdit");
        IplineEdit->setGeometry(QRect(960, 520, 261, 26));
        opencap = new QPushButton(centralwidget);
        opencap->setObjectName("opencap");
        opencap->setGeometry(QRect(1250, 520, 131, 26));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1427, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelVideo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelCount->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        opencap->setText(QCoreApplication::translate("MainWindow", "Open Capture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
