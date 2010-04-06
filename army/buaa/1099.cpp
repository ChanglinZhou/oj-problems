#include <iostream>
using namespace std;

void solve(int n, int i, int j)
{
	for (int k = 1; k <= n; ++k)
		cout << "(" << i << "," << k << ")";
	cout << endl;
	
	for (int k = 1; k <= n; ++k)
		cout << "(" << k << "," << j << ")";
	cout << endl;
	
	int x, y;
	if (i == j) {
		x = y = 1;
	}
	else if (i < j) {
		x = 1;
		y = j - i + 1;
	}
	else {
		y = 1;
		x = i - j + 1;
	}
	for (;x <= n && y <= n; ++x, ++y)
		cout << "(" << x << "," << y << ")";
	cout << endl;
	
	if (i + j == n + 1) {
		x = n;
		y = 1;
	}
	else if (i + j < n + 1) {
		x = i + j - 1;
		y = 1;
	}
	else {
		x = n;
		y = j + i - n;
	}
	for (;x >= 1 && y <= n; --x, ++y)
		cout << "(" << x << "," << y << ")";
	cout << endl;
}

int main()
{
	char buf[100];
	for (;;) {
		int n, i, j;
		cin.getline(buf, 100);
		sscanf(buf, "n=%d", &n);
		if (n == 0)
			break;
		cin.getline(buf, 100);
		sscanf(buf, "i=%d", &i);
		cin.getline(buf, 100);
		sscanf(buf, "j=%d", &j);
		solve(n, i, j);
	}
	return 0;
}
