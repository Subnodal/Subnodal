#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

#include "routes.h"
#include "main.h"

void routes::init() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(LittleFS, "/pages/index.html", "text/html", false, [](const String& var) {
            return emptyString;
        });
    });
}