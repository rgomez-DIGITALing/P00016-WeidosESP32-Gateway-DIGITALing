#include "EM750.h"
#include <ArduinoModbus.h>
#include "DebugLogger.h"


#define MODBUS_ADDRESS      1
#define MODBUS_TIMEOUT      5000


#define REG_ADDRESS         19000
#define NUM_REGISTERS       122
#define NUM_DATA            NUM_REGISTERS/2

#define REG_ADDRESS2         828
#define NUM_REGISTERS2       20
#define NUM_DATA2            NUM_REGISTERS2/2

#define REG_ADDRESS3         10085
#define NUM_REGISTERS3       2
#define NUM_DATA3            NUM_REGISTERS3/2

EM750::EM750(ModbusTCPClient& client, IPAddress ipAddress) : _client(client), ipAddress(ipAddress){}

int EM750::begin(){
    _client.setTimeout(MODBUS_TIMEOUT);
    return _client.begin(ipAddress);
}

void EM750::stop(){
  _client.stop();
  return;
}

int EM750::update(){
    comState = COM_STATE_OK;

    int response = _client.requestFrom(MODBUS_ADDRESS, INPUT_REGISTERS, REG_ADDRESS, NUM_REGISTERS);
    if(!response)
    {   
        comState = COM_STATE_ERROR;
        return 0;
    }
    assignData();


    response = _client.requestFrom(MODBUS_ADDRESS, INPUT_REGISTERS, REG_ADDRESS2, NUM_REGISTERS2);
    if(!response)
    {
        comState = COM_STATE_ERROR;
        return 0;
    }
    assignData2();
    

    response = _client.requestFrom(MODBUS_ADDRESS, INPUT_REGISTERS, REG_ADDRESS3, NUM_REGISTERS3);  
    if(!response)
    {
        comState = COM_STATE_ERROR;
        return 0;
    }
    assignData3();

    computeData();
    
    return 1;
}


void EM750::printData(){
  LOG2("voltageL1N: ");
  LOG(voltageL1N);
  LOG2("voltageL2N: ");
  LOG(voltageL2N);
  LOG2("voltageL3N: ");
  LOG(voltageL3N);
  LOG2("currentL1: ");
  LOG(currentL1);
  LOG2("currentL2: ");
  LOG(currentL2);
  LOG2("currentL3: ");
  LOG(currentL3);
  /*LOG2("realPowerL1N: ");
  LOG(realPowerL1N);
  LOG2("realPowerL2N: ");
  LOG(realPowerL2N);
  LOG2("realPowerL3N: ");
  LOG(realPowerL3N);
  LOG2("apparentPowerL1N: ");
  LOG(apparentPowerL1N);
  LOG2("apparentPowerL2N: ");
  LOG(apparentPowerL2N);
  LOG2("apparentPowerL3N: ");
  LOG(apparentPowerL3N);
  LOG2("reactivePowerL1N: ");
  LOG(reactivePowerL1N);
  LOG2("reactivePowerL2N: ");
  LOG(reactivePowerL2N);
  LOG2("reactivePowerL3N: ");
  LOG(reactivePowerL3N);
  LOG2("powerFactorL1N: ");
  LOG(powerFactorL1N);
  LOG2("powerFactorL2N: ");
  LOG(powerFactorL2N);
  LOG2("powerFactorL3N: ");
  LOG(powerFactorL3N);
  LOG2("cosPhiL1: ");
  LOG(cosPhiL1);
  LOG2("cosPhiL2: ");
  LOG(cosPhiL2);
  LOG2("cosPhiL3: ");
  LOG(cosPhiL3);
  LOG2("avgVoltageLN: ");
  LOG(avgVoltageLN);
  LOG2("avgCurrentL: ");
  LOG(avgCurrentL);
  LOG2("currentTotal: ");
  LOG(currentTotal);
  LOG2("realPowerTotal: ");
  LOG(realPowerTotal);
  LOG2("apparentPowerTotal: ");
  LOG(apparentPowerTotal);
  LOG2("reactivePowerTotal: ");
  LOG(reactivePowerTotal);
  LOG2("powerFactorTotal: ");
  LOG(powerFactorTotal);
  LOG2("avgCosPhi: ");
  LOG(avgCosPhi);
  LOG2("frequency: ");
  LOG(frequency);
  LOG2("apparentEnergyTotal: ");
  LOG(apparentEnergyTotal);
  LOG2("voltageL1L2: ");
  LOG(voltageL1L2);
  LOG2("voltageL2L3: ");
  LOG(voltageL2L3);
  LOG2("voltageL1L3: ");
  LOG(voltageL1L3);
  LOG2("avgVoltageLL : ");
  LOG(avgVoltageLL );
  LOG2("currentNeutral: ");
  LOG(currentNeutral);
  LOG2("THDVoltsL1N: ");
  LOG(THDVoltsL1N);
  LOG2("THDVoltsL2N: ");
  LOG(THDVoltsL2N);
  LOG2("THDVoltsL3N: ");
  LOG(THDVoltsL3N);
  LOG2("THDCurrentL1N: ");
  LOG(THDCurrentL1N);
  LOG2("THDCurrentL2N: ");
  LOG(THDCurrentL2N);
  LOG2("THDCurrentL3N: ");
  LOG(THDCurrentL3N);
  LOG2("avgTHDVoltsLN: ");
  LOG(avgTHDVoltsLN);
  LOG2("avgTHDCurrentLN: ");
  LOG(avgTHDCurrentLN);
  LOG2("THDVoltsL1L2 : ");
  LOG(THDVoltsL1L2 );
  LOG2("THDVoltsL2L3 : ");
  LOG(THDVoltsL2L3 );
  LOG2("THDVoltsL1L3 : ");
  LOG(THDVoltsL1L3 );
  LOG2("avgTHDVoltsLL: ");
  LOG(avgTHDVoltsLL);
  LOG2("realEnergyTotal: ");
  LOG(realEnergyTotal);
  LOG2("reactiveEnergyTotal: ");
  LOG(reactiveEnergyTotal);
  //LOG2("realEnergyL1: ");
  //LOG(realEnergyL1);
  //LOG2("realEnergyL2: ");
  //LOG(realEnergyL2);
  //LOG2("realEnergyL3: ");
  //LOG(realEnergyL3);
  LOG2("reactiveEnergyL1: ");
  LOG(reactiveEnergyL1);
  LOG2("reactiveEnergyL2: ");
  LOG(reactiveEnergyL2);
  LOG2("reactiveEnergyL3: ");
  LOG(reactiveEnergyL3);
  LOG2("apparentEnergyL1: ");
  LOG(apparentEnergyL1);
  LOG2("apparentEnergyL2: ");
  LOG(apparentEnergyL2);
  LOG2("apparentEnergyL3: ");
  LOG(apparentEnergyL3);
  LOG2("rotField: ");
  LOG(rotField);*/


/*
  LOG("Union, data:");
  for(int i=0; i<NUM_TOTAL_DATA; i++){
    LOG(data[i]);
  }
*/
  return;
}

void EM750::copyData(float* buffer, int bufferSize){
  int length = (bufferSize<NUM_TOTAL_DATA) ? bufferSize : NUM_TOTAL_DATA;


  for(int i=0; i<length; i++){
    buffer[i] = data[i];
  }
  return;
};

void EM750::getData(em750Data_t& payload){
  payload.comState = comState;
  copyData(payload.data, NUM_TOTAL_DATA);
  return;
}

float* EM750::getData(){
  return data;
};

void EM750::assignData(){
    voltageL1N = getNextData();
    voltageL2N = getNextData();
    voltageL3N = getNextData();
    voltageL1L2 = getNextData();
    voltageL2L3 = getNextData();
    voltageL1L3 = getNextData(); 
    currentL1 = getNextData();
    currentL2 = getNextData();
    currentL3 = getNextData();
    currentTotal = getNextData();
    realPowerL1N = getNextData();
    realPowerL2N = getNextData();
    realPowerL3N = getNextData();
    realPowerTotal = getNextData();
    apparentPowerL1N = getNextData();
    apparentPowerL2N = getNextData();
    apparentPowerL3N = getNextData();
    apparentPowerTotal = getNextData();
    reactivePowerL1N = getNextData();
    reactivePowerL2N = getNextData();
    reactivePowerL3N = getNextData();
    reactivePowerTotal = getNextData();
    cosPhiL1 = getNextData();
    cosPhiL2 = getNextData();
    cosPhiL3 = getNextData();
    frequency = getNextData();
    rotField = getNextData();
    realEnergyL1N = getNextData()/1000.0f;
    realEnergyL2N = getNextData()/1000.0f;
    realEnergyL3N = getNextData()/1000.0f;
    realEnergyTotal = getNextData()/1000.0f;
    getNextData();       //realEnergyConsL1 deleted variable
    getNextData();       //realEnergyConsL2 deleted variable
    getNextData();       //realEnergyConsL3 deleted variable
    getNextData();      //realEnergyConsTotal deleted variable
    getNextData();      //realEnergyDelivL1 deleted variable     
    getNextData();      //realEnergyDelivL2 deleted variable
    getNextData();      //realEnergyDelivL3 deleted variable
    getNextData();      //realEnergyDelivTotal deleted variable
    apparentEnergyL1 = getNextData()/1000.0f;
    apparentEnergyL2 = getNextData()/1000.0f;
    apparentEnergyL3 = getNextData()/1000.0f;
    apparentEnergyTotal = getNextData()/1000.0f;
    reactiveEnergyL1 = getNextData()/1000.0f;
    reactiveEnergyL2 = getNextData()/1000.0f;
    reactiveEnergyL3 = getNextData()/1000.0f;
    reactiveEnergyTotal = getNextData()/1000.0f;
    getNextData();      //reactiveEnergyIndL1 deleted variable
    getNextData();      //reactiveEnergyIndL2 deleted variable   
    getNextData();      //reactiveEnergyIndL3 deleted variable    
    getNextData();      //reactiveEnergyIndTotal deleted variable
    getNextData();      //reactiveEnergyCapL1 deleted variable
    getNextData();      //reactiveEnergyCapL2 deleted variable
    getNextData();      //reactiveEnergyCapL3 deleted variable
    getNextData();      //reactiveEnergyCapTotal deleted variable
    THDVoltsL1N = getNextData();
    THDVoltsL2N = getNextData();
    THDVoltsL3N = getNextData();
    THDCurrentL1N = getNextData();
    THDCurrentL2N = getNextData();
    THDCurrentL3N = getNextData();
}

void EM750::assignData2(){
    powerFactorL1N = getNextData();
    powerFactorL2N = getNextData();
    powerFactorL3N = getNextData();
    powerFactorTotal = getNextData();
    THDVoltsL1L2 = getNextData();
    THDVoltsL2L3 = getNextData();
    THDVoltsL1L3 = getNextData();
}

void EM750::assignData3(){
    currentNeutral = getNextData();
}

void EM750::computeData(){
    avgVoltageLN = (voltageL1N + voltageL2N + voltageL3N)/3.0f;
    avgVoltageLL = (voltageL1L2 + voltageL2L3 + voltageL1L3)/3.0f;
    avgCurrentL = (currentL1 + currentL2 + currentL3)/3.0f;

    if(apparentPowerTotal != 0) avgCosPhi = realPowerTotal/apparentPowerTotal;
    else avgCosPhi = -1;
    if(isnan(avgCosPhi)) avgCosPhi = -1;  //Check if, after all, it is still NaN

    avgTHDVoltsLN = (THDVoltsL1N + THDVoltsL2N + THDVoltsL3N)/3.0f;
    avgTHDCurrentLN = (THDCurrentL1N + THDCurrentL2N + THDCurrentL3N)/3.0f;
    avgTHDVoltsLL = (THDVoltsL1L2 + THDVoltsL2L3 + THDVoltsL1L3)/3.0f;
}

float EM750::getNextData(){
    long msb = _client.read();
    long lsb =  _client.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData; 
    return data;
};
