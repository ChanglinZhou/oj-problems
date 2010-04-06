#include <stdio.h>

#define MAX 100

typedef struct t_Person {
    unsigned short id;
    unsigned short time;
} Person;

Person people[MAX];

void sort( int n )
{
    int i, j;
    Person ps;

    i = 1;
    while( i < n )
    {
        j = i - 1;
        ps = people[i];
        while( j >= 0 && ps.time < people[j].time )
        {
            people[j+1] = people[j];
            --j;
        }
        people[j+1] = ps;
        ++i;
    }
}

int main()
{
    int i, t, n, sum;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        i = 0;
        while ( i < n )
        {
            scanf("%d", &people[i].time);
            people[i].id = i + 1;
            ++i;
        }

        sort( n );

        sum = i = 0;
        while ( i < n )
        {
            if ( i > 0 )
                printf(" ");
            printf("%d", people[i].id);

            sum += people[i].time * (n - i - 1);
            ++i;
        }
        printf("\n%.2f\n", (float)sum / n);
    }
    return 0;
}