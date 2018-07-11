#ifndef PastaScreen_h
#define PastaScreen_h

#include <LiquidCrystal_I2C.h>
#include "../configuration.h"
#include "dryer.h"

#define LINE1  0
#define LINE2  1
#define LINE3  2
#define LINE4  3
#define COL1   0
#define COL2  10

class Screen
{
public:
    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void init(void);
    void update(int state, Dryer dryer, int endTickCount, int curTickCount, int temperature, int humidity, int targetedTemperature, int targetedHumidity, int curCycle, int totalTickCount, int totalTime);
    void clear(void);
    void printTemperature(int temperature, int targetedTemperature);
    void printHumidity(int humidity, int targetedHumidity);
    void printTime(int curTickCount, int endTickCount, int totalTickCount, int totalTime);
    void hello(void);
    void off(void);
    void end(void);

private:
    LiquidCrystal_I2C _lcd;
    const char *_getStatus(int status);
    const char *_getStiring(int fan);
    const char *_getExtractor(int fan);
    const char *_getHeater(int heat);

    void _print2digit(int integer);
    void _print3digit(int integer);
};

#endif
