#ifndef PastaScreen_h
#define PastaScreen_h

#include <LiquidCrystal_I2C.h>
#include "../configuration.h"

class Screen
{
public:
    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void init(void);
    void update(int state, int ventilation, int endTickCount, int curTickCount, int temperature, int humidity, int targetedTemperature, int targetedHumidity);
    void clear(void);
	void off(void);
    void printTemperature(int temperature, int targetedTemperature);
    void printHumidity(int humidity, int targetedHumidity);
    void printTime(int curTickCount, int endTickCount);

private:
    LiquidCrystal_I2C _lcd;
    const char *_getStatus(int status);
    const char *_getVentilation(int ventilation);
    const char *_intTo2char(int integer);
    const char *_intTo3char(int integer);
};

#endif
