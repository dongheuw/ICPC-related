#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 2005;

int T,ind,cnt;
int tot,a[maxn],b[maxn],c[maxn];
map<string,int> A,B;
char s[maxn];
string v[10];

void Insert(int x,int y)
{
	tot ++;
	b[tot] = y;
	c[tot] = a[x];
	a[x] = tot;
}

void READ()
{
	while (scanf("%s",s) == 1)
	{
		int len = strlen(s);
		if (s[len-1] == '?' || s[len-1] == '.' || s[len-1] == '!')
		{
			char x = s[len-1];
			s[len-1] = 0;
			v[cnt++] = string(s);
			s[0] = x, s[1] = 0;
			v[cnt++] = string(s);
			break;
		} else v[cnt++] = string(s);
	}
}

int d[maxn];
bool vis[maxn];
bool Bfs(int x,int y)
{
	if (x == y) return 1;
	fo(i,1,ind) vis[i] = 0;
	d[1] = x; vis[x] = 1;
	int l = 0, r = 1;
	while (l < r)
	{
		int cur = d[++l];
		for (int i = a[cur];i;i = c[i])
			if (!vis[b[i]])
			{
				vis[d[++r] = b[i]] = 1;
				if (b[i] == y) return 1;
			}
	}
	return 0;
}

void Query(int x,int y)
{
	if (Bfs(x,y)) printf("Y"); else printf("M");
}

void Initialize()
{
	A.clear(), B.clear();
	memset(a,0,sizeof a);
	tot = ind = 0;
}

int Noun(const string &s)
{
	if (!A[s]) A[s] = ++ ind;
	return A[s];
}

int Verb(const string &s)
{
	if (!B[s]) B[s] = ++ ind;
	return B[s];
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d",&T);
	fo(cs,1,T)
	{
		Initialize();
		printf("Case #%d:\n",cs);
		while (1)
		{
			cnt = 0;
			READ();
			if (v[cnt-1] == "!")
			{
				printf("\n");
				break;
			} else if (v[cnt-1] == "?")
			{
				if (cnt == 4)
				{
					if (v[0] == "are") Query(Noun(v[1]),Noun(v[2]));
					else Query(Noun(v[1]),Verb(v[2]));
				} else
				{
					if (v[0] == "can") Query(Verb(v[4]),Verb(v[5]));
					else Query(Verb(v[4]),Noun(v[5]));
				}
			} else if (v[cnt-1] == ".")
			{
				if (cnt == 4)
				{
					if (v[1] == "are") Insert(Noun(v[0]),Noun(v[2]));
					else Insert(Noun(v[0]),Verb(v[2]));
				} else
				{
					if (v[4] == "can") Insert(Verb(v[3]),Verb(v[5]));
					else Insert(Verb(v[3]),Noun(v[5]));
				}
			}
		}
	}
	return 0;
}
