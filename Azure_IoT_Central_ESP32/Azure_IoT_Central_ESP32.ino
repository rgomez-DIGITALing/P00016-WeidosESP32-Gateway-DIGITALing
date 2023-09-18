// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/*
 * This is an Arduino-based Azure IoT Central sample specific for Espressif ESP32.
 * It uses our Azure Embedded SDK for C to help interact with Azure IoT.
 * For reference, please visit https://github.com/azure/azure-sdk-for-c and
 * https://azureiotcentral.com/.
 *
 * To connect and work with Azure IoT Hub you need an MQTT client, connecting, subscribing
 * and publishing to specific topics to use the messaging features of the hub.
 * Our azure-sdk-for-c is an MQTT client support library, helping composing and parsing the
 * MQTT topic names and messages exchanged with the Azure IoT Hub.
 *
 * The additional layers in this sketch provide a structured use of azure-sdk-for-c and
 * the MQTT client of your choice to perform all the steps needed to connect and interact with
 * Azure IoT Central.
 *
 * AzureIoT.cpp contains a state machine that implements those steps, plus abstractions to simplify
 * its overall use. Besides the basic configuration needed to access the Azure IoT services,
 * all that is needed is to provide the functions required by that layer to:
 * - Interact with your MQTT client,
 * - Perform data manipulations (HMAC SHA256 encryption, Base64 decoding and encoding),
 * - Receive the callbacks for Plug and Play properties and commands.
 *
 * Azure_IoT_PnP_Template.cpp contains the actual implementation of the IoT Plug and Play template
 * specific for the Espressif ESP32 board.
 *
 * To properly connect to your Azure IoT services, please fill the information in the
 * `iot_configs.h` file.
 */

/* --- Dependencies --- */
// C99 libraries
#include <cstdarg>
#include <cstdlib>
#include <string.h>
#include <time.h>

// For hmac SHA256 encryption
#include <mbedtls/base64.h>
#include <mbedtls/md.h>
#include <mbedtls/sha256.h>

#define ARDUINO
// Libraries for MQTT client and WiFi connection
//#include <WiFi.h>
#include <ArduinoBearSSL.h>
//#include <ArduinoMqttClient.h>
#include <MQTTClient.h>


// For hmac SHA256 encryption
#include <ECCX08.h>


#include <Ethernet.h>

// Azure IoT SDK for C includes
#include <az_core.h>
#include <az_iot.h>
#include <azure_ca.h>

// Additional sample headers
#include <clockModule.h>
#include <LogModule.h>
#include <EthernetModule.h>
#include "src/classes/AzureIoTClass/AzureIoTClass.h"
//#include "./tasks/energyMeterTask.h"
#include "src/AzureDevices.h"
#include "src/energyMeterManager.h"
#include "src/WeidosManager.h"
#include "src/DataHub.h"
#include "src/classes/PersistentData/PersistentDataClass.h"
#include "src/classes/WebServer/WebServer.h"
#include "src/classes/WeidosESP32Class/WeidosESP32Class.h"

//#include "Azure_IoT_PnP_Template.h"

#include "src/iot_configs.h"
#include "src/DataHub.h"

#include <ArduinoBearSSL.h>
#include "src/classes/PersistentData/PersistentDataClass.h"
#include "src/payloadGenerators.h"

/* --- Sample-specific Settings --- */



/* --- Time and NTP Settings --- */
/*
#define NTP_SERVERS "pool.ntp.org", "time.nist.gov"

#define PST_TIME_ZONE -8
#define PST_TIME_ZONE_DAYLIGHT_SAVINGS_DIFF 1

#define GMT_OFFSET_SECS (PST_TIME_ZONE * 3600)
#define GMT_OFFSET_SECS_DST ((PST_TIME_ZONE + PST_TIME_ZONE_DAYLIGHT_SAVINGS_DIFF) * 3600)

#define UNIX_TIME_NOV_13_2017 1510592825
#define UNIX_EPOCH_START_YEAR 1900
*/


/* --- Handling iot_config.h Settings --- */
//static const char* wifi_ssid = IOT_CONFIG_WIFI_SSID;
//static const char* wifi_password = IOT_CONFIG_WIFI_PASSWORD;

/* --- Function Declarations --- */
//static void sync_device_clock_with_ntp_server();
//static void connect_to_wifi();
//static void on_message_received(int message_size);
//static esp_err_t esp_mqtt_event_handler(esp_mqtt_event_handle_t event);



/* --- Sample variables --- */
//static azure_iot_config_t azure_iot_config;
//static azure_iot_t azure_iot;
//static WiFiClient wifi_client;
//static BearSSLClient bear_ssl_client(wifi_client);

//static MQTTClient& arduino_mqtt_client = mqttClient;

//static char mqtt_broker_uri[128];



//#define MQTT_PROTOCOL_PREFIX "mqtts://"




void loopEnergyMeters();


/*
 * See the documentation of `get_time_t` in AzureIoT.h for details.
 */
static unsigned long get_time()
{
    return systemClock.getEpochTime();
}

//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x7A, 0x5B};      //User defined MAC
WeidosESP32Class WeidosESP32;

char emModelId[60] = "dtmi:conexiones:EnergyMeter_6bm;1";
char gwModelId[60] = "dtmi:conexionesSmartFactory:gateway_62;1";
char gatewayId[50] = IOT_CONFIG_DEVICE_GATEWAY_ID;
/* --- Arduino setup and loop Functions --- */
void setup()
{
  Serial.begin(SERIAL_LOGGER_BAUD_RATE);
  set_logging_function(logging_function);
  Serial.println("Welcome!");
  
  EthernetModule.init();

  //Ethernet.init(ETHERNET_CS);
  //while(!Ethernet.begin(mac)){
  //  Serial.print("e");
  //  delay(1000);
  //}
  //Serial.println();
  //Serial.print("Local IP: ");
  //Serial.println(Ethernet.localIP());

  //connect_to_wifi();
  systemClock.begin();
  ArduinoBearSSL.onGetTime(get_time); // Required for server trusted root validation.

  //azure_pnp_init();
  Serial.println("Let's persist: ");
  PersistentDataModule.begin();
  Serial.println("Persisten Module has begun!");
  Serial.println(PersistentDataModule.getWiFiSSID());
  Serial.println(PersistentDataModule.getScopeId());

  //WebServer.setAP();
  //WebServer.setServer();
  //while(1){}
  
  //char* scopeId = PersistentDataModule.getScopeId();
  char* scopeId = DPS_ID_SCOPE;
  createObjects();

  Azure0->usingSasToken(IOT_CONFIG_DEVICE_GATEWAY_KEY);
  Azure0->setDeviceId(IOT_CONFIG_DEVICE_GATEWAY_ID);
  Azure0->setDpsScopeId(scopeId);
  Azure0->setModelId(gwModelId);
  Azure0->init();
  
  Azure1->usingSasToken(IOT_CONFIG_DEVICE_1_KEY);
  Azure1->setDeviceId(IOT_CONFIG_DEVICE_1_ID);
  Azure1->setDpsScopeId(scopeId);
  Azure1->setGatewayId(gatewayId);
  Azure1->setModelId(emModelId);
  Azure1->init();

  Azure2->usingSasToken(IOT_CONFIG_DEVICE_2_KEY);
  Azure2->setDeviceId(IOT_CONFIG_DEVICE_2_ID);
  Azure2->setDpsScopeId(scopeId);
  Azure2->setGatewayId(gatewayId);
  Azure2->setModelId(emModelId);
  Azure2->init();

  Azure3->usingSasToken(IOT_CONFIG_DEVICE_3_KEY);
  Azure3->setDeviceId(IOT_CONFIG_DEVICE_3_ID);
  Azure3->setDpsScopeId(scopeId);
  Azure3->setGatewayId(gatewayId);
  Azure3->setModelId(emModelId);
  Azure3->init();


  Azure4->usingSasToken(IOT_CONFIG_DEVICE_4_KEY);
  Azure4->setDeviceId(IOT_CONFIG_DEVICE_4_ID);
  Azure4->setDpsScopeId(scopeId);
  Azure4->setGatewayId(gatewayId);
  Azure4->setModelId(emModelId);
  Azure4->init();


  Azure5->usingSasToken(IOT_CONFIG_DEVICE_5_KEY);
  Azure5->setDeviceId(IOT_CONFIG_DEVICE_5_ID);
  Azure5->setDpsScopeId(scopeId);
  Azure5->setGatewayId(gatewayId);
  Azure5->setModelId(emModelId);
  Azure5->init();


  fillArray();

  weidosMetadata_t metadata = WeidosESP32.getMetadata();
  metadata.printMetadata();
  emDataHub.setPayloadGenerator(em750_generete_payload);
  weidosDataHub.setPayloadGenerator(weidosESP32_generete_payload);
  LogInfo("Let's go to the looP function");
}

unsigned long prevTime = 0;
static const unsigned long DELTA_TIME = 60*1000;

unsigned long prevTime2 = 0;
static const unsigned long DELTA_TIME2 = 2*60*1000;

unsigned long prevTime3 = 0;
static const unsigned long DELTA_TIME3 = 10*1000;


bool  networkUp = false;
bool  clockRunning = false;
int prevLinkStatus = LinkON;

void loop()
{
  EthernetModule.loop();
  networkUp = EthernetModule.isNetworkUp();
  systemClock.loop(networkUp);
  clockRunning = systemClock.clockRunning();
  
  if(!networkUp){
    Azure0->stop();
    Azure1->stop();
    Azure2->stop();
    Azure3->stop();
    Azure4->stop();
    Azure5->stop();
  }





  if(networkUp && clockRunning){
    if(millis()-prevTime>DELTA_TIME){
      transelevador1.triggerUpdate();
      transelevador2.triggerUpdate();
      transelevador3.triggerUpdate();
      modula4.triggerUpdate();
      modula11.triggerUpdate();
      weidosESP32Manager.triggerUpdate();
      prevTime = millis();
    }
  }



  if(networkUp){
    weidosESP32Manager.loop();
    loopEnergyMeters();
  }


  if(networkUp){
    emDataHub.loop();
    weidosDataHub.loop();
  }


  if(networkUp){
    Azure0->loop();
    Azure1->loop();
    Azure2->loop();
    Azure3->loop();
    Azure4->loop();
    Azure5->loop();
  }

  Azure0->statusChange();
  Azure1->statusChange();
  Azure2->statusChange();
  Azure3->statusChange();
  Azure4->statusChange();
  Azure5->statusChange();

  if(millis()-prevTime3>DELTA_TIME3){
    prevTime3 = millis();
    LogInfo("Azure0 state: %i", Azure0->getStatus());
    LogInfo("Azure1 state: %i", Azure1->getStatus());
    LogInfo("Azure2 state: %i", Azure2->getStatus());
    LogInfo("Azure3 state: %i", Azure3->getStatus());
    LogInfo("Azure4 state: %i", Azure4->getStatus());
    LogInfo("Azure5 state: %i", Azure5->getStatus());
  }

  if(millis()-prevTime2>DELTA_TIME2){
    prevTime2 = millis();
    LogInfo("Link status: %i", Ethernet.linkStatus());  
  }
}


//This function is needed so there is only one energy meter looping when not in idle state.
//Since they all share the same Modbus TCP Client, they can not work at the same time.
void loopEnergyMeters(){
  if(transelevador1.loop() != ENERGY_METER_IDLE) return;
  if(transelevador2.loop() != ENERGY_METER_IDLE) return;
  if(transelevador3.loop() != ENERGY_METER_IDLE) return;
  if(modula4.loop() != ENERGY_METER_IDLE) return;
  if(modula11.loop() != ENERGY_METER_IDLE) return;
  return;
}
