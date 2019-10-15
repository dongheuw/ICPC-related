#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define INF 0x3f3f3f3f

using namespace std;

int T,n,k,m,N = 26;
int A[75][75],B[75][75],C[75][75];
int lx[75],ly[75],px[75],py[75],slk[75],M;
bool qx[75],qy[75];
int K[10005];

bool dfs(int x)
{
	if (qx[x]) return 0;
	qx[x] = 1;
	fo(i,1,N)
		if (px[x] != i)
		{
			int d = lx[x] + ly[i] - C[x][i];
			if (!d)
			{
				qy[i] = 1;
				if (!py[i] || dfs(py[i]))
				{
					px[x] = i;
					py[i] = x;
					return 1;
				}
			} else slk[i] = min(slk[i],d);
		}
	return 0;
}

int KM()
{
	fo(i,1,N) lx[i] = -INF, ly[i] = 0, px[i] = py[i] = 0;
	fo(i,1,N) fo(j,1,N) lx[i] = max(lx[i],C[i][j]);
	fo(i,1,N)
	{
		while (1)
		{
			memset(qx,0,N+1);
			memset(qy,0,N+1);
			fo(j,1,N) slk[j] = INF;
			if (dfs(i)) break;
			int M = INF;
			fo(j,1,N) if (!qy[j] && slk[j] < M) M = slk[j];
			fo(j,1,N) if (qx[j]) lx[j] -= M;
			fo(j,1,N) if (qy[j]) ly[j] += M; 
		}
	}
	int ret = 0;
	fo(i,1,N) ret += C[i][px[i]];
	return ret;
}

int readch()
{
	char ch = getchar();
	while (!isupper(ch)) ch = getchar();
	return ch - 64;
}

int main()
{
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
	scanf("%d",&T);
	while (T --)
	{
		scanf("%d%d%d",&n,&k,&m);
		fo(i,1,n) K[i] = readch();
		fo(z,1,m)
		{
			fo(i,1,26) fo(j,1,26) C[i][j] = 0;
			fo(i,1,n) C[K[i]][readch()] ++;
			printf("%.4lf\n",double(KM())/n);
		}
	}
	return 0;
}
