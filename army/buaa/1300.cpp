#include <iostream>
#include <vector>
using namespace std;

int nodeCnt, edgeCnt;

int dis[11][11];

void addCandidate(int i, vector<bool>& visited, vector<int>& mindis, vector<int>& candidates)
{
	for (int j = 1; j <= nodeCnt; ++j)
	{
		if (visited[j] == false && dis[i][j] != -1)
		{
			int newMindis = mindis[i] + dis[i][j];
			if (mindis[j] == -1)
			{
				mindis[j] = newMindis;
				candidates.push_back(j);
			}
			else if (mindis[j] > newMindis)
				mindis[j] = newMindis;
		}
	}
}

int solve()
{
	vector<int> mindis(nodeCnt + 1, -1);
	vector<bool> visited(nodeCnt + 1, false);
	vector<int> candidates;
	
	visited[1] = true;
	mindis[1] = 0;
	addCandidate(1, visited, mindis, candidates);
	
	while (candidates.empty() == false)
	{
		int mini = 0;
		for (int i = 1; i < candidates.size(); ++i)
		{
			if (mindis[candidates[i]] < mindis[candidates[mini]])
				mini = i;
		}
		int nodeIndex = candidates[mini];
		
		if (nodeIndex == nodeCnt)
			break;
		visited[nodeIndex] = true;
		candidates.erase(candidates.begin() + mini);
		addCandidate(nodeIndex, visited, mindis, candidates);
	}
	return mindis[nodeCnt];
}

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--)
	{
		cin >> nodeCnt >> edgeCnt;
		for (int i = 1; i <= nodeCnt; ++i)
			for (int j = 1; j <= nodeCnt; ++j)
				dis[i][j] = -1;
		for (int i = 0; i < edgeCnt; ++i)
		{
			int a, b, d;
			cin >> a >> b >> d;
			dis[a][b] = d;
			dis[b][a] = d;
		}
		cout << solve() << endl;
	}
}
