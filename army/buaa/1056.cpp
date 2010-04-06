#include <iostream>
using namespace std;

int solve(int a, int b, int c, int d, int e, int f)
{
	int h, m, s;
	
	d += 12;
	if (f < c) {
		f += 60;
		--e;
	}
	s = f - c;
	
	if (e < b) {
		e += 60;
		--d;
	}
	m = e - b;
	
	h = d - a;
	return h * 3600 + m * 60 + s;
}

int main()
{
	for (;;) {
		int a, b, c, d, e, f;
		cin >> a >> b >> c >> d >> e >> f;
		if (a == 0)
			break;
		cout << solve(a, b, c, d, e, f) << endl;
	}
}
