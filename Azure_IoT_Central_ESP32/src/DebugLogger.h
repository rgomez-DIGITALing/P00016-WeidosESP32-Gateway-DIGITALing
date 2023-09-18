#pragma once

#define DEBUG_LOGGER true

#if DEBUG_LOGGER
#define LOG(x) Serial.println(x)
#define LOG2(x) Serial.print(x)

#else
#define LOG(x)
#define LOG2(x)

#endif