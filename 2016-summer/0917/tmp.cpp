#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<bitset>
#include<math.h>
#include<vector>
#include<string>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
const int N=52;
const int mod=1000000007;
const int MOD1=1000000007;
const int MOD2=1000000009;
const double EPS=0.00000001;
typedef long long ll;
const ll MOD=1000000007;
const int INF=1000000010;
const ll MAX=1ll<<55;
const double eps=1e-5;
const double inf=~0u>>1;
const double pi=acos(-1.0);
typedef double db;
typedef unsigned int uint;
typedef unsigned long long ull;
bitset<90>A[11];
int n,a[N],b[4],q[N][N][N];
int check(int i,int j,int k) {
    for (int h=0;h<=10;h++) A[h].reset();A[0][0]=1;
    for (int h=1;h<=n;h++)
    if (h!=i&&h!=j&&h!=k&&a[h]<=87) {
        for (int ii=9;ii>=0;ii--) A[ii+1]|=A[ii]<<a[h];
        if (A[10][87]) return 1;
    }
    return 0;
}
int main()
{
    int i,j,k,T,Q;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (i=1;i<=n;i++) scanf("%d", &a[i]);
        for (i=1;i<=n;i++)
            for (j=i;j<=n;j++)
                for (k=j;k<=n;k++) q[i][j][k]=check(i,j,k);
        scanf("%d", &Q);
        while (Q--) {
            scanf("%d%d%d", &b[1], &b[2], &b[3]);
            sort(b+1,b+4);
            if (q[b[1]][b[2]][b[3]]) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
