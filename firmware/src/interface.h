#ifndef PastaInterface_h
#define PastaInterface_h

#include "Arduino.h"
#include "../configuration.h"

#define OFF 0
#define ON  1

class Interface
{
public:
    Interface(int onOffButtonPin);
    int getButtonOnOff(void);

private:
    int _onOffButtonPin;
};

#endif
