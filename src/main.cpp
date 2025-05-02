#include <Arduino.h>
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WireGuard-ESP32.h>

static AsyncWebServer server(80);
static WireGuard wg;

IPAddress localIp(10, 200, 200, 2);

void setup() {
    Serial.begin(115200);

    Serial.println(
        "   ##                #                        #         ###    ##   \r\n"
        "  #                  #                        #           #      #  \r\n"
        "  #     ####  #   #  ####   ####    ###    ####   ####    #      #  \r\n"
        " #     #      #   #  #   #  #   #  #   #  #   #  #   #    #       # \r\n"
        "  #     ###   #   #  #   #  #   #  #   #  #   #  #   #    #      #  \r\n"
        "  #        #  #  ##  #   #  #   #  #   #  #   #  #  ##    #      #  \r\n"
        "   ##  ####    ## #  ####   #   #   ###    ####   ## #  #####  ##   \r\n"
    );
}

void loop() {
    
}