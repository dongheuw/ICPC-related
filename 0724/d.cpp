#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int N = 200005;

int T,n,m,k,num,v[N],b[N];

struct Node
{
    int L,R,mid,v,add;
}tr[4*N];

void Update(int t)
{
    if (tr[t].L == tr[t].R) return ;
    tr[t].v = max(tr[t<<1].v,tr[t<<1|1].v);
}

void Pushdown(int t)
{
    if (tr[t].L == tr[t].R)return ;
    tr[t<<1].v += tr[t].add;
    tr[t<<1].add += tr[t].add;
    tr[t<<1|1].v += tr[t].add;
    tr[t<<1|1].add += tr[t].add;
    tr[t].add = 0;
}

int Query(int t,int L,int R)
{
    if (tr[t].L == L && tr[t].R == R) return tr[t].v;
    if (tr[t].add != 0) Pushdown(t);
    if (R <= tr[t].mid) return Query(t<<1,L,R);
    else if(L > tr[t].mid) return Query(t<<1|1,L,R);
    else return max(Query(t<<1,L,tr[t].mid),Query(t<<1|1,tr[t].mid+1,R));
}

void Modify(int t,int L,int R,int v)
{
    if (tr[t].L == L && tr[t].R == R)
    {
        tr[t].v += v;
        tr[t].add += v;
        return;
    }
    if (tr[t].add) Pushdown(t);
    if (R <= tr[t].mid) Modify(t<<1,L,R,v);
    else if(L > tr[t].mid) Modify(t<<1|1,L,R,v);
    else
    {
       Modify(t<<1,L,tr[t].mid,v);
       Modify(t<<1|1,tr[t].mid+1,R,v);
    }
    Update(t);
}

int Maketree(int t,int L,int R)
{
    tr[t].L = L;
    tr[t].R = R;
    tr[t].mid = (L+R) >> 1;
    tr[t].add = 0;
    if (L == R)
    {
         tr[t].v = b[L];
         return b[L];
    }
    tr[t].v = max(Maketree(t<<1,L,tr[t].mid),Maketree(t<<1|1,tr[t].mid+1,R));
    return tr[t].v;
}

int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    for (scanf("%d",&T);T;T --)
    {
        scanf("%d%d%d",&n,&m,&k);
        num = n-k+1;
        fo(i,1,n) scanf("%d",&v[i]);
        memset(b,0,sizeof b);
        fo(i,1,k) b[1] += v[i];
        fo(i,2,n-k+1) b[i] = b[i-1]-v[i-1]+v[i+k-1];
        Maketree(1,1,num);
        while(m --)
        {
            int op,a,b;
            scanf("%d%d%d",&op,&a,&b);
            if(op == 0)
            {
                Modify(1,max(1,a-k+1),min(a,num),b-v[a]);
                v[a] = b;
            }
            else if (op == 1)
            {
                if(a == b)continue;
                Modify(1,max(1,a-k+1),min(a,num),v[b]-v[a]);
                Modify(1,max(1,b-k+1),min(b,num),v[a]-v[b]);
                swap(v[a],v[b]);
            }
            else printf("%d\n",Query(1,a,b-k+1));
        }
    }
    return 0;
}
