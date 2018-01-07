#include "src/dryer.h"
#include "program.h"

#define DHT_PIN              2
#define HEATER_PIN           8
#define BIG_FAN_SUCK_PIN     9
#define BIG_FAN_EXTRACT_PIN 10
#define FAN_PIN             11

#define VENTILATION 0
#define PAUSE       1
#define COOLING     2

// 100ms semble un délais interressant pour ne rater aucun évènement
// (bouton appuyé notament)
#define TICK_TIME          100 //ms

Dryer dryer(DHT_PIN, HEATER_PIN, BIG_FAN_SUCK_PIN, BIG_FAN_EXTRACT_PIN, FAN_PIN);
unsigned short int curCycle;
unsigned short int state;
unsigned int tickCount;

unsigned int targetedTemperature;
unsigned int targetedHumidity;
unsigned int stateTickMax;

void setTargetedValues() {
    targetedTemperature = program[curCycle][VENTILATION_HEAT];
    targetedHumidity = program[curCycle][VENTILATION_HUMIDITY];
    stateTickMax = program[curCycle][VENTILATION_TIME] * 60000 / TICK_TIME;
}

void setup()
{
    tickCount = 0;
    curCycle = 0;
    state = VENTILATION;
    Serial.begin(9600);
    dryer.init();

    setTargetedValues();

}

void loop()
{
    // Vérification des mesures toutes les secondes (et si non pause).
    if (tickCount % 10 == 0 and state != PAUSE) {
        // TODO Action si l'humidité ou la chaleur ne correspond pas
    }

    // Changement d'état' si necessaire (ventilation, pause, refroidissement)
    if (tickCount >= stateTickMax) {
        state = (state + 1) % 3;
        tickCount = 0; // On remet a zéro, plus simple pour les durée des cycles

        if (state == VENTILATION) {
            curCycle++; // On passe au cycle suivant.
            setTargetedValues();
        }

        if (state == PAUSE) {
            // On éteind tout pour la pause !
            dryer.heatingOff();
            dryer.bigFanOff();
            dryer.fanOff();
        }

        if (state == COOLING) {
            setTargetedValues();
        }
    }

    delay(TICK_TIME);
    tickCount++;
}
