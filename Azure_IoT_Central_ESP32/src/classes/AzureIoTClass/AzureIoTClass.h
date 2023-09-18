#pragma once

//#define MQTT_HAS_FUNCTIONAL false
#include "AzureIoT_definitions.h"
#include <MQTTClient.h>
#include <Client.h>
#include "../../iot_configs.h"

enum securityType_t{
    UNDEFINED,
    SAS_TOKEN,
    X509_CERTIFICATE
};

#define AZ_IOT_DATA_BUFFER_SIZE 4096
#define DATA_BUFFER_SIZE 4096


class AzureIoTDevice{
    public:
        AzureIoTDevice() : mqttClient(nullptr), client(nullptr){};
        AzureIoTDevice(MQTTClient& mqttClient, Client& client) : mqttClient(&mqttClient), client(&client){};
        AzureIoTDevice(MQTTClient& mqttClient, Client* client) : mqttClient(&mqttClient), client(client){};
        AzureIoTDevice(MQTTClient* mqttClient, Client* client) : mqttClient(mqttClient), client(client){};
        void loop();
        void stop();
        bool isProvisioned(){ return provisioned; }
        void init();
        bool sendDeviceInfo(){ return deviceInfoSent; }
        void isDeviceInfoSent(bool deviceInfoSent){ this->deviceInfoSent = deviceInfoSent; }
        azure_iot_status_t getStatus(){ return azure_iot_get_status(&azure_iot); }
        void setDeviceId(char* deviceId);
        void setDpsScopeId(char* scopeId);
        void setModelId(char* modelId);
        void usingCertificate(char* certificate, char* privateKey);
        void usingSasToken(char* key);
        int sendMessage(az_span message);
        uint8_t* getDataBuffer(){ return az_iot_data_buffer; }
        uint8_t* getDataBuffer2(){ return data_buffer; }
        void setClients(MQTTClient& mqttClient, Client& client){ this->mqttClient = &mqttClient; this->client = &client;}
        void setGatewayId(char* gatewayId){ this->gatewayId = gatewayId; }
        void statusChange();

    private:
        azure_iot_status_t prevState = azure_iot_connected;
        bool provisioned = false;
        azure_iot_t azure_iot;
        azure_iot_config_t azure_iot_config;
        uint8_t az_iot_data_buffer[AZ_IOT_DATA_BUFFER_SIZE];
        uint8_t data_buffer[DATA_BUFFER_SIZE];
        Client* client;
        MQTTClient* mqttClient;
        bool deviceInfoSent = false;
        securityType_t securityType;
        char* gatewayId = nullptr;
        unsigned long mqttLastLoopTime = 0;

        int mqtt_client_init(mqtt_client_config_t* mqtt_client_config);
        int mqtt_client_subscribe(az_span topic, mqtt_qos_t qos);
        int mqtt_client_publish(mqtt_message_t* mqtt_message);
        int mqtt_client_deinit();
        void onMessageReceived(String &topic, String &payload);
        void azure_iot_init(azure_iot_t* azure_iot, azure_iot_config_t* azure_iot_config);
        int azure_iot_start(azure_iot_t* azure_iot);
        int azure_iot_stop(azure_iot_t* azure_iot);
        azure_iot_status_t azure_iot_get_status(azure_iot_t* azure_iot);
        void azure_iot_do_work(azure_iot_t* azure_iot);
        int azure_iot_send_telemetry(azure_iot_t* azure_iot, az_span message);
        int azure_iot_send_properties_update(azure_iot_t* azure_iot, uint32_t request_id, az_span message);
        int azure_iot_send_command_response(
            azure_iot_t* azure_iot,
            az_span request_id,
            uint16_t response_status,
            az_span payload);
        int azure_iot_mqtt_client_connected(azure_iot_t* azure_iot);
        int azure_iot_mqtt_client_disconnected(azure_iot_t* azure_iot);
        int azure_iot_mqtt_client_subscribe_completed(azure_iot_t* azure_iot, int packet_id);
        int azure_iot_mqtt_client_publish_completed(azure_iot_t* azure_iot, int packet_id);
        int azure_iot_mqtt_client_message_received(azure_iot_t* azure_iot, mqtt_message_t* mqtt_message);
        az_span generate_dps_register_custom_property(az_span model_id, az_span data_buffer, az_span* remainder);




        unsigned long lastTime;
        int mqttClientId = 23;
        
};