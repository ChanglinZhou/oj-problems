#include <iostream>
using namespace std;

void solve(int a)
{
	int b, c, d, e, f;
	f = a % 10;
	a = a / 10;
	e = a % 10;
	a = a / 10;
	d = a % 10;
	a = a / 10;
	c = a % 10;
	a = a / 10;
	b = a % 10;
	a = a / 10;
	
	if (b == f && c == e)
		cout << "Yes." << endl;
	else
		cout << "No." << endl;
}

int main()
{
	for (;;) {
		int a;
		cin >> a;
		if (a == 0)
			break;
		solve(a);
	}
	return 0;
}
