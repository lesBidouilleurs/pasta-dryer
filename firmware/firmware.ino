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
unsigned int drying;
unsigned int heating;

unsigned int tickCount;
unsigned int totalTickCount;

unsigned int ventilatingLeftTickCount;
unsigned int ventilatingPauseTickCount;
unsigned int ventilatingRightTickCount;
unsigned int restingTickCount;
unsigned int cycleTickCount;

unsigned int cycleDuration; // Durée du cycle en minutes

unsigned int targetedTemperature;
unsigned int targetedHumidity;
unsigned int temperature;
unsigned int humidity;

unsigned long loopStartTime;

int min2tick(int minutes) {
    return minutes * (MIN_2_MS / TICK_TIME);
}

int tick2min(int ticks) {
    return ticks / (MIN_2_MS / TICK_TIME);
}

void setTargetedValues() {
    if (state == RESTING) {
        targetedTemperature = program[curCycle][RESTING_HEAT];
        targetedHumidity = program[curCycle][RESTING_HUMIDITY];

        Serial.print("########################\n# REPOS\n########################\n");
        Serial.print("Température cible : "); Serial.print(targetedTemperature); Serial.print("\n");
        Serial.print("Humidité cible : "); Serial.print(targetedHumidity); Serial.print("\n\n\n");

        return;
    }

    targetedTemperature = program[curCycle][VENTILATING_HEAT];
    targetedHumidity = program[curCycle][VENTILATING_HUMIDITY];

    cycleDuration = program[curCycle][VENTILATING_TIME] + program[curCycle][RESTING_TIME];

    ventilatingPauseTickCount = min2tick(program[curCycle][VENTILATING_PAUSE]);
    ventilatingLeftTickCount = min2tick((program[curCycle][VENTILATING_TIME] - program[curCycle][VENTILATING_PAUSE]) / 2);
    ventilatingRightTickCount = ventilatingLeftTickCount;
    restingTickCount = min2tick(program[curCycle][VENTILATING_PAUSE]);
    cycleTickCount = min2tick(cycleDuration);

    Serial.print("########################\n# Nouveau cycle\n########################\n");
    Serial.print("Température cible : "); Serial.print(targetedTemperature); Serial.print("\n");
    Serial.print("Humidité cible : "); Serial.print(targetedHumidity); Serial.print("\n");
    Serial.print("Durée cyle : "); Serial.print(cycleDuration); Serial.print("min / "); Serial.print(cycleTickCount); Serial.print("ticks \n");
    Serial.print("Agitation a gauche : "); Serial.print(tick2min(ventilatingLeftTickCount)); Serial.print("min / "); Serial.print(ventilatingLeftTickCount); Serial.print("ticks \n");
    Serial.print("Agitation a droite : "); Serial.print(tick2min(ventilatingRightTickCount)); Serial.print("min / "); Serial.print(ventilatingRightTickCount); Serial.print("ticks \n");
    Serial.print("Pause agitation : "); Serial.print(tick2min(ventilatingPauseTickCount)); Serial.print("min / "); Serial.print(ventilatingPauseTickCount); Serial.print("ticks \n");
    Serial.print("Temps repos : "); Serial.print(tick2min(restingTickCount)); Serial.print("min / "); Serial.print(restingTickCount); Serial.print("ticks \n\n\n");
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
    dryer.stopDrying();
    dryer.stopStiring();
    dryer.stopHeating();
    state = VENTILATING;
    ventilation = OFF;
    heating = OFF;
    drying = OFF;
    Serial.begin(115200);
    sensor.init();
    dryer.init();
    screen.init();
    setTargetedValues();

    screen.update(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
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

    loopStartTime = millis();

    temperature = (int)sensor.getTemperature();
    humidity = (int)sensor.getHumidity();

    screen.update(state, ventilation, cycleDuration, tickCount, temperature, humidity, targetedTemperature, targetedHumidity, curCycle, totalTickCount, getTotalTime());

    if (temperature < (targetedTemperature - DELTA_TEMPERATURE)) {
        dryer.startHeating();
        heating = ON;
    }

    if (temperature > (targetedTemperature + DELTA_TEMPERATURE)) {
        dryer.stopHeating();
        heating = OFF;
    }

    if (humidity < (targetedHumidity - DELTA_HUMIDITY)) {
        dryer.stopDrying();
        drying = OFF;
    }

    if (humidity > (targetedHumidity + DELTA_HUMIDITY)) {
        dryer.startDrying();
        drying = ON;
    }

    if (state == VENTILATING) {
        if (tickCount < ventilatingLeftTickCount) {
            dryer.leftStiring();
            ventilation = LEFT;
        }

        if (tickCount >= ventilatingLeftTickCount
            and tickCount < (ventilatingLeftTickCount + ventilatingPauseTickCount)
        ) {
            dryer.stopStiring();
            ventilation = OFF;
        }

        if (tickCount >= (ventilatingLeftTickCount + ventilatingPauseTickCount)) {
            dryer.rightStiring();
            ventilation = RIGHT;
        }

        if (tickCount >= (ventilatingLeftTickCount + ventilatingRightTickCount + ventilatingPauseTickCount)) {
            // Passe a repos
            dryer.stopStiring();
            ventilation = OFF;
            state = RESTING;
            setTargetedValues();
            delay(TICK_TIME - (millis() - loopStartTime));
            tickCount++;
            totalTickCount++;
            return;
        }
    }

    if (state == RESTING) {
        if (tickCount >= cycleTickCount) {
            // On passe au cycle suivant.
            curCycle++;
            state = VENTILATING;
            setTargetedValues();
            tickCount = 0;
        }
    }

    //Serial.print("Attends : "); Serial.print(TICK_TIME - (millis() - loopStartTime)); Serial.print("\n\n");
    delay(TICK_TIME - (millis() - loopStartTime));

    tickCount++;
    totalTickCount++;
}
