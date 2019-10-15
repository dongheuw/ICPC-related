#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 200010;

int N,k,ans[maxn],tot,sum;

struct dragon
{
	int x,id;
	dragon(int _x,int _id){x = _x, id = _id;}
	bool operator < (const dragon a) const { return x > a.x; }
};

priority_queue<dragon> q;

int main()
{
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
	scanf("%d",&N);
	fo(i,2,N)
	{
		char sig[10];
		scanf("%s %d\n",sig,&k);
		if (i == N) break;
		if (sig[0] == 'd') q.push(dragon(k,i));
		else
		{
			int s = q.size();
			if (s >= k)
			{
				k = s - k + 1;
				while (k --) q.pop();
			}
		}
	}

	int s = q.size();
	if (s < k) printf("-1\n");
	else
	{
		tot = sum = 0;
		while (!q.empty())
		{
			dragon cur = q.top();
			q.pop();
			sum += cur.x, ans[tot ++] = cur.id;
		}
		sort(ans,ans+tot);
		
		printf("%d\n%d\n",sum,tot);
		fo(i,0,tot-2) printf("%d ",ans[i]);
		printf("%d\n",ans[tot-1]);
	}
	return 0;
}
