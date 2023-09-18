#include "DataHub.h"
#include "globals.h"
#include "payloadGenerators.h"
#include <LogModule.h>
#include "AzureDevices.h"
//enum DataHubState{
//    GET_DATA_FROM_FIFO,
//    MOVE_MESSAGE,
//    TELEMETRY_SENT,
//    TELEMETRY_SEND_FAILURE,
//
//    SD_SAVE_DATA,
//    SD_INITIALIZE,
//    SD_NOT_INITIALIZED,
//    SD_INITIALIZATION_TIMEOUT,
//    SD_OPEN_FILE,
//    SD_WRITE_FILE,
//    SD_CLOSE_FILE,
//    WAITING
//};



//void DataHub::push(energyMeterPayload_t data){
//    emData.push(data);
//}
//
//template <class T>
//void DataHub<T>::loop(){
//    uint8_t deviceId = 0;
//    switch(state){
//        case GET_DATA_FROM_FIFO:
//            //LOG("case: GET_DATA_FROM_FIFO");
//            if(emData.pop(currentPayload)){
//                state = MOVE_MESSAGE;
//                deviceId = currentPayload.deviceId;
//                LogInfo("Info for device ID: %i poped", deviceId);
//            }
//            break;
//
//        case MOVE_MESSAGE:
//            deviceId = currentPayload.deviceId;
//            LogInfo("Moving Info for device ID: %i", deviceId);
//            if(azureDevices[deviceId]->getStatus() == azure_iot_connected){
//                size_t payload_buffer_length = 0;
//                uint8_t* payload_buffer = azureDevices[deviceId]->getDataBuffer2();
//
//                em750_generete_payload(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
//
//                int error = azureDevices[deviceId]->sendMessage(az_span_create(payload_buffer, payload_buffer_length));
//                if(!error) state = TELEMETRY_SENT;
//                else state = TELEMETRY_SEND_FAILURE;
//            }else state = TELEMETRY_SEND_FAILURE;
//            break;
//
//        case TELEMETRY_SENT:
//            LogInfo("Message successfully sent.");
//            state = GET_DATA_FROM_FIFO;
//            break;
//
//        case TELEMETRY_SEND_FAILURE:
//            LogError("Failed sending telemetry");
//            state = GET_DATA_FROM_FIFO;
//            break;
//
//        default:
//            state = GET_DATA_FROM_FIFO;
//            break;
//    }
//}



DataHub<energyMeterManagerData_t> emDataHub;
DataHub<WeidosManagerData_t> weidosDataHub;