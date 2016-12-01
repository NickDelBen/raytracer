#include "util.h"

// Generate a random number in the specified range
int get_random_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

// Generate a random float in the specified range
float get_random_float(float min, float max) {
    return (((float)rand()/(float)(RAND_MAX)) * (max - min)) + min;
}
