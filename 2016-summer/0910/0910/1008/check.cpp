#include <bits/stdc++.h>
int main()
{
	while (1)
	{
		system("./maker");
		system("./h");
		system("./vio");
		if (system("diff h.out vio.out"))
		{
			puts("WA");
			break;
		}
		puts("AC");
	}
}
