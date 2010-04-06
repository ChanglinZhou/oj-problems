#include <stdio.h>

int cost[12];

void solve()
{
	int saved = 0;
	int money = 0;
	int i;
	for (i = 0; i < 12; ++i)
	{
		money += 300;
	
		if (money < cost[i])
		{
			printf("%d\n", -(i + 1));
			return;
		}
			
		money -= cost[i];
		while (money >= 100)
		{
			money -= 100;
			saved += 100;
		}
	}
	printf("%g\n", money + saved * 1.2);
}

int main()
{
	int cnt;
	scanf("%d", &cnt);
	while (cnt--)
	{
		int i;
		for (i = 0; i < 12; ++i)
			scanf("%d", &cost[i]);
		solve();
	}
}
