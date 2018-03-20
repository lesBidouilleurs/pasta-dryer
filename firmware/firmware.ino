#include "configuration.h"
#include "src/dryer.h"
#include "src/sensor.h"
#include "program.h"

Dryer dryer(HEATER_PIN, BIG_FAN_LEFT_PIN, BIG_FAN_RIGHT_PIN, FAN_PIN);
Sensor sensor(DHT_PIN);
unsigned short int curCycle;
unsigned short int state;
unsigned int tickCount;

unsigned int targetedTemperature;
unsigned int targetedHumidity;
unsigned int stateTickMax;

void setTargetedValues() {
    if (state == VENTILATING) {
        targetedTemperature = program[curCycle][VENTILATION_HEAT];
        targetedHumidity = program[curCycle][VENTILATION_HUMIDITY];
        stateTickMax = program[curCycle][VENTILATION_TIME] * 60000 / TICK_TIME;
        stateTickStartPause = 0;
        stateTickEndPause = 0;
    }

    if (state == VENTILATING) {

    }

}

void setup()
{
    tickCount = 0;
    curCycle = 0;
    state = VENTILATING;
    Serial.begin(9600);
    dryer.init();
    sensor.init();

    setTargetedValues();
}

void loop()
{
    // Vérification des mesures toutes les secondes (et si non pause).
    if (tickCount % 10 == 0 and state != PAUSE) {
        // TODO Action si l'humidité ou la chaleur ne correspond pas
        temperature = sensor.getTemperature();
        humidity = sensor.getHumidity();

        if (temperature < (targetedTemperature - DELTA_TEMPERATURE)) {
            dryer.startHeating();
        }

        if ((temperature > (targetedTemperature + DELTA_TEMPERATURE)) {
            dryer.stopHeating();
        }

        if (($humidity < ($targetedHumidity - DELTA_HUMIDITY)) {
            dryer.stopDrying();
        }

        if (($humidity > ($targetedHumidity + DELTA_HUMIDITY)) {
            dryer.starDrying();
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

    // Changement d'état' si necessaire (ventilation, pause, refroidissement)
    if (tickCount >= stateTickMax) {
        state = (state + 1) % 3;
        tickCount = 0; // On remet a zéro, plus simple pour les durée des cycles

        if (state == VENTILATING) {
            curCycle++; // On passe au cycle suivant.
            setTargetedValues();
        }

        if (state == RESTING) {
            setTargetedValues();
        }
    }

    delay(TICK_TIME);
    tickCount++;
}
