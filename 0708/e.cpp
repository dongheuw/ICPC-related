#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 10007;
const int maxm = 105;

int T,N,M,K;
char s[maxn],t[maxm];
bool done;
set<int> hs;

void Hash()
{
	fo(i,M,N)
	{
		int cur = 0;
		fo(j,i-M+1,i) cur = cur * 26 + s[j];
		hs.insert(cur);
	}
}

void dfs(int x)
{
	if (done) return;
	if (x > M)
	{
		int cur = 0;
		fo(i,1,M) cur = cur * 26 + t[i];
		if (hs.find(cur) == hs.end()) done = 1;
		return;
	}
	for (int i = 1;i <= K;i ++)
	{
		t[x] = i+96;
		dfs(x+1);
		if (done) return;
	}
	if (done) return;
}

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d%d%d",&N,&M,&K);
		scanf("%s",s+1);
		hs.clear();
		Hash();
		done = 0;
		dfs(1);
		fo(i,1,M) putchar(t[i]);
		puts("");
	}
	return 0;
}
