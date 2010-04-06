# include <stdio.h>
# include <stdlib.h>

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

#define MAX( a, b ) \
    ((a) > (b) ? (a) : (b))

#define MIN( a, b ) \
    ((a) < (b) ? (a) : (b))

typedef enum Shape { C, R } Shape;

typedef struct s_Point {
    float x;
    float y;
} Point;

typedef struct s_Rectangle {
    Point pt1;
    Point pt2;
} Rectangle;

typedef struct s_Circle {
    Point center;
    float radius;
} Circle;

typedef union u_CR {
    Rectangle rect;
    Circle circ;
} t_CR;

typedef struct CR {
    t_CR data;
    Shape s;
} CR;


BOOL IsInRectangle( const Rectangle& rect, const Point& pt )
{
    float left = MIN( rect.pt1.x, rect.pt2.x );
    float right = MAX( rect.pt1.x, rect.pt2.x );
    float bottom = MIN( rect.pt1.y, rect.pt2.y );
    float up = MAX( rect.pt1.y, rect.pt2.y );

    if ( left < pt.x && pt.x < right &&
        bottom < pt.y && pt.y < up )
        return TRUE;
    else
        return FALSE;
}


BOOL IsInCircle( const Circle& circ, const Point& pt )
{
    float distanceX = circ.center.x - pt.x;
    float distanceY = circ.center.y - pt.y;

    if ( (distanceX*distanceX + distanceY*distanceY) < (circ.radius*circ.radius) )
        return TRUE;
    else
        return FALSE;
}


int main( )
{
    int n, m;

    while ( scanf( "%d %d", &n, &m ) != EOF )
    {
        if ( n == 0 || m == 0 )
            break;

        // memory allocation for shapes and points
        CR* p1 = (CR*) malloc( sizeof(CR) * n );
        Point* p2 = (Point*) malloc( sizeof(Point) * m );

        int i, j;
        char shape;

        // read shapes data
        for( i = 0; i < n; ++i )
        {
            scanf( "\n%c", &shape );

            switch ( shape )
            {
            case 'r':
                scanf( "%f %f %f %f", &p1[i].data.rect.pt1, &p1[i].data.rect.pt1.y,
                    &p1[i].data.rect.pt2.x, &p1[i].data.rect.pt2.y );
                p1[i].s = R;
                break;

            case 'c':
                scanf( "%f %f %f", &p1[i].data.circ.center.x, &p1[i].data.circ.center.y,
                    &p1[i].data.circ.radius );
                p1[i].s = C;
                break;

            default:
                break;
            }
        }

        // read points data
        for ( j = 0; j < m; ++j )
        {
            scanf( "%f %f", &p2[j].x, &p2[j].y );
        }

        for ( j = 0; j < m; ++j )
        {
            int sum = 0;
            for ( i = 0; i < n; ++i )
            {
                if( p1[i].s == C )
                    sum += IsInCircle( p1[i].data.circ, p2[j] );
                else // Shape = R
                    sum += IsInRectangle( p1[i].data.rect, p2[j] );
            }

            printf( "%d\n", sum );
        }
        // free out memory
        free( p1 );
        free( p2 );
    }

    return 0;
}