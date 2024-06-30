#include <stdio.h>

// base N from A to B function
void fromTo(int n, int from, int to)
{
    if (n == 1)
    {
        printf("%d %d\n", from, to);
        return;
    }
    int aux; // 보조기둥
    int set[] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        if (set[i] != from && set[i] != to)
        {
            aux = set[i];
            break;
        }
    }
    fromTo(n - 1, from, aux);
    printf("%d %d\n", from, to);
    fromTo(n - 1, aux, to);
}

int main()
{
    int k;
    scanf("%d", &k);
    printf("%d\n", (1 << k) - 1);
    fromTo(k, 1, 3);
    return 0;
}