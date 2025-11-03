#include "jsbridge.h"

void JSBridge::sendCoordinates(double lat, double lon) {
    emit coordinatesReceived(lat, lon);
}
