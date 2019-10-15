#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;
const int maxn = 32768;

struct Matrix
{
    int a,b,c,d;
}x[maxn*2+1];

int R,N,M;

Matrix Product(Matrix A,Matrix B)
{
    Matrix ret;
    ret.a = (A.a*B.a+A.b*B.c)%R;
    ret.b = (A.a*B.b+A.b*B.d)%R;
    ret.c = (A.c*B.a+A.d*B.c)%R;
    ret.d = (A.c*B.b+A.d*B.d)%R;
    return ret;
}

Matrix Query(int p,int left,int right,int l,int r)
{
    if (left == l && right == r) return x[p];
    int mid = (left+right) >> 1;
    if (r <= mid) return Query(p*2,left,mid,l,r);
    else if (l > mid) return Query(p*2+1,mid+1,right,l,r);
    return Product(Query(p*2,left,mid,l,mid),Query(p*2+1,mid+1,right,mid+1,r));
}
int main()
{
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    int cas = 0;
    while (scanf("%d%d%d",&R,&N,&M) != EOF)
    {
        int S = 1;
        while (S < N) S <<= 1;
        fo(i,0,N-1)
            scanf("%d%d%d%d",&x[S+i].a,&x[S+i].b,&x[S+i].c,&x[S+i].d);
        for(int i = S-1;i;i --) x[i] = Product(x[i*2],x[i*2+1]);
        while (M --)
        {
            if (cas) puts(""); cas ++;
            int a,b;
            scanf("%d%d",&a,&b);
            Matrix ret = Query(1,1,S,a,b);
            printf("%d %d\n%d %d\n",ret.a,ret.b,ret.c,ret.d);
        }
    }
    return 0;
}
