#include <iostream>
using namespace std;

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		int sum = a + b + c;
		long long product = a * b * c;
		cout << sum << " " << sum / 3 << " " << product << " " << min(a, min(b, c)) << " " << max(a, max(b, c)) << endl;
	}
	return 0;
}
