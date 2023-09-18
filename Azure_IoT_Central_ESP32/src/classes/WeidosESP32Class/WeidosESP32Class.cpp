#include "WeidosESP32Class.h"


weidosMetadata_t WeidosESP32Class::getMetadata(){
    weidosMetadata_t metadata;
    metadata.freeHeap = getFreeHeap();
    metadata.heapSize = getHeapSize();
    metadata.maxAllocHeap = getMaxAllocHeap();
    metadata.minFreeHeap = getMinFreeHeap();
    metadata.freePsram = getFreePsram();
    metadata.psramSize = getPsramSize();
    metadata.maxAllocPsram = getMaxAllocPsram();
    metadata.minFreePsram = getMinFreePsram();
    metadata.sketchSize = getSketchSize();
    metadata.internalTemperature = getTemperature();
    metadata.runningTime = millis();
    metadata.hallSensor = getHall();
    return metadata;
}
