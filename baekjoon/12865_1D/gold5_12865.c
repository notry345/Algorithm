#include <stdio.h>
#include <stdbool.h>

// 1차원 배열을 이용한 0-1 KnapSack 문제 풀이
// 공간효율성 개선

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    // 입력 받기
    int N, K;
    scanf("%d %d", &N, &K);
    int table[2][K + 1];
    int weight[N];
    int value[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &weight[i], &value[i]);
    }

    // 테이블 초기화
    for (int j = 0; j < K + 1; j++)
        table[0][j] = 0;
    table[1][0] = 0;

    // 구현
    bool a = true; // 스위치 역할
    int b;
    for (int i = 1; i < N + 1; i++)
    {
        // 스위치에 의해 결정되는 배열 행 인덱스
        if (a == true)
            b = 1;
        else
            b = 0;

        for (int j = 1; j < K + 1; j++)
        {
            if (weight[i-1] > j)
                table[b][j] = table[!b][j];
            else
                table[b][j] = max(value[i - 1] + table[!b][j - weight[i - 1]], table[!b][j]);
        }
        a = !a;
    }
    printf("%d", table[b][K]);

    return 0;
}