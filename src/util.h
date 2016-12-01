// Collection of useful helper functions

#ifndef _h_util
#define _h_util

#include <stdlib.h>

/*********************
* Generate a random integer number in the specified range
* @param min Minimum value of generated number
* @param max Maximum value of generated number
*********************/
int get_random_int(int min, int max);

/*********************
* Generate a random float in the specified range
* @param min Minimum value of generated number
* @param max Maximum value of generated number
*********************/
float get_random_float(float min, float max);

#endif