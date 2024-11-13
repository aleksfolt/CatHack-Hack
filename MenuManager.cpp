#include "MenuManager.h"

void MenuManager::init(WiFiManager* wifiManagerPtr) {
    wifiManager = wifiManagerPtr;
    drawMenu();
}

void MenuManager::update() {
    handleInput();
}

void MenuManager::drawMenu() {
    M5.Lcd.fillScreen(ORANGE_COLOR);
    M5.Lcd.setTextSize(3);

    int yOffset = 10;
    int lineHeight = 45;
    const char** currentMenuOptions;
    int currentMenuLength;

    if (inWifiSubMenu) {
        currentMenuOptions = wifiSubMenuOptions;
        currentMenuLength = wifiSubMenuLength;
    } else {
        currentMenuOptions = mainMenuOptions;
        currentMenuLength = mainMenuLength;
    }

    for (int i = 0; i < visibleOptions && (scrollIndex + i) < currentMenuLength; i++) {
        int optionIndex = scrollIndex + i;
        drawOption(currentMenuOptions[optionIndex], optionIndex, yOffset + i * lineHeight);
    }
}

void MenuManager::drawOption(const char* text, int optionIndex, int y) {
    int x = 20;
    bool isSelected = (selectedOption == optionIndex);

    if (isSelected) {
        M5.Lcd.drawRoundRect(2, y - 10, M5.Lcd.width() - 6, 40, 8, TFT_BLACK);
    }
    M5.Lcd.setTextColor(TFT_BLACK, ORANGE_COLOR);
    M5.Lcd.drawString(text, x, y);
}

void MenuManager::handleInput() {
    if (M5.BtnB.wasPressed()) { 
        scrollDown();
        drawMenu();
    }

    if (M5.BtnPWR.wasPressed()) { 
        scrollUp();
        drawMenu();
    }

    if (M5.BtnA.wasPressed() && !inWifiSubMenu && selectedOption == 2) {
        inWifiSubMenu = true;
        scrollIndex = 0;
        selectedOption = 0;
        wifiManager->scanNetworks();
        drawMenu();
    }

    if (M5.BtnA.wasPressed() && inWifiSubMenu) { 
        wifiManager->sendDeauthPacket();
    }
}

void MenuManager::scrollDown() {
    const int currentMenuLength = inWifiSubMenu ? wifiSubMenuLength : mainMenuLength;
    selectedOption++;
    if (selectedOption >= currentMenuLength) {
        selectedOption = 0;
        scrollIndex = 0;
    } else if (selectedOption >= scrollIndex + visibleOptions) {
        scrollIndex++;
    }
}

void MenuManager::scrollUp() {
    const int currentMenuLength = inWifiSubMenu ? wifiSubMenuLength : mainMenuLength;
    selectedOption--;
    if (selectedOption < 0) {
        selectedOption = currentMenuLength - 1;
        scrollIndex = max(0, currentMenuLength - visibleOptions);
    } else if (selectedOption < scrollIndex) {
        scrollIndex--;
    }
}
