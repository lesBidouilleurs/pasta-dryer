#include "dummysensor.h"

#define POT_TEMPERATURE 1
#define POT_HUMIDITY 2

float DummySensor::getTemperature(void)
{
    int val = analogRead(POT_TEMPERATURE);
    int tmp = map(val, 1, 255, 10, 100);
    return (float)tmp;
}

float DummySensor::getHumidity(void)
{
    int val = analogRead(POT_HUMIDITY);
    int tmp = map(val, 1, 255, 20, 100);
    return (float)tmp;
}
