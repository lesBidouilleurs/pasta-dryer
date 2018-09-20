#ifndef PastaParameters_h
#define PastaParameters_h

#define DHT_PIN              2
#define BUTTON_ON_OFF_PIN    6
#define HEATER_PIN           8
#define BIG_FAN_LEFT_PIN     9
#define BIG_FAN_RIGHT_PIN   10
#define FAN_PIN             11
#define RESET_PIN           12

#define VENTILATING 0
#define RESTING     1
#define END        99

#define SCREEN_ADDRESS       0x3F
#define SCREEN_NB_COLUMNS    20
#define SCREEN_NB_ROWS       4

// L'humidité est controlé par le petit ventilateur
// la temperature par le chauffage
// delta de 2° pour les températures
// delta de 5% pour l'humidité
#define DELTA_TEMPERATURE 2
#define DELTA_HUMIDITY    5

//#define MIN_2_MS 60000 // Une minute est vraiment une minute
#define MIN_2_MS 60000 // Une minute est 6s --> pour les tests.

// 500ms semble un peu long mais nous sommes sûre que loop est entièrement
// executé. (environ 340ms max)
#define TICK_TIME          500 //ms

#endif
