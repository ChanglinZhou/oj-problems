#include <iostream>
using namespace std;

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int a, b;
		cin >> a >> b;
		if (a == 0 && b == 0)
			cout << 1 << endl;
		else if (b == 0)
			cout << 0 << endl;
		else if (a % b == 0)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}
