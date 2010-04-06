#include <iostream>
using namespace std;

int const len = 501;
char tab[len*len/8 + 1];

void init()
{
    memset(tab, 0, sizeof(tab));
}

void settab(int i, int j)
{
    int r = i*len + j;
    tab[r/8] |= 1<<r%8;
}

bool gettab(int i, int j)
{
    int r = i*len + j;
    return (tab[r/8] & (1<<r%8)) != 0;
}

bool next(istream& is)
{
    char c;
    while (c = is.peek()) {
        if (c >= '0' && c <= '9')
            return false;
        if (c == '\n')
            return true;
        is.ignore();
    }
    return true;
}

int nswitch(int n)
{
    static int dist[len];

    int i, j, p, d;

    memset(dist, 0, sizeof(dist));
    for (i = 2; i <= n; ++i) {
        if (gettab(1, i))
            dist[i] = 1;
    }

    for (i = 2; i <= n; ++i) {
        p = d = 0;
        for (j = 2; j <= n; ++j) {
            if (gettab(j, j))
                continue;
            if (dist[j] && (!d || dist[j] <= d))
                p = j, d = dist[j];
        }
        if (!p || p == n)
            break;

        settab(p, p);
        for (j = 2; j <= n; ++j) {
            if (gettab(j, j))
                continue;
            if (gettab(p, j) && (!dist[j] || dist[j] > dist[p] + 1))
                dist[j] = dist[p] + 1;
        }
    }

    return dist[n] - 1;
}

int main()
{
    static int stop[len];

    int n, m, i, j, k, r;
    cin>>m>>n;
    while (m && n) {
        init();
        for (i = 0; i < m; ++i) {
            j = 0;
            do {
                cin>>stop[j];
                for (k = 0; k < j; ++k) {
                    if (stop[k] != stop[j])
                        settab(stop[k], stop[j]);
                }
                ++j;
            } while (!next(cin));
        }
        r = nswitch(n);
        if (r < 0)
            cout<<"NO";
        else
            cout<<r;
        cout<<endl;
        cin>>m>>n;
    }
}