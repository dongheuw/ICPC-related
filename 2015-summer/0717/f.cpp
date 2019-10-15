#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;

int T,ans,ind;
char s[55];

struct NUM
{
	int len,a[60];
}c[maxn];

struct Node
{
	int next[10],id;
}trie[maxn*50];

void Insert(int x)
{
	int p = 0;
	for (int i = c[x].len-1;i >= 0;i --)
	{
		int tmp = c[x].a[i];
		if (!trie[p].next[tmp]) trie[p].next[tmp] = ind ++;
		p = trie[p].next[tmp];
		trie[p].id = x;
	}
}

void Add(NUM &ret,NUM &a,NUM &b)
{
	int t = 0;
	ret.len = a.len;
	fo(i,0,ret.len-1)
	{
		ret.a[i] = a.a[i] + b.a[i] + t;
		t = ret.a[i] / 10;
		ret.a[i] %= 10;
	}
	if (t > 0) ret.a[ret.len ++] = t;
	if (ret.len > 50)
	{
		fo(i,0,ret.len-1)
		{
			ret.a[i] = ret.a[i+1];
			a.a[i] = a.a[i+1];
		}
		ret.len --;
		a.len --;
	}
}

void Find()
{
	int len = strlen(s), p = 0;
	fo(i,0,len-1)
	{
		int tmp = s[i] - 48;
		if (trie[p].next[tmp] == 0)
		{
			ans = -1;
			break;
		} else
		{
			p = trie[p].next[tmp];
			ans = trie[p].id;
		}
	}
}

int main()
{
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	c[0].a[0] = c[1].a[0] = c[0].len = c[1].len = ind = 1;
	fo(i,2,99999)
	{
		Add(c[i],c[i-1],c[i-2]);
		//printf("%d ",i);
		//for (int j = c[i].len-1;j >= 0;j --) printf("%d",c[i].a[j]);
		//printf("\n");
	}
	for (int i = 99999;i >= 0;i --) Insert(i);
	scanf("%d",&T);
	fo(cs,1,T)
	{
		scanf("%s",s);
		Find();
		printf("Case #%d: %d\n",cs,ans);
	}
	return 0;
}
