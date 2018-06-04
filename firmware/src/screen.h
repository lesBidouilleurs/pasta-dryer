#ifndef PastaScreen_h
#define PastaScreen_h

#include <LiquidCrystal_I2C.h>

class Screen
{
public:
    Screen();
    void init(void);
    void printStatus(const char *statut);
    void printVentilation(const char *statut);
    void printTime(int temps);
    void endCycle(int temps);
    void clear(void);

private:
    LiquidCrystal_I2C _lcd;
};

#endif
