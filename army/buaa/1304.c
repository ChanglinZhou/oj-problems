#include <stdio.h>

int ret[10001][4] = {0};

int main()
{
	ret[1][0] = 1;
	ret[1][1] = 1;
	ret[1][2] = 1;
	ret[1][3] = 1;
	
	int i;
	for (i = 2; i <= 10000; ++i)
	{
		ret[i][0] = ret[i - 1][1];
		ret[i][1] = (ret[i - 1][0] + ret[i - 1][2]) % 7654321;
		ret[i][2] = (ret[i - 1][1] + ret[i - 1][3]) % 7654321;
		ret[i][3] = ret[i - 1][2];
	}
	
	int cnt;
	scanf("%d", &cnt);
	while (cnt--)
	{
		int n;
		scanf("%d", &n);
		printf("%d\n", ret[n][0]);
	}
}
