#include <stdio.h>


double discount( int price )
{
    double dis;
    switch( ((price > 5000) ? 5000 : price) / 1000) 
    {
    case 5:
        dis = 0.8 * price;
        break;

    case 4:
    case 3:
        dis = 0.85 * price;
        break;

    case 2:
        dis = 0.9 * price;
        break;

    case 1:
        dis = 0.95 * price;
        break;

    default:
        dis = price;
        break;
    }

    return dis;
}

int main()
{
    int t, p;

    scanf("%d", &t);
    while( t-- )
    {
        scanf("%d", &p);
        printf("%.1lf\n", discount(p));
    }

    return 0;
}