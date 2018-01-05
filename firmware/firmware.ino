#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2
#define DHT_TYPE DHT22

#define HEATER_PIN 8
#define BIG_FAN_SUCK_PIN 9
#define BIG_FAN_EXTRACT_PIN 10
#define FAN_PIN 11

DHT_Unified dht(DHT_PIN, DHT_TYPE);
uint32_t delayMS;

float getTemperature()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        return 0.0;
    }
    return event.temperature;
}

float getHumidity()
{
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (isnan(event.temperature)) {
        return 0.0;
    }
    return event.temperature;
}

void heatingOn()
{
    digitalWrite(HEATER_PIN, 0);
}

void heatingOff()
{
    digitalWrite(HEATER_PIN, 1);
}

void bigFanOff()
{
    digitalWrite(BIG_FAN_SUCK_PIN, 1);
    digitalWrite(BIG_FAN_EXTRACT_PIN, 1);
}

void bigFanExtract()
{
    digitalWrite(BIG_FAN_SUCK_PIN, 1);
    digitalWrite(BIG_FAN_EXTRACT_PIN, 0);
    
}

void bigfanSuck()
{
    digitalWrite(BIG_FAN_SUCK_PIN, 0);
    digitalWrite(BIG_FAN_EXTRACT_PIN, 1);
}

void fanOff()
{
    digitalWrite(FAN_PIN, 1);
}

void fanOn()
{
    digitalWrite(FAN_PIN, 0);
}

void setup()
{
    Serial.begin(9600);
    dht.begin();
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(BIG_FAN_SUCK_PIN, OUTPUT);
    pinMode(BIG_FAN_EXTRACT_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);

    heatingOff();
    bigFanOff();
    fanOff();
}

void loop()
{
    // TODO
}
