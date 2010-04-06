#include <iostream>
#include <sstream>
using namespace std;

int val[21][21][21] = {0};
bool f[21][21][21] = {0};

int g(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	if (a > 20 || b > 20 || c > 20)
	{
		a = b = c = 20;
	}
	if (f[a][b][c] == false)
	{
		if (a < b && b < c)
		{
			val[a][b][c] = g(a, b, c - 1) + g(a, b - 1, c - 1) - g(a, b - 1, c);
		}
		else
		{
			val[a][b][c] = g(a - 1, b, c) + g(a - 1, b - 1, c) + g(a - 1, b, c - 1) - g(a - 1, b - 1, c - 1);
		}
		f[a][b][c] = true;
	}
	return val[a][b][c];
}

int main()
{
	int cnt;
	cin >> cnt;
	ostringstream ss;
	while (cnt--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		ss << g(a, b, c) << endl;
	}
	cout << ss.str();
}
