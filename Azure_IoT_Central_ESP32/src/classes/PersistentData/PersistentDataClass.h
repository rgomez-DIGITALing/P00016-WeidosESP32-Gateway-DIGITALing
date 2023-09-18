#pragma once
#include <Arduino.h>
#include <E2PROM.h>
#include "eepromIndex.h"

//static const int WIFI_SSID_SIZE = 32;
//static const int WIFI_PASS_SIZE = 63;
//static const int SCOPE_ID_SIZE = 20;
//static const int WEIDOS_MODEL_ID_SIZE = 63;
//static const int GATEWAY_DEVICE_ID_SIZE = 20;
//gatewayDeviceId, GATEWAY_DEVICE_ID_SIZE




class PersistentDataClass{
    public:
        bool begin();
        
        bool isWiFiSSIDSet();
        bool isWiFiPassSet();
        bool isScopeIdSet();
        
        char* getWiFiSSID(){ return WiFiSSID; };
        char* getWiFiPass(){ return WiFiPass; };
        char* getScopeId(){ return scopeId; };
        
        void setWiFiSSID(String& ssid);
        void setWiFiPass(String& pass);
        void setScopeId(String& scopeId);
        
    private:
        void restoreWiFiSSID(){ E2PROM.get(WIFI_SSID_INDEX, WiFiSSID); };
        void restoreWiFiPassword(){ E2PROM.get(WIFI_PASS_INDEX, WiFiPass); }
        void restoreScopeId(){ E2PROM.get(SCOPE_ID_INDEX, scopeId); }
        
        char WiFiSSID[WIFI_SSID_SIZE] = "";
        char WiFiPass[WIFI_PASS_SIZE] = "";
        char scopeId[SCOPE_ID_SIZE] = "";

//Azure parameters
        //char gatewayDeviceId[GATEWAY_DEVICE_ID_SIZE];
        //char scopeId[SCOPE_ID_SIZE];
        
        //char groupPrimaryKey[20];
        //char weidosModelId[20];
        //char em3BasicLineId[20];
        //char em1BasicLineId[20];
};


extern PersistentDataClass PersistentDataModule;