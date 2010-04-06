/*

 *author : meta

 *date : 2008-11-14

 *problem : Beauty Contest(POJ 2187)

 *algorithm : Convex Hull

 *input : the number of points at line 1, the coordinate of each point at line 2.

 *output : squared distance between the pair of farms that are farthest apart from each other.

*/

#include <cstdio>
#include <cassert>
#include <cstdlib>

using namespace std;

#define MAX_LEN 50000

struct point2d {
    int x;
    int y;
};

point2d pts[MAX_LEN];
int left[MAX_LEN];
int ch[MAX_LEN];

void swap(point2d& pt1, point2d& pt2)
{
    if (&pt1 == &pt2)
        return;

    point2d tmp = pt1;
    pt1 = pt2;
    pt2 = tmp;
}

void setRespectPoint(point2d* pts, int n)
{
    if ( pts == NULL || n < 1 )
        return;

    int pos = 0;

    for ( int i = 1; i < n; ++i ) {
        
        if ( pts[i].y < pts[pos].y ) {
            pos = i;
        }
        else if ( pts[i].y == pts[pos].y && 
                  pts[i].x < pts[pos].x ) {
            pos = i;
        }
    }

    swap(pts[0], pts[pos]);
}

int Multi(const point2d& pt0, const point2d& pt1, const point2d& pt2)
{
    // (p1 - p0) X (p2 - p0)
    return (pt1.x - pt0.x)*(pt2.y - pt0.y) - (pt2.x - pt0.x)*(pt1.y - pt0.y);
}

int distance( const point2d& pt1, const point2d& pt2 )
{
    return (pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y);
}

int compare(const void* pt1, const void* pt2)
{
    assert( pt1 != NULL && pt2 != NULL );

    const point2d& p1 = *static_cast<const point2d*>(pt1);
    const point2d& p2 = *static_cast<const point2d*>(pt2);

    int value = -Multi(pts[0], p1, p2);

    if (value == 0)
        value = distance(pts[0], p1) - distance(pts[0], p2);

    return value;
}

int area( const point2d& pt1, const point2d& pt2, const point2d& pt3 )
{
    // 2 * area of triangle
    return (pt1.x*pt2.y - pt1.x*pt3.y - pt2.x*pt1.y + pt3.x*pt1.y + pt2.x*pt3.y - pt3.x*pt2.y);
}

int next(int p, int n)
{
    return (p + 1) % n;
}

int diameter( int* ch, int n )
{
    int diam = 0;
    int dist1, dist2;
    int p = 0;
    int q = next(p, n);

    while ( p < n ) {
        while ( area(pts[ch[p]], pts[ch[next(p, n)]], pts[ch[next(q, n)]]) > 
                area(pts[ch[p]], pts[ch[next(p, n)]], pts[ch[q]]) ) {
                q = next(q, n);
        }
        dist1 = distance(pts[ch[p]], pts[ch[q]]);
        dist2 = distance(pts[ch[next(p, n)]], pts[ch[q]]);
        if (dist1 > diam)
            diam = dist1;
        if (dist2 > diam)
            diam = dist2;

        ++p;
    }

    return diam;
}


int main()
{
    int n;
    
    FILE* in = fopen("msworld.11.in", "r");
    if (in) {
        fscanf(in, "%d", &n);

        for ( int i = 0; i < n; ++i ) {
            fscanf( in, "%d %d", &pts[i].x, &pts[i].y );
        }
    }
    //scanf("%d", &n);

    //for ( int i = 0; i < n; ++i ) {
    //    scanf( "%d %d", &pts[i].x, &pts[i].y );
    //}

    
    // set the point with least Y-Coordinate, if there're many points, get the 
    // leftmost
    setRespectPoint(pts, n);
    // sort the left points with polar angle to p0
    qsort( pts + 1, n - 1, sizeof(point2d), compare );

    int m = 0;
    int s = 1;
    while ( s < n ) {
        while ( ++s < n ) {
            if (Multi(pts[0], pts[s - 1], pts[s]) != 0)
                break;
        }
        left[m++] = s - 1;
    }

    // push p0, p1, p2
    ch[0] = 0;
    ch[1] = left[0];
    int top = 1;

    for ( int i = 1; i < m; ++i ) {
        while ( Multi(pts[ch[top]], pts[ch[top - 1]], pts[left[i]]) >= 0 ) {
            --top;
        }
        ch[++top] = left[i];
    }

    if (top == 1)
        printf( "%d\n", distance(pts[ch[0]], pts[ch[1]]) );
    else
        printf( "%d\n", diameter(ch, top + 1) );

    return 0;
}
