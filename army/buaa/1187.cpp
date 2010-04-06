#include <iostream>
using namespace std;

void print(char c, int cnt)
{
	while (cnt--)
		cout << c;
}

void solve(int a)
{
	for (int i = 1; i <= a; ++i)
	{
		print('*', i);
		print('-', a - i + 1);
		print('*', a - i + 1);
		print('-', i - 1);
		cout << endl;
	}
}

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int a;
		cin >> a;
		solve(a);
	}
	return 0;
}
