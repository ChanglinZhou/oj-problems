#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int k;
		cin >> k;
		cout << (k * (k + 1) >> 1) << endl;
	}
}
