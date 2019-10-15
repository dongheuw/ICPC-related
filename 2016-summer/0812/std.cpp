#include<cstdio>
#include<cstring>
#include<queue>
#include<utility>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
typedef pair<int,int> PI;
const int maxn = 10005;
const int maxm = 200005;

int N,M,tot;

int ans[maxn],a[maxn],b[maxm],c[maxm],d[maxm];
bool poped[maxn];
priority_queue<PI> Q;

void Insert(int x,int y,int z)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	d[tot] = z;
	a[x] = tot;
}

int main()
{
	scanf("%d%d",&N,&M);
	fo(i,1,N)
	{
		int x;
		scanf("%d",&x);
		ans[i] = x;
		Q.push(make_pair(-x,i));
	}
	fo(i,1,M)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		Insert(y,z,x);
		Insert(z,y,x);
	}
	while (!poped[1])
	{
		PI top = Q.top(); Q.pop();
		int x = top.second;
		if (poped[x]) continue;
		poped[x] = 1; ans[x] = -top.first;
		for (int i = a[x];i;i = c[i])
			if (poped[b[i]] && ans[x] + ans[b[i]] < ans[d[i]])
			{
				ans[d[i]] = ans[x] + ans[b[i]];
				Q.push(make_pair(-ans[d[i]],d[i]));
			}
	}
	printf("%d\n",ans[1]);
	return 0;
}
