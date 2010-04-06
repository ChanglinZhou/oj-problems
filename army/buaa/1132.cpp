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
		if (a == b)
			cout << "These numbers are equal." << endl;
		else
			cout << max(a, b) << endl;
	}
	return 0;
}
