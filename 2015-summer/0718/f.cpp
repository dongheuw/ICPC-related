#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 1205;

int n,N,L,w[maxn];
int c[maxn][4],fail[maxn],mask[maxn];
char s[maxn];
bool f[2][maxn][maxn];

int C(char ch)
{
	if (ch == 'A') return 0;
	if (ch == 'G') return 1;
	if (ch == 'C') return 2;
	return 3;
}

void Construct_Trie()
{
	memset(mask,0,sizeof mask);
	memset(c,0,sizeof c);
	N = 1; w[n] = 0;
	fo(i,0,n-1)
	{
		scanf("%s%d",s,&w[i]);
		int p = 1;
		for (int j = 0;s[j];j ++)
		{
			int ch = C(s[j]);
			if (!c[p][ch]) c[p][ch] = ++ N;
			p = c[p][ch];
		}
		mask[p] = 1 << i;
	}
}

int q[maxn];
void Construct_Fail()
{
	int l = 0, r = 0;
	fo(i,0,3)
		if (c[1][i])
		{
			fail[c[1][i]] = 1;
			q[r ++] = c[1][i];
		} else c[1][i] = 1;
	while (l < r)
	{
		int x = q[l ++];
		fo(i,0,3)
		{
			if (c[x][i])
			{
				fail[c[x][i]] = c[fail[x]][i];
				q[r ++] = c[x][i];
			} else c[x][i] = c[fail[x]][i];
			mask[c[x][i]] |= mask[fail[c[x][i]]];
		}
	}
}

inline int Calc(int x)
{
	int ret = 0;
	fo(i,0,n-1) if (x&(1<<i)) ret += w[i];
	return ret;
}

void DynamicProgram()
{
	memset(f,0,sizeof f);
	f[0][1][0] = 1;
	int i = 1;
	fo(x,0,L-1)
	{
		i ^= 1;
		fo(j,1,N)
			fo(k,0,(1<<n)-1)
			{
				if (!f[i][j][k]) continue;
				fo(t,0,3) f[i^1][c[j][t]][k|mask[c[j][t]]] = 1;
			}
		memset(f[i],0,sizeof f[i]);
	}
	int ans = -(int)1e9;
	fo(k,0,(1<<n)-1)
	{
		int temp = Calc(k);
		fo(j,1,N) if (f[i^1][j][k]) ans = max(ans,temp);
	}
	if (ans >= 0) printf("%d\n",ans); else printf("No Rabbit after 2012!\n");
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	while (scanf("%d%d",&n,&L) != EOF)
	{
		Construct_Trie();
		Construct_Fail();
		DynamicProgram();
	}
	return 0;
}
