#include <stdio.h>

#define PRECISION 0.0001

double sqrt( double x )
{
    double y1, y2;
    y1 = 1.0;
    
    do {
        y2 = x / y1;
        y1 = (y1 + y2) / 2;
    } while ((y1 - y2) > PRECISION || (y1 - y2) < -PRECISION);

    return y1;
}

int main()
{
    int t;
    double x;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%lf", &x);
        
        printf("%.3lf\n", sqrt(x));
    }

    return 0;
}