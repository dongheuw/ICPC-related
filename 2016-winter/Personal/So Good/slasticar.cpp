#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)
#define fd(i,a,b) for (int i = a;i >= b;i --)

using namespace std;
typedef long long LL;
typedef pair<int,int> PI;

const int maxn = 200005;
const int MAXN = 3000005;
int n,N,Q;
char T[maxn],s[maxn],S[MAXN];
int sa[maxn],rank[maxn],rk[maxn],tmp[maxn],tank[maxn];
int len[maxn],st[maxn];
LL ans[maxn];
PI start[maxn];

void BuildSA(char *s)
{
	fo(i,1,N) tank[(int)s[i]] ++;
	fo(i,1,255) tank[i] += tank[i-1];
	fd(i,N,1) sa[tank[(int)s[i]]--] = i;
	int j = 0;
	fo(i,1,N)
	{
		if (i == 1 || s[sa[i]] != s[sa[i-1]]) j ++;
		rank[sa[i]] = j;
	}
	for (int k = 1;k <= N;k <<= 1)
	{
		int j = 0;
		fo(i,N+1,N+k) tmp[++j] = i-k;
		fo(i,1,N) if (sa[i] > k) tmp[++j] = sa[i]-k;
		memset(tank,0,(N+1)*4);
		fo(i,1,N) tank[rank[tmp[i]]] ++;
		fo(i,1,N) tank[i] += tank[i-1];
		fd(i,N,1) sa[tank[rank[tmp[i]]]--] = tmp[i];
		copy(rank+1,rank+1+N,rk+1);
		j = 0;
		fo(i,1,N)
		{
			if ((i == 1) || ((rk[sa[i]] != rk[sa[i-1]]) || (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+k] != rk[sa[i-1]+k]))) j ++;
			rank[sa[i]] = j;
		}
	}
}

inline int Findl(int l,int r,int i,char c)
{
	int ret = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (T[sa[mid]+i-1] >= c) ret = mid, r = mid-1;
		else l = mid+1;
	}
	if (T[sa[ret]+i-1] != c || !ret) ret = r+1;
	return ret;
}

inline int Findr(int l,int r,int i,char c)
{
	int ret = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (T[sa[mid]+i-1] > c) ret = mid, r = mid-1;
		else l = mid+1;
	}
	if (!ret) ret = r+1;
	return ret;
}

int SearchStart(char *s,int x)
{
	int l = 1, r = N;
	fo(i,1,len[x])
	{
		l = Findl(l,r,i,s[i]);
		r = Findr(l,r-1,i,s[i]);
		if (l >= r) break;
	}
	int ret = 0;
	fo(i,l,r-1)
		if (!ret || sa[i] < sa[ret]) ret = i;
	if (!ret) return N;
	return sa[ret];
}

void Initialize()
{
	scanf("%d",&N);
	scanf("%s",T+1);
	n = N;
	fo(i,1,n) T[++N] = 90;
	BuildSA(T);
	scanf("%d",&Q);
	int last = 0;
	fo(i,1,Q)
	{
		scanf("%s",s+1);
		len[i] = strlen(s+1);
		fo(j,last+1,last+len[i]) S[j] = s[j-last];
		st[i] = last + 1;
		last += len[i];
		start[i] = PI(SearchStart(s,i),i);
	}
}

int c[maxn];
void Insert(int x)
{
	for (;x <= N;x += x&(-x)) c[x] ++;
}

int Query(int x)
{
	int ret = 0;
	for (;x;x -= x&(-x)) ret += c[x];
	return ret;
}

LL Solve(char *s,int x)
{
	int l = 1, r = N;
	LL ret = 0;
	fo(i,1,len[x]-1)
	{
		l = Findl(l,r,i,s[i]);
		r = Findr(l,r-1,i,s[i]);
		if (r-1 > l-1) ret += Query(r-1) - Query(l-1);
	}
	return ret;
}

void Work()
{
	sort(start+1,start+1+Q);
	fo(i,1,Q)
	{
		fo(j,start[i-1].first+1,start[i].first) 
			if (rank[j] <= n) Insert(rank[j]);
		int x = start[i].second;
		fo(j,st[x],st[x]+len[x]-1) s[j-st[x]+1] = S[j];
		ans[x] = Solve(s,x) + min(n,start[i].first);
	}
	fo(i,1,Q) printf("%lld\n",ans[i]);
}

int main()
{
	Initialize();
	Work();
	return 0;
}
