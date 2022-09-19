#ifndef TRIGNOMETRY_PWM_H_
#define TRIGNOMETRY_PWM_H_

#include "math_utils.h"

#define SIN_ARRAY_SIZE 1024
#define SIN_ARRAY_SCALE 32767

extern short int sin_data_16bit[];
void init_sin_array(void);

#endif