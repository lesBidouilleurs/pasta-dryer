#ifndef PastaScreen_h
#define PastaScreen_h

#include <LiquidCrystal_I2C.h>

class Screen
{
public:
    Screen(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void init(void);
    void printStatus(const char *statut);
    void printVentilation(const char *statut);
    void printTime(int temps);
    void endCycle(int temps);
    void clear(void);
	void off(void);

private:
    LiquidCrystal_I2C _lcd;
};

#endif
