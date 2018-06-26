#ifndef PastaFunctions_h
#define PastaFunctions_h

int is_on(){ //indique si le bouton marche arret est sut ON ou OFF
	if (digitalRead (BUTTON_PIN) == HIGH){
		return true;
	}else{
		return false;
	}
}


// Cette fonction simule la pression du bouton Reset
void pushReset() {
  pinMode(RESET_PIN, OUTPUT);
  // Déactive le reset forçant la sortie au niveau bas
  digitalWrite(RESET_PIN, LOW);
}

#endif
