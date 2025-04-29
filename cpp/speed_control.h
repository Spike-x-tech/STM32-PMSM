#ifndef SPEED_CONTROL_H
#define SPEED_CONTROL_H

#include "speed_pi.h"
#include "speed_smc.h"

// 控制模式枚举
typedef enum {
    CONTROL_PI,   // 仅 PI 控制
    CONTROL_SMC,  // 仅滑膜控制
    CONTROL_BOTH  // PI + 滑膜 组合控制
} ControlMode;

// 选择控制模式
void Set_Speed_Control_Mode(ControlMode mode);
ControlMode Get_Speed_Control_Mode(void);

// 计算速度环的 Iq 参考值
float Speed_Controller_Update(Speed_PI_Controller *pi, SMC_Controller *smc, 
                              float speed_Nr_ref, float speed_actual, float dt);

#endif // SPEED_CONTROL_H
