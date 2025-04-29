#include <stdio.h>
#include <math.h>

#define A 0.4  // 峰值 0.4
#define N 256   // 点数

int main() {
    float cogging_table_128[N];

    // 计算正弦波四分之一周期
    for (int i = 0; i < N; i++) {
        cogging_table_128[i] = A * cos(2*(M_PI / 2) * i / (N - 1));
    }

    // 打印数组，每行 8 个
    printf("float cogging_table_128[%d] = {\n", N);
    for (int i = 0; i < N; i++) {
        printf("    %.6f", cogging_table_128[i]);

        if (i < N - 1) {
            printf(","); // 最后一项不加逗号
        }

        // 每 8 个一行，或最后一个换行
        if ((i + 1) % 8 == 0 || i == N - 1) {
            printf("\n");
        }
    }
    printf("};\n");

    return 0;
}
