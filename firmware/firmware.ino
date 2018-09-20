#include "src/dryer.h"
#include "src/sensor.h"
#include "src/screen.h"

#include "configuration.h"
#include "program.h"
#include "src/interface.h"

Dryer dryer(HEATER_PIN, BIG_FAN_LEFT_PIN, BIG_FAN_RIGHT_PIN, FAN_PIN);
Sensor sensor(DHT_PIN);
Screen screen(SCREEN_ADDRESS, SCREEN_NB_COLUMNS, SCREEN_NB_ROWS);
Interface interface(BUTTON_ON_OFF_PIN);

unsigned short int curCycle;
unsigned short int state;

unsigned int tickCount;
unsigned int totalTickCount;

unsigned int ventilatingLeftTickCount;
unsigned int ventilatingPauseTickCount;
unsigned int ventilatingRightTickCount;
unsigned int restingTickCount;
unsigned int cycleTickCount;

unsigned int cycleDuration; // Durée du cycle en minutes

float targetedTemperature;
float targetedHumidity;
unsigned int temperature;
unsigned int humidity;

unsigned long loopStartTime;

unsigned int statusOnOff = ON;

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
        return;
    }

    targetedTemperature = (float)program[curCycle][VENTILATING_HEAT];
    targetedHumidity = (float)program[curCycle][VENTILATING_HUMIDITY];

    cycleDuration = program[curCycle][VENTILATING_TIME] + program[curCycle][RESTING_TIME];

    ventilatingPauseTickCount = min2tick(program[curCycle][VENTILATING_PAUSE]);
    ventilatingLeftTickCount = min2tick((program[curCycle][VENTILATING_TIME] - program[curCycle][VENTILATING_PAUSE]) / 2);
    ventilatingRightTickCount = ventilatingLeftTickCount;
    restingTickCount = min2tick(program[curCycle][VENTILATING_PAUSE]);
    cycleTickCount = min2tick(cycleDuration);
}

int getTotalTime() {
    int totalTime = 0;
    int nbLines = sizeof(program) / 7 / sizeof(int);
    for (size_t line = 0; line < nbLines; line++) {
        totalTime += program[line][VENTILATING_TIME] + program[line][RESTING_TIME];
    }
    return totalTime;
}

void setup()
{
    statusOnOff = OFF;
    Serial.begin(115200);
    tickCount = 0;
    totalTickCount = 0;
    curCycle = 0;
    state = VENTILATING;
    sensor.init();
    dryer.init();
    //screen.init();
    setTargetedValues();
    delay(1000);
}

void loop()
{

    if (interface.getButtonOnOff() == OFF && statusOnOff == ON) {
        Serial.print(interface.getButtonOnOff());
        // Tout est remis a zéro pour préparer un nouveau départ.
        screen.off();
        dryer.stopAll();
        tickCount = 0;
        totalTickCount = 0;
        curCycle = 0;
        state = VENTILATING;
        setTargetedValues();
        statusOnOff = OFF;
        delay(1000);
        return;
    }

    if (interface.getButtonOnOff() == ON) {
      if (statusOnOff == OFF){ // premiere boucle depuis que le bouton est sur ON
        screen.init();
      }

      statusOnOff = ON;


      if (state == END) {
          dryer.stopAll();
          screen.end();
          return;
      }

      loopStartTime = millis();

      temperature = (int)sensor.getTemperature();
      humidity = (int)sensor.getHumidity();


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

      if (state == VENTILATING) {
          if (tickCount < ventilatingLeftTickCount) {
              dryer.leftStiring();
          }

          if (tickCount >= ventilatingLeftTickCount
              and tickCount < (ventilatingLeftTickCount + ventilatingPauseTickCount)
          ) {
              dryer.stopStiring();
          }

          if (tickCount >= (ventilatingLeftTickCount + ventilatingPauseTickCount)) {
              dryer.rightStiring();
          }

          if (tickCount >= (ventilatingLeftTickCount + ventilatingRightTickCount + ventilatingPauseTickCount)) {
              // Passe a repos
              dryer.stopStiring();
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
              curCycle++;
              if (curCycle >= CYCLES_COUNT) {
                  state = END;
              } else {
                  state = VENTILATING;
                  setTargetedValues();
                  tickCount = 0;
              }
          }
      }

      screen.update(state, dryer, cycleDuration, tickCount, temperature, humidity, targetedTemperature, targetedHumidity, curCycle, totalTickCount, getTotalTime());
      delay(TICK_TIME - (millis() - loopStartTime));

      tickCount++;
      totalTickCount++;
    }
}
