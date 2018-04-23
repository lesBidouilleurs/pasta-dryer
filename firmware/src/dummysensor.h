#ifndef PastaDummySensor_h
#define PastaDummySensor_h

#include "Arduino.h"

class DummySensor
{
public:
    float getTemperature(void);
    float getHumidity(void);
};

#endif
