#include <Arduino.h>
#include <LittleFS.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WireGuard-ESP32.h>

#include "config.h"
#include "routes.h"

AsyncWebServer server(80);
WireGuard wg;
struct tm currentTime;

IPAddress localIp(10, 200, 200, 2);

#define DIE while (true) {}

void setup() {
    Serial.begin(115200);

    delay(2000);

    Serial.println(
        "   ##                #                        #         ###    ##   \r\n"
        "  #                  #                        #           #      #  \r\n"
        "  #     ####  #   #  ####   ####    ###    ####  ####     #      #  \r\n"
        " #     #      #   #  #   #  #   #  #   #  #   #      #    #       # \r\n"
        "  #     ###   #   #  #   #  #   #  #   #  #   #   ####    #      #  \r\n"
        "  #        #  #  ##  #   #  #   #  #   #  #   #  #   #    #      #  \r\n"
        "   ##  ####    ## #  ####   #   #   ###    ####   ####  #####  ##   \r\n"
    );

    if (!LittleFS.begin(true)) {
        Serial.println("Error: Cannot initialise filesystem"); DIE;
    }

    Serial.println("Connecting to Wi-Fi network: " WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    switch (WiFi.status()) {
        case WL_NO_SHIELD: Serial.println("Error: No Wi-Fi hardware"); DIE;
        case WL_CONNECT_FAILED: Serial.println("Error: Failed to connect to Wi-Fi"); DIE;
        default: break;
    }

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.printf("Still connecting... %d\r\n", WiFi.status());
    }

    Serial.printf("Wi-Fi connected successfully - IP address: %s\r\n", WiFi.localIP().toString());

    configTime(0, 0, "pool.ntp.org");

    Serial.println("Configured NTP servers");

    Serial.println("Syncing time...");

    while (time(nullptr) <= 86400000) {
        delay(1000);
    }

    getLocalTime(&currentTime);
    Serial.println(&currentTime, "Time synced: %A %d %B %Y %H:%M:%S");

    #ifdef ENDPOINT_ADDRESS
        if (wg.begin(
            IPAddress(LOCAL_IP),
            CLIENT_PRIVATE_KEY,
            ENDPOINT_ADDRESS,
            ENDPOINT_PUBLIC_KEY,
            ENDPOINT_PORT
        )) {
            Serial.println("Connected via WireGuard");
        } else {
            Serial.println("Failed to connect via WireGuard");
        }
    #endif

    routes::init();

    server.begin();

    Serial.println("Server started");
}

void loop() {
    delay(5000);

    getLocalTime(&currentTime);
}