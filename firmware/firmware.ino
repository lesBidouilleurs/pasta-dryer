#include "configuration.h"
#include "src/dryer.h"
#include "src/sensor.h"
#include "program.h"

Dryer dryer(HEATER_PIN, BIG_FAN_LEFT_PIN, BIG_FAN_RIGHT_PIN, FAN_PIN);
Sensor sensor(DHT_PIN);
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
        stateTickMax = program[curCycle][VENTILATING_TIME] * 60000 / TICK_TIME;
        stateTickStartPause = ((program[curCycle][VENTILATING_TIME] - program[curCycle][VENTILATING_PAUSE]) / 2) * 60000 / TICK_TIME ;
        stateTickEndPause = stateTickStartPause
                            + (program[curCycle][VENTILATING_TIME]  * 60000 / TICK_TIME);
    }

    if (state == RESTING) {
        targetedTemperature = program[curCycle][RESTING_HEAT];
        targetedHumidity = program[curCycle][RESTING_HUMIDITY];
        stateTickMax = program[curCycle][RESTING_TIME] * 60000 / TICK_TIME;
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
    Serial.begin(9600);
    sensor.init();
    dryer.init();

    setTargetedValues();
}

void loop()
{
    // Vérification des mesures toutes les secondes (et si non pause).
    // TODO Faire en sorte que ce soit indépendant de la la valeur de
    // TICK_TIME
    if (tickCount % 10 == 0) {
        // TODO Action si l'humidité ou la chaleur ne correspond pas
        temperature = sensor.getTemperature();
        humidity = sensor.getHumidity();

        if (temperature < (targetedTemperature - DELTA_TEMPERATURE)) {
            dryer.startHeating();
        }

        if (temperature > (targetedTemperature + DELTA_TEMPERATURE)) {
            dryer.stopHeating();
        }

        if (humidity < (targetedHumidity - DELTA_HUMIDITY)) {
            dryer.stopDrying();
        }

        if (humidity > (targetedHumidity + DELTA_HUMIDITY)) {
            dryer.startDrying();
        }

    }

    if (state == VENTILATING) {
        if (tickCount < stateTickStartPause)
        {
            dryer.rightStiring();
        }

        if (tickCount >= stateTickStartPause
            and tickCount < stateTickEndPause
        ) {
            dryer.stopStiring();
        }

        if (tickCount >= stateTickEndPause
        ) {
            dryer.leftStiring();
        }
    }

    // Changement d'état si necessaire (ventilation, pause, refroidissement)
    if (tickCount >= stateTickMax) {
        state = (state + 1) % 3;
        tickCount = 0; // On remet a zéro, plus simple pour les durée des cycles

        if (state == RESTING) {
            curCycle++; // On passe au cycle suivant.
            setTargetedValues();
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
