#include <iostream>
using namespace std;

int cost[12];

void solve()
{
	int saved = 0;
	int money = 0;
	for (int i = 0; i < 12; ++i)
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
	printf("%f\n", money + saved * 1.2);
}

int main()
{
	int cnt;
	scanf("%d", &cnt);
	while (cnt--)
	{
		for (int i = 0; i < 12; ++i)
			scanf("%d", &cost[i]);
		solve();
	}
	cout << 7 * 1.2 << endl;
}
