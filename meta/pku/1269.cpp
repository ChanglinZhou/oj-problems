/*

 *author: meta

 *date: 2008-12-17

 *problem: Intersecting Lines(POJ 1269)

 *algorithm: trivial

 *input: pair of plannar lines

 *output: relationship

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

typedef enum type {
    none,
    line,
    point
} type;

double det(const vector2d& v1, const vector2d& v2) {
    double x1 = v1.b.x - v1.a.x;
    double y1 = v1.b.y - v1.a.y;
    double x2 = v2.b.x - v2.a.x;
    double y2 = v2.b.y - v2.a.y;

    return (x1*y2 - y1*x2);
}

int cmp(double value)
{
    return (fabs(value) < eps) ? 0 : (value > 0 ? 1 : -1);
}

int direction(const point2d& pt, const vector2d& v2) {
    vector2d v1;
    v1.a = v2.a;
    v1.b = pt;
    double value = det(v1, v2);

    return cmp(value);
}

type lineIntersect(const vector2d& v1, const vector2d& v2) {
    if (cmp(det(v1, v2)))
        return point;

    if (direction(v1.a, v2) == 0)
        return line;

    return none;
}

point2d intersectPoint(const vector2d& Va, const vector2d& Vb) {
    point2d pt;

    vector2d v1, v2, v3, v4;
    
    v1.a = Va.a;
    v1.b = Vb.b;

    v2.a = Va.a;
    v2.b = Vb.a;

    pt.x = ( det(v1, Va)*Vb.a.x - det(v2, Va)*Vb.b.x ) /
           ( det(v1, Va) - det(v2, Va) );

    pt.y = ( det(v1, Va)*Vb.a.y - det(v2, Va)*Vb.b.y ) /
           ( det(v1, Va) - det(v2, Va) );

    return pt;
}

int main() 
{
    int n;
    vector2d v1, v2;

    scanf("%d", &n);
    
    printf("INTERSECTING LINES OUTPUT\n");
    while (n--) {
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", 
               &v1.a.x, &v1.a.y, &v1.b.x, &v1.b.y, 
               &v2.a.x, &v2.a.y, &v2.b.x, &v2.b.y);
        type t = lineIntersect(v1, v2);
        switch (t) {
            case none:
                printf("NONE\n");
                break;

            case line:
                printf("LINE\n");
                break;

            case point:
                point2d pt = intersectPoint(v1, v2);
                printf("POINT %.2lf %.2lf\n", pt.x, pt.y);
                break;
        }
    }
    printf("END OF OUTPUT\n");
    
    return 0;
}