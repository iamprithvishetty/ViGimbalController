#include <math.h>
#include "math_utils.h"

/*
 * Convert from Radians to Degree
 */
float Rad2Deg(float x)
{
    return x * (180.0F / M_PI);
}

/*
 * Convert from Degree to Radians
 */
float Deg2Rad(float x)
{
    return x * (M_PI / 180.0F);
}

/*
 * Round the value to the nearest integer
 */
float Round(float x)
{
    if (x >= 0)
    {
        return x + 0.5F;
    }
    else
    {
        return x - 0.5F;
    }
}