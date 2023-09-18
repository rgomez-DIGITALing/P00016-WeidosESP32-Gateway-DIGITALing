#pragma once
#include "classes/WeidosESP32Class/WeidosESP32Class.h"
//#include "DataHub.h"


enum WeidosState{
  WEIDOS_IDLE,
  WEIDOS_GET_DATA,
};



typedef struct WeidosManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  weidosMetadata_t payload;
} WeidosManagerData_t;


class WeidosManager{
    public:
        WeidosManager(WeidosESP32Class& weido, int deviceId) : weidos(weidos), deviceId(deviceId){}
        //WeidosManager(WeidosESP32Class& weidos, DataHub<WeidosManagerData_t>& dataHub, int deviceId) : weidos(weidos), dataBuffer(dataHub), deviceId(deviceId){}
        void triggerUpdate(){ state = WEIDOS_GET_DATA; }
        WeidosState loop();
    private:
        WeidosESP32Class& weidos;
        WeidosState state = WEIDOS_IDLE;
        int deviceId;
        //DataHub<WeidosManagerData_t>& dataBuffer;
};

extern WeidosManager weidosESP32Manager;