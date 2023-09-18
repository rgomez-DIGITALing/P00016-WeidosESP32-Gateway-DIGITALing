#include "WebServer.h"
#include <Arduino.h>
#include <WiFi.h>


#include "../PersistentData/PersistentDataClass.h"


#include "./html/pages.h"
#include <E2PROM.h>
#include "config.h"

#pragma once
#include <Arduino.h>


AsyncWebServer server(80);
//SSID and password for the Access Point generated WiFi for user configuration inputs.
static const IPAddress AP_IP(192, 168, 6, 1);
static const IPAddress AP_MASK(255, 255, 255, 0);

#define CONFIG_AP_SSID "WeidosESP32WiFi"
#define CONFIG_AP_PASS "Detmold1"           //Last char is a one (do not confuse with an L)

const char *AP_SSID = CONFIG_AP_SSID;
const char *AP_PASSWORD = CONFIG_AP_PASS;  



bool WebServerClass::setAP(){
  if(WiFi.softAP(AP_SSID, AP_PASSWORD)){
    WiFi.softAPConfig(AP_IP, INADDR_NONE, AP_MASK);
    Serial.print("Access Point set with SSID: ");
    Serial.print(AP_SSID);
    Serial.print(" and password: ");
    Serial.println(AP_PASSWORD);

    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
    return true;
  }else{
    Serial.println("Access Point has not been set.");
    return false;
  }
}





//Simulated values for the current WiFi parameters. 
//In the final application, those will be variables that are linked to the actual state.
//String currentSSID = "IoT_Hub";
//String currentPass = "Detmold";
String wifiProcessor(const String& var){
  if(var == "SSID"){
    char* ssid = PersistentDataModule.getWiFiSSID();
    return String(ssid);
  }
  
  if(var == "password"){
    char* pass = PersistentDataModule.getWiFiPass();
    return String(pass);
  }
  
  return String();
}



//Simulated values for the current values of Azure configuration. 
//In the final application, those will be variables that are linked to the actual state.
 String gatewayDeviceId = "sd8qf79asd";
 String scopeId = "qw9742asd";
 String groupPrimaryKey = "QW=as7891gasd41312qasG";
 String weidosModelId = "fs874sdasd";
 String em3BasicLineId = "4k71561bnm";
 String em1BasicLineId = "cl471asd3";
String azureProcessor(const String& var){
  if(var == "deviceId"){} return gatewayDeviceId;
  if(var == "scopeId") return scopeId;
  if(var == "groupPrimaryKey") return groupPrimaryKey;
  if(var == "weidosModelId") return weidosModelId;
  if(var == "em3BasicLineId") return em3BasicLineId;
  if(var == "em1BasicLineId") return em1BasicLineId;
  return String();
}


//Simulated values for the current values of the slected Energy Meter. 
//In the final application, those will be variables that are linked to the actual state.
 String currentEM1 = "EM110";
 String currentEM2 = "None";
 String currentEM3 = "EM110";
 String currentEM4 = "None";
 String currentEM5 = "EM122";
String peripheralsProcessor(const String& var){
  if(var == "EM1") return currentEM1;
  if(var == "EM2") return currentEM2;
  if(var == "EM3") return currentEM3;
  if(var == "EM4") return currentEM4;
  if(var == "EM5") return currentEM5;

  return String();
}



bool isValid = true;

void WebServerClass::setServer()
{
  //* Set each endpoint and its callback function---

    server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", wifiForm, wifiProcessor);
    });



    server.on("/wifi", HTTP_POST, [](AsyncWebServerRequest *request)
    {
      int params = request->params();
      Serial.print("Number of parameters: ");
      Serial.println(params);

      if(params == 2){
        String ssid = request->getParam(0)->value();
        Serial.print("SSID: ");
        Serial.println(ssid);

        if(isValid){
          PersistentDataModule.setWiFiSSID(ssid);
        }

        String password = request->getParam(1)->value();
        Serial.print("Password: ");
        Serial.println(password);

        if(isValid){
          PersistentDataModule.setWiFiPass(password);
        }
      }

      request->send_P(200, "text/html", "WiFi Posted!");
    });



    server.on("/azure", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", azureForm, azureProcessor);
    });



    server.on("/azure", HTTP_POST, [](AsyncWebServerRequest *request)
    {
      int params = request->params();
      Serial.print("Number of parameters: ");
      Serial.println(params);

      if(params == 6){
        //String inputDeviceId = request->getParam(0)->value();
        //Serial.print("Device ID: ");
        //Serial.println(inputDeviceId);
        //if(isValid){
        //  inputDeviceId.toCharArray(gatewayDeviceId, GATEWAY_DEVICE_ID_SIZE);
        //  E2PROM.put(GATEWAY_DEVICE_ID_INDEX, gatewayDeviceId);
        //  E2PROM.write(GATEWAY_DEVICE_ID_SET_FLAG_INDEX, 0);
        //}

        String inputScopeId = request->getParam(1)->value();
        Serial.print("Scope ID: ");
        Serial.println(inputScopeId);
        if(isValid){
          PersistentDataModule.setScopeId(inputScopeId);
          //inputScopeId.toCharArray(scopeId, SCOPE_ID_SIZE);
          //E2PROM.put(SCOPE_ID_INDEX, scopeId);
          //E2PROM.write(SCOPE_ID_SET_FLAG_INDEX, 0);
        }

        //String inputGroupPrimaryKey = request->getParam(2)->value();
        //Serial.print("Group Primary Key: ");
        //Serial.println(inputGroupPrimaryKey);
        //if(isValid){
        //  inputGroupPrimaryKey.toCharArray(groupPrimaryKey, GROUP_PRIMARY_KEY_SIZE);
        //  E2PROM.put(GROUP_PRIMARY_KEY_INDEX, groupPrimaryKey);
        //  E2PROM.write(GROUP_PRIMARY_KEY_SET_FLAG_INDEX, 0);
        //}
//
        //String inputWeidosModelId = request->getParam(3)->value();
        //Serial.print("WeidOS-ESP32-Wifi Model ID: ");
        //Serial.println(inputWeidosModelId);
        //if(isValid){
        //  inputWeidosModelId.toCharArray(weidosModelId, WEIDOS_MODEL_ID_SIZE);
        //  E2PROM.put(WEIDOS_MODEL_ID_INDEX, weidosModelId);
        //  E2PROM.write(WEIDOS_MODEL_ID_SET_FLAG_INDEX, 0);
        //}
//
        //String inputEm3BasicLine = request->getParam(4)->value();
        //Serial.print("EM3Ph Basic Line Serial Model ID: ");
        //Serial.println(inputEm3BasicLine);
        //if(isValid){
        //  inputEm3BasicLine.toCharArray(em3BasicLineId, EM_3PH_BASIC_LINE_MODEL_ID_SIZE);
        //  E2PROM.put(EM_3PH_BASIC_LINE_MODEL_ID_INDEX, em3BasicLineId);
        //  E2PROM.write(EM_3PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX, 0);
        //}
//
        //String inputEm1BasicLine = request->getParam(5)->value();
        //Serial.print("EM1Ph Basic Line Serial Model ID: ");
        //Serial.println(inputEm1BasicLine);
        //if(isValid){
        //  inputEm1BasicLine.toCharArray(em1BasicLineId, EM_1PH_BASIC_LINE_MODEL_ID_SIZE);
        //  E2PROM.put(EM_1PH_BASIC_LINE_MODEL_ID_INDEX, em1BasicLineId);
        //  E2PROM.write(EM_1PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX, 0);
        //}
      }
      

      request->send_P(200, "text/html", "Azure parameters Posted!");
    });


/*
    server.on("/energy-meters", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", energyMetersForm, peripheralsProcessor);
    });



    server.on("/energy-meters", HTTP_POST, [](AsyncWebServerRequest *request)
    {
      int params = request->params();
      Serial.print("Number of parameters: ");
      Serial.println(params);

      if(params == 15){
        String EM1 = request->getParam(0)->value();
        Serial.print("EM1: ");
        Serial.println(EM1);
        String CT1Primary = request->getParam(1)->value();
        Serial.print("CT1Primary: ");
        Serial.println(CT1Primary);
        String CT1Secondary = request->getParam(2)->value();
        Serial.print("CT1Secondary: ");
        Serial.println(CT1Secondary);


        String EM2 = request->getParam(3)->value();
        Serial.print("EM2: ");
        Serial.println(EM2);
        String CT2Primary = request->getParam(4)->value();
        Serial.print("CT2Primary: ");
        Serial.println(CT2Primary);
        String CT2Secondary = request->getParam(5)->value();
        Serial.print("CT2Secondary: ");
        Serial.println(CT2Secondary);


        String EM3 = request->getParam(6)->value();
        Serial.print("EM3: ");
        Serial.println(EM3);
        String CT3Primary = request->getParam(7)->value();
        Serial.print("CT3Primary: ");
        Serial.println(CT3Primary);
        String CT3Secondary = request->getParam(8)->value();
        Serial.print("CT3Secondary: ");
        Serial.println(CT3Secondary);

        String EM4 = request->getParam(9)->value();
        Serial.print("EM4: ");
        Serial.println(EM4);
        String CT4Primary = request->getParam(10)->value();
        Serial.print("CT4Primary: ");
        Serial.println(CT4Primary);
        String CT4Secondary = request->getParam(11)->value();
        Serial.print("CT4Secondary: ");
        Serial.println(CT4Secondary);


        String EM5 = request->getParam(12)->value();
        Serial.print("EM5: ");
        Serial.println(EM5);
        String CT5Primary = request->getParam(13)->value();
        Serial.print("CT5Primary: ");
        Serial.println(CT5Primary);
        String CT5Secondary = request->getParam(14)->value();
        Serial.print("CT5Secondary: ");
        Serial.println(CT5Secondary);
      }
      
      request->send_P(200, "text/html", "Energy Meters posted!");
    });


    server.on("/flow-meters", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", "Flow Meters!");
    });



    server.on("/flow-meters", HTTP_POST, [](AsyncWebServerRequest *request)
    {      
      request->send_P(200, "text/html", "Flow Meters posted!");
    });


    server.on("/pulse-meters", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", "Pulse Meters!");
    });



    server.on("/pulse-meters", HTTP_POST, [](AsyncWebServerRequest *request)
    {      
      request->send_P(200, "text/html", "Pulse Meters posted!");
    });
*/

    server.onNotFound([](AsyncWebServerRequest *request)
    {
      request->send(404, "text/html", homePage);
    });



  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", homePage);
    });

  server.begin();
}




WebServerClass WebServer;
