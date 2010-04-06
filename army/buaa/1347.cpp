#include <iostream>
using namespace std;

bool solve(long long n)
{
	if (n <= 9)
		return true;
	else if (n > 9 && n <= 18)
		return false;
	else {
		long long t = n % 18;
		n /= 18;
		if (t != 0)
			++n;
		return solve(n);
	}
}

int main()
{
	char buf[100];
	for (;;) {
		cin.getline(buf, 100);
		if (strlen(buf) == 0)
			break;
		long long tmp;
		sscanf(buf, "%ld", &tmp);
		if (solve(tmp))
			cout << "wf is the winner!" << endl;
		else
			cout << "fzw is the winner!" << endl;
	}
	return 0;
}
