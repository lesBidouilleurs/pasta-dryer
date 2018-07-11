#include "screen.h"

Screen::Screen(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : _lcd(lcd_Addr, lcd_cols, lcd_rows)
{ }

void Screen::init()
{
    this->_lcd.init();
    this->_lcd.backlight();
    this->_lcd.display();
    this->hello();
}

void Screen::clear()
{
    this->_lcd.clear();
}

void Screen::update(int state, Dryer dryer, int endTickCount, int curTickCount, int temperature, int humidity, int targetedTemperature, int targetedHumidity, int curCycle, int totalTickCount, int totalTime)
{
    this->_lcd.setCursor(COL1, LINE1);
    this->_lcd.print(this->_getStatus(state));

    this->_lcd.setCursor(COL2, LINE1);
    this->_lcd.print(this->_getStiring(dryer.bigfan));

    this->_lcd.setCursor(COL1, LINE2);
    this->_lcd.print("Cyc:");
    this->_print2digit(curCycle);
    this->_lcd.print("  ");
    this->_lcd.print(this->_getHeater(dryer.heater));
    this->_lcd.print("  ");
    this->_lcd.print(this->_getExtractor(dryer.extractor));

    this->_lcd.setCursor(COL1, LINE3);
    printTemperature(temperature, targetedTemperature);
    printHumidity(humidity, targetedHumidity);
    this->_lcd.setCursor(COL1, LINE4);
    printTime(curTickCount, endTickCount, totalTickCount, totalTime);


}

void Screen::printTemperature(int temperature, int targetedTemperature)
{
    this->_lcd.print("T:");
    this->_print2digit(temperature);
    this->_lcd.print("/");
    this->_print2digit(targetedTemperature);
    this->_lcd.print("d  ");
}

void Screen::printHumidity(int humidity, int targetedHumidity)
{
    this->_lcd.print("H:");
    this->_print2digit(humidity);
    this->_lcd.print("/");
    this->_print2digit(targetedHumidity);
    this->_lcd.print("%  ");
}

void Screen::printTime(int curTickCount, int cycleDuration, int totalTickCount, int totalTime)
{
    int curMinute = curTickCount / (MIN_2_MS / TICK_TIME);
    int curTotalMinute = totalTickCount / (MIN_2_MS / TICK_TIME);

    this->_lcd.print("Tp:");
    this->_print3digit(curMinute);
    this->_lcd.print("/");
    this->_print3digit(cycleDuration);
    this->_lcd.print("m ");
    this->_print3digit(curTotalMinute);
    this->_lcd.print("/");
    this->_print3digit(totalTime);
    this->_lcd.print("m");
}

const char *Screen::_getStatus(int status)
{
    if (status == VENTILATING) {
        return "Stat:Agit";
    }

    if (status == RESTING) {
        return "Stat:repo";
    }

    return "Stat:Err ";
}

const char *Screen::_getStiring(int fan)
{
    if (fan == OFF) {
        return "Vent:off  ";
    }

    if (fan == RIGHT) {
        return "Vent:droit";
    }

    if (fan == LEFT) {
        return "Vent:Gauch";
    }

    return "Vent:Err  ";
}

const char *Screen::_getHeater(int heat)
{
    if (heat == OFF) {
        return "C:off";
    }

    if (heat == ON) {
        return "C:on ";
    }

    return "C:Err";
}

const char *Screen::_getExtractor(int fan)
{
    if (fan == OFF) {
        return "V:off";
    }
    if (fan == ON) {
        return "V:on ";
    }

    return "V:Err";
}

void Screen::_print2digit(int integer)
{
    if (integer < 10) {
        this->_lcd.print("0");
    }
    this->_lcd.print(integer);
}

void Screen::_print3digit(int integer)
{
    if (integer < 100) {
        this->_lcd.print("0");
    }
    this->_print2digit(integer);
}

void Screen::hello()
{
    this->_lcd.setCursor(COL1, LINE2);
    this->_lcd.print("H H EEE L   L   OOO ");
    this->_lcd.setCursor(COL1, LINE3);
    this->_lcd.print("HHH EE  L   L   O O ");
    this->_lcd.setCursor(COL1, LINE4);
    this->_lcd.print("H H EEE LLL LLL OOO ");
}

void Screen::off(void)
{
    this->_lcd.setCursor(COL1, LINE2);
    this->_lcd.print("    OOO FFF FFF    ");
    this->_lcd.setCursor(COL1, LINE3);
    this->_lcd.print("    0 0 FF  FF     ");
    this->_lcd.setCursor(COL1, LINE4);
    this->_lcd.print("    000 F   F      ");
}

void Screen::end(void)
{
    this->_lcd.setCursor(COL1, LINE1);
    this->_lcd.print("                    ");
    this->_lcd.setCursor(COL1, LINE2);
    this->_lcd.print("    C'est fini !    ");
    this->_lcd.setCursor(COL1, LINE3);
    this->_lcd.print("                    ");
    this->_lcd.setCursor(COL1, LINE4);
    this->_lcd.print("                    ");
}
