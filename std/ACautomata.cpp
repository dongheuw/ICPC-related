<span style="font-size:14px;">#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1505;
const int P = (int)1e9 + 7;
int N[maxn],M,S[maxn],tot;

void read(int *x)
{
	x[0] = 0;
	static char ch;
	do ch = getchar(); while (ch < '0' || ch > '9');
	do x[++x[0]] = ch - 48, ch = getchar(); while (ch >= '0' && ch <= '9');
}

struct Node
{
	int son[10],fail;
	bool flag;
}t[maxn];

void Insert(int *s)
{
	int x = 0;
	fo(i,1,s[0])
	{
		if (!t[x].son[s[i]]) t[x].son[s[i]] = ++ tot;
		x = t[x].son[s[i]];
	}
	t[x].flag = 1;
}

void Construct_fail()
{
	static int d[maxn];
	int l = 0,r = 1;
	while (l < r)
	{
		int x = d[++l];
		fo(i,0,9)
			if (t[x].son[i])
			{
				int v = t[x].son[i];
				if (x == 0) t[v].fail = 0;
				else t[v].fail = t[t[x].fail].son[i];
				t[v].flag |= t[t[v].fail].flag;
				d[++r] = v;
			} else t[x].son[i] = t[t[x].fail].son[i];
	}
}

void Initialize()
{
	read(N);
	scanf("%d",&M);
	fo(i,1,M)
	{
		read(S);
		Insert(S);
	}
	Construct_fail();
}

int f[maxn][maxn][2];
int DP()
{
	fo(i,1,N[1]-1) 
		if (!t[t[0].son[i]].flag) f[1][t[0].son[i]][0] ++;
	if (!t[t[0].son[N[1]]].flag) f[1][t[0].son[N[1]]][1] ++;
	fo(i,1,N[0])
	{
		if (i > 1)
			fo(j,1,9) 
				if (!t[t[0].son[j]].flag) f[i][t[0].son[j]][0] ++;
		fo(j,0,tot)
		{
			if (f[i][j][0])
				fo(k,0,9)
				{
					int _j = t[j].son[k];
					if (!t[_j].flag) f[i+1][_j][0] = (f[i+1][_j][0] + f[i][j][0]) % P;
				}
			if (f[i][j][1])
			{
				fo(k,0,N[i+1]-1)
				{
					int _j = t[j].son[k];
					if (!t[_j].flag) f[i+1][_j][0] = (f[i+1][_j][0] + f[i][j][1]) % P;
				}
				int _j = t[j].son[N[i+1]];
				if (!t[_j].flag) f[i+1][_j][1] = (f[i+1][_j][1] + f[i][j][1]) % P;
			}
		}
	}
	int ret = 0;
	fo(i,0,tot) ret = ((ret + f[N[0]][i][0]) % P + f[N[0]][i][1]) % P;
	return ret;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	Initialize();
	printf("%d\n",DP());
	return 0;
}</span>
