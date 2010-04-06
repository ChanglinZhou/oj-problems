/*

 *author: meta

 *date: 2008-12-17

 *problem: Intervals(POJ 1375)

 *algorithm: tangent

 *input: situations in basement

 *output: non-overlapping intervals

*/

#include <cstdio>
#include <cmath>

using namespace std;

const double eps = 1e-8;

typedef struct point2d {
    double x, y;
} point2d;

typedef struct vector2d {
    point2d a, b;
} vector2d;

/* anticlockwise rotate
 * p = x + y*i
 * p*(cost(d) + i*sin(d))
*/
point2d rotate(point2d pt, double angle) {
    double x = pt.x;
    double y = pt.y;

    pt.x = x*cos(angle) - y*sin(angle);
    pt.y = x*sin(angle) + y*cos(angle);
    return pt;
}

int main()
{
    return 0;
}