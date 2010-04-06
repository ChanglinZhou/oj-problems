#include <iostream>
#include <string>
using namespace std;

void solve(int c)
{
	int cnt = c;
	double maxv = 0;
	while (c--) {
		double v;
		cin >> v;
		maxv += v;
	}
	cout.precision(2);
	cout << fixed << maxv / cnt << endl;
}

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--) {
		int c;
		cin >> c;
		solve(c);
	}
	return 0;
}

