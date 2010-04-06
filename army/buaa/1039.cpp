#include <iostream>
#include <vector>
using namespace std;

vector<int> steps(31, 0);

int main()
{
	steps[1] = 1;
	steps[2] = 2;
	for (int i = 3; i < 31; ++i)
		steps[i] = steps[i - 1] + steps[i - 2];
		
	int cnt;
	cin >> cnt;
	while (cnt--) {
		int v;
		cin >> v;
		cout << steps[v] << endl;
	}
	return 0;
}

