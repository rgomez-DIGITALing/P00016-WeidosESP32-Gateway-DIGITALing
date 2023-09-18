#include "WeidosManager.h"
#include "DataHub.h"
#include <clockModule.h>
#include <LogModule.h>



WeidosState WeidosManager::loop(){
    switch(state){
      case WEIDOS_IDLE:
        break;
      case WEIDOS_GET_DATA:
        weidosMetadata_t metadata = weidos.getMetadata();
        WeidosManagerData_t msg;
        msg.deviceId = deviceId;
        msg.payload = metadata;
        msg.timestamp = systemClock.getEpochTime();
        weidosDataHub.push(msg);
        state = WEIDOS_IDLE;
        break;
    }

    return state;
}



WeidosESP32Class weidosESP32;
WeidosManager weidosESP32Manager(weidosESP32, 0);
//WeidosManager weidosESP32Manager(weidosESP32, weidosDataHub, 0);
