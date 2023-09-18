#pragma once

#include <ESPAsyncWebServer.h>

class WebServerClass{
    public:
        bool setAP();
        void setServer();

    private:
        int a = 55;
};


extern WebServerClass WebServer;
