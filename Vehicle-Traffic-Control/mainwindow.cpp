#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QWebChannel>
#include "jsbridge.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <cmath>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Setup SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");
    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS entries (label TEXT, value1 INTEGER, value2 INTEGER, value3 INTEGER)");
    }

    // Start periodic insertion
    connect(&insertTimer, &QTimer::timeout, this, &MainWindow::insertData);
    insertTimer.start(10000); // every 10 seconds


    ui->webView->page()->settings()->setAttribute(
        QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);

    ui->webView->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/map.html"));
    auto *bridge = new JSBridge(this);
    auto *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("qtBridge"), bridge);
    ui->webView->page()->setWebChannel(channel);
    connect(bridge, &JSBridge::coordinatesReceived, this, [=](double lat, double lon) {
        ui->latEdit->setText(QString::number(lat, 'f', 6));
        ui->lonEdit->setText(QString::number(lon, 'f', 6));
    });
    ui->latEdit->setText("57.022800");
    ui->lonEdit->setText("9.903089");
    bridge->sendCoordinates(57.0228004, 9.9030888);

    carCascade.load("cars.xml");

    //cap1.open(""); //http://IP-Address/mjpg/video.mjpg
    connect(&timer, &QTimer::timeout, this, &MainWindow::readFrame);
    //connect(&timer2, &QTimer::timeout, this, &MainWindow::readframe2);
    timer.start(30);
    //timer2.start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
    cap.release();
    //cap1.release();

}
/*void MainWindow::readframe2()
{
    cv::Mat frame;
    if (!cap1.read(frame)) return;

    std::vector<cv::Rect> cars;
    carCascade.detectMultiScale(frame, cars, 1.2, 1);

    for (const auto& rect : cars) {
        cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 2);
    }

    carCount1 += cars.size();
    ui->labelcount2->setText(QString::number(carCount1));

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->labelvideo2->setPixmap(QPixmap::fromImage(img));
}*/
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

void MainWindow::on_checkBox_toggled(bool checked)
{

          ui->webView->page()->runJavaScript(QString("toggleOffline(%1);").arg(checked ? "true" : "false"));

        /*if (!checked) {
            // Online mode: download missing tiles from OpenStreetMap
            downloadTileRegion(57.0228004, 9.9030888, 2); // radius 2 tiles around location
        }*/
}

/*void MainWindow::downloadTile(int zoom, int x, int y) {
    QString folder = QString("%1/tiles/%2/%3").arg(QCoreApplication::applicationDirPath()).arg(zoom).arg(x);
    QDir().mkpath(folder);
    QString filePath = QString("%1/%2.png").arg(folder).arg(y);
    if (QFile::exists(filePath)) return;

    QUrl url(QString("https://tile.openstreetmap.org/%1/%2/%3.png").arg(zoom).arg(x).arg(y));
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, [reply, filePath]() {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        }
        reply->deleteLater();
    });
}
void MainWindow::downloadTileRegion(double lat, double lon, int radius, int zoomStart, int zoomEnd) {
    for (int z = zoomStart; z <= zoomEnd; ++z) {
        QPoint center = latLonToTile(lat, lon, z);
        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                downloadTile(z, center.x() + dx, center.y() + dy);
            }
        }
    }
}*/

QPoint MainWindow::latLonToTile(double lat, double lon, int zoom) {
    int x = static_cast<int>((lon + 180.0) / 360.0 * (1 << zoom));
    int y = static_cast<int>((1 - log(tan(lat * M_PI / 180.0) + 1 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0 * (1 << zoom));
    return QPoint(x, y);
}

void MainWindow::on_opencap_clicked()
{
    QString ip = ui->iplineEdit->text(); // e.g., "192.168.1.10"
    QString url = "http://" + ip + "/mjpg/video.mjpg";
    cap.open(url.toStdString());
}
void MainWindow::insertData() {
    QString label = ui->labelCount->text(); // car count as string
    double lat = ui->latEdit->text().toDouble(); // latitude as float
    double lon = ui->lonEdit->text().toDouble(); // longitude as float
    QString street = ui->streetlineEdit->text(); //Street Name as string

    QSqlQuery query;
    query.prepare("INSERT INTO entries (label, value1, value2, value3) VALUES (?, ?, ?, ?)");
    query.addBindValue(label);
    query.addBindValue(lat);
    query.addBindValue(lon);
    query.addBindValue(street);
    if (!query.exec()) {
        qDebug() << "Insert error:" << query.lastError().text();
    }
}


