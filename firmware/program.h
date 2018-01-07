#ifndef PastaDryerProgram_h
#define PastaDryerProgram_h

#define CYCLES_COUNT        10

#define VENTILATION_HEAT     0
#define VENTILATION_HUMIDITY 1
#define VENTILATION_TIME     2
#define PAUSE_TIME           3
#define COOLING_HEAT         4
#define COOLING_HUMIDITY     5
#define COOLING_TIME         6

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
