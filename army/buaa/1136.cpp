#include <iostream>
using namespace std;

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int a;
		cin >> a;
		if (a & 1)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}
