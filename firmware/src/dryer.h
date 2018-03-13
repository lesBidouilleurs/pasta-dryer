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
    Dryer(int heaterPin, int bigFanSuckPin, int bigFanExtractPin, int fanExtractPin);

    void startHeating(void);
    void stopHeating(void);
    void startDrying(void);
    void stopDrying(void);
    void leftStiring(void);
    void rightStiring(void);
    void stopStiring(void);
    void stopAll(void);

private:
    int _heaterPin;
    int _bigFanRightPin;
    int _bigFanLeftPin;
    int _fanPin;
};

#endif
