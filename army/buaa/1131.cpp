#include <stdio.h>

int main()
{
	int cnt;
	scanf("%d", &cnt);
	while (cnt--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d %d %d %d\n", a + b, a * b, a - b, a / b);
	}
	return 0;
}
