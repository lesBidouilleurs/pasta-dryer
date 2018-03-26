#include "dryer.h"

Dryer::Dryer(int heaterPin, int bigFanLeftPin, int bigFanRightPin, int fanExtractPin)
  :_heaterPin(heaterPin), _bigFanRightPin(bigFanRightPin),_bigFanLeftPin(bigFanLeftPin), _fanExtractPin(fanExtractPin)
{ }

void Dryer::init(void)
{
    pinMode(this->_heaterPin, OUTPUT);
    pinMode(this->_bigFanRightPin, OUTPUT);
    pinMode(this->_bigFanLeftPin, OUTPUT);
    pinMode(this->_fanExtractPin, OUTPUT);
    this->stopStiring();
    this->stopHeating();
    this->stopDrying();
}

void Dryer::startHeating(void)
{
    digitalWrite(this->_heaterPin, 0);
}

void Dryer::stopHeating(void)
{
    digitalWrite(this->_heaterPin, 1);
}

void Dryer::stopStiring(void)
{
    digitalWrite(this->_bigFanRightPin, 1);
    digitalWrite(this->_bigFanLeftPin, 1);
}

void Dryer::rightStiring(void)
{
    digitalWrite(this->_bigFanRightPin, 1);
    digitalWrite(this->_bigFanLeftPin, 0);
}

void Dryer::leftStiring(void)
{
    digitalWrite(this->_bigFanRightPin, 0);
    digitalWrite(this->_bigFanLeftPin, 1);
}

void Dryer::startDrying(void)
{
    digitalWrite(this->_fanExtractPin, 1);
}

void Dryer::stopDrying(void)
{
    digitalWrite(this->_fanExtractPin, 0);
}
