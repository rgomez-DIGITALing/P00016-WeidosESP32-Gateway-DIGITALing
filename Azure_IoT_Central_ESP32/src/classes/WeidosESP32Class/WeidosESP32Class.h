#pragma once

#include "WeidosESP32Class_telemetryDefinition.h"
#include <ESP.h>

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();


typedef struct weidosMetadata_struct_t{
    uint32_t freeHeap;
    uint32_t heapSize;
    uint32_t maxAllocHeap;
    uint32_t minFreeHeap;
    uint32_t freePsram;
    uint32_t psramSize;
    uint32_t maxAllocPsram;
    uint32_t minFreePsram;
    uint32_t sketchSize;
    float internalTemperature;
    unsigned long runningTime;
    int hallSensor;

    void printMetadata(){
        Serial.print("Free heap: ");
        Serial.println(freeHeap);

        Serial.print("Heap Size: ");
        Serial.println(heapSize);

        Serial.print("Max Alloc Heap: ");
        Serial.println(maxAllocHeap);

        Serial.print("Min Free Heap: ");
        Serial.println(minFreeHeap);

        Serial.print("Free Psram: ");
        Serial.println(freePsram);

        Serial.print("Psram Size: ");
        Serial.println(psramSize);

        Serial.print("Max Alloc Sram: ");
        Serial.println(maxAllocPsram);

        Serial.print("Min Free Sram: ");
        Serial.println(minFreePsram);

        Serial.print("Sketch Size: ");
        Serial.println(sketchSize);

        Serial.print("Internal Temperature: ");
        Serial.println(internalTemperature);

        Serial.print("Running Time: ");
        Serial.println(runningTime);

        Serial.print("Hall Sensor: ");
        Serial.println(hallSensor);
    }

} weidosMetadata_t;

class WeidosESP32Class{
    public:
        uint32_t getFreeHeap(){ return ESP.getFreeHeap(); }
        uint32_t getHeapSize(){ return ESP.getHeapSize(); }
        uint32_t getMaxAllocHeap(){ return ESP.getMaxAllocHeap(); }
        uint32_t getMinFreeHeap(){ return ESP.getMinFreeHeap(); }
        uint32_t getFreePsram(){ return ESP.getFreePsram(); }
        uint32_t getPsramSize(){ return ESP.getPsramSize(); }
        uint32_t getMaxAllocPsram(){ return ESP.getMaxAllocPsram(); }
        uint32_t getMinFreePsram(){ return ESP.getMinFreePsram(); }
        uint32_t getSketchSize(){ return ESP.getSketchSize(); }
        float getTemperature(){ return ((temprature_sens_read() - 32) / 1.8); }
        int getHall(){ return hallRead(); }
        weidosMetadata_t getMetadata();
        //running time
        //SD telemetry (free memory etc)
        //Ethernet telemetry
        //ClockModule source (RTC o NTP)
};
