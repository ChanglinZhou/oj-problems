#include <iostream>
#include <vector>

using namespace std;

#define MAXI 100000000

void solve(int x, int y, int z, int n)
{
	vector<long long> a(max(int(n + 1), z + 1), 0);
	a[0] = 1;
	for (int i = 0; i < a.size(); ++i)
	{
		int end_j = min(int(a.size()), i + y + 1);
		for (int j = i + x; j < end_j; ++j)
		{
			a[j] += a[i];
			if (a[j] > MAXI)
				a[j] -= MAXI;
		}
	}

	long long sum = 0;
	for (int i = (n - z + 1 < 0 ? 0 : n - z + 1); i < n; ++i)
	{
		sum += a[i];
		sum %= MAXI;
	}
	cout << sum << endl;
}
/*
void solve(int x, int y, int z, int n)
{
	vector<long long> a(max(n + 1, z + 1), 0);
	a[0] = 1;
	for (int i = 1; i < x; i++)
		a[i] = 0;
	a[x] = 1;
	for (int i = x + 1; i < n; ++i) {
		long long k = a[i - 1] + (i - x < 0 ? 0 : a[i - x]);
		long long t = (i - y - 1 < 0 ? 0 : a[i - y - 1]); 
		if (k < t)
			k += 100000000;
		a[i] = (k - t) % 100000000;
	} 
	long long sum = 0;
	for (int i = (n - z + 1 < 0 ? 0 : n - z + 1); i < n; ++i) {
		sum += a[i];
		sum %= 100000000;
	}
	cout << sum << endl;
}
*/
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
