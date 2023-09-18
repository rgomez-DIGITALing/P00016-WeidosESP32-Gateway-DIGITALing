#pragma once
#include <ArduinoModbus.h>
#include "EM750_telemetryDefinition.h"

#define LOG(x) Serial.println(x)
#define LOG2(x) Serial.print(x)

#define ETHERNET_TIMEOUT            60000
#define ETHERNET_RESPONSE_TIMEOUT   4000

#define MODBUS_BEGIN_TRIES      3
#define MODBUS_REQUEST_TRIES    3

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

#define NUM_TOTAL_DATA 60

#define COM_STATE_OK    1
#define COM_STATE_ERROR 0



typedef struct em750Data_struct_t{
  uint8_t comState;
  union{
      float data[NUM_TOTAL_DATA];

      struct{
        float voltageL1N, voltageL2N, voltageL3N;
        float avgVoltageLN;
        float voltageL1L2, voltageL2L3, voltageL1L3, avgVoltageLL;
        float currentL1, currentL2, currentL3;
        float currentNeutral;
        float avgCurrentL;
        float currentTotal;
        float realPowerL1N, realPowerL2N, realPowerL3N;
        float realPowerTotal;
        float apparentPowerL1N, apparentPowerL2N, apparentPowerL3N;
        float apparentPowerTotal;
        float reactivePowerL1N, reactivePowerL2N, reactivePowerL3N;
        float reactivePowerTotal;
        float cosPhiL1, cosPhiL2, cosPhiL3;
        float avgCosPhi, frequency, rotField;
        float realEnergyL1N, realEnergyL2N, realEnergyL3N;
        float realEnergyTotal;
        float apparentEnergyL1, apparentEnergyL2, apparentEnergyL3;
        float apparentEnergyTotal;
        float reactiveEnergyL1, reactiveEnergyL2, reactiveEnergyL3;
        float reactiveEnergyTotal;
        float THDVoltsL1N, THDVoltsL2N, THDVoltsL3N;
        float avgTHDVoltsLN;
        float THDCurrentL1N, THDCurrentL2N, THDCurrentL3N;
        float avgTHDCurrentLN;
        float THDVoltsL1L2, THDVoltsL2L3, THDVoltsL1L3;
        float avgTHDVoltsLL;
        float powerFactorL1N, powerFactorL2N, powerFactorL3N;
        float powerFactorTotal;
      };
    };
} em750Data_t;
  

class EM750{
  public:
    EM750(ModbusTCPClient& client, IPAddress ipAddress);
    
    /**
     * Begin Modbus RTU Client with default Configuration (Baudrate = 9600 and config = SERIAL_8N1).
     *
     *
     * @return 0 on failure, number of values read on success
    */
    int begin();


    void stop();

    /**
     * Update attributes by requesting all registers. 
     *
     *
     * @return 0 on failure, 1 on success
     */
    int update();

    void setId(uint8_t id){ this->id = id; }
    uint8_t getId(){ return id; }
    
    void printData();
    void printDataPack();
    void copyData(float* buffer, int bufferSize);
    void getData(em750Data_t& payload);
    float* getData();
  private:
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the first batch.
     */
    void assignData();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the second batch.
     */
    void assignData2();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the third batch.
     */
    void assignData3();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the second batch.
     */
    void computeData();
    /**
     * Read two bytes from the Modbus Client and join them to cast it into a float variable.
     *  
     * @return Register's data.
     */
    float getNextData();
    
    ModbusTCPClient& _client;
    IPAddress ipAddress;
    uint8_t id;

    uint8_t comState;
    
    union{
      float data[NUM_TOTAL_DATA];

      struct{
        float voltageL1N, voltageL2N, voltageL3N;
        float avgVoltageLN;
        float voltageL1L2, voltageL2L3, voltageL1L3, avgVoltageLL;
        float currentL1, currentL2, currentL3;
        float currentNeutral;
        float avgCurrentL;
        float currentTotal;
        float realPowerL1N, realPowerL2N, realPowerL3N;
        float realPowerTotal;
        float apparentPowerL1N, apparentPowerL2N, apparentPowerL3N;
        float apparentPowerTotal;
        float reactivePowerL1N, reactivePowerL2N, reactivePowerL3N;
        float reactivePowerTotal;
        float cosPhiL1, cosPhiL2, cosPhiL3;
        float avgCosPhi, frequency, rotField;
        float realEnergyL1N, realEnergyL2N, realEnergyL3N;
        float realEnergyTotal;
        float apparentEnergyL1, apparentEnergyL2, apparentEnergyL3;
        float apparentEnergyTotal;
        float reactiveEnergyL1, reactiveEnergyL2, reactiveEnergyL3;
        float reactiveEnergyTotal;
        float THDVoltsL1N, THDVoltsL2N, THDVoltsL3N;
        float avgTHDVoltsLN;
        float THDCurrentL1N, THDCurrentL2N, THDCurrentL3N;
        float avgTHDCurrentLN;
        float THDVoltsL1L2, THDVoltsL2L3, THDVoltsL1L3;
        float avgTHDVoltsLL;
        float powerFactorL1N, powerFactorL2N, powerFactorL3N;
        float powerFactorTotal;
      };
    };
};
