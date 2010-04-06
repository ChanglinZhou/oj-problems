#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

struct buint {
    int v[3100];        // the biggest one has 15010 digits!
    int n;
    static int const base=100000;
    static int const len=5;

    void operator = (int r) { v[0] = r%base, v[1] = r/base; n = v[1] ? 1 : 0; }
    void operator *= (int r);
    buint() { clear(); }
    void clear() { n = v[0] = 0; }
};

void buint::operator *= (int r)
{
    int i;
    for (i = 0; i <= n; ++i)
        v[i] *= r;

    int c = 0;
    for (i = 0; i <= n; ++i) {
        v[i] += c;
        c = v[i]/base;
        v[i] %= base;
    }
    v[++n] = c;

    while (!v[n])
        --n;
}

ostream& operator << (ostream& os, buint const & r)
{
    int n = r.n;
    os<<r.v[n];
    while (n-- > 0)
        os<<setw(buint::len)<<setfill('0')<<r.v[n];
    return os;
}

bool isprime(int n)
{
    for (int i = 2; i*i <= n; ++i) {
        if (!(n%i))
            return false;
    }
    return true;
}

int pow(int b, int e)
{
    if (!b)
        return 0;

    int r = 1;
    while (e-- > 0)
        r *= b;

    return r;
}

int log(int b, int n)
{
    int r, c;
    r = 0, c = 1;
    while (c < n)
        c *= b, ++r;

    return r;
}

void factorize(int n, priority_queue<int> &r)
{
    int i;
    for (i = 2; i*i <= n; ++i) {    // find the minimal prime factor
        if (!(n%i))
            break;
    }
    if (n%i || n == 2)  // n is a prime
        r.push(n);
    else {
        r.push(i);
        factorize(n/i, r);
    }
}

typedef priority_queue< int, vector<int>, greater_equal<int> > factor_queue;

int init(factor_queue& f, priority_queue<int>& r, int n)
{
    // clear
    while (!f.empty())
        f.pop();
    while (!r.empty())
        r.pop();

    factorize(n, r);

    int m, p;
    m = log(2, n), p = 0;

    int i, c;
    for (i = 2, c = 0; c < m; ++i) {
        if (isprime(i)) {
            f.push(i), ++c;
            if (i > p)
                p = i;
        }
    }

    return p;
}

buint& minofnfactor(int n)
{
    static buint v;
    v = 1;

    if (n == 1)
        return v;

    priority_queue<int> r;
    factor_queue q;

    int m, b, e, t;
    m = init(q, r, n);
    while (!r.empty()) {
        e = r.top();
        b = q.top();
        r.pop();
        q.pop();

        if (e < log(b, m)) {
            t = pow(b, e);
            q.push(t);
            v *= t/b;
        } else {
            t = e;
            while (--t > 0)     // optimize here!
                v *= b;
        }
    }

    return v;
}

int main()
{
    int n;
    cin>>n;
    while (n) {
        cout<<minofnfactor(n)<<endl;
        cin>>n;
    }

    return 0;
}