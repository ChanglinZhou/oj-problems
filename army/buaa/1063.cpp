#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

void solve(double a, double b, double c)
{
	double key = b * b - 4 * a * c;
	if (key < 0)
		cout << "no answer!" << endl;
	else
	{
		cout.precision(2);
		cout << fixed << (-b - sqrt(key)) / (2 * a) << endl;
	}
}

void solve(double r)
{
	cout.precision(2);
	cout << fixed << 3.14 * r * r << endl;
}

void solve(int w, int h)
{
	cout << w * h << endl;
}

int main()
{
	char buf[100];
	for (;;) {
		cin.getline(buf, 100);
		if (strlen(buf) == 0)
			break;
		stringstream ss(buf);
		int type;
		ss >> type;
		switch (type)
		{
		case 1:
			{
				int w, h;
				ss >> w >> h;
				solve(w, h);
			}
			break;
		case 2:
			{
				double r;
				ss >> r;
				solve(r);
			}
			break;
		case 3:
			{
				double a, b, c;
				ss >> a >> b >> c;
				solve(a, b, c);
			}
			break;
		}
	}
	return 0;
}
