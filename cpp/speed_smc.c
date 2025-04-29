#include <math.h>
#include"speed_smc.h"

// 滑膜控制器结构体
typedef struct {
    float c;         // 设计参数 c
    float q;         // 滑膜控制参数 q
    float D;         // 系统参数 D = 3 * P_n * ph_f / (2 * J)
    float integral;  // 积分项 iq_ref
    float output_max; // 输出限幅
    float output_min; // 输出限幅
} SMC_Controller;

// **滑膜控制器初始化**
void SMC_Controller_Init(SMC_Controller *smc, float c, float q, float D, float output_max, float output_min) {
    smc->c = c;
    smc->q = q;
    smc->D = D;
    smc->integral = 0.0001f;  // 初始积分项为 0.0001
    smc->output_max = output_max;
    smc->output_min = output_min;
}

// **滑膜控制计算**
float SMC_Controller_Update(SMC_Controller *smc, float speed_Nr_ref, float speed_actual, float dt) {
    // 计算滑膜变量 x1 和 x2
    float speed_Nr_actual = speed_actual * 30.0f / M_PI;
    static float x1_last = 0.0f;  // 用于计算 x2
    float x1 = (speed_Nr_ref - speed_Nr_actual) * M_PI /30.0f;    // x1 = 期望速度 - 实际速度
    float x2 = (x1 - x1_last) / dt;         // x2 = dx1/dt (速度误差的导数)
    x1_last = x1;                           // 更新 x1 用于下一次计算

    // 计算滑膜面 s
    float s = smc->c * x1 + x2;

    // 计算滑膜控制律 u 
    float u = (1.0f / smc->D) * (smc->c * x2 + (s > 0 ? 1 : (s < 0 ? -1 : 0)) + smc->q * s);

    // 计算 iq_ref 
    smc->integral += u * dt;  // iq_ref = ∫ u dt

    // 限制积分项，防止积分饱和
    if (smc->integral > smc->output_max) {
        smc->integral = smc->output_max;
    } else if (smc->integral < smc->output_min) {
        smc->integral = smc->output_min;
    }

    return smc->integral;  // 返回 q 轴电流 iq_ref
}