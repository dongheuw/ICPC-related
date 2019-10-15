#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 15;
const int maxq = 105;
const int maxS = 10005;

int n,m,q,A[maxn][maxn],a[maxq],b[maxq],c[maxq];
long long f[maxn][maxS];

void Initialize()
{
	scanf("%d%d%d",&n,&m,&q);
	fo(i,0,m-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x --, y --;
		A[x][y] = A[y][x] = 1;
	}
	fo(i,0,q-1)
	{
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
		a[i] --, b[i] --, c[i] --;
	}
}

inline bool inSet(int x,int S){return ((S >> x) & 1);}
long long DP(int u,int S)
{
	long long &ret = f[u][S];
	if (ret != -1) return ret;
	ret = 0;
	int St = S - (1 << u), fix;
	for (fix = 0;fix < n;fix ++) if (inSet(fix,St)) break;
	for (int cSt = St;cSt;cSt = (cSt-1)&St)
		if (inSet(fix,cSt))
		{
			bool flag = 1;
			//Condition 1
			fo(i,0,n-1)
				if (i != u)
				{
					fo(j,0,n-1)
						if (j != u)
							if (A[i][j] && (inSet(i,cSt) ^ inSet(j,cSt)))
							{
								flag = 0;
								break;
							}
					if (!flag) break;
				}
			if (!flag) continue;
			//Condition 2
			int v, cnt = 0;
			fo(i,0,n-1)
				if (A[u][i] && inSet(i,cSt))
					cnt ++, v = i;
			if (cnt >= 2) continue;
			//Condition 3
			fo(i,0,q-1)
			{
				if (c[i] == u && inSet(a[i],cSt) && inSet(b[i],cSt)) flag = 0;
				if (inSet(c[i],cSt) && (!inSet(a[i],cSt) || !inSet(b[i],cSt))) flag = 0;
				if (!flag) break;
			}
			if (!flag) continue;
			
			if (cnt != 1)
			{
				fo(v,0,n-1)
					if (inSet(v,cSt)) ret += DP(v,cSt) * DP(u,S-cSt);
			} else ret += DP(v,cSt) * DP(u,S-cSt);
				
		}
		return ret;
}

void Work()
{
	memset(f,-1,sizeof f);
	fo(i,0,n-1) f[i][1<<i] = 1;
	printf("%lld\n",DP(0,(1<<n)-1));
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	Initialize();
	Work();
	return 0;
}
