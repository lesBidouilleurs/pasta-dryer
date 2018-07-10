#include "src/dryer.h"
#include "src/sensor.h"
#include "src/screen.h"

#include "configuration.h"
#include "program.h"
#include "src/fonction.h"

Dryer dryer(HEATER_PIN, BIG_FAN_LEFT_PIN, BIG_FAN_RIGHT_PIN, FAN_PIN);
Sensor sensor(DHT_PIN); //DHT_PIN
Screen screen(SCREEN_ADDRESS, SCREEN_NB_COLUMNS, SCREEN_NB_ROWS);

unsigned short int curCycle;
unsigned short int state;
unsigned short int ventilation;
unsigned int tickCount;
unsigned int totalTickCount;
unsigned int stateTickStartPause; // Nombre de tick avant la pause (VENTILATING)
unsigned int stateTickEndPause; // Nombre de tick pour la fin de la pause (VENTILATING)
unsigned int stateTickMax; // Nombre de tick pour le cyle en cours (VENTILATING / RESTING)
unsigned int cycleDuration;

unsigned int targetedTemperature;
unsigned int targetedHumidity;
unsigned int temperature;
unsigned int humidity;

unsigned long time;

void setTargetedValues() {
    cycleDuration = program[curCycle][VENTILATING_TIME] + program[curCycle][RESTING_TIME];

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

int getTotalTime() {
    int totalTime = 0;
    int nbLines = sizeof(program) / 7 / sizeof(int);
    for (size_t line = 0; line < nbLines; line++) {
        totalTime += program[line][VENTILATING_TIME] + program[line][VENTILATING_PAUSE] + program[line][RESTING_TIME];
    }
    return totalTime;
}

void setup()
{
    tickCount = 0;
    totalTickCount = 0;
    curCycle = 0;
    stateTickStartPause = 0;
    stateTickEndPause = 0;
    state = VENTILATING;
    ventilation = OFF;
    Serial.begin(115200);
    sensor.init();
    dryer.init();
    screen.init();
    setTargetedValues();
}

void loop()
{

    /*if (is_on() ==  false) { // le bonton est sur off
        //pushReset();
        screen.off();
        tickCount = 0;
        totalTickCount = 0;
        curCycle = 0;
        stateTickStartPause = 0;
        stateTickEndPause = 0;
        state = VENTILATING;
        ventilation = OFF;
        return;
    }*/

    // Vérification des mesures toutes les secondes (et si non pause).
    // TODO Faire en sorte que ce soit indépendant de la la valeur de
    // TICK_TIME
    time = millis();

    if (tickCount % 10 == 0) {
        temperature = (int)sensor.getTemperature();
        humidity = (int)sensor.getHumidity();

        screen.update(state, ventilation, cycleDuration, tickCount, temperature, humidity, targetedTemperature, targetedHumidity, curCycle, totalTickCount, getTotalTime());

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
        if (tickCount < stateTickStartPause) {
            dryer.rightStiring();
            ventilation = LEFT;
        }

        if (tickCount >= stateTickStartPause
            and tickCount < stateTickEndPause
        ) {
            dryer.stopStiring();
            ventilation = OFF;
        }

        if (tickCount >= stateTickEndPause) {
            dryer.leftStiring();
            ventilation = RIGHT;
        }
    }

    if (state != VENTILATING) {
        dryer.stopStiring();
        ventilation = OFF;
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
    //delay(TICK_TIME - (int)(millis() - time)); // prend en compte la durée de l'execution
                                          // du code pour améliorer la précision.
    tickCount++;
    totalTickCount++;
}
