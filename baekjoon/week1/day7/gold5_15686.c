#include <stdio.h>
#define maxN 50

int town[maxN + 1][maxN + 1];

typedef struct
{
    int x;
    int y;
} House;

House chicken[14];
int wp = 0; // write pointer

int main()
{
    // 입력 받기
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int t;
            scanf("%d", &t);
            town[i][j] = t;
            // 치킨집 좌표와 함께 배열에 저장
            if (t == 2)
            {
                chicken[wp].x = j;
                chicken[wp].y = i;
                wp++;
            }
        }
    }

    return 0;
}