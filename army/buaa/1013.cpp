#include <iostream>
#include <vector>

using namespace std;


void solve(int w, int h)
{
	int* rawData = new int[w];
	int* max_s = new int[w];
	int* oldmax_s = new int[w];
	int* rowLength = new int[w];
	int* colLength = new int[w];
	int* oldcolLength = new int[w];
	memset(rawData, 0, sizeof(int) * w);
	memset(max_s, 0, sizeof(int) * w);
	memset(oldmax_s, 0, sizeof(int) * w);
	memset(rowLength, 0, sizeof(int) * w);	
	memset(colLength, 0, sizeof(int) * w);
	memset(oldcolLength, 0, sizeof(int) * w);

	int maxSize = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> rawData[j];
		}
		
		int* pRaw = rawData;
		int* pMax = max_s;
		int* pRow = rowLength;
		int* pCol = colLength;
		for (int j = 0; j < w; j++) {
			if (*pRaw == 1) {
				*pMax = *pCol = *pRow = 0;
			}
			else if (i == 0 || j == 0) {
				*pMax = *pCol = *pRow = 1;
				maxSize = max(maxSize, *pMax);
			}
			else {
				*pCol = oldcolLength[j] + 1;
				*pRow = *(pRow - 1) + 1;
				*pMax = min(oldmax_s[j - 1] + 1, min(*pRow, *pCol));
				maxSize = max(maxSize, *pMax);
			}
			++pRaw;
			++pMax;
			++pCol;
			++pRow;
		}
		swap(max_s, oldmax_s);
		swap(colLength, oldcolLength);
	}
	cout << maxSize << endl;
	delete[] rawData;
	delete[] max_s;
	delete[] oldmax_s;
	delete[] rowLength;
	delete[] colLength;
	delete[] oldcolLength;					
}

int main()
{
	for (;;) {
		int w, h;
		cin >> h >> w;
		if (w == 0 && h == 0)
			break;
		solve(w, h);
	}
	return 0;
}
