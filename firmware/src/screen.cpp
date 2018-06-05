#include "screen.h"

Screen::Screen(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : _lcd(lcd_Addr, lcd_cols, lcd_rows)
{ }

void Screen::init()
{
	this->_lcd.init();
	this->_lcd.backlight();
	this->_lcd.display();
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

void Screen::off()
{
	this->_lcd.noDisplay();
	this->_lcd.home();
	this->_lcd.noBacklight();
}
