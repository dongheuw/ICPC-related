#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = (int)1e5 + 10;
const int inf = (int)1e9 + 5;

int n,ans,d[maxn];
struct node
{
    int l,r,ma,mi;
}tree[maxn*4];

int Query_min(int x,int st,int ed)
{
    int l = tree[x].l, r = tree[x].r;
    if (st <= l && r <= ed) return tree[x].mi;
    int mid = (l+r) >> 1, ret = inf;
    if (st <= mid) ret = min(ret,Query_min(x*2,st,ed));
    if (ed > mid) ret = min(ret,Query_min(x*2+1,st,ed));
    return ret;
}

int Query_max(int x,int st,int ed)
{
    int l = tree[x].l, r = tree[x].r;
    if (st <= l && r <= ed) return tree[x].ma;
    int mid = (l+r) >> 1, ret = -inf;
    if (st <= mid) ret = max(ret,Query_max(x*2,st,ed));
    if (ed > mid) ret = max(ret,Query_max(x*2+1,st,ed));
    return ret;
}

void Maketree(int x,int l,int r)
{
    tree[x].l = l, tree[x].r=r;
    tree[x].ma = -inf, tree[x].mi = inf;
    if (l == r) tree[x].ma = tree[x].mi = d[l];
    else
    {
        int mid = (l+r) >> 1;
        Maketree(x*2,l,mid);
        Maketree(x*2+1,mid+1,r);
        tree[x].ma = max(tree[x*2].ma,tree[x*2+1].ma);
        tree[x].mi = min(tree[x*2].mi,tree[x*2+1].mi);
    }
}

int main()
{
    scanf("%d",&n);
    fo(i,1,n) scanf("%d",&d[i]);
    Maketree(1,1,n);
    int last = 1;
    ans = 1;
    fo(i,1,n-1)
        if (Query_max(1,last,i) <= Query_min(1,i+1,n)) ans ++, last = i+1;
    printf("%d\n",ans);
}
