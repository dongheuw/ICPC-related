#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

typedef long long LL;

const int maxn = 605;
const int maxm = 300005;
const int mod = 1000000000;

struct NUM
{
	LL a[maxn];
	int len;
}c[10];

int n;
bool u[10],cal[maxm];
char rep[maxm][10];
LL tmp[maxn];

void Add(int x,int y)
{
	LL t = 0;
	int l = max(c[x].len,c[y].len) + 5;
	fo(i,0,l)
	{
		c[x].a[i] += c[y].a[i] + t;
		if (c[x].a[i] >= mod)
		{
			c[x].a[i] -= mod;
			t = 1;
		} else t = 0;
	}
	c[x].len = 600;
	while (c[x].a[c[x].len] == 0 && c[x].len > 0) c[x].len --;
}

void Mul(int x,int y)
{
	LL t;
	memset(tmp,0,sizeof tmp);
	fo(i,0,c[x].len)
	{
		t = 0;
		fo(j,0,c[y].len||t)
		{
			tmp[i+j] += c[x].a[i] * c[y].a[j] + t;
			t = tmp[i+j] / mod;
			tmp[i+j] %= mod;
		}
	}
	memcpy(c[x].a,tmp,sizeof (tmp));
	c[x].len = 600;
	while (c[x].a[c[x].len] == 0 && c[x].len > 0) c[x].len --;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	fo(i,0,9) c[i].a[0] = 1, c[i].len = 0;
	while (scanf("%s",rep[n]) != EOF) n ++;
	fo(i,0,9) u[i] = 1;
	for (int i = n-1;i >= 0;i --)
	{
		cal[i] = u[rep[i][0] - 'A'];
		if (rep[i][1] == '=')
		{
			cal[i] = 1;
			u[rep[i][0]-'A'] = 0;
			u[rep[i][2]-'A'] = 1;
		} else u[rep[i][3]-'A'] = 1;
	}
	fo(i,0,n-1)
	{
		if (!cal[i]) continue;
		if (rep[i][1] == '+') Add(rep[i][0]-'A',rep[i][3]-'A');
		if (rep[i][1] == '*') Mul(rep[i][0]-'A',rep[i][3]-'A');
		if (rep[i][1] == '=') memcpy(c[rep[i][0]-'A'].a,c[rep[i][2]-'A'].a,sizeof(c[rep[i][2]-'A'].a));
	}
	fo(i,0,9)
	{
		for (int j = c[i].len;j >= 0;j --) printf(j == c[i].len?"%lld":"%09lld",c[i].a[j]);
		printf("\n");
	}
	return 0;
}
