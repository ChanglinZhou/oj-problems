#include <stdio.h>

#define MAX 400

int opt[MAX][3];

int distR( int r, int g, int b )
{
    return (255 - r) + g + b;
}

int distG( int r, int g, int b )
{
    return (255 - g) + r + b;
}

int distB( int r, int g, int b )
{
    return (255 - b) + r + g;
}


int main()
{
    return 0;
}