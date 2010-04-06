#include <iostream>
using namespace std;

int const nmax=200;

int c[nmax];
int v[nmax];

int cv[nmax][nmax];
int mv[nmax][nmax];
int top;

void init()
{
    memset(cv, 0, sizeof(cv));
    memset(mv, 0, sizeof(mv));
}

int cost(int s, int e)
{
    if (s == e)
        return c[s];

    if (!cv[s][e])
        cv[s][e] = cost(s+1, e) + c[s];
    return cv[s][e];
}

int value(int s, int e)
{
    if (s == e)
        return v[s];

    if (!cv[e][s])
        cv[e][s] = value(s+1, e) + v[s];
    return cv[e][s];
}

int maxvalue(int s, int e, int t)
{
    if (cost(s, e) <= t)
        return value(s, e);
    if (s == e)
        return 0;
    return max( maxvalue(s+1, e, t-cost(s, s)) + value(s, s), maxvalue(s+1, e, t) );
}

int maxvalue(int s, int e)
{
    if (!mv[s][e])
        mv[s][e] = maxvalue(s, e, top*(e-s+1)) + 1;
    return mv[s][e] - 1;
}

int maxgroupvalue(int s, int e, int m)
{
    int i, r = 0;
    if (e-s+1 == m) {
        for (i = s; i <= e; ++i)
            r += maxvalue(i, i);
    } else if (m == 1) {
        r = maxvalue(s, e);
    } else {
        for (i = s; i < e-m+1; ++i)
            r = max( r, maxgroupvalue(i+1, e, m-1) + maxvalue(s, i) );
    }
    return r;
}

int main()
{
    int n, m, i;
    while (cin>>n>>m>>top) {
        for (i = 0; i < n; ++i)
            cin>>c[i]>>v[i];
        init();
        cout<<maxgroupvalue(0, n-1, m)<<endl;
    }
    return 0;
}