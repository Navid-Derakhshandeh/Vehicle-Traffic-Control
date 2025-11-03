#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void readFrame();
    void readframe2();
    void on_checkBox_toggled(bool checked);

    void on_opencap_clicked();
    void insertData();
private:
    Ui::MainWindow *ui;
    QPoint latLonToTile(double lat, double lon, int zoom);
    void downloadTile(int zoom, int x, int y);
    void downloadTileRegion(double lat, double lon, int radius, int zoomStart = 13, int zoomEnd = 15);
    cv::VideoCapture cap;
    //cv::VideoCapture cap1;
    QTimer timer;
    QTimer insertTimer;
    //QTimer timer2;
    QSqlDatabase db;
    cv::CascadeClassifier carCascade;
    int carCount = 0;
    //int carCount1 = 0;
};
#endif // MAINWINDOW_H
