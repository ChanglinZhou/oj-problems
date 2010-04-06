#include <iostream>
#include <string>
using namespace std;

void solve(int c)
{
	long long maxv = 1;
	while (c > 1) {
		maxv *= c;
		--c;
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

