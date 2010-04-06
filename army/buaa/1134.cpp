#include <iostream>
using namespace std;

int main()
{
	char buf[20];
	for (;;) {
		cin.getline(buf, 20);
		if (strlen(buf) == 0)
			break;
		double a;
		sscanf(buf, "%lf", &a);
		cout.precision(2);
		cout << fixed << 2 * a << " " << 2 * 3.1415926 * a << " " << 3.1415926 * a * a << endl;
	}
	return 0;
}
