#ifndef PastaDryer_h
#define PastaDryer_h

#include "Arduino.h"

#define OFF   0
#define ON    1
#define RIGHT 2
#define LEFT  4

class Dryer
{
public:
    int stiring;
    int heating;
    int drying;

    Dryer(int heaterPin, int bigFanLeftPin, int bigFanRightPin, int fanExtractPin);

    void init(void);
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
    int _fanExtractPin;
};

#endif
