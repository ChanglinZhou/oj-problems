#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define TOLERANCE 0.000001


double f( )
{
    double x2 = PI / 4;
    double x1;

    do {
        x1 = x2;
        x2 = x1 + ( cos(x1) - x1 ) / ( sin(x1) + 1 );
    } while( (x2 - x1) >= TOLERANCE || (x2 - x1) <= -TOLERANCE );

    return x2;
}
int main()
{
    printf("%.6lf", f());

    return 0;
}