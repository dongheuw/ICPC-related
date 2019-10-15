#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
	freopen("china.in","w",stdout);
	srand(time(0));
	int N = rand() % 500000 + 3;
	printf("%d\n",N);
	return 0;
}
