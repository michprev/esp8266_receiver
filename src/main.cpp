#include <Arduino.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

WiFiUDP udp;

void setup() {
    WiFi.softAP("DRON_WIFI", "123456789");
    udp.begin(4789);
    Serial.begin(115200);
}

void crc16(uint16_t& crc, uint8_t value) {
    const uint16_t CRC_POLYNOME = 0x1021;

    crc = crc ^ (int16_t)value << 8;

    for (uint8_t i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ CRC_POLYNOME;
        else
            crc = (crc << 1);
    }
}
uint8_t data[50];

void loop() {
    if (udp.parsePacket()) {
        int size = udp.available();

        udp.read(data, size);
        udp.flush();
        Serial.write(data, size);
    }

    /*if (millis() - time >= 10) {
        time = millis();

        uint8_t data[13];
        data[0] = 0xA8;
        data[1] = 0x01;
        data[2] = 0x04;
        data[3] = 0x3B; // roll high
        data[4] = 0x60; // roll low
        data[5] = 0x22; // pitch high
        data[6] = 0x60; // pitch low
        data[7] = 0x3B; // throttle high
        data[8] = 0x00; // throttle low
        data[9] = 0x2E; // yaw high
        data[10] = 0x00; // yaw low

        uint16_t crc = 0;

        for (int i = 0; i < 11; i++)
            crc16(crc, data[i]);

        data[11] = crc >> 8;
        data[12] = crc & 0xFF;

        Serial.write(data, 13);
    }*/
}