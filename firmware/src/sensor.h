#ifndef PastaSensor_h
#define PastaDryer_h

#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class Sensor
{
public:
    Sensor(int dhtPin);
    void init(void);
    float getTemperature(void);
    float getHumidity(void);

private:
    DHT_Unified _dht;
    uint32_t _delayMS;
    int _dthPin;
};

#endif
