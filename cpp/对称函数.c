#include <stdio.h>
#include <math.h>

#define A 0.4
#define N 128

int main() {
    float cogging_table_128[N];
    const float k = 0.8f / M_PI;

    for (int i = 0; i < N; i++) {
        float x = (M_PI / 2.0f) * i / (N - 1);   // x ∈ [0, π/2]
        float y = A * sinf(x);                  // 原始正弦值

        // 对称计算
        float x_sym = ((1 - k * k) * x + 2 * k * y) / (1 + k * k);
        float y_sym = ((k * k - 1) * y + 2 * k * x) / (1 + k * k);

        cogging_table_128[i] = y_sym; // 记录对称后的 y 值
    }

    // 打印数组，每行 8 个
    printf("float cogging_table_128[%d] = {\n", N);
    for (int i = 0; i < N; i++) {
        printf("    %.6f", cogging_table_128[i]);

        if (i < N - 1) {
            printf(",");
        }

        if ((i + 1) % 8 == 0 || i == N - 1) {
            printf("\n");
        }
    }
    printf("};\n");

    return 0;
}
