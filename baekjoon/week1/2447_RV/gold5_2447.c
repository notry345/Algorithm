#include <stdio.h>

int n;

// x와 y는 좌표 (x, y)
void star(int x, int y, int n)
{
    if ((x / n) % 3 == 1 && (y / n) % 3 == 1)
        printf(" ");
    else
    {
        if (n == 1)
        {
            printf("*");
            return;
        }
        star(x, y, n / 3);
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            star(i, j, n);
        }
        printf("\n");
    }

    return 0;
}