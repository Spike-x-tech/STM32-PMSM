#include "speed_control.h"

// **全局变量**: 当前的控制模式（默认使用 PI 控制）
static ControlMode control_mode = CONTROL_PI;

// **设置速度环控制模式**
void Set_Speed_Control_Mode(ControlMode mode) {
    control_mode = mode;
}

// **获取当前控制模式**
ControlMode Get_Speed_Control_Mode(void) {
    return control_mode;
}

// **速度环控制计算**
float Speed_Controller_Update(Speed_PI_Controller *pi, SMC_Controller *smc, 
                              float speed_Nr_ref, float speed_actual, float dt) {
    float iq_ref_pi = 0.0f;
    float iq_ref_smc = 0.0f;

    // 获取当前控制模式
    ControlMode mode = Get_Speed_Control_Mode();

    switch (mode) {
        case CONTROL_PI:
            iq_ref_pi = Speed_PI_Update(pi, speed_Nr_ref, speed_actual, dt);
            return iq_ref_pi;  // 仅返回 PI 控制输出

        case CONTROL_SMC:
            iq_ref_smc = SMC_Controller_Update(smc, speed_Nr_ref, speed_actual, dt);
            return iq_ref_smc;  // 仅返回滑膜控制输出

        case CONTROL_BOTH:
            iq_ref_pi = Speed_PI_Update(pi, speed_Nr_ref, speed_actual, dt);
            iq_ref_smc = SMC_Controller_Update(smc, speed_Nr_ref, speed_actual, dt);
            return iq_ref_pi + iq_ref_smc;  // 组合 PI + 滑膜 控制输出

        default:
            return 0.0f;  // 默认输出 0
    }
}
