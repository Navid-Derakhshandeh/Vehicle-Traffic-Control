#ifndef JSBRIDGE_H
#define JSBRIDGE_H
#pragma once
#include <QObject>

class JSBridge : public QObject {
    Q_OBJECT
public:
    explicit JSBridge(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void sendCoordinates(double lat, double lon);

signals:
    void coordinatesReceived(double lat, double lon);
};
#endif // JSBRIDGE_H
