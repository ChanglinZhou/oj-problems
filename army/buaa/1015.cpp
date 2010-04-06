#include <iostream>
#include <vector>

using namespace std;


void solve(int n, int m, int tk, int t)
{
	int totalTime = 0;
	vector<int> node(n + 1, 0);
	for (int i = 0; i < m; ++i) {
		int a, b, Tab, Eab;
		cin >> a >> b >> Tab >> Eab;
		totalTime += Tab + Eab * tk;
		++node[a];
		++node[b];
	}
	int odd = 0;
	for (int i = 1; i <= n; ++i)
		if (node[i] % 2 == 1)
			++odd;
	totalTime += (odd / 2 - 1) * t;
	if (node[n] % 2 == 0)
		totalTime += t;
	if (node[1] % 2 == 0)
		totalTime += t;
	cout << totalTime << endl;
}

int main()
{
	for (;;) {
		int x, y, z, n;
		cin >> x >> y >> z >> n;
		if (x == 0 && y == 0 && z == 0 && n == 0)
			break;
		solve(x, y, z, n);
	}
	return 0;
}
