#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int N = 15;
const int mod = 2007;
int n,k;

struct Matrix
{
    int a[N][N];
    int sz;
    Matrix(int x,int n)
    {
        sz = n;
        fo(i,0,N-1)
            fo(j,0,N-1) a[i][j] = (i == j) ? x : 0;
    }
    Matrix operator*(Matrix &b)
    {
        Matrix tmp(0,sz);
        fo(i,0,sz-1)
            fo(j,0,sz-1)
                fo(k,0,sz-1)
                {
                    tmp.a[i][j] += a[i][k] * b.a[k][j] % mod;
                    tmp.a[i][j] %= mod;
                }
        return tmp;
    }
};

int main()
{
    freopen("e.in","r",stdin);
    freopen("e.out","w",stdout);
    scanf("%d%d",&n,&k);
    Matrix M = Matrix(0,k+1);
    fo(i,1,k)
    {
        M.a[i-1][i] = 1;
        M.a[i][i] = i;
    }
    M.a[0][0] = 1;
    
    Matrix ret(1,M.sz);
    for (int k = n-1;k;)
    {
        if (k & 1) ret = ret * M;
        M = M * M;
        k >>= 1;
    }
    printf("%d\n",ret.a[1][k]);
    return 0;
}
