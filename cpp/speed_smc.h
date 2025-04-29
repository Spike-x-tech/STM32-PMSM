#ifndef SMC_SPEED_H
#define SMC_SPEED_H

#include <stdint.h>

typedef struct {
    float c;
    float q;
    float D;
    float integral;
    float output_max;
    float output_min;
} SMC_Controller;

void SMC_Controller_Init(SMC_Controller *smc, float c, float q, float D, float output_max, float output_min);
float SMC_Controller_Update(SMC_Controller *smc, float speed_Nr_ref, float speed_actual, float dt);

#endif
