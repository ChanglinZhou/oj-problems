#include <stdio.h>
#include <string.h>

#define MAX 200

char tmp[MAX + 1];
char left[MAX + 1];
char right[MAX + 1];
char result[MAX + 2];

void add()
{
    int i;
    for( i = 0; i < MAX; ++i )
    {
        result[i] = left[i] + right[i] + result[i];
        result[i+1] = result[i] / 10;
        result[i] = result[i] % 10;
    }
}

void print()
{
    int highest = MAX + 1;
    while ( result[--highest] == 0 );

    while (highest >= 0) {
        printf("%d", result[highest--]);
    }
    printf("\n");
}

void init()
{
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(result, 0, sizeof(result));
    // left
    char *des, *src;
    scanf("%s", tmp);
    des = left;
    src = tmp + strlen(tmp) - 1;
    while( src >= tmp )
    {
        *des++ = (*src--) - '0';
    }

    // right
    scanf("%s", tmp);
    des = right;
    src = tmp + strlen(tmp) - 1;
    while( src >= tmp )
    {
        *des++ = (*src--) - '0';
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    
    while( t-- )
    {
        init();
        add();
        print();
    }

    return 0;
}