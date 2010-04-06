#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int c = 0;
int index_ = -1;
int answerCnt = 0;
vector<int> tmp;
vector<int> data(8, 0);
vector<int> finalResult;

bool check()
{
	for (int i = 0; i < index_; ++i)
		if (tmp[i] == tmp[index_])
			return false;

	switch (index_)
	{
	case 0:
		return true;
	case 1:
		if (abs(tmp[1] - tmp[0]) == 1)
			return false;
		else
			return true;
		break;
	case 2:
		if (abs(tmp[2] - tmp[0]) == 1
			|| abs(tmp[2] - tmp[1]) == 1)
			return false;
		else
			return true;
		break;
	case 3:
		if (abs(tmp[3] - tmp[0]) == 1
			|| abs(tmp[3] - tmp[2]) == 1)
			return false;
		else
			return true;
		break;
	case 4:
		if (abs(tmp[4] - tmp[1]) == 1
			|| abs(tmp[4] - tmp[2]) == 1)
			return false;
		else
			return true;
		break;
	case 5:
		if (abs(tmp[5] - tmp[1]) == 1
			|| abs(tmp[5] - tmp[2]) == 1
			|| abs(tmp[5] - tmp[3]) == 1
			|| abs(tmp[5] - tmp[4]) == 1)
			return false;
		else
			return true;
		break;
	case 6:
		if (abs(tmp[6] - tmp[2]) == 1
			|| abs(tmp[6] - tmp[3]) == 1
			|| abs(tmp[6] - tmp[5]) == 1)
			return false;
		else
			return true;
		break;
	case 7:
		if (abs(tmp[7] - tmp[4]) == 1
			|| abs(tmp[7] - tmp[6]) == 1
			|| abs(tmp[7] - tmp[5]) == 1)
			return false;
		else
			return true;
		break;
	}
}

void forward()
{
	for (;;) {

		do {
			++index_;
			if (index_ < 8 && data[index_] != 0)
				if (!check()) {
					index_--;
					return;
				}
		} while (index_ < 8 && data[index_] != 0);
		
		if (index_ == 8) {
			index_ = 7;
			return;
		}
		
		int i = 1;
		for (; i < 9; ++i) {
			tmp[index_] = i;
			if (check())
				break;
		}
		if (i == 9) {
			--index_;
			return;
		}
	}	
}

void backward()
{
	for (;;) {
		while (index_ >= 0 && data[index_] != 0)
			--index_;	
		
		if (index_ < 0) {
			return;
		}
		
		for (int i = tmp[index_] + 1; i < 9; ++i) {
			tmp[index_] = i;
			if (check())
				return;
		}
		--index_;
	}	
}

int solve()
{
	answerCnt = 0;
	index_ = -1;
	tmp = data;

	for (;;) {
		forward();
		if (index_ == 7) {
			answerCnt++;
			if (answerCnt > 1)
				return 2;
			finalResult = tmp;
		}
		backward();
		if (index_ == -1)
			break;
	}
	return answerCnt;
}

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		cin >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6] >> data[7];
		c++;
		int ret = solve();
		if (ret == 1)
			cout << "Case " << c << ": " << finalResult[0] << " " << finalResult[1] << " " << finalResult[2] << " " << finalResult[3] << " " << finalResult[4] << " " << finalResult[5] << " " << finalResult[6] << " " << finalResult[7] << endl;
		else if (ret > 1)
			cout << "Case " << c << ": Not unique" << endl;
		else
			cout << "Case " << c << ": No answer" << endl;
	}
}
