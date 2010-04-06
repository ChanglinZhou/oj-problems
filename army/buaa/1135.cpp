#include <iostream>
using namespace std;

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int a[5];
		cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4];
		cout << *max_element(a, a + 5) << " " << *min_element(a, a + 5) << endl;
	}
	return 0;
}
