#include <stdio.h>

// 2차원 배열을 이용한 0-1 KnapSack 문제 풀이

int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int main()
{
    // 입력 받기
    int N, K;
    scanf("%d %d", &N, &K);
    int table[N + 1][K + 1];
    int weight[N];
    int value[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &weight[i], &value[i]);
    }

    // 테이블 초기화
    for(int i=0; i<N+1; i++)
        table[i][0] = 0;
    for(int j=0; j<K+1; j++)
        table[0][j] = 0;

    // DP가 아니라 memorization 기법 아닌가
    for(int i=1; i<N+1; i++) {
        for(int j=1; j<K+1; j++) {
            if (weight[i-1]>j)
                table[i][j] = table[i-1][j];
            else 
                table[i][j] = max(value[i-1]+table[i-1][j-weight[i-1]], table[i-1][j]);
        }
    }

    printf("%d", table[N][K]);

    return 0;
}