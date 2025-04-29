#ifndef SPEED_PI_H
#define SPEED_PI_H

#include <stdint.h>

typedef struct {
    float Kp;
    float Ki;
    float integral;
    float output_max;
    float output_min;
} Speed_PI_Controller;

void Speed_PI_Init(Speed_PI_Controller *pi, float Kp, float Ki, float output_max, float output_min);
float Speed_PI_Update(Speed_PI_Controller *pi, float speed_Nr_ref, float speed_actual, float dt) ;

#endif
