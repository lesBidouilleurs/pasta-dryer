#include "src/dryer.h"

#define DHT_PIN              2
#define HEATER_PIN           8
#define BIG_FAN_SUCK_PIN     9
#define BIG_FAN_EXTRACT_PIN 10
#define FAN_PIN             11

Dryer dryer(DHT_PIN, HEATER_PIN, BIG_FAN_SUCK_PIN, BIG_FAN_EXTRACT_PIN, FAN_PIN);

void setup()
{
    Serial.begin(9600);
    dryer.init();
    
}

void loop()
{
    // TODO
}
