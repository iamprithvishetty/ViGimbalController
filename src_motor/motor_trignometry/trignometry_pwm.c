#include <math.h>
#include "trignometry_pwm.h"

/*
 * Create Array of size SIN_ARRAY_SIZE to store sin value ranging from (-2^15, +2^15]
 */
short int sin_data_16bit[SIN_ARRAY_SIZE];

/*
 * Initializes value in sin_data_16bit[] to make sin wave from
 * min amplitude: -SIN_ARRAY_SCALE to max amplitude: +SIN_ARRAY_SCALE
 */
void init_sin_array(void)
{
    for (int count = 0; count < SIN_ARRAY_SIZE; count++)
    {
        float angle_radians = count * M_2PI / SIN_ARRAY_SIZE; // mapping (0,SIN_ARRAY_SIZE-1) to (0,M_2PI)

        sin_data_16bit[count] = (short int)Round(sinf(angle_radians) * SIN_ARRAY_SCALE); // Coverting sin values to range from (-1,1) to (-SINARRAYSCALE,SINARRAYSCALE)
    }
}
