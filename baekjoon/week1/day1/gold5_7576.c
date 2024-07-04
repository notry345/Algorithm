#include <stdio.h>
// 전처리기 지시자를 이용하여 정의한 최대 크기를 나타내는 상수
#define MAX 1000

int m, n; // 가로, 세로
int box[MAX + 5][MAX + 5];
int write = 0;  // write pointer
int read = 0;   // read pointer
int unripe = 0; // 안익은 토마토 개수

typedef struct
{
    int x;
    int y;
    int day;
} Tomato;

// 객체 배열
Tomato queue[MAX * MAX + 5];

// 배열로 큐 구현
void push(int x, int y, int day)
{
    if (write >= MAX * MAX + 5)
    {
        printf("Queue overflow.\n");
        return;
    }
    queue[write].x = x;
    queue[write].y = y;
    queue[write].day = day;
    write++;
}

Tomato pop(void)
{
    return queue[read++];
}

int isEmpty(void)
{
    return write == read; // true면 1, false면 0
}

int main()
{
    scanf("%d %d", &m, &n);

    // 배열 초기화
    for (int i = 0; i < n; i++) // 세로
    {
        for (int j = 0; j < m; j++) // 가로
        {
            int x;
            scanf("%d", &x);
            box[i][j] = x;

            if (x == 1)
            {
                push(i, j, 0);
            } // 익은 토마토 큐에 넣기
            else if (x == 0)
            {
                unripe++; // 안익은 토마토 개수 세기
            }
        }
    }
    // 처음부터 토마토 다 익어 있음!
    if (unripe == 0)
    {
        printf("0");
        return 0;
    }

    // 토마토 익히기
    int dx[] = {-1, 0, 1, 0}; // 좌우 이동
    int dy[] = {0, 1, 0, -1}; // 상하 이동
    while (!isEmpty())
    {
        Tomato current = pop();
        // 위 아래 양 옆 확인
        for (int i = 0; i < 4; i++)
        {
            int checkX = current.x + dx[i];
            int checkY = current.y + dy[i];

            // 배열 범위 안인지 체크
            if (checkX < 0 || checkX >= n || checkY < 0 || checkY >= m)
                continue;
            // 안익은 토마토 익히고 큐에 넣기
            if (box[checkX][checkY] == 0)
            {
                box[checkX][checkY] = 1;
                unripe--;
                push(checkX, checkY, current.day + 1);
            }
        }
        // 토마토 다 익음!
        if (unripe == 0)
        {
            printf("%d", current.day + 1);
            return 0;
        }
    }
    // 토마토가 다 익지 못했음!
    printf("-1");
    return 0;
}