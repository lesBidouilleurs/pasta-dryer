#ifndef PastaDryerProgram_h
#define PastaDryerProgram_h

#define VENTILATING_HEAT     0
#define VENTILATING_HUMIDITY 1
#define VENTILATING_TIME     2 // A diviser en deux, un sens puis l'autre
#define VENTILATING_PAUSE    3 // Minute de pause entre les deux sens précédent
#define RESTING_HEAT         4
#define RESTING_HUMIDITY     5
#define RESTING_TIME         6

// La deuxième partie du tableau c'est sans le gros ventilateur double sense brasseur

#define CYCLES_COUNT        17

int program[CYCLES_COUNT][7] = {
    {40, 85, 3,  1, 38, 75, 1},
    {40, 85, 5,  1, 38, 75, 2},
    {40, 85, 5,  1, 38, 75, 2},
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
