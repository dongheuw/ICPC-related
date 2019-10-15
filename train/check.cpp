#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

int main()
{
	while (1)
	{
		system("./china_make");
		system("./china");
		system("./china_brute");
		if (system("diff china.out china.ans")) printf("WA\n");
		else printf("AC\n");
	}
}
