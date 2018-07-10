#ifndef PastaParameters_h
#define PastaParameters_h

#define DHT_PIN              2
#define BUTTON_PIN           6
#define HEATER_PIN           8
#define BIG_FAN_LEFT_PIN     9
#define BIG_FAN_RIGHT_PIN   10
#define FAN_PIN             11
#define RESET_PIN           12

#define VENTILATING 0
#define RESTING     1

#define OFF   0
#define LEFT  1
#define RIGHT 2
#define ON    4

#define SCREEN_ADDRESS       0x3F
#define SCREEN_NB_COLUMNS    20
#define SCREEN_NB_ROWS       4

//#define MIN_2_MS 60000 // Une minute est vraiment une minute
#define MIN_2_MS 6000 // Une minute est 6s --> pour les tests.

// 100ms semble un délais interressant pour ne rater aucun évènement
// (bouton appuyé notament)
#define TICK_TIME          500 //ms

#endif
