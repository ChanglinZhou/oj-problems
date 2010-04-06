#include <iostream>
#include <string>
using namespace std;

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a <= 0 || b <= 0 || c <= 0)
		{
			cout << 0 << endl;
			continue;
		}
		a *= a;
		b *= b;
		c *= c;
		if (a + b == c || a + c == b || b + c == a)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}
