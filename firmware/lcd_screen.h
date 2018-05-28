LiquidCrystal_I2C lcd(0x3F,20,4);


void lcd_initialisation(){
   lcd.init();
   lcd.backlight();
}

void lcd_affiche_statut(char statut[]){
 lcd.setCursor(0, 0);
 lcd.print(" statut: ");
 lcd.print(statut);
}

void lcd_affiche_ventilation(char statut[]){
 lcd.setCursor(0, 1);
 lcd.print(" ventil: ");
 lcd.print(statut);
}

void lcd_affiche_temps(int temps){
 lcd.setCursor(0, 2);
 lcd.print(" T: ");
 lcd.print(temps);
}

void lcd_fin_cycle(int temps){
 lcd.setCursor(10, 2);
 lcd.print(" FC: ");
 lcd.print(temps);
}


void lcd_termine(){
  lcd.clear();      
}

