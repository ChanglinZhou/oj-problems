#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int const vmax = 10000;

struct edge {
    int v, d;
};
vector<edge> graph[vmax+1];

class vheap {
public:
    void push(int p, long long k);
    void pop();
    int top() { return h[1]; }
    long long topkey() { return d[1]; }
    vheap() { n = 0; memset(v, 0, sizeof(v)); }

private:
    static int v[vmax+1];
    static int h[vmax+1];
    static long long d[vmax+1];
    static int n;

private:
    int parent(int i) { return i/2; }
    int left(int i) { return 2*i; }
    int right(int i) { return 2*i+1; }
    void heapify(int i);
    void decrease(int i, long long d);
};
int vheap::v[vmax+1];
int vheap::h[vmax+1];
long long vheap::d[vmax+1];
int vheap::n;

void vheap::pop()
{
    if (n > 0) {
        v[h[1]] = 0;
        d[1] = d[n], h[1] = h[n];
        --n;
        heapify(1);
    }
}

void vheap::push(int p, long long k)
{
    int i = v[p];
    if (!i) {
        i = ++n;
        d[n] = 0, h[n] = p, v[p] = n;
    }
    decrease(i, k);
}

void vheap::heapify(int i)
{
    int l, r, m;
    l = left(i), r = right(i), m = i;
    if (l <= n && d[l] < d[m])
        m = l;
    if (r <= n && d[r] < d[m])
        m = r;
    if (m != i) {
        swap(d[m], d[i]);
        swap(h[m], h[i]);
        swap(v[h[m]], v[h[i]]);
        heapify(m);
    }
}

void vheap::decrease(int i, long long k)
{
    if (!d[i] || d[i] > k) {
        int p;
        for (d[i] = k, p = parent(i); i > 1 && d[p] > d[i]; i = parent(i), p 
= parent(p)) {
            swap(d[p], d[i]);
            swap(h[p], h[i]);
            swap(v[h[p]], v[h[i]]);
        }
    }
}

long long distance(int a, int b, int n)
{
    vheap heap;
    while (!graph[a].empty()) {
        heap.push(graph[a].back().v, graph[a].back().d);
        graph[a].pop_back();
    }

    long long d = 0;
    int p;
    for (int i = 1; i < n; ++i) {
        p = heap.top();
        d = heap.topkey();
        heap.pop();
        if (p == 0 || p == b)
            break;
        while (!graph[p].empty()) {
            heap.push(graph[p].back().v, graph[p].back().d + d);
            graph[p].pop_back();
        }
    }

    return d;
}

int main()
{
    int m, n, i, a, b;
    edge e;
    while (cin>>n>>m) {
        for (i = 1; i <= n; ++i)
            graph[i].clear();
        for (i = 0; i < m; ++i) {
            cin>>a>>e.v>>e.d;
            graph[a].push_back(e);
        }
        cin>>a>>b;
        cout<<distance(a, b, n)<<endl;
    }
}