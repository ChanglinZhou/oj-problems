#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int64;

int64 a[] =
{
1,
1,
2,
3,
5,
8,
13,
21,
34,
55,
89,
144,
233,
377,
610,
987,
1597,
2584,
4181,
6765,
10946,
17711,
28657,
46368,
75025,
121393,
196418,
317811,
514229,
832040,
1346269,
2178309,
3524578,
5702887,
9227465,
14930352,
24157817,
39088169,
63245986,
102334155,
165580141,
267914296,
433494437,
701408733,
1134903170,
1836311903,
2971215073,
};

int solve(int64 n)
{
	int64* p = upper_bound(a, a + 47, n);
	if (*(p - 1) == n)
		return -1;
	else
		return p - a - 1; 
}

int main() 
{
	char buf[100];
	while (true) {
		int64 n;
		cin.getline(buf, 100);
		if (strlen(buf) == 0)
			break;
		sscanf(buf, "%ld", &n);
		cout << solve(n) << endl;
	}
	return 0;
}
