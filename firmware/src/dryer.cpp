#include "dryer.h"

Dryer::Dryer(int heaterPin, int bigFanLeftPin, int bigFanRightPin, int fanExtractPin)
  :_heaterPin(heaterPin), _bigFanRightPin(bigFanRightPin),_bigFanLeftPin(bigFanLeftPin), _fanExtractPin(fanExtractPin)
{
    this->stiring = OFF;
    this->heating = OFF;
    this->drying = OFF;
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
    if (this->drying == OFF) {
        digitalWrite(this->_heaterPin, 0);
        this->drying = ON;
    }
}

void Dryer::stopHeating(void)
{
    if (this->drying == ON) {
        digitalWrite(this->_heaterPin, 1);
        this->drying = OFF;
    }
}

void Dryer::stopStiring(void)
{
    if ((this->stiring == RIGHT) or (this->stiring == LEFT)) {
        digitalWrite(this->_bigFanRightPin, 0);
        digitalWrite(this->_bigFanLeftPin, 0);
        this->stiring = OFF;
    }
}

void Dryer::rightStiring(void)
{
    if ((this->stiring == OFF) or (this->stiring == LEFT)) {
        digitalWrite(this->_bigFanRightPin, 0);
        digitalWrite(this->_bigFanLeftPin, 1);
        this->stiring = RIGHT;
    }
}

void Dryer::leftStiring(void)
{
    if ((this->stiring == OFF) or (this->stiring == RIGHT)) {
        digitalWrite(this->_bigFanRightPin, 1);
        digitalWrite(this->_bigFanLeftPin, 0);
        this->stiring = LEFT;
    }
}

void Dryer::startDrying(void)
{
    if (this->stiring == OFF) {
        digitalWrite(this->_fanExtractPin, 1);
        this->stiring = ON;
    }
}

void Dryer::stopDrying(void)
{
    if (this->stiring == ON) {
        digitalWrite(this->_fanExtractPin, 0);
        this->stiring = OFF;
    }
}

void Dryer::stopAll(void)
{
    digitalWrite(this->_fanExtractPin, 0);
    this->stiring = OFF;
    digitalWrite(this->_bigFanRightPin, 0);
    digitalWrite(this->_bigFanLeftPin, 0);
    this->stiring = OFF;
    digitalWrite(this->_heaterPin, 1);
    this->drying = OFF;
}
