#include <stdio.h>
#define MAX 100

char rgb[MAX + 1][MAX + 1];

// DFS with stack
int pointer = 0; // stack pointer
int normal = 0;  // 정상인이 보는 구역의 개수
int blind = 0; // 적록색맹

typedef struct
{
    int x;
    int y;
} Color;

Color stack[MAX * MAX + 2];

void push(int x, int y)
{
    stack[pointer].x = x;
    stack[pointer].y = y;
    pointer++;
}

Color pop()
{
    return stack[--pointer];
}

int isEmpty()
{
    return pointer == 0; // 1(true)이면 stack is empty
    // note that number of zone is +1 when stack becomes empty
}

int main()
{
    // 입력 받기
    int n;
    scanf("%d", &n);
    getchar(); // 버퍼에 남아있는 개행문자 제거
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rgb[i][j] = getchar();
        }
        getchar();
    }

    // 우, 하, 좌, 상 순 탐색
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, -1, 0, 1};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (rgb[i][j] == '0' || rgb[i][j] == '1')
                continue;             // 이미 방문한 좌표 건너뛰기
            char current = rgb[i][j]; // 현재 탐색 중인 문자
            push(i, j);
            while (!isEmpty())
            {
                Color c = pop();
                switch (rgb[c.x][c.y])
                {
                case 'R':
                case 'G':
                    rgb[c.x][c.y] = '0';
                    break;
                case 'B':
                    rgb[c.x][c.y] = '1';
                    break;
                } // 방문 표시
                for (int k = 0; k < 4; k++)
                {
                    int newX = c.x + dx[k];
                    int newY = c.y + dy[k];
                    if (newX < 0 || newX >= n || newY < 0 || newY >= n)
                        continue; // 범위 안인지 체크
                    if (rgb[newX][newY] == current)
                        push(newX, newY);
                }
            }
            normal++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (rgb[i][j] == 'c')
                continue;
            char current = rgb[i][j]; // 현재 탐색 중인 문자
            push(i, j);
            while (!isEmpty())
            {
                Color c = pop();
                rgb[c.x][c.y] = 'c';
                for (int k = 0; k < 4; k++)
                {
                    int newX = c.x + dx[k];
                    int newY = c.y + dy[k];
                    if (newX < 0 || newX >= n || newY < 0 || newY >= n)
                        continue; // 범위 안인지 체크
                    if (rgb[newX][newY] == current)
                        push(newX, newY);
                }
            }
            blind++;
        }
    }
    printf("%d %d", normal, blind);
    return 0;
}