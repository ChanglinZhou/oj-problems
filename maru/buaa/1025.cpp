#include <iostream>
#include <algorithm>
using namespace std;

struct factor {
    int n;
    int f;
    bool operator < (factor const & r) const { return f > r.f || f == r.f && n < r.n; }
};

int const num = 10000;
factor fall[num+1];
factor fab[num+1];

void printrank(ostream& os, int a, int b, int k)
{
    int n = b-a+1;
    memcpy(fab, fall+a, sizeof(factor)*n);
    sort(fab, fab+n);

    if (k >= n || k != 0 && fab[k].f == fab[k-1].f) {
        os<<"None";
        return;
    }

    int c = fab[k].f;
    os<<fab[k++].n;
    while (k < n && fab[k].f == c)
        os<<' '<<fab[k++].n;
}

void init()
{
    static int mark[num+1];
    memset(mark, 0, sizeof(mark));

    int i;
    for (i = 1; i <= num; ++i)
        fall[i].n = i, fall[i].f = 1;

    int j, t, k;
    for (i = 2; i <= num; ++i) {
        if (mark[i])     // not prime
            continue;

        k = 1;
        for (t = i; t <= num; t *= i) {     // for each t = pow(i, k)
            ++k;
            for (j = 1; t*j <= num; ++j) {  // for each multiple of t
                if (!(j%i))
                    continue;
                mark[t*j] = 1;
                fall[t*j].f *= k;
            }
        }
    }
}

int main()
{
    init();

    int t, a, b, k, i;
    cin>>t;
    for (i = 1; i <= t; ++i) {
        cin>>a>>b>>k;
        cout<<"Case "<<i<<": ";
        printrank(cout, a, b, k);
        cout<<endl;
    }

    return 0;
}