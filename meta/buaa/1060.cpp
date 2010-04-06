#include <stdio.h>
#include <string.h>

#define MAX 100

unsigned char tags[MAX];

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

BOOL IsVisited( char* visited, char ch )
{
    size_t len = strlen(visited);
    BOOL isIn = FALSE;
    int i = 0;
    while( i < len) {
        if(visited[i] == ch)
        {
            isIn = TRUE;
            break;
        }
        ++i;
    }

    if(!isIn) 
        visited[i] = ch;

    return isIn;
}

int permutation(char* buffer, int m)
{
    int sum = 0;
    if( m == 0 )
        return 1;

    size_t len = strlen(buffer);
    size_t i;
    char visited[MAX + 1];
    memset(visited, 0, sizeof(visited));

    for( i = 0; i < len; ++i )
    {
        if( tags[i] == 0 )
        {
            if(!IsVisited(visited, buffer[i]))
            {
                tags[i] = 1;
                sum += permutation(buffer, m-1);
                tags[i] = 0;
            }
        }
    }

    return sum;
}

int main()
{
    char buffer[MAX + 1];
    int m;
    while( scanf("%s", buffer ) )
    {
        if( strcmp(buffer, "-1" ) == 0 )
            break;

        scanf("%d", &m);
        memset(tags, 0, sizeof(tags));
        printf("%d\n", permutation(buffer, m));
    }

    return 0;
}
