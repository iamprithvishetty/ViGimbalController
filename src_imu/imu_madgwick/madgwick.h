#ifndef MADGWICK_H
#define MADGWICK_H

typedef struct{

    float q0;
    float q1;
    float q2;
    float q3;

    float sampling_frequency;
    float beta;

}madgwick_filter;

void madgwick_init(madgwick_filter *current_filter, float current_beta, float current_sampling_frequency);
void madgwick_set_sampling_freq(madgwick_filter *current_filter, float current_sampling_frequency);
void madgwick_update(madgwick_filter *current_filter, float gx, float gy, float gz, float ax, float ay, float az);
void madgwick_compute_angle(madgwick_filter *current_filter, float *angle);
float inv_sqrt(float x);

#endif