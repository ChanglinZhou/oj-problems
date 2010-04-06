#include <stdio.h>
#include <math.h>

#define PI 3.14

void display( int A, int B )
{
    printf("%d\n",  A * B);
}

void display( double r ) 
{
    printf("%.2lf\n", PI * r * r);
}

void display( double a, double b, double c )
{
    double delta = b*b - 4*a*c;
    if( delta < 0.0 )
    {
        printf("no answer!\n");
    }
    else {
        printf("%.2lf\n", (-b - sqrt(delta))/(2*a));
    }
}
int main()
{
    unsigned int type;
    int A, B;
    double r, a, b, c;

    while( scanf("%d", &type) != EOF )
    {
        switch(type) 
        {
        case 1:
            scanf("%d %d", &A, &B);
            display(A, B);
            break;

        case 2:
            scanf("%lf", &r);
            display(r);
            break;
            
        case 3:
            scanf("%lf %lf %lf", &a, &b, &c);
            display(a, b, c);
            break;

        default:
            break;
        }
    }

    return 0;
}