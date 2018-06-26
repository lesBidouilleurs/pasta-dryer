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

void Screen::update(int state, int ventilation, int endTickCount, int curTickCount, int temperature, int humidity, int targetedTemperature, int targetedHumidity)
{
    this->_lcd.setCursor(0, 0);
    this->_lcd.print(this->_getStatus(state));

    this->_lcd.setCursor(12, 0);
    this->_lcd.print(this->_getVentilation(ventilation));

    printTemperature(temperature, targetedTemperature);
    printHumidity(humidity, targetedHumidity);
    printTime(curTickCount, endTickCount);
}

void Screen::printTemperature(int temperature, int targetedTemperature)
{
    this->_lcd.setCursor(0, 1);
    this->_lcd.print("T:");
    this->_lcd.print(this->_intTo2char(temperature));
    this->_lcd.print("/");
    this->_lcd.print(this->_intTo2char(targetedTemperature));
    this->_lcd.print("°");
}

void Screen::printHumidity(int humidity, int targetedHumidity)
{
    this->_lcd.setCursor(12, 1);
    this->_lcd.print("H:");
    this->_lcd.print(this->_intTo2char(humidity));
    this->_lcd.print("/");
    this->_lcd.print(this->_intTo2char(targetedHumidity));
    this->_lcd.print("%");
}

void Screen::printTime(int curTickCount, int endTickCount)
{
    int curMinute = (curTickCount * TICK_TIME) / 60000;
    int endMinute = (endTickCount * TICK_TIME) / 60000;

    this->_lcd.setCursor(1, 3);
    this->_lcd.print("Temps:");
    this->_lcd.print(this->_intTo3char(curMinute));
    this->_lcd.print("/");
    this->_lcd.print(this->_intTo3char(endMinute));
    this->_lcd.print("min");
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

// TODO c"est sale mais c"est une solution rapide... a améliorer
const char *Screen::_intTo2char(int integer)
{
    char string[] = "  ";
    string[1] = (char)(integer % 10);
    string[0] = (char)((integer / 10) % 10);
    const char *cstring = string;
    return cstring;
}

// TODO c"est sale mais c"est une solution rapide... a améliorer
const char *Screen::_intTo3char(int integer)
{
    char string[] = "   ";
    string[2] = (char)(integer % 10);
    string[1] = (char)((integer / 10) % 10);
    string[0] = (char)((integer / 100) % 10);
    const char *cstring = string;
    return cstring;
}

void Screen::off()
{
	this->_lcd.noDisplay();
	this->_lcd.home();
	this->_lcd.noBacklight();
}
