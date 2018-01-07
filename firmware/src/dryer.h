#ifndef PastaDryer_h
#define PastaDryer_h

#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// TODO l'idée est de remplacer les méthodes concernant les
// ventilateurs par des méthodes du type : "lowerHumidity", "refresh" qui
// représente mieux les actions. Une meilleur compréhension des effets des
// différents ventilateur (et de leur sens de rotation) est necessaires
// pour définir ces méthodes

class Dryer
{
public:
    Dryer(int dhtPin, int heaterPin, int bigFanSuckPin, int bigFanExtractPin, int fanPin);
    void init(void);
    void ticks(void);
    float getTemperature(void);
    float getHumidity(void);
    void heatingOn(void);
    void heatingOff(void);
    void bigFanOff(void);
    void bigFanExtract(void);
    void bigfanSuck(void);
    void fanOff(void);
    void fanOn(void);

private:
    DHT_Unified _dht;
    uint32_t _delayMS;
    int _dthPin;
    int _heaterPin;
    int _bigFanSuckPin;
    int _bigFanExtractPin;
    int _fanPin;
};

#endif
