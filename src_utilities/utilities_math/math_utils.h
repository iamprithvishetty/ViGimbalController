#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

#define EULAR 3

#define R2D 57.3F
#define D2R 0.01745329


// Define value of PI and 2xPI
#define M_PI      (3.141592653589793)
#define M_2PI     (M_PI * 2)

// To constrain float value from min to max
#define constrain_float(value, min, max) ((float)value>(float)max?(float)max:(((float)value<(float)min)?(float)min:(float)value))

// To constrain
#define constrain(value, min, max) (value>max?max:((value<min)?min:value))

float Rad2Deg(float x);
float Deg2Rad(float x);
float Round(float x);

#endif /* MATH_UTILS_H_ */