#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <marble/MarbleWidget.h>
#include <marble/MarbleGlobal.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataCoordinates.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/MarbleModel.h>
#include <QFile>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configureMarble();
    carCascade.load("cars.xml");
    //cap.open("http:///mjpg/video.mjpg"); //http://IP-Address/mjpg/video.mjpg
    connect(&timer, &QTimer::timeout, this, &MainWindow::readFrame);
    timer.start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
    cap.release();

}
void MainWindow::configureMarble() {
    Marble::MarbleWidget *mw = ui->widget;

    mw->setProjection(Marble::Spherical);
    mw->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");

    // Load UAV KML directly
    mw->model()->addGeoDataFile(":/data/camera.kml");
    mw->setShowOverviewMap(false);
    mw->setShowCompass(true);
    mw->setShowClouds(false);
    mw->setShowScaleBar(true);

    mw->setZoom(1200);
}

void MainWindow::addCamera() {
    Marble::MarbleWidget *mw = ui->widget;

    auto *doc = new Marble::GeoDataDocument;
    auto *placemark = new Marble::GeoDataPlacemark("camera");


    placemark->setCoordinate(Marble::GeoDataCoordinates(
        9.903089,          // longitude
        57.022800,        // latitude
        1000.0,    // altitude in meters
        Marble::GeoDataCoordinates::Degree
        ));
    placemark->setStyleUrl("#cameraStyle");

    doc->append(placemark);

    mw->model()->treeModel()->addDocument(doc);
}
void MainWindow::readFrame() {
    cv::Mat frame;
    if (!cap.read(frame)) return;

    std::vector<cv::Rect> cars;
    carCascade.detectMultiScale(frame, cars, 1.2, 1);

    for (const auto& rect : cars) {
        cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 2);
    }

    carCount += cars.size();

    ui->labelCount->setText(QString::number(carCount));

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->labelVideo->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::on_opencap_clicked()
{
    QString ip = ui->IplineEdit->text(); // e.g., "192.168.1.10"
    QString url = "http://" + ip + "/mjpg/video.mjpg";
    cap.open(url.toStdString());
}
