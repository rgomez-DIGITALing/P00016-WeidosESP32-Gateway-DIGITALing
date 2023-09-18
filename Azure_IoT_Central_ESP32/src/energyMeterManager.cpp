//#include "tasks.h"
#include "energyMeterManager.h"
#include "DataHub.h"
#include <Ethernet.h>
#include <LogModule.h>
#include <clockModule.h>


static EthernetClient ethernetClientModbus(7);
static ModbusTCPClient modbusTCPClient(ethernetClientModbus);

IPAddress ipAddress1(10, 88, 47, 242);        //Transelevador 1
EM750 transelevador1EM(modbusTCPClient, ipAddress1);

IPAddress ipAddress2(10, 88, 47, 243);        //Transelevador 2
EM750 transelevador2EM(modbusTCPClient, ipAddress2);

IPAddress ipAddress3(10, 88, 47, 244);        //Transelevador 3
EM750 transelevador3EM(modbusTCPClient, ipAddress3);

IPAddress ipAddress4(10, 88, 47, 222);        //Modula 4
EM750 modula4EM(modbusTCPClient, ipAddress4);

IPAddress ipAddress5(10, 88, 47, 223);        //Modula 11
EM750 modula11EM(modbusTCPClient, ipAddress5);


EnergyMeterManager modula4(modula4EM, 1, 5);
EnergyMeterManager modula11(modula11EM, 2, 5);
EnergyMeterManager transelevador1(transelevador1EM, 3, 5);
EnergyMeterManager transelevador2(transelevador2EM, 4, 5);
EnergyMeterManager transelevador3(transelevador3EM, 5, 5);





EnergyMeterUpdateState EnergyMeterManager::loop(){
    switch(state){
      case ENERGY_METER_IDLE:
        break;
      case UPDATE_ENERGY_METER:
        //state = ENERGY_METER_UPDATED;
        if(!em750.begin()){
          state = ENERGY_METER_UPDATE_FAILED;
          em750.stop();
          LogError("Modbus Client for device ID %i could not begin.", deviceId);  
          break;
        }

        if(em750.update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_UPDATE_FAILED;
        
        em750.stop();
        break;
      
      case ENERGY_METER_UPDATE_FAILED:
        numTries++;
        if(numTries>maxTries){
          numTries = 0;
          state = END_TASK;
          LogError("Energy meter update failed.");
        }else{
          state = UPDATE_ENERGY_METER;
          LogError("Retrying (%i/%i)", numTries, maxTries);
        }
        break;
      case ENERGY_METER_UPDATED:
        
        //em750.printData();
        //Serial.println();
        LogInfo("Energy Meter updated: %i", deviceId);
        state = PASS_MESSAGE;
        break;
      case PASS_MESSAGE:
        energyMeterManagerData_t payload;
        payload.deviceId = deviceId;
        payload.timestamp = systemClock.getEpochTime();
        em750.getData(payload.data);
        LogInfo("Pushing data for device ID: %i", deviceId);
        emDataHub.push(payload);
        state = END_TASK;
        break;
      case END_TASK:
        state = ENERGY_METER_IDLE;
        //em750.stop();
        break;
    }

    return state;
}
