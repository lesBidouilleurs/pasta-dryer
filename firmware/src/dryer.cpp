#include "dryer.h"

Dryer::Dryer(int heaterPin, int bigFanLeftPin, int bigFanRightPin, int fanExtractPin)
  :_heaterPin(heaterPin), _bigFanRightPin(bigFanRightPin),_bigFanLeftPin(bigFanLeftPin), _fanExtractPin(fanExtractPin)
{
    this->bigfan = OFF;
    this->heater = OFF;
    this->extractor = OFF;
}

void Dryer::init(void)
{
    pinMode(this->_heaterPin, OUTPUT);
    pinMode(this->_bigFanRightPin, OUTPUT);
    pinMode(this->_bigFanLeftPin, OUTPUT);
    pinMode(this->_fanExtractPin, OUTPUT);
    this->stopAll();

}

void Dryer::startHeating(void)
{
    if (this->heater == OFF) {
        digitalWrite(this->_heaterPin, 0);
        this->heater = ON;
    }
}

void Dryer::stopHeating(void)
{
    if (this->heater == ON) {
        digitalWrite(this->_heaterPin, 1);
        this->heater = OFF;
    }
}

void Dryer::stopStiring(void)
{
    if ((this->bigfan == RIGHT) or (this->bigfan == LEFT)) {
        digitalWrite(this->_bigFanRightPin, 0);
        digitalWrite(this->_bigFanLeftPin, 0);
        this->bigfan = OFF;
    }
}

void Dryer::rightStiring(void)
{
    if ((this->bigfan == OFF) or (this->bigfan == LEFT)) {
        digitalWrite(this->_bigFanRightPin, 0);
        digitalWrite(this->_bigFanLeftPin, 1);
        this->bigfan = RIGHT;
    }
}

void Dryer::leftStiring(void)
{
    if ((this->bigfan == OFF) or (this->bigfan == RIGHT)) {
        digitalWrite(this->_bigFanRightPin, 1);
        digitalWrite(this->_bigFanLeftPin, 0);
        this->bigfan = LEFT;
    }
}

void Dryer::startDrying(void)
{
    if (this->extractor == OFF) {
        digitalWrite(this->_fanExtractPin, 1);
        this->extractor = ON;
    }
}

void Dryer::stopDrying(void)
{
    if (this->extractor == ON) {
        digitalWrite(this->_fanExtractPin, 0);
        this->extractor = OFF;
    }
}

void Dryer::stopAll(void)
{
    digitalWrite(this->_fanExtractPin, 0);
    this->extractor = OFF;
    digitalWrite(this->_bigFanRightPin, 0);
    digitalWrite(this->_bigFanLeftPin, 0);
    this->bigfan = OFF;
    digitalWrite(this->_heaterPin, 1);
    this->heater = OFF;
}
