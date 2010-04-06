#include <iostream>
#include <cstdio>
using namespace std;

struct ship {
    int p, o;
};

int const num = 30000;
ship bship[num+1];

inline void init()
{
    memset(bship, 0, sizeof(bship));
}

int find(int x, int& o)
{
    int r, p;

    p = bship[x].p;                     // get parent
    if (p <= 0) {                       // x is root
        o = bship[x].o;
        r = x;
    } else {
        r = find(p, o);
        o += bship[x].o;
        if (p != r) {                   // path compress
            bship[x].p = r;
            bship[x].o = o - bship[r].o;
        }
    }

    return r;
}

void merge(int i, int j)
{
    int pi, pj, o;
    pi = find(i, o), pj = find(j, o);

    if (pi == pj)
        return;

    bship[pi].o -= bship[pj].p - 1;
    if (bship[pi].p >= bship[pj].p) {       // j set is larger than i set
        bship[pi].o -= bship[pj].o;         // adjust child's order
        bship[pj].p += bship[pi].p - 1;
        bship[pi].p = pj;
    } else {
        bship[pj].o -= bship[pi].o;
        bship[pi].p += bship[pj].p - 1;
        bship[pj].p = pi;
    }
}

int main()
{
    char c;
    int t, i, j, oi, oj;

    scanf("%d\n", &t);
    while (t) {
        init();
        while (t--) {
            scanf("%c %d %d\n", &c, &i, &j);
            if (c == 'M')
                merge(i, j);
            else {
                if (find(i, oi) == find(j, oj))
                    printf( "%d\n", max( abs(oi-oj)-1, 0 ) );
                else
                    printf("-1\n");
            }
        }
        scanf("%d\n", &t);
    }

    return 0;
}