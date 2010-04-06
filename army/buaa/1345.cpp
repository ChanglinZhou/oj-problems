#include <iostream>
#include <vector>
using namespace std;

vector<int> events;

long long solve()
{
	long long n = 0;
	vector<int>::iterator iter = events.begin();
	if (iter == events.end())
		return 0;
	while (true) {
		if (iter + 1 != events.end()) {
			if (*iter > *(iter + 1))
				n += *iter - *(iter + 1);
		}
		else {
			n += *iter;
			break;
		}
		++iter;
	}
	return n;
}

int main()
{
	events.reserve(1000000);
	char buf[100];
	for (;;) {
		cin.getline(buf, 100);
		if (strlen(buf) == 0)
			break;
		int cnt;
		sscanf(buf, "%d", &cnt);
		events.clear();
		while (cnt--) {
			int tmp;
			tmp;
			cin >> tmp;
			events.push_back(tmp);
		}
		cin.getline(buf, 100);
		cout << solve() << endl;
	}
	return 0;
}
