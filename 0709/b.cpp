#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1005;

int T,N,f[maxn][maxn];
char s1[maxn],s2[maxn];

bool Check()
{
	fo(i,1,N) fo(j,1,N) f[i][j] = 0;
	fo(i,1,N) fo(j,1,N)
	{
		if (s1[i]-s2[j] <= 1 && s1[i]-s2[j] >= -1) f[i][j] = f[i-1][j-1] + 1;
		if (f[i][j] >= (N+1)/2) return 1;
	}
	return 0;
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d",&N);
		scanf("%s%s",s1+1,s2+1);
		puts(Check()?"POSITIVE":"NEGATIVE");
	}
	return 0;
}
