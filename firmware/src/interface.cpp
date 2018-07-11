#include "interface.h"

Interface::Interface(int onOffButtonPin) : _onOffButtonPin(onOffButtonPin)
{ }

int Interface::getButtonOnOff()
{
    if (digitalRead(this->_onOffButtonPin) == HIGH){
        return true;
    }

    if (digitalRead(this->_onOffButtonPin) == LOW){
        return false;
    }

    return 666;
}
