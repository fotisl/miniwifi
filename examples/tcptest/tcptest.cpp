#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MiniWiFi.h"

#define WIFI_SSID   "MYWIFI"
#define WIFI_PASS   "MyPassword123"

SoftwareSerial espSerial(2, 3);
MiniWiFi wifi(&espSerial);

void setup()
{
    espSerial.begin(9600);
    Serial.begin(9600);

    wifi.reset();
    wifi.connectWiFi((char *) WIFI_SSID, (char *) WIFI_PASS);

    while(wifi.getStatus() != WIFI_CONNECTED)
        delay(100);
}

void loop()
{
    int s;
    char buf[255];
    String request = "GET / HTTP/1.1\r\nHost: api.ipify.org\r\n\r\n";

    s = wifi.connectTCP((char *) "api.ipify.org", 80);
    if(s == -1) {
        delay(1000);
        return;
    }

    wifi.writeTCP(s, (uint8_t *) request.c_str(), request.length());
    wifi.readTCP(s, (uint8_t *) buf, sizeof(buf));
    wifi.closeTCP(s);

    Serial.println(buf);

    delay(1000);
}
