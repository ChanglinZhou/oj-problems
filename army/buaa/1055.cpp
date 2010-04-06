#include <iostream>
#include <string>
using namespace std;

void solve(int c)
{
	int maxv = 0;
	while (c--) {
		int v;
		cin >> v;
		maxv += v;
	}
	cout << maxv << endl;
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

