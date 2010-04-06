#include <stdio.h>
#include <math.h>

#define PRECISION 0.000000001

int main()
{
    unsigned int i;
    double e, delta;
    delta = e = 1.0;
    i = 0;
    while ( delta >= PRECISION )
    {
        delta /= ++i;
        e += delta;
    }
    int n, x;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        printf("%.5lf\n", pow(e, x));
    }
    return 0;
}