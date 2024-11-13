#include <M5StickCPlus2.h>
#include "MenuManager.h"
#include "WiFiManager.h"

MenuManager menuManager;
WiFiManager wifiManager;

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(ORANGE_COLOR);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    menuManager.init(&wifiManager);
}

void loop() {
    M5.update();
    menuManager.update();
}
