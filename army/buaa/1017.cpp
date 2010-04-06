#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> groupsCnt;
vector<int> result;

int SIZE = 10000;

int realSolve(int n)
{
	for (int i = result.size(); i <= n; ++i) {
		int sum = groupsCnt[1];
		for (int j = groupsCnt.size() - 1; j > 1; --j) {
			groupsCnt[j] = (j * groupsCnt[j] + groupsCnt[j - 1]) % SIZE;
			sum = (sum + groupsCnt[j]) % SIZE;
		}
		groupsCnt.push_back(1);
		++sum;
		sum %= SIZE;
		result.push_back(sum);
	}
	return result.back();
}

void solve(int n)
{
	if (result.size() > n)
		cout << result[n] << endl;
	else
		cout << realSolve(n) << endl;
}

int main()
{
	groupsCnt.reserve(2000);
	result.reserve(2000);
	groupsCnt.push_back(0);
	groupsCnt.push_back(1);
	result.push_back(0);
	result.push_back(1);
	
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		int tmp;
		cin >> tmp;
		solve(tmp);
	}
}

