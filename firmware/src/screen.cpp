#include "screen.h"

Screen::Screen() : _lcd(0x3F, 20, 4)
{ }

void Screen::init()
{
    this->_lcd.init();
    this->_lcd.backlight();
}

void Screen::printStatus(const char *statut)
{
    this->_lcd.setCursor(0, 0);
    this->_lcd.print(" statut: ");
    this->_lcd.print(statut);
}

void Screen::printVentilation(const char *statut)
{
    this->_lcd.setCursor(0, 1);
    this->_lcd.print(" ventil: ");
    this->_lcd.print(statut);
}

void Screen::printTime(int temps)
{
    this->_lcd.setCursor(0, 2);
    this->_lcd.print(" T: ");
    this->_lcd.print(temps);
}

void Screen::endCycle(int temps)
{
    this->_lcd.setCursor(10, 2);
    this->_lcd.print(" FC: ");
    this->_lcd.print(temps);
}

void Screen::clear()
{
    this->_lcd.clear();
}
