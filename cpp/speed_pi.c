#include <math.h>
#include"speed_pi.h"

// 速度环 PI 控制器结构体
typedef struct {
    float Kp;         // 比例增益
    float Ki;         // 积分增益
    float integral;   // 积分项
    float output_max; // 输出最大限制
    float output_min; // 输出最小限制
} Speed_PI_Controller;

// **速度环 PI 控制器初始化**
void Speed_PI_Init(Speed_PI_Controller *pi, float Kp, float Ki, float output_max, float output_min) {
    pi->Kp = Kp;
    pi->Ki = Ki;
    pi->integral = 0.0f;
    pi->output_max = output_max;
    pi->output_min = output_min;
}

// **速度环 PI 计算**
float Speed_PI_Update(Speed_PI_Controller *pi, float speed_Nr_ref, float speed_actual, float dt) {
//  speed_ref是位置环的输出，speed_actual是测量的角速度值

    float speed_Nr_actual = speed_actual * 30.0f / M_PI;
    float error = speed_Nr_ref - speed_actual;  // 计算速度误差
    float proportional = pi->Kp * error;     // 计算比例项
    pi->integral += pi->Ki * error * dt;     // 计算积分项

    // 防止积分饱和
    if (pi->integral > pi->output_max) {
        pi->integral = pi->output_max;
    } else if (pi->integral < pi->output_min) {
        pi->integral = pi->output_min;
    }

    // 计算最终输出
    float output = proportional + pi->integral;

    // 限幅输出
    if (output > pi->output_max) {
        output = pi->output_max;
    } else if (output < pi->output_min) {
        output = pi->output_min;
    }

    return output;  // 返回 Iq 参考值
}
