#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;
int n,m,k,c[maxn*13],t[maxn][2],q[maxn];
int id[maxn*4];

void Up(int x)
{
    if (c[x*2] == c[x*2+1]) c[x] = c[x*2];
    else c[x] = -1;
}

void Down(int x)
{
    if (c[x] != -1) c[x*2] = c[x*2+1] = c[x];
}

int Query(int l,int r,int x,int p)
{
    if (l == r) return c[x];
    Down(x);
    int mid = (l + r) >> 1, ret;
    if (p <= mid) ret = Query(l,mid,x*2,p);
    else ret = Query(mid+1,r,x*2+1,p);
    Up(x);
    return ret;
}

void Modify(int l,int r,int x,int L,int R,int val)
{
    if (L <= l && r <= R)
    {
        c[x] = val;
        return;
    }
    Down(x);
    int mid = (l+r) >> 1;
    if (L <= mid) Modify(l,mid,x*2,L,R,val);
    if (R > mid) Modify(mid+1,r,x*2+1,L,R,val);
    Up(x);
}

void Initialize()
{
    fo(i,1,n)
    {
        scanf("%d%d",&t[i][0],&t[i][1]);
        id[k++] = t[i][0];
        id[k++] = t[i][1];
    }
    scanf("%d",&m);
    fo(i,0,m-1)
    {
        scanf("%d",&q[i]);
        id[k++] = q[i];
    }
    sort(id,id+k);
    k = unique(id,id+k) - id;
    memset(c,-1,sizeof c);
    fo(i,1,n)
    {
        int L = lower_bound(id,id+k,t[i][0]) - id + 1;
        int R = lower_bound(id,id+k,t[i][1]) - id + 1;
        Modify(1,k,1,L,R,i);
    }
}

int main()
{
    while (~scanf("%d",&n))
    {
        Initialize();
        fo(i,0,m-1) printf("%d\n",Query(1,k,1,lower_bound(id,id+k,q[i])-id+1));
    }
    return 0;
}
