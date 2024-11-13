#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include "esp_wifi.h"

class WiFiManager {
public:
    void scanNetworks();
    void sendDeauthPacket();
};

#endif // WIFIMANAGER_H
