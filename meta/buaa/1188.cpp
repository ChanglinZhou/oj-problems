#include <stdio.h>

#define MAX 500

int main()
{
    int side1, side2, hypotenuse;

    for( side1 = 3; side1 <= MAX; ++side1 )
        for ( side2 = side1 + 1; side2 <= MAX; ++side2 )
            for ( hypotenuse = side2 + 1; hypotenuse <= MAX; ++hypotenuse )
            {
                if ( side1 * side1 + side2 * side2 == hypotenuse * hypotenuse )
                {
                    printf("%d %d %d\n", side1, side2, hypotenuse);
                    break;
                }
            }
    return 0;
}