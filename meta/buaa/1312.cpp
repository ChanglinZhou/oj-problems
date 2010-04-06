#include <stdio.h>
#include <string.h>

#define M 10
#define N 20

void sort( int n, char** data )
{
    if( n <= 0 )
        return;

    int i, j;
    char* p;
    
    i = 1;
    while( i < n ) {
        j = i - 1;
        p = data[i];
        while( j >= 0 && strcmp( p, data[j] ) < 0 )
        {
            data[j+1] = data[j];
            --j;
        }
        data[j+1] = p;
        ++i;
    }
}

int main()
{
    char strings[N][M + 1];
    char* data[N];

    int i, n;
    
    scanf("%d", &n);
    
    for( i = 0; i < n; ++i )
    {
        scanf("%s", strings[i]);
        data[i] = strings[i];
    }
    sort( n, data );
    for( i = 0; i < n; ++i )
    {
        printf("%s\n", data[i]);
    }

    return 0;
}