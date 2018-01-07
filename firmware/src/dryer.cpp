#include "dryer.h"

Dryer::Dryer(int dhtPin, int heaterPin, int bigFanSuckPin, int bigFanExtractPin, int fanPin)
  :_heaterPin(heaterPin), _bigFanSuckPin(bigFanSuckPin),_bigFanExtractPin(bigFanExtractPin), _fanPin(fanPin),  _dht(dhtPin, DHT22)
{ }

void Dryer::init()
{
    this->_dht.begin();
    pinMode(this->_heaterPin, OUTPUT);
    pinMode(this->_bigFanSuckPin, OUTPUT);
    pinMode(this->_bigFanExtractPin, OUTPUT);
    pinMode(this->_fanPin, OUTPUT);
    this->bigFanOff();
    this->heatingOff();
    this->fanOff();
}

float Dryer::getTemperature()
{
    sensors_event_t event;
    this->_dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        return 0.0;
    }
    return event.temperature;
}

float Dryer::getHumidity()
{
    sensors_event_t event;
    this->_dht.humidity().getEvent(&event);
    if (isnan(event.temperature)) {
        return 0.0;
    }
    return event.temperature;
}

void Dryer::heatingOn(void)
{
    digitalWrite(this->_heaterPin, 0);
}

void Dryer::heatingOff(void)
{
    digitalWrite(this->_heaterPin, 1);
}

void Dryer::bigFanOff(void)
{
    digitalWrite(this->_bigFanSuckPin, 1);
    digitalWrite(this->_bigFanExtractPin, 1);
}

void Dryer::bigFanExtract(void)
{
    digitalWrite(this->_bigFanSuckPin, 1);
    digitalWrite(this->_bigFanExtractPin, 0);

}

void Dryer::bigfanSuck(void)
{
    digitalWrite(this->_bigFanSuckPin, 0);
    digitalWrite(this->_bigFanExtractPin, 1);
}

void Dryer::fanOff(void)
{
    digitalWrite(this->_fanPin, 1);
}

void Dryer::fanOn(void)
{
    digitalWrite(this->_fanPin, 0);
}
