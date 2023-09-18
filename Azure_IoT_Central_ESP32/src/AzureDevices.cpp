#include "AzureDevices.h"

#include <Ethernet.h>
#include <ArduinoBearSSL.h>

EthernetClient ethernetClient0(1);
EthernetClient ethernetClient1(2);
EthernetClient ethernetClient2(3);
EthernetClient ethernetClient3(4);
EthernetClient ethernetClient4(5);
EthernetClient ethernetClient5(6);



AzureIoTDevice* Azure0;
AzureIoTDevice* Azure1;
AzureIoTDevice* Azure2;
AzureIoTDevice* Azure3;
AzureIoTDevice* Azure4;
AzureIoTDevice* Azure5;


#define MQTT_CLIENT_BUFFER_SIZE 4096

void createObjects(){
    BearSSLClient* bear_ssl_client0 = new BearSSLClient(ethernetClient0);
    MQTTClient* mqttClient0 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure0 = new AzureIoTDevice(mqttClient0, bear_ssl_client0);

    BearSSLClient* bear_ssl_client1 = new BearSSLClient(ethernetClient1);
    MQTTClient* mqttClient1 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure1 = new AzureIoTDevice(mqttClient1, bear_ssl_client1);

    BearSSLClient* bear_ssl_client2 = new BearSSLClient(ethernetClient2);
    MQTTClient* mqttClient2 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure2 = new AzureIoTDevice(mqttClient2, bear_ssl_client2);

    BearSSLClient* bear_ssl_client3 = new BearSSLClient(ethernetClient3);
    MQTTClient* mqttClient3 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure3 = new AzureIoTDevice(mqttClient3, bear_ssl_client3);

    BearSSLClient* bear_ssl_client4 = new BearSSLClient(ethernetClient4);
    MQTTClient* mqttClient4 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure4 = new AzureIoTDevice(mqttClient4, bear_ssl_client4);

    BearSSLClient* bear_ssl_client5 = new BearSSLClient(ethernetClient5);
    MQTTClient* mqttClient5 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure5 = new AzureIoTDevice(mqttClient5, bear_ssl_client5);
}


AzureIoTDevice* azureDevices[6];

void fillArray(){
    azureDevices[0] = Azure0;
    azureDevices[1] = Azure1;
    azureDevices[2] = Azure2;
    azureDevices[3] = Azure3;
    azureDevices[4] = Azure4;
    azureDevices[5] = Azure5;
    return;
}
