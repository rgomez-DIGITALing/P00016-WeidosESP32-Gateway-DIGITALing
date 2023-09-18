#include "PersistentDataClass.h"

#define WIFI_SSID_SET_FLAG_INDEX                    FIRST_INDEX
#define WIFI_PASS_SET_FLAG_INDEX                    (WIFI_SSID_SET_FLAG_INDEX + FLAG_SIZE)
#define GATEWAY_DEVICE_ID_SET_FLAG_INDEX            (WIFI_PASS_SET_FLAG_INDEX + FLAG_SIZE)
#define SCOPE_ID_SET_FLAG_INDEX                     (GATEWAY_DEVICE_ID_SET_FLAG_INDEX + FLAG_SIZE)


bool PersistentDataClass::isWiFiSSIDSet(){
    bool wifiSsidNotSet = E2PROM.read(WIFI_SSID_SET_FLAG_INDEX);
    return !wifiSsidNotSet;
}

bool PersistentDataClass::isWiFiPassSet(){
    bool wifiPassNotSet = E2PROM.read(WIFI_PASS_SET_FLAG_INDEX);
    return !wifiPassNotSet;
}

bool PersistentDataClass::isScopeIdSet(){
    bool scopeIdNotSet = E2PROM.read(SCOPE_ID_SET_FLAG_INDEX);
    return !scopeIdNotSet;
}


bool PersistentDataClass::begin(){
    E2PROM.begin();

    //WiFiSSID = "";
    //WiFiPass = "";

    if(isWiFiSSIDSet()) restoreWiFiSSID();
    if(isWiFiPassSet()) restoreWiFiPassword();
    if(isScopeIdSet()) restoreScopeId();

    

    return true;

}

void PersistentDataClass::setWiFiSSID(String& ssid){
    ssid.toCharArray(WiFiSSID, WIFI_SSID_SIZE);
    E2PROM.put(WIFI_SSID_INDEX, WiFiSSID);
    E2PROM.write(WIFI_SSID_SET_FLAG_INDEX, 0);
    return;
}

void PersistentDataClass::setWiFiPass(String& pass){
    pass.toCharArray(WiFiPass, WIFI_PASS_SIZE);
    E2PROM.put(WIFI_PASS_INDEX, WiFiPass);
    E2PROM.write(WIFI_PASS_SET_FLAG_INDEX, 0);
    return;
}


void PersistentDataClass::setScopeId(String& scopeId){
    scopeId.toCharArray(this->scopeId, SCOPE_ID_SIZE);
    E2PROM.put(SCOPE_ID_INDEX, this->scopeId);
    E2PROM.write(SCOPE_ID_SET_FLAG_INDEX, 0);
    return;
}

PersistentDataClass PersistentDataModule;