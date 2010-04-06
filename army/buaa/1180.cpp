#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int houseNum, storeCap;
vector<int> houseLoc;
float tab[200][200];
float eVal[200][200];

float error(int a, int b)
{
	float e = 0;
	for (int i = a + 1; i < b; ++i) {
		float k = fabs((houseLoc[b] - houseLoc[a]) / float(b - a) * (i - a) + houseLoc[a] - houseLoc[i]);
		e += k;
	}
	return e;
}

float solve()
{
	if (houseNum == storeCap)
		return 0;

	for (int i = 0; i < houseNum; ++i) {
		for (int j = i; j < houseNum; ++j) {
			eVal[i][j] = error(i, j);
		}
	}

	if (storeCap == 2)
		return eVal[0][houseNum - 1] / houseNum;

	for (int i = 1; i < houseNum - 1; ++i)
		tab[i][1] = eVal[0][i];
		
	for (int i = 2; i <= storeCap - 2; ++i) {
		for (int j = i; j < houseNum - 1; ++j) {
			float minE = -1;
			for (int k = i - 1; k < j; ++k)
			{
				float err = tab[k][i - 1] + eVal[k][j];
				if (minE < 0 || err < minE)
					minE = err;
			}
			tab[j][i] = minE;
		}
	}
	
	float minV = -1;
	for (int i = storeCap - 2; i < houseNum - 1; ++i)
	{
		float v = tab[i][storeCap - 2] + eVal[i][houseNum - 1];
		if (minV < 0 || v < minV)
			minV = v;
	}
	return minV / houseNum;
}

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--) {
		cin >> houseNum >> storeCap;
		houseLoc.clear();
		for (int i = 0; i < houseNum; ++i) {
			int tmp;
			cin >> tmp;
			houseLoc.push_back(tmp);
		}
		printf("%.4f\n", solve());
	}
}

