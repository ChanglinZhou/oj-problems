#include <stdio.h>

int main()
{
    int n, data, sum;
    while (scanf("%d", &n) != EOF)
    {
        sum = 0;
        while (n--)
        {
            scanf("%d", &data);
            sum += data;
        }
        printf("%d\n", sum);
    }

    return 0;
}