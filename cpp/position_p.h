#ifndef POSITION_P_H
#define POSITION_P_H

// 位置环 P 控制结构体
typedef struct {
    float Kp;          // 位置环比例增益
    float output_max;  // 最大速度限幅 (rad/s)
    float output_min;  // 最小速度限幅 (rad/s)
    float feeforward;  // 前馈增益 0.7-0.9
} Position_Controller;

// **位置环 P 控制初始化**
void Position_Controller_Init(Position_Controller *pos, float Kp, float output_max, float output_min, float feeforward);


// **位置环 P 控制计算**
float Position_Controller_Update(Position_Controller *pos, float position_ref, float position_actual);

#endif