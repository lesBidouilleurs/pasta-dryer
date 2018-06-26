#ifndef PastaDryer_h
#define PastaDryer_h

#include "Arduino.h"

class Dryer
{
public:
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
