#include <stdio.h>

int main()
{
    int n, m, data, sum;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &m);
        sum = 0;
        while (m--)
        {
            scanf("%d", &data);
            sum += data;
        }
        printf("%d\n", sum);
    }

    return 0;
}