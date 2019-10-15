#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 755;

int k,a[maxn][maxn];

struct Node
{
	int sum,last;
	bool operator < (const Node &a) const
	{
		return sum > a.sum;
	}
	Node(int _sum,int _last){sum = _sum, last = _last;}
};

void Merge(int *a,int *b)
{
	priority_queue<Node> Q;
	fo(i,0,k-1) Q.push(Node(a[i]+b[0],0));
	fo(i,1,k-1)
	{
		Node cur = Q.top(); Q.pop();
		a[i-1] = cur.sum;
		cur.sum = cur.sum - b[cur.last] + b[++cur.last];
		Q.push(cur);
	}
	a[k-1] = Q.top().sum;
}

int main()
{
	freopen("k.in","r",stdin);
	freopen("k.out","w",stdout);
	while (scanf("%d",&k) != EOF)
	{
		fo(i,0,k-1)
		{
			fo(j,0,k-1) scanf("%d",&a[i][j]);
			sort(a[i],a[i]+k);
		}
		fo(i,1,k-1) Merge(a[0],a[i]);
		fo(i,0,k-2) printf("%d ",a[0][i]);
		printf("%d\n",a[0][k-1]);
	}
	return 0;
}
