#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Node
{
	int score;
	vector<int> str;
};

vector<vector<Node> > mat(30, vector<Node>(30));

unsigned int compute(int head, int end)
{
	if (mat[head][end].score > 0)
		return mat[head][end].score;
	
	for (int i = head; i <= end; ++i)
	{
		int leftScore = (head <= i - 1 ? compute(head, i - 1) : 1);
		int rightScore = (i + 1 <= end ? compute(i + 1, end) : 1);
		int score = leftScore * rightScore + mat[i][i].score;
		if (mat[head][end].score == 0 || mat[head][end].score < score)
		{
			mat[head][end].score = score;
			mat[head][end].str.clear();
			mat[head][end].str.push_back(i);
			if (head <= i - 1)
				copy(mat[head][i - 1].str.begin(), mat[head][i - 1].str.end(), back_inserter(mat[head][end].str));
			if (i + 1 <= end)
				copy(mat[i + 1][end].str.begin(), mat[i + 1][end].str.end(), back_inserter(mat[head][end].str));
		}
	}
	return mat[head][end].score;
}  

void solve(const vector<int>& nodes)
{
	for (size_t i = 0; i < nodes.size(); ++i)
		for (size_t j = 0; j < nodes.size(); ++j)
		{
			if (i == j)
			{
				mat[i][j].score = nodes[i];
				mat[i][j].str.clear();
				mat[i][j].str.push_back(i);
			}
			else
			{
				mat[i][j].score = 0;
				mat[i][j].str.clear();
			}
		}
	
	cout << compute(0, nodes.size() - 1) << endl;
	for (vector<int>::iterator iter = mat[0][nodes.size() - 1].str.begin(); iter != mat[0][nodes.size() - 1].str.end(); ++iter)
		cout << *iter + 1<< " ";
	cout << endl;
}

int main()
{
	char buf[200];
	for (;;)
	{
		cin.getline(buf, 200);
		int cnt;
		sscanf(buf, "%d", &cnt);
		if (cnt == 0)
			break;
		vector<int> nodes;
		cin.getline(buf, 200);
		stringstream ss(buf);
		while (cnt--)
		{
			int val;
			ss >> val;
			nodes.push_back(val);
		}
		solve(nodes);
	}
}
