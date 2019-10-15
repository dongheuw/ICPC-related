#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

const int N = 100005;
const int M = 5000005;

using namespace std;

int n,m,sz;
int A[30],B[30],num[N],pos[N],a1[N],a2[N],t[N],root[N];
int ls[M],rs[M],sum[M];
long long ans;

inline long long read()
{
    long long x = 0,f = 1;
    char ch=getchar();
    while (ch > '9' || ch < '0') {if (ch == '-')f = -1; ch=getchar();}
    while (ch >= '0'&& ch <= '9'){x = x*10+ch-'0';ch = getchar();}
    return x * f;
}

inline int lowbit(int x){return x&(-x);}

void Reset()
{
    memset(t,0,sizeof t);
    memset(num,0,sizeof num);
    memset(pos,0,sizeof pos);
    memset(a1,0,sizeof a1);
    memset(a2,0,sizeof a2);
    memset(root,0,sizeof root);
    memset(ls,0,sizeof ls);
    memset(rs,0,sizeof rs);
    memset(sum,0,sizeof sum);
}

inline int Get(int x)
{
    int ret = 0;
    for (int i = x;i;i -= lowbit(i)) ret += t[i];
    return ret;
}

void Update(int &y,int l,int r,int x)
{
    if (!y) y = ++sz;
    sum[y] ++;
    if (l == r)return;
    int mid = (l + r) >> 1;
    if (x <= mid) Update(ls[y],l,mid,x);
    else Update(rs[y],mid+1,r,x);
}

int Query_less(int x,int y,int num)
{
    A[0] = B[0] = 0;
    int ret = 0; x --;
    for (int i = x;i;i -= lowbit(i)) A[++A[0]] = root[i];
    for (int i = y;i;i -= lowbit(i)) B[++B[0]] = root[i];
    int l = 1,r = n;
    while (l != r)
    {
        int mid = (l+r) >> 1;
        if(num > mid)
        {
            fo(i,1,A[0]) ret -= sum[ls[A[i]]];
            fo(i,1,B[0]) ret += sum[ls[B[i]]];
            fo(i,1,A[0]) A[i] = rs[A[i]];
            fo(i,1,B[0]) B[i] = rs[B[i]];
            l = mid+1;
        }
        else
        {
            fo(i,1,A[0]) A[i] = ls[A[i]];
            fo(i,1,B[0]) B[i] = ls[B[i]];
            r = mid;
        }
    }
    return ret;
}

int Query_more(int x,int y,int num)
{
	A[0] = B[0] = 0;
    int ret = 0; x --;
	for (int i = x;i;i -= lowbit(i)) A[++A[0]] = root[i];
	for (int i = y;i;i -= lowbit(i)) B[++B[0]] = root[i];
	int l = 1, r = n;
	while (l != r)
	{
		int mid = (l + r) >> 1;
        if (num <=mid)
        {
            fo(i,1,A[0]) ret -= sum[rs[A[i]]];
            fo(i,1,B[0]) ret += sum[rs[B[i]]];
            fo(i,1,A[0]) A[i] = ls[A[i]];
            fo(i,1,B[0]) B[i] = ls[B[i]];
            r = mid;
        }
		else
        {
            fo(i,1,A[0]) A[i] = rs[A[i]];
            fo(i,1,B[0]) B[i]= rs[B[i]];
            l = mid + 1;
        }
	}
	return ret;
}

int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    while (scanf("%d%d",&n,&m) != EOF)
    {
        Reset();
        fo(i,1,n)
        {
            num[i] = read(); pos[num[i]] = i;
            a1[i] = Get(n) - Get(num[i]);
            ans += a1[i];
            for (int j = num[i];j <= n;j += lowbit(j)) t[j] ++;
        }
        memset(t,0,sizeof t);
        for (int i = n;i >= 1;i --)
        {
            a2[i] = Get(num[i]-1);
            for (int j = num[i];j <= n;j += lowbit(j)) t[j] ++;
        }
        fo(i,1,m)
        {
            printf("%lld\n",ans);
            int x = read(); x = pos[x];
            ans -= (a1[x]+a2[x]-Query_more(1,x-1,num[x])-Query_less(x+1,n,num[x]));
            for (int j = x;j <= n;j += lowbit(j)) Update(root[j],1,n,num[x]);
        }
    }
	return 0;
}
