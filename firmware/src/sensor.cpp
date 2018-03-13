#include "sensor.h"

Sensor::Sensor(int dhtPin) : _dht(dhtPin, DHT22)
{ }

void Sensor::init()
{
    this->_dht.begin();
}

float Sensor::getTemperature()
{
    sensors_event_t event;
    this->_dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        return 0.0;
    }
    return event.temperature;
}

float Sensor::getHumidity()
{
    sensors_event_t event;
    this->_dht.humidity().getEvent(&event);
    if (isnan(event.temperature)) {
        return 0.0;
    }
    return event.temperature;
}
