#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <M5StickCPlus2.h>
#include "WiFiManager.h"

#define ORANGE_COLOR 0xFD20
#define visibleOptions 3 

class MenuManager {
public:
    void init(WiFiManager* wifiManager);
    void update();

private:
    int selectedOption = 0;
    int scrollIndex = 0;   
    bool inWifiSubMenu = false, inWifiScanMenu = false, deauthing = false, paused = false;
    WiFiManager* wifiManager;

    const char* mainMenuOptions[5] = {"Infrared", "SubGhz", "Wifi", "Bluetooth", "Settings"};
    const int mainMenuLength = sizeof(mainMenuOptions) / sizeof(mainMenuOptions[0]);
    const char* wifiSubMenuOptions[1] = {"Deauth Wifi"};
    const int wifiSubMenuLength = sizeof(wifiSubMenuOptions) / sizeof(wifiSubMenuOptions[0]);

    void drawMenu();
    void drawOption(const char* text, int optionIndex, int y);
    void handleInput();
    void scrollUp();
    void scrollDown();
};

#endif // MENUMANAGER_H
