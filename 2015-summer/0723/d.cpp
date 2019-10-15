#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 200500;
const int blk_size = 450;

int N,M,A[maxn];
struct blk
{
    int cnt,sum;
}blk[blk_size][blk_size];

struct space
{
    int X[maxn],Y[maxn];
    void Reset()
    {
        memset(X,-1,sizeof X);
        memset(Y,-1,sizeof Y);
    }
    void insert(const int x, const int y) {X[y] = x, Y[x] = y;}
    void remove(const int x, const int y) {X[y] = -1, Y[x] = -1;}
    int getx(const int y) {return X[y];}
    int gety(const int x) {return Y[x];}
}a;

int Count(int x,int y) 
{
    int bw = (x+1)/blk_size, bh = (y+1)/blk_size;
    int ret = 0;
    fo(i,0,bh-1) if (bw > 0) ret += blk[bw-1][i].sum;
    fo(i,bw*blk_size,x) if (a.gety(i) != -1 && a.gety(i) < bh*blk_size) ret ++;
    fo(i,bh*blk_size,y) if (a.getx(i) != -1 && a.getx(i) <= x) ret ++;
    return ret;
}

int cnt_inv(int x,int y) 
{
    int inter = Count(x,y);
    return Count(x,N-1) - inter + Count(N-1,y) - inter;
}

void Update(int bx,int by) 
{
    int sum = (bx > 0 ? blk[bx-1][by].sum : 0);
    for (int i = bx;i < blk_size;i ++)
    {
        sum += blk[i][by].cnt;
        blk[i][by].sum = sum;
    }
}

void Add(int x,int y) 
{
    a.insert(x,y);
    int bx = x / blk_size;
    int by = y / blk_size;
    blk[bx][by].cnt ++, Update(bx,by);
}

void Remove(int x,int y) 
{
    a.remove(x,y);
    int bx = x / blk_size;
    int by = y / blk_size;
    blk[bx][by].cnt --, Update(bx,by);
}

int main()
{
    freopen("d.in","r",stdin);
    freopen("d.out","w",stdout);
    while (scanf("%d%d",&N,&M) != EOF)
    {
        a.Reset();
        memset(blk,0,sizeof blk);
        fo(i,0,N-1) scanf("%d",&A[i]), A[i] --;
        long long inv = 0;
        fo(i,0,N-1) Add(i,A[i]), inv += cnt_inv(i,A[i]);
        fo(i,0,M-1)
        {
            int x;
            scanf("%d",&x), x --;
            printf("%lld\n",inv);
            inv -= cnt_inv(a.getx(x),x);
            Remove(a.getx(x),x);
        }
    }
    return 0;
}
