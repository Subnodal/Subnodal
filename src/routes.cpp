#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

#include "routes.h"
#include "main.h"

void routes::init() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(LittleFS, "/pages/index.html", "text/html", false, [](const String& var) -> String {
            if (var == "YEAR") {
                return String(currentTime.tm_year + 1900);
            }

            return emptyString;
        });
    });

    server.serveStatic("/static", LittleFS, "/static");
    server.serveStatic("/media", LittleFS, "/media");
}