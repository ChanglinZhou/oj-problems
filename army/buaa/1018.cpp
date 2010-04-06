#include <iostream>
#include <vector>

using namespace std;

int solve(int n)
{
	vector<int> result(n + 1, 0);
	vector<bool> stone(n + 1, false);
	int s, t, m;
	cin >> s >> t >> m;
	while (m--) {
		int tmp;
		cin >> tmp;
		stone[tmp] = true;
	}
	for (int i = 1; i <= n; i++) {
		int minStone = (n << 1);
		for (int j = (i - t < 0 ? 0 : i - t); j <= i - s; ++j) {
			minStone = min(minStone, result[j]);
		}
		if (stone[i])
			result[i] = minStone + 1;
		else
			result[i] = minStone;
	}	
	cout << result[n] << endl;
}

int main()
{
	for (;;) {
		int len;
		cin >> len;
		if (len == 0)
			break;
		solve(len);
	}
	return 0;
}
