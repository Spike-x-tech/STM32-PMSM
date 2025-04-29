#define PI_F 3.14159265358979323846f

// 输入期望转速，电机转子角速度，电机转子角度，时间间隔，虚拟齿槽转矩系数，虚拟阻尼系数
float ComputeIqVctRef(float Rotational_speed, float theta_m, float Omega_m, float Ts, float A, float k)
{
    // 计算Omega_ref，单位：rad/s
    extern float Omega_ref;
    Omega_ref = Rotational_speed * PI_F / 30;

    // 假设theta_ref是一个全局变量
    extern float theta_ref;

    // 计算theta_ref，即Omega_ref的积分，得到期望的电机转子角度
    theta_ref += Omega_ref * Ts;

    // 使用fmod来限制theta_ref在0到2π的范围内
    theta_ref = fmod(theta_ref, 2 * PI_F);
    if (theta_ref < 0) {
        theta_ref += 2 * PI_F;  // 确保theta_ref为正值
    }

    // 计算Iq_VCT_Ref
    float Iq_VCT_Ref = A * sin(theta_ref - theta_m) + k * (Omega_ref - Omega_m);

    return Iq_VCT_Ref;
}
