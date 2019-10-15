#include <cstdio>
#include <cstring>
#include <cstdlib>
int main()
{
	while (1)
	{
		system("./maker");
		system("./j");
		system("./vio");
		if (system("diff j.out vio.out"))
		{
			puts("WA");
			break;
		}
		puts("AC");
	}
}
