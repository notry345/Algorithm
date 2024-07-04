#include <stdio.h>
#define MAX 100

int M, N, H;
int table[MAX + 2][MAX + 2][MAX + 2];

int wp = 0;
int rp = 0;

int unripe = 0;

typedef struct
{
    int x;
    int y;
    int z;
    int day;
} Tomato;

Tomato queue[MAX * MAX * MAX + 2];

void push(int z, int y, int x, int day)
{
    queue[wp].x = x;
    queue[wp].y = y;
    queue[wp].z = z;
    queue[wp].day = day;
    wp++;
}

Tomato pop()
{
    return queue[rp++];
}

int main()
{
    scanf("%d %d %d", &M, &N, &H);

    // 입력
    for (int i = 0; i < H; i++) // 높이
    {
        for (int j = 0; j < N; j++) // 세로
        {
            for (int k = 0; k < M; k++) // 가로
            {
                int input;
                scanf("%d", &input);
                table[i][j][k] = input;
                // 토마토 큐에 넣기
                if (input == 1)
                    push(i, j, k, 0);
                // 안 익은 토마토 개수 세기
                else if (input == 0)
                    unripe++;
            }
        }
    }

    if (unripe == 0)
    {
        printf("0");
        return 0;
    }

    int dx[] = {1, 0, -1, 0, 0, 0}; // 행
    int dy[] = {0, 1, 0, -1, 0, 0}; // 열
    int dz[] = {0, 0, 0, 0, 1, -1}; // 상하

    // 토마토 익히기
    while (rp != wp)
    { // rp가 wp 따라잡으면 큐는 empty
        Tomato current = pop();
        for (int i = 0; i < 6; i++)
        {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            int newZ = current.z + dz[i];

            if (newZ < 0 || newZ >= H || newY < 0 || newY >= N || newX < 0 || newX >= M)
                continue;
            if (table[newZ][newY][newX] == 0)
            {
                table[newZ][newY][newX] = 1;
                push(newZ, newY, newX, current.day + 1);
                unripe--;
            }
        }
        // 토마토 다 익음
        if (unripe == 0)
        {
            printf("%d", current.day + 1);
            return 0;
        }
    }
    // 토마토 다 못 익음
    printf("-1");
    return 0;
}