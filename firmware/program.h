#ifndef PastaDryerProgram_h
#define PastaDryerProgram_h

#define CYCLES_COUNT        10

#define VENTILATION_HEAT     0
#define VENTILATION_HUMIDITY 1
#define VENTILATION_TIME     2 // A diviser en deux, un sens puis l'autre
#define PAUSE_TIME           3 // Minute de pause entre les deux sens précédent
#define REST_HEAT         4
#define REST_HUMIDITY     5
#define REST_TIME         6

#define DELTA_TEMPERATURE 2
#define DELTA_HUMIDITY    5

// L'humidité est controlé par le petit ventilateur
// la temperature par le chauffage
// delta de 2° pour les températures
// delta de 5% pour l'humidité
// La deuxième partie du tableau c'est sans le gros ventilateur double sense brasseur



int program[CYCLES_COUNT][7] = {
    {40, 85, 20,  1, 38, 75, 5},
    {40, 80, 20,  1, 39, 75, 5},
    {40, 75, 20,  1, 40, 75, 5},
    {40, 75, 20,  1, 40, 75, 8},
    {40, 75, 16,  1, 40, 70, 8},
    {40, 75, 16,  1, 40, 70, 10},
    {40, 75, 16,  1, 40, 70, 10},
    {40, 75, 16,  1, 40, 70, 12},
    {40, 75,  8,  1, 40, 65, 12},
    {40, 75,  8,  1, 40, 65, 12},
};

#endif
