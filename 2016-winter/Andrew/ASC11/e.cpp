#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 50010;
const int maxm = 500;
const int dx[6] = {0,0,-1,-1,1,1};
const int dy[6] = {1,-1,1,0,1,0};
const int _dy[6] = {1,-1,0,-1,0,-1};
int n,s,numn,a[maxn],b[maxn],father[maxn],c[maxn],num[2*maxm+10][2*maxm+10];
bool land[2*maxm+10][2*maxm+10];

int get(int x)
{ 
    return x == father[x] ? x : father[x] = get(father[x]);
}

int main()
{
    while (scanf("%d%d",&n,&s) != EOF)
    {
        numn = 0;
        memset(land,0,sizeof land);
        scanf("%d%d",&a[0],&b[0]);
        land[a[0]+maxm][b[0]+maxm] = 1;
        num[a[0]+maxm][b[0]+maxm] = 0;
        father[0] = 0; c[0] = 1; numn = 1;
        for (int i = 1;i < n;i ++)
        {
            int ta,tb;
            scanf("%d%d",&ta,&tb);
            if (land[ta+maxm][tb+maxm]) continue;
            int sum,numr,r[10];            
            sum = 0; numr = 0;
            for (int k = 0;k < 6;k ++)
            {
                int x = ta + dx[k];
                int y = (ta&1)?tb+dy[k]:tb+_dy[k];
                if (!land[x+maxm][y+maxm]) continue;
                int m = num[x+maxm][y+maxm], tmfather = get(m);
                int j;
                for (j = 0;j < numr;j ++) if (r[j] == tmfather) break;
                if (j == numr) r[numr++] = tmfather;
            }
            for (int k = 0;k < numr;k ++) sum += c[r[k]];
            if (sum < s)
            {
                a[numn] = ta; b[numn] = tb;
                land[ta+maxm][tb+maxm] = 1;
                num[ta+maxm][tb+maxm] = numn;
                father[numn] = numn;
                c[numn] = sum + 1;
                for (int k = 0;k < numr;k ++) father[r[k]] = numn;
                numn ++;
            }
        }
        int cnt = 0,ans[maxn];
        for (int k = 0;k < numn;k ++) if (father[k] == k) ans[cnt++] = c[k];
        sort(ans,ans+cnt);
        printf("%d\n",cnt);
        for (int k = 0;k < cnt;k ++)
            printf("%d%c",ans[k],k+1==cnt?'\n':' ');
    }
    return 0;
}
