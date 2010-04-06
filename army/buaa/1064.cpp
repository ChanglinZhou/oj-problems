#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double x = 3.14159 / 4;
	for (;;) {
		double y = x + (cos(x) - x) / (sin(x) + 1);
		if (fabs(x - y) < 1e-6)
			break;
		x = y;
	}
	cout.precision(6);
	cout << fixed << x << endl;
}
