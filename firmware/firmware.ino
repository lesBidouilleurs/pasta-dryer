#include <LiquidCrystal_I2C.h>

#include "configuration.h"
#include "src/dryer.h"
#include "src/dummysensor.h"
#include "program.h"
#include "lcd_screen.h"

Dryer dryer(HEATER_PIN, BIG_FAN_LEFT_PIN, BIG_FAN_RIGHT_PIN, FAN_PIN);
DummySensor sensor; //DHT_PIN
unsigned short int curCycle;
unsigned short int state;
unsigned int tickCount;
unsigned int stateTickStartPause; // Nombre de tick avant la pause (VENTILATING)
unsigned int stateTickEndPause; // Nombre de tick pour la fin de la pause (VENTILATING)
unsigned int stateTickMax; // Nombre de tick pour le cyle en cours (VENTILATING / RESTING)

unsigned int targetedTemperature;
unsigned int targetedHumidity;
unsigned int temperature;
unsigned int humidity;


void setTargetedValues() {
    if (state == VENTILATING) {
        targetedTemperature = program[curCycle][VENTILATING_HEAT];
        targetedHumidity = program[curCycle][VENTILATING_HUMIDITY];
        stateTickMax = program[curCycle][VENTILATING_TIME] * TIME_CONVERTER / TICK_TIME;
        stateTickStartPause = ((program[curCycle][VENTILATING_TIME] - program[curCycle][VENTILATING_PAUSE]) / 2)
                              * TIME_CONVERTER / TICK_TIME ;
        stateTickEndPause = stateTickStartPause
                            + (program[curCycle][VENTILATING_PAUSE]  * TIME_CONVERTER / TICK_TIME);
    }

    if (state == RESTING) {
        targetedTemperature = program[curCycle][RESTING_HEAT];
        targetedHumidity = program[curCycle][RESTING_HUMIDITY];
        stateTickMax = program[curCycle][RESTING_TIME] * TIME_CONVERTER / TICK_TIME;
        stateTickStartPause = 0;
        stateTickEndPause = 0;
    }
}

void setup()
{
    tickCount = 0;
    curCycle = 0;
    stateTickStartPause = 0;
    stateTickEndPause = 0;
    state = VENTILATING;
    Serial.begin(115200);
    //sensor.init();
    dryer.init();
    lcd_initialisation();
    

    setTargetedValues();
 
}

void loop()
{
    // Vérification des mesures toutes les secondes (et si non pause).
    // TODO Faire en sorte que ce soit indépendant de la la valeur de
    // TICK_TIME
    if (tickCount % 10 == 0) {
        // TODO Action si l'humidité ou la chaleur ne correspond pas

        temperature = (int)sensor.getTemperature();
        humidity = (int)sensor.getHumidity();
        Serial.println(); Serial.println(); Serial.println();
        Serial.print("Température : "); Serial.println(temperature);
        Serial.print("Humidité :    "); Serial.println(humidity); 
        
        if (temperature < (targetedTemperature - DELTA_TEMPERATURE)) {
            Serial.print("chauffage allumé, cible :"); Serial.println(targetedTemperature);
            dryer.startHeating();
        }

        if (temperature > (targetedTemperature + DELTA_TEMPERATURE)) {
            Serial.print("chauffage éteint, cible :"); Serial.println(targetedTemperature);
            dryer.stopHeating();
        }

        if (humidity < (targetedHumidity - DELTA_HUMIDITY)) {
            Serial.print("Séchage arrété, cible :"); Serial.println(targetedHumidity);
            dryer.stopDrying();
        }

        if (humidity > (targetedHumidity + DELTA_HUMIDITY)) {
            Serial.print("Séchage allumé, cible : "); Serial.println(targetedHumidity);
            dryer.startDrying();
        }

        if (state == RESTING) {
          Serial.println("État : repos");
          lcd_affiche_statut("repos");
        }

       if (state == VENTILATING) {
        Serial.println("État : remuage");
        lcd_affiche_statut("Sechage");
       }

    }

    Serial.print("Début pause : "); Serial.println(stateTickStartPause);
    Serial.print("Fin pause : "); Serial.println(stateTickEndPause);
    Serial.print("Fin cycle : "); Serial.println(stateTickMax);
    Serial.println();
    Serial.print("tick : ");Serial. println(tickCount);
    lcd_fin_cycle(stateTickMax);
    lcd_affiche_temps(tickCount);
    lcd_fin_cycle(stateTickMax);
    if (state == VENTILATING) {
        if (tickCount < stateTickStartPause)
        {
            dryer.rightStiring();
            Serial.println("Tourne à droite"); 
            lcd_affiche_ventilation("normale");
        }

        if (tickCount >= stateTickStartPause
            and tickCount < stateTickEndPause
        ) {
            dryer.stopStiring();
            Serial.println("Ne tourne pas");
            lcd_affiche_ventilation("off");
        }

        if (tickCount >= stateTickEndPause
        ) {
            dryer.leftStiring();
            Serial.println("Tourne à gauche");
            lcd_affiche_ventilation("inverse");
        }
    }

  
   

    // Changement d'état si necessaire (ventilation, pause, refroidissement)
    if (tickCount >= stateTickMax) {
        state = (state + 1) % 3;
        tickCount = 0; // On remet a zéro, plus simple pour les durée des cycles

        if (state == RESTING) {
            curCycle++; // On passe au cycle suivant.
            setTargetedValues();
            dryer.stopStiring();
            state == VENTILATING;
        }

        if (state == VENTILATING) {
            setTargetedValues();
            state == RESTING;
        }
    }
    
    delay(TICK_TIME);
    tickCount++;
    
}
