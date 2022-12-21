#include "madgwick.h"
#include "math.h"

#include "ch.h"
#include "hal.h"

#include "misc_utils.h"
#include "math_utils.h"

void madgwick_init(madgwick_filter *current_filter, float current_beta, float current_sampling_frequency) {

	current_filter->q0 = 1.0f;
	current_filter->q1 = 0.0f;
	current_filter->q2 = 0.0f;
	current_filter->q3 = 0.0f;

	current_filter->beta = current_beta;
	current_filter->inv_sampling_frequency = 1.0f/current_sampling_frequency;
	
}

void madgwick_set_sampling_freq(madgwick_filter *current_filter, float current_sampling_frequency) {

	current_filter->inv_sampling_frequency = 1.0f/current_sampling_frequency;

}

void madgwick_set_beta(madgwick_filter *current_filter, float current_beta) {
	current_filter->beta = current_beta;
}

void madgwick_update(madgwick_filter *current_filter, float gx, float gy, float gz, float ax, float ay, float az) {
	
	float recipNorm;
	float s0, s1, s2, s3;
	float q1_dot, q2_dot, q3_dot, q4_dot;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	// Convert gyroscope degrees/sec to radians/sec
	gx *= 0.0174533f;
	gy *= 0.0174533f;
	gz *= 0.0174533f;

	// Rate of change of quaternion from gyroscope
	q1_dot = 0.5f * (-current_filter->q1 * gx - current_filter->q2 * gy - current_filter->q3 * gz);
	q2_dot = 0.5f * (current_filter->q0 * gx + current_filter->q2 * gz - current_filter->q3 * gy);
	q3_dot = 0.5f * (current_filter->q0 * gy - current_filter->q1 * gz + current_filter->q3 * gx);
	q4_dot = 0.5f * (current_filter->q0 * gz + current_filter->q1 * gy - current_filter->q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = inv_sqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * current_filter->q0;
		_2q1 = 2.0f * current_filter->q1;
		_2q2 = 2.0f * current_filter->q2;
		_2q3 = 2.0f * current_filter->q3;
		_4q0 = 4.0f * current_filter->q0;
		_4q1 = 4.0f * current_filter->q1;
		_4q2 = 4.0f * current_filter->q2;
		_8q1 = 8.0f * current_filter->q1;
		_8q2 = 8.0f * current_filter->q2;
		q0q0 = current_filter->q0 * current_filter->q0;
		q1q1 = current_filter->q1 * current_filter->q1;
		q2q2 = current_filter->q2 * current_filter->q2;
		q3q3 = current_filter->q3 * current_filter->q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * current_filter->q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * current_filter->q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * current_filter->q3 - _2q1 * ax + 4.0f * q2q2 * current_filter->q3 - _2q2 * ay;
		recipNorm = inv_sqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		q1_dot -= current_filter->beta * s0;
		q2_dot -= current_filter->beta * s1;
		q3_dot -= current_filter->beta * s2;
		q4_dot -= current_filter->beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	current_filter->q0 += q1_dot * current_filter->inv_sampling_frequency;
	current_filter->q1 += q2_dot * current_filter->inv_sampling_frequency;
	current_filter->q2 += q3_dot * current_filter->inv_sampling_frequency;
	current_filter->q3 += q4_dot * current_filter->inv_sampling_frequency;

	// Normalise quaternion
	recipNorm = inv_sqrt(current_filter->q0 * current_filter->q0 + current_filter->q1 * current_filter->q1 + current_filter->q2 * current_filter->q2 + current_filter->q3 * current_filter->q3);
	current_filter->q0 *= recipNorm;
	current_filter->q1 *= recipNorm;
	current_filter->q2 *= recipNorm;
	current_filter->q3 *= recipNorm;

}

void madgwick_compute_angle(madgwick_filter *current_filter, float *angle) {

	angle[ROLL] = atan2f(current_filter->q0*current_filter->q1 + current_filter->q2*current_filter->q3, 0.5f - current_filter->q1*current_filter->q1 - current_filter->q2*current_filter->q2)*R2D;
	angle[PITCH] = asinf(-2.0f * (current_filter->q1*current_filter->q3 - current_filter->q0*current_filter->q2))*R2D;
	angle[YAW] = atan2f(current_filter->q1*current_filter->q2 + current_filter->q0*current_filter->q3, 0.5f - current_filter->q2*current_filter->q2 - current_filter->q3*current_filter->q3)*R2D;

}

// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

float inv_sqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	y = y * (1.5f - (halfx * y * y));
	return y;
}