#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once


#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void readFrame();
    void on_opencap_clicked();
private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    QTimer timer;
    cv::CascadeClassifier carCascade;
    int carCount = 0;
    void configureMarble();
    void addCamera();
};
#endif // MAINWINDOW_H
