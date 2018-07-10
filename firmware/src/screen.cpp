#include "screen.h"

Screen::Screen(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : _lcd(lcd_Addr, lcd_cols, lcd_rows)
{ }

void Screen::init()
{
    this->_lcd.init();
    this->_lcd.backlight();
    this->_lcd.display();
}

void Screen::clear()
{
    this->_lcd.clear();
}

void Screen::update(int state, int ventilation, int endTickCount, int curTickCount, int temperature, int humidity, int targetedTemperature, int targetedHumidity, int curCycle, int totalTickCount, int totalTime)
{
    this->_lcd.setCursor(COL1, LINE1);
    this->_lcd.print(this->_getStatus(state));

    this->_lcd.setCursor(COL2, LINE1);
    this->_lcd.print(this->_getVentilation(ventilation));

    printTemperature(temperature, targetedTemperature);
    printHumidity(humidity, targetedHumidity);
    printTime(curTickCount, endTickCount, totalTickCount, totalTime);

    this->_lcd.setCursor(COL1, LINE4);
    this->_lcd.print("Cycle:");
    this->_print2digit(curCycle);
}

void Screen::printTemperature(int temperature, int targetedTemperature)
{
    this->_lcd.setCursor(COL1, LINE2);
    this->_lcd.print("T:");
    this->_print2digit(temperature);
    this->_lcd.print("/");
    this->_print2digit(targetedTemperature);
    this->_lcd.print("d");
}

void Screen::printHumidity(int humidity, int targetedHumidity)
{
    this->_lcd.setCursor(COL2, LINE2);
    this->_lcd.print("H:");
    this->_print2digit(humidity);
    this->_lcd.print("/");
    this->_print2digit(targetedHumidity);
    this->_lcd.print("%");
}

void Screen::printTime(int curTickCount, int cycleDuration, int totalTickCount, int totalTime)
{
    int curMinute = (curTickCount * TICK_TIME) / TIME_CONVERTER;
    int curTotalMinute = (totalTickCount * TICK_TIME) / TIME_CONVERTER;

    this->_lcd.setCursor(0, 2);
    this->_lcd.print("Tp:");
    this->_print3digit(curTickCount * TICK_TIME / TIME_CONVERTER);
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
        return "Stat:Sech ";
    }

    if (status == RESTING) {
        return "Stat:repo ";
    }

    return "Stat:Err  ";
}

const char *Screen::_getVentilation(int ventilation)
{
    if (ventilation == OFF) {
        return "Vent:off ";
    }

    if (ventilation == RIGHT) {
        return "Vent:D   ";
    }

    if (ventilation == LEFT) {
        return "Vent:G   ";
    }

    return "Vent:Err ";
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

void Screen::off()
{
    this->_lcd.noBacklight();
}

void Screen::on()
{
    this->init();
}
